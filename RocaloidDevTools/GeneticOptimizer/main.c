#include <stdio.h>
#include <malloc.h>
#include "RUtil/RUtil.h"
#include "RUtil/IO/FileUtil.h"
#include "GFormant/GFormant.h"
#include "GPitch/GPitch.h"
#include "GDetect/GDetect.h"
#include "GeneticSimulator.h"

#include "CVEDSP/Algorithm/Formant.h"
#include "CVEDSP/Algorithm/BaseFreq.h"
#include "CVEDSP/DFT/FFT.h"
#include "CVEDSP/DSPBase/Filter.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include "CVEDSP/Algorithm/SpeechDetector.h"

#include <string.h>

int main(void)
{
    GeneticSimulator GSim;
    GeneticSimulator_Ctor(& GSim);
    String_FromChars(Path, "/tmp/GFormantTestList");
    SetSampleRate(44100);
/*
    GeneticSimulator_SetParameter(& GSim, sizeof(SpeechDetectorParameters), 50);

    SPara = SPara;
    GeneticSimulator_SetInitialParam(& GSim, & SPara);

    GeneticSimulator_SetTask(& GSim, sizeof(GDWave), 1000);
    GeneticSimulator_SetResult(& GSim, sizeof(float));
    GeneticSimulator_SetSelectionNum(& GSim, 10);

    GeneticSimulator_SetRunFunc(& GSim, GDetect_Run);
    GeneticSimulator_SetEvaluateFunc(& GSim, GDetect_Eval);
    GeneticSimulator_SetSetParamFunc(& GSim, GDetect_SetParam);
    GeneticSimulator_SetMutateFunc(& GSim, GDetect_Mutate);
    GeneticSimulator_SetDisplayFunc(& GSim, GDetect_Display);
    GDetect_LoadFileList(& GSim, & Path);*/


    GeneticSimulator_SetParameter(& GSim, sizeof(FormantAnalyzerParameters), 100);
    GeneticSimulator_SetInitialParam(& GSim, & APara);
    GeneticSimulator_SetTask(& GSim, sizeof(Wave), 1000);
    GeneticSimulator_SetResult(& GSim, sizeof(FormantDescriptor));
    GeneticSimulator_SetSelectionNum(& GSim, 10);

    GeneticSimulator_SetRunFunc(& GSim, GFormant_Run);
    GeneticSimulator_SetEvaluateFunc(& GSim, GFormant_Eval);
    GeneticSimulator_SetSetParamFunc(& GSim, GFormant_SetParam);
    GeneticSimulator_SetMutateFunc(& GSim, GFormant_Mutate);
    GeneticSimulator_SetDisplayFunc(& GSim, GFormant_Display);
    GFormant_LoadFileList(& GSim, & Path);

/*
    GeneticSimulator_SetParameter(& GSim, sizeof(BaseFreqAnalyzerParameters), 100);
    GeneticSimulator_SetInitialParam(& GSim, & BPara);
    GeneticSimulator_SetTask(& GSim, sizeof(GPWave), 1000);
    GeneticSimulator_SetResult(& GSim, sizeof(float));
    GeneticSimulator_SetSelectionNum(& GSim, 20);

    GeneticSimulator_SetRunFunc(& GSim, GPitch_Run);
    GeneticSimulator_SetEvaluateFunc(& GSim, GPitch_Eval);
    GeneticSimulator_SetSetParamFunc(& GSim, GPitch_SetParam);
    GeneticSimulator_SetMutateFunc(& GSim, GPitch_Mutate);
    GeneticSimulator_SetDisplayFunc(& GSim, GPitch_Display);
    GPitch_LoadFileList(& GSim, & Path);
*/
    GeneticSimulator_RunSimulation(& GSim, 20);

/*
    int i;
    ArrayType_Ctor(String, PitchList);
    String_FromChars(Pitch, "C2");
    ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "C#2"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "D2"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "D#2"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "E2"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "F2"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "F#2"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "G2"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "G#2"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "A2"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "A#2"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "B2"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "C3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "C#3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "D3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "D#3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "E3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "F3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "F#3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "G3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "G#3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "A3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "A#3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "B3"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "C4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "C#4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "D4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "D#4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "E4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "F4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "F#4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "G4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "G#4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "A4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "A#4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "B4"); ArrayType_PushObj(String, PitchList, & Pitch);
    String_SetChars(& Pitch, "C5"); ArrayType_PushObj(String, PitchList, & Pitch);

    float Freq = 131.0f;
    for(i = 0; i <= PitchList_Index; i ++)
    {
        printf("/tmp/Raw1/a_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/o_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/i_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/e_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/o_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/e-_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/u_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/v_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/n_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/NN_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/NG_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/n@_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/n3_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/n[_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/n~_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        printf("/tmp/Raw1/n#_%s.wav\t%f\n", String_GetChars(PitchList + i), Freq);
        Freq *= 1.05946;
    }

    String_Dtor(& Pitch);
    ArrayType_ObjDtor(String, PitchList);
    ArrayType_Dtor(String, PitchList);
    */
    String_Dtor(& Path);
    GeneticSimulator_Dtor(& GSim);
    printf("Simulation Finished !\n");
    return 0;
}

