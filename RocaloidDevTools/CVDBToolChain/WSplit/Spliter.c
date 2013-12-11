#include "Spliter.h"
#include "../../../CVEDSP/IntrinUtil/FloatArray.h"
#include "../../../CVEDSP/Algorithm/BaseFreq.h"
#include "../../../CVEDSP/DSPBase/Spectrum.h"
#include "../../../CVEDSP/DSPBase/Filter.h"
#include "../../../RUtil/IO/FileUtil.h"
#include "../../../RUtil/Misc/Converter.h"
#include <malloc.h>

float Spec[256];

float BaseFreqDetect(float* Wave, int Length, float LowFreq)
{
    //Obtain the approximated freq
    ArrayType_Ctor(float, FF);
    int i;
    for(i = Length / 3 > 5000 ? 5000 : Length / 3; i < Length - 1536; i += 1536)
    {
        MagnitudeFromWave(Spec, Wave + i, 8);
        int State = Boost_FloatSum(Spec + 3, 50) > 1.5;
        if(State)
        {
            //Onset
            float TmpFreq = GetBaseFrequencyFromWave(Wave + i, LowFreq, 1500, 12);
            int Index;
            ArrayType_IncreaseSortFind(Index, float, FF, TmpFreq);
            ArrayType_Insert(float, FF, Index, TmpFreq);
            if(FF_Index > 6)
                break;
        }
    }

    ArrayType_Dtor(float, FF);
    return FF[3];
}

float MagnitudeDetect(float* Wave, int Length)
{
    int i;
    float MagnSum = 0;
    float MagnNum = 0;
    for(i = Length / 3 > 5000 ? 5000 : Length / 3; i < Length - 1536; i += 1536)
    {
        MagnitudeFromWave(Spec, Wave + i, 8);
        int State = Boost_FloatSum(Spec + 3, 50) > 1.5;
        if(State)
        {
            MagnSum += Boost_FloatMax(Wave, i, i + 1024);
            MagnNum ++;
        }
    }
    return MagnSum / MagnNum;
}

int WSplit(WCONF* Dest, String* FragPath, SCONF* Src, CDS* Scheme, String* Raw)
{
    int i;
    int WaveSize = GetFileLength(Raw) / 2;
    float* RawWave = (float*)malloc(sizeof(float) * WaveSize);
    if(! (WaveSize = LoadWaveAll(RawWave, Raw)))
    {
        printf("Error: cannot open raw data.\n");
        return 0;
    }
    printf("Raw data loaded, length: %.2fs.\n", (float)WaveSize / 44100);

    SetSampleRate(44100);
    float* Wave = 0;
    int WaveLen = 0;
    int RepeatCount = 0;
    String OutDir, OutPath, CountStr;
    String_Ctor(& OutDir);
    String_Ctor(& OutPath);
    String_Ctor(& CountStr);
    String_Copy(& OutDir, FragPath);
    String_JoinChars(& OutDir, "/");

    printf("Spliting...\n");
    float LastFreq = 80;
    float MagnSum = 0;
    for(i = 0; i <= Src -> TickList_Index; i ++)
    {
        if(i == Src -> TickList_Index)
            WaveLen = WaveSize - Src -> TickList[i].Time * 44100;
        else
            WaveLen = (Src -> TickList[i + 1].Time - Src -> TickList[i].Time) * 44100;
        Wave = (float*)realloc(Wave, sizeof(float) * WaveLen);
        Boost_FloatCopy(Wave, RawWave + (int)(Src -> TickList[i].Time * 44100), WaveLen);
        String_Copy(& OutPath, & OutDir);
        if(! String_EqualChars(& Src -> TickList[i].Consonant, "/"))
            String_Join(& OutPath, & Src -> TickList[i].Consonant);
        String_Join(& OutPath, & Src -> TickList[i].Vowel);
        if(i == 0)
            RepeatCount = 0;
        else
        {
            RepeatCount ++;
            if((! String_Equal(& Src -> TickList[i].Consonant, & Src -> TickList[i - 1].Consonant)) ||
               (! String_Equal(& Src -> TickList[i].Vowel    , & Src -> TickList[i - 1].Vowel    )))
            {
                RepeatCount = 0;
                LastFreq = 80;
            }
        }
        CStrInt(& CountStr, RepeatCount);
        String_Join(& OutPath, & CountStr);
        String_JoinChars(& OutPath, ".wsp");
        WriteWaveAll(& OutPath, Wave, WaveLen, 44100);

        LastFreq = BaseFreqDetect(Wave, WaveLen, LastFreq);
        ArrayType_PushNull(SampleList_Type, Dest -> SampleList);
        SampleList_Type* Top = Dest -> SampleList + Dest -> SampleList_Index;
        SampleList_Type_Ctor(Top);
        String_Copy(& Top -> Consonant, & Src -> TickList[i].Consonant);
        String_Copy(& Top -> Vowel    , & Src -> TickList[i].Vowel);
        Top -> Num = RepeatCount;
        Top -> F0  = LastFreq;

        int CDSIndex = CDS_SearchByVowel(Scheme, & Top -> Vowel);
        Top -> F1 = Scheme -> SrcVList[CDSIndex].F1;
        Top -> F2 = Scheme -> SrcVList[CDSIndex].F2;
        Top -> F3 = Scheme -> SrcVList[CDSIndex].F3;
        Top -> S1 = Scheme -> SrcVList[CDSIndex].S1;
        Top -> S2 = Scheme -> SrcVList[CDSIndex].S2;
        Top -> S3 = Scheme -> SrcVList[CDSIndex].S3;
        Top -> Mul = 1;

        MagnSum += MagnitudeDetect(Wave, WaveLen);
    }
    Dest -> AverageMagnitude = MagnSum / Src -> TickList_Index;
    String_Dtor(& OutDir);
    String_Dtor(& OutPath);
    String_Dtor(& CountStr);
    free(Wave);
    free(RawWave);
    return 1;
}
