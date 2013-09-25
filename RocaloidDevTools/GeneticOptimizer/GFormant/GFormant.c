#include "GFormant.h"
#include "Rand.h"
#include "RUtil/IO/FileUtil.h"
#include "RUtil/Misc/Converter.h"

#include "CVEDSP/Algorithm/Formant.h"
#include "CVEDSP/Algorithm/BaseFreq.h"
#include "CVEDSP/DFT/FFT.h"
#include "CVEDSP/DSPBase/Filter.h"

#include <malloc.h>
#include <math.h>

_Constructor_ (Wave)
{
    Dest -> Data = (float*)malloc(sizeof(float) * 44100 * 5);
}

_Destructor_ (Wave)
{
    free(Dest -> Data);
}

void GFormant_LoadFileList(GeneticSimulator* Dest, String* Path)
{
    void* FileStore = malloc(1024 * 50);
    StringStream StringReader;
    StringStream_Init(& StringReader, FileStore);
    String Temp;
    String_Ctor(& Temp);
    LoadFileAll(FileStore, Path);

    int i;
    for(i = 0; ; i ++)
    {
        Wave* TW;
        StringStream_ReadWord(& Temp, & StringReader);
        if(String_EqualChars(& Temp, "End"))
            break;
        Wave_Ctor((Wave*)Dest -> TaskList + i);
        TW = (Wave*)Dest -> TaskList + i;
        ((Wave*)Dest -> TaskList + i) -> Length = LoadWaveAll(((Wave*)Dest -> TaskList + i) -> Data, & Temp);
        ((Wave*)Dest -> TaskList + i) -> BaseFreq = GetBaseFrequencyFromWave(TW -> Data + TW -> Length / 4, 80, 1500, 12);

        printf("%f\n", ((Wave*)Dest -> TaskList + i) -> BaseFreq);

        FormantDescriptor* FD = ((FormantDescriptor*)Dest -> ResultList) + i;
        StringStream_ReadWord(& Temp, & StringReader);
        FD -> F1 = CFloatStr(& Temp);
        StringStream_ReadWord(& Temp, & StringReader);
        FD -> F2 = CFloatStr(& Temp);
        StringStream_ReadWord(& Temp, & StringReader);
        FD -> F3 = CFloatStr(& Temp);
    }
    Dest -> TaskNum = i;
    String_Dtor(& Temp);
    free(FileStore);
}

void GFormant_SetParam(void* Src)
{
    Analyzer_SetParameters(*((FormantAnalyzerParameters*)Src));
}

float WeightItg(float* Src, int From, int To)
{
    int i;
    float Sum = 0;
    for(i = From; i < To; i ++)
        Sum += Src[i];
    return Sum;
}

#define FloatMalloc(Size) (float*)malloc(sizeof(float) * Size)
void GFormant_Run(void* Result, void* Task)
{
    FormantDescriptor* FD = (FormantDescriptor*)Result;
    Wave* TW = (Wave*)Task;
    float* Spectrum = FloatMalloc(10240);

    SetSampleRate(44100);
    FormantEnvelopeFromWave(Spectrum, TW -> Data + TW -> Length / 4, TW -> BaseFreq, 4500, 50, 10);

    *FD = AnalyzeFormantFromEnvelope(Spectrum, 1024);
    free(Spectrum);
}
#undef FloatMalloc

float GFormant_Eval(void* Desc1, void* Desc2)
{
    FormantDescriptor* FD1 = (FormantDescriptor*)Desc1;
    FormantDescriptor* FD2 = (FormantDescriptor*)Desc2;
    float Score =  - (float)(abs(FD1 -> F1 - FD2 -> F1) +
                             abs(FD1 -> F2 - FD2 -> F2) * 2 +
                             abs(FD1 -> F3 - FD2 -> F3));
    if(Score > 0)
        Score = - 9999999;
    return Score;
}

