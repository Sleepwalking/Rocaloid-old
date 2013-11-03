#include "GDetect.h"
#include "../Rand.h"
#include "../RUtil/IO/FileUtil.h"
#include "../RUtil/Misc/Converter.h"
#include "../GFormant/GFormant.h"

#include "../CVEDSP/Algorithm/Formant.h"
#include "../CVEDSP/Algorithm/BaseFreq.h"
#include "../CVEDSP/DSPBase/Spectrum.h"
#include "../CVEDSP/DFT/FFT.h"
#include "../CVEDSP/DSPBase/Filter.h"
#include "../CVEDSP/Algorithm/SpeechDetector.h"
#include "../CVEDSP/IntrinUtil/FloatArray.h"

#include <malloc.h>
#include <math.h>

_Constructor_ (GDWave)
{
    Dest -> Data = (float*)malloc(sizeof(float) * 44100 * 5);
}

_Destructor_ (GDWave)
{
    free(Dest -> Data);
}

void GDetect_LoadFileList(GeneticSimulator* Dest, String* Path)
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
        GDWave_Ctor((GDWave*)Dest -> TaskList + i);
        ((GDWave*)Dest -> TaskList + i) -> Length = LoadWaveAll(((GDWave*)Dest -> TaskList + i) -> Data, & Temp);
\
        StringStream_ReadWord(& Temp, & StringReader);
        float* VOT = ((float*)Dest -> ResultList) + i;
        *VOT = CFloatStr(& Temp);
    }
    Dest -> TaskNum = i;
    String_Dtor(& Temp);
    free(FileStore);
}

void GDetect_SetParam(void* Src)
{
    SDetector_SetParameters(*((SpeechDetectorParameters*)Src));
}

#define FloatMalloc(Size) (float*)malloc(sizeof(float) * Size)
void GDetect_Run(void* Result, void* Task)
{
    float* VOT = (float*)Result;
    GDWave* TW = (GDWave*)Task;
    float* Averaged = FloatMalloc(44100 * 10);

    SetSampleRate(44100);
    float BF = GetBaseFrequencyFromWave(TW -> Data + TW -> Length / 2, 80, 1500, 13);
    SpeechDetectorPreProcess(Averaged, TW -> Data, BF, TW -> Length / 2);
    * VOT = DetectVOTWithBaseFreq(Averaged, BF, TW -> Length / 2);

    free(Averaged);
}
#undef FloatMalloc

float GDetect_Eval(void* Desc1, void* Desc2)
{
    float* P1 = (float*)Desc1;
    float* P2 = (float*)Desc2;
    float Score =  - ((*P1 - *P2) > 0 ? (*P1 - *P2) : (*P2 - *P1));
    if(Score > 0)
        Score = - 9999999;
    return Score;
}

void GDetect_Mutate(void* Param)
{
    SpeechDetectorParameters* P = (SpeechDetectorParameters*)Param;

    RandRange(VoiceThreshold, 0.0002, 0.0001, 0.1);

    RandRange(PreProcessLowFreq, 4, 10, 120);
    RandRange(PreProcessHighFreqFactor, 0.05, 1.1, 2.0);
    RandRange(PreProcessMovingAverageRatio, 0.01, 0.03, 0.8);

    RandRange(Delay, 0.15, - 3, 3);
}

#define DisplayParamF(Name) printf("  > " #Name " = %f;\n", ((SpeechDetectorParameters*)Param) -> Name)
void GDetect_Display(void* Param)
{
    DisplayParamF(VoiceThreshold);

    DisplayParamF(PreProcessLowFreq);
    DisplayParamF(PreProcessHighFreqFactor);
    DisplayParamF(PreProcessMovingAverageRatio);

    DisplayParamF(Delay);
}
