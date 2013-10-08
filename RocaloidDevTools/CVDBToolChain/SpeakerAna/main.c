#include <stdio.h>
#include "SList.h"
#include "TData.h"
#include "RUtil/RUtil.h"
#include "../CSPR.h"

#include "CVEANN/Network/SOFM.h"
#include "CVEANN/Trainer/Trainer_SOFM.h"
#include "CVEANN/Trainer/Trainer_FeedForward.h"
#include "CVEANN/Network/FeedForwardMomentum.h"
#include "CVEDSP/IntrinUtil/Calculation.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include "CVEDSP/DSPBase/Filter.h"

float Distance(float X1, float Y1, float X2, float Y2)
{
    return Boost_Sqr((X1 - X2) * (X1 - X2) + (Y1 - Y2) * (Y1 - Y2));
}

float ClassifyFreq(TData* Src)
{
    int LayerSize [] = {105, 100};
    FeedForward FFNet;
    FeedForward_Ctor(& FFNet);
    FeedForward_SetLayer(& FFNet, LayerSize, 2);
    FeedForward_RandomInit(& FFNet, 0);
    SOFMDescriptor FClsfr = SOFM_FromFeedForward(& FFNet, 10, 10);
    printf("SOFM Neuron Network constructed.\n");
    printf("Training...\n");

    int i, j;
    float r = 10;
    for(i = 0; i < 1000; i ++)
    {
        float Eit = 0.5 - (float)i / 2000;
        for(j = 0; j <= Src -> WaveList_Index; j ++)
            Trainer_SOFM(FClsfr, Src -> SpecList[j].Data, Eit, r);
        if(i % 100 == 0)
            printf("%d%%\n", i / 10);
    }

    printf("SOFM Training Finished.\n");

    ArrayType_Ctor(float, XList);
    ArrayType_Ctor(float, YList);

    for(i = 0; i <= Src -> WaveList_Index; i ++)
    {
        int Index;
        FeedForward_SetInput(& FFNet, Src -> SpecList[i].Data);
        Index = SOFM_GetWinnerIndex(FClsfr);
        ArrayType_Push(float, XList, SOFM_X(FClsfr, Index));
        ArrayType_Push(float, YList, SOFM_Y(FClsfr, Index));
        if(i > 0)
        {
            float Dist = Distance(XList[XList_Index], YList[YList_Index], XList[XList_Index - 1], YList[YList_Index - 1]);
            if(Dist >= 4)
                break;
        }
    }
    float MidF = (Src -> SpecList[i].BaseFreq + Src -> SpecList[i - 1].BaseFreq) * 0.5;
    printf("Mid Freq = %fHz. Index = %d.\n", MidF, i);

    ArrayType_Dtor(float, XList);
    ArrayType_Dtor(float, YList);

    FeedForward_Dtor(& FFNet);
    return MidF;
}

void TrainProcess(FeedForward* Dest, TData* TDataList, int TDataList_Index, float MidFreq, int TrainHigh)
{
    int i, j, k, l;
    float* Rsut = (float*)malloc(sizeof(float) * (TDataList_Index + 1));
    FeedForwardMomentum fm;
    FeedForwardMomentum_Ctor(& fm);
    FeedForwardMomentum_Construct(& fm, Dest);
    FeedForwardMomentum_Clear(& fm);
    Trainer_SetBPMomentum(& fm);
    Trainer_SetBPMomentumFactor(0.5);
    for(i = 1; i < 10; i ++)
    {
        //Trial Cycle
        float InitVal = (i % 2 - 0.5) * i * 0.1 + 0.5;
        FeedForward_RandomInit(Dest, InitVal);
        printf("Trial %d, InitVal = %f.\n", i, InitVal);
        for(j = 0; j < 100000; j ++)
        {
            //Train Cycle
            float Eit = 0.3;//1.0f - (float)j / 10000;
            float E = 0;
            for(k = 0; k <= TDataList_Index; k ++)
            {
                //Phone Cycle
                Boost_FloatSet(Rsut, 0, TDataList_Index + 1);
                Rsut[k] = 1;
                for(l = 0; l <= TDataList[k].SpecList_Index; l ++)
                {
                    //Pitch/File Cycle
                    if(((! TrainHigh) && TDataList[k].SpecList[l].BaseFreq < MidFreq) ||
                       ((  TrainHigh) && TDataList[k].SpecList[l].BaseFreq > MidFreq))
                    {
                        float TE = Trainer_FeedForward_BP(Dest, TDataList[k].SpecList[l].Data, Rsut, Eit);
                        if(TE > E)
                            E = TE;
                    }
                }
            }
            if(E < 0.02)
            {
                printf("Training Succeeded at cycle %d.\n", j);
                goto _JMP_TrainingLFFinished;
            }
        }
        printf("Training at InitVal = %f failed.\n", InitVal);
    }
    _JMP_TrainingLFFinished:
    free(Rsut);
    FeedForwardMomentum_Dtor(& fm);
}

int main(void)
{
    String_FromChars(Path, "/tmp/task.slist");
    SList Task;
    SList_Ctor(& Task);
    SList_Load(& Task, & Path);

    SetSampleRate(44100);

    TData FreqTrainData;
    TData_Ctor(& FreqTrainData);
    TData_LoadFromString(& FreqTrainData, Task.PitchList, Task.PitchList_Index + 1);

    printf("Freq Classification started.\n");
    float MidFreq = ClassifyFreq(& FreqTrainData);

    TData_Dtor(& FreqTrainData);

    int LayerSize [] = {105, 130, Task.PhoneList_Index + 1};

    CSPR Output;
    CSPR_Ctor(& Output);

    FeedForward_SetLayer(& Output.FFNetLow, LayerSize, 3);
    FeedForward_SetLayer(& Output.FFNetHigh, LayerSize, 3);

    printf("FF Neuron Network constructed: {105, 130, %d}.\n", Task.PhoneList_Index + 1);

    ArrayType_Ctor(TData, TDataList);

    int i;
    for(i = 0; i <= Task.PhoneList_Index; i ++)
    {
        ArrayType_PushNull(TData, TDataList);
        TData_Ctor(TDataList + i);
        TData_LoadFromString(TDataList + i, Task.PhoneList[i].FileList, Task.PhoneList[i].FileList_Index + 1);
    }
    printf("Training data loaded.\n");

    printf("Training Low Freq Network...\n");
    TrainProcess(& Output.FFNetLow, TDataList, TDataList_Index, MidFreq, 0);
    printf("Training High Freq Network...\n");
    TrainProcess(& Output.FFNetHigh, TDataList, TDataList_Index, MidFreq, 1);

    Output.DividingFreq = MidFreq;
    Output.ClassNum = TDataList_Index + 1;
    ArrayType_Resize(FormantDescriptor, Output.FormantClasses, Output.ClassNum);
    Output.FormantClasses_Index = Output.ClassNum - 1;
    for(i = 0; i < Output.ClassNum; i ++)
    {
        Output.FormantClasses[i].F1 = Task.PhoneList[i].F1;
        Output.FormantClasses[i].F2 = Task.PhoneList[i].F2;
        Output.FormantClasses[i].F3 = Task.PhoneList[i].F3;
    }

    String_FromChars(OutputPath, "/tmp/x.cspr");
    CSPR_Save(& Output, & OutputPath);
    CSPR_Dtor(& Output);

    String_Dtor(& OutputPath);
    ArrayType_Dtor(TData, TDataList);

    SList_Dtor(& Task);
    String_Dtor(& Path);
    printf("Analysis Finished.\n");
    return 0;
}