void GFormant_Mutate(void* Param)
{
    FormantAnalyzerParameters* P = (FormantAnalyzerParameters*)Param;

    RandRange(F1Min, 20, 100, 800);
    RandRange(F1Max, 20, 1500, 2300);
    RandRange(F2Min, 20, 100, 800);
    RandRange(F2Max, 20, 3500, 4200);
    RandRange(F3Min, 20, 2600, 5000);
    RandRange(F3Max, 20, 2600, 5000);

    RandRange(PreEmphasisStrength, 0.04, 0, 3);
    RandRange(FPeakDistanceWidth, 5, 60, 300);
    RandRange(FPeakThreshold, 0.03, 0.2, 0.5);
    RandRange(FPeakWeightWidth, 4, 150, 300);

    RandRange(F2SearchRatioThreshold, 0.002, 0, 1);
    RandRange(F2SearchWidth, 10, 100, 700);
    RandRange(F2SearchWeightThreshold, 0.003, 0.01, 0.1);
    RandRange(F2SearchWeightThresholdRatio, 0.004, 0.05, 0.5);
    RandRange(F2SearchF3MinWeight, 0.001, 0.005, 0.1);

    RandRange(F1F2WeightDeviationFactor, 0.3, 5, 50);
    RandRange(F1F2WeightMinDeviation, 20, 1200, 2300);

    RandRange(HighFreqAdditionalRange, 14, 100, 1000);
    RandRange(HighLowFreqSearchInterval, 7, 50, 500);
    RandRange(HighLowFreqSearchThreshold, 0.01, 0.2, 0.8);
    RandRange(F2Interval, 15, 50, 400);

    RandRange(F3PosibilityFactor, 0.03, 1, 3);
    RandRange(LowSideF1LowFactor, 0.01, 0.5, 2);
    RandRange(LowSideF1HighFactor, 0.01, 0.5, 1.5);
    RandRange(LowSideF2LowFactor, 0.01, 0.1, 0.6);
    RandRange(LowSideF2HighFactor, 0.01, 0.8, 1.7);
    RandRange(HighSideF2LowFactor, 0.01, - 0.3, 0.3);
    RandRange(HighSideF2HighFactor, 0.01, 0.3, 0.9);
    RandRange(HighSideF3LowFactor, 0.01, 0, 0.6);
    RandRange(HighSideF3HighFactor, 0.01, 0.6, 1.1);
}

#define DisplayParam(Name) printf("  > " #Name " = %f;\n", ((FormantAnalyzerParameters*)Param) -> Name)
void GFormant_Display(void* Param)
{
    DisplayParam(F1Min);
    DisplayParam(F1Max);
    DisplayParam(F2Min);
    DisplayParam(F2Max);
    DisplayParam(F3Min);
    DisplayParam(F3Max);
    printf("\n");
    DisplayParam(PreEmphasisStrength);
    DisplayParam(FPeakDistanceWidth);
    DisplayParam(FPeakThreshold);
    DisplayParam(FPeakWeightWidth);
    printf("\n");
    DisplayParam(F2SearchRatioThreshold);
    DisplayParam(F2SearchWidth);
    DisplayParam(F2SearchWeightThreshold);
    DisplayParam(F2SearchWeightThresholdRatio);
    DisplayParam(F2SearchF3MinWeight);
    printf("\n");
    DisplayParam(F1F2WeightDeviationFactor);
    DisplayParam(F1F2WeightMinDeviation);
    printf("\n");
    DisplayParam(HighFreqAdditionalRange);
    DisplayParam(HighLowFreqSearchInterval);
    DisplayParam(HighLowFreqSearchThreshold);
    DisplayParam(F2Interval);
    printf("\n");
    DisplayParam(F3PosibilityFactor);
    DisplayParam(LowSideF1LowFactor);
    DisplayParam(LowSideF1HighFactor);
    DisplayParam(LowSideF2LowFactor);
    DisplayParam(LowSideF2HighFactor);
    DisplayParam(HighSideF2LowFactor);
    DisplayParam(HighSideF2HighFactor);
    DisplayParam(HighSideF3LowFactor);
    DisplayParam(HighSideF3HighFactor);
}
