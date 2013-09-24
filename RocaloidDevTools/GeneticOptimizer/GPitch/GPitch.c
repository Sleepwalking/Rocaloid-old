#include "GPitch.h"
#include "RUtil/IO/FileUtil.h"
#include "RUtil/Misc/Converter.h"
#include "GFormant/GFormant.h"

#include "CVEDSP/FreqDomain/Formant.h"
#include "CVEDSP/FreqDomain/FDAnalysis.h"
#include "CVEDSP/FreqDomain/Spectrum.h"
#include "CVEDSP/DFT/FFT.h"
#include "CVEDSP/FreqDomain/Filter.h"

#include <malloc.h>
#include <math.h>

_Constructor_ (GPWave)
{
    Dest -> Data = (float*)malloc(sizeof(float) * 44100 * 5);
}

_Destructor_ (GPWave)
{
    free(Dest -> Data);
}

void GPitch_LoadFileList(GeneticSimulator* Dest, String* Path)
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
        StringStream_ReadWord(& Temp, & StringReader);
        if(String_EqualChars(& Temp, "End"))
            break;
        GPWave_Ctor((GPWave*)Dest -> TaskList + i);
        ((GPWave*)Dest -> TaskList + i) -> Length = LoadWaveAll(((GPWave*)Dest -> TaskList + i) -> Data, & Temp);
\
        StringStream_ReadWord(& Temp, & StringReader);
        float* BF = ((float*)Dest -> ResultList) + i;
        *BF = CFloatStr(& Temp);
    }
    Dest -> TaskNum = i;
    String_Dtor(& Temp);
    free(FileStore);
}

void GPitch_SetParam(void* Src)
{
    BFAnalyzer_SetParameters(*((BaseFreqAnalyzerParameters*)Src));
}

#define FloatMalloc(Size) (float*)malloc(sizeof(float) * Size)
void GPitch_Run(void* Result, void* Task)
{
    float* BF = (float*)Result;
    GPWave* TW = (GPWave*)Task;
    float* Spectrum = FloatMalloc(8192);

    SetSampleRate(44100);
    MagnitudeFromWave(Spectrum, TW -> Data + TW -> Length / 4, 12);
    *BF = GetBaseFrequencyFromSpectrum(Spectrum, 80, 1500, 4096);

    free(Spectrum);
}
#undef FloatMalloc

float GPitch_Eval(void* Desc1, void* Desc2)
{
    float* P1 = (float*)Desc1;
    float* P2 = (float*)Desc2;
    float Score =  - (float)(abs(*P1 - *P2));
    //printf("%f, %f\n", *P1, *P2);

    if(Score > 0)
        Score = - 9999999;
    return Score;
}

int IntRandom(int Range)
{
    return rand() % Range - Range / 2;
}

#define RandRange(Para, Width, LowerLimit, UpperLimit)\
    P -> Para += Random() * Width;\
    if(P -> Para < LowerLimit)\
        P -> Para = LowerLimit + Random() * Width;\
    if(P -> Para > UpperLimit)\
        P -> Para = UpperLimit + Random() * Width;

#define IntRandRange(Para, Width, LowerLimit, UpperLimit)\
    P -> Para += IntRandom(Width);\
    if(P -> Para < LowerLimit)\
        P -> Para = LowerLimit + IntRandom(Width);\
    if(P -> Para > UpperLimit)\
        P -> Para = UpperLimit + IntRandom(Width);

void GPitch_Mutate(void* Param)
{
    BaseFreqAnalyzerParameters* P = (BaseFreqAnalyzerParameters*)Param;

    IntRandRange(Forward, 3, 1, 5);
    IntRandRange(Backward, 3, 1, 5);
    RandRange(AvgFactor, 0.1, 0.3, 2);
    RandRange(MinFactor, 0.1, 0.3, 3);
    IntRandRange(Start, 3, 1, 7);
}

#define DisplayParamF(Name) printf("  > " #Name " = %f;\n", ((BaseFreqAnalyzerParameters*)Param) -> Name)
#define DisplayParamI(Name) printf("  > " #Name " = %d;\n", ((BaseFreqAnalyzerParameters*)Param) -> Name)
void GPitch_Display(void* Param)
{
    DisplayParamI(Forward);
    DisplayParamI(Backward);
    DisplayParamF(AvgFactor);
    DisplayParamF(MinFactor);
    DisplayParamI(Start);
}
