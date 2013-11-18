#include <stdio.h>
#include <malloc.h>
#include "CVEGlobal.h"
#include "DSPInclude.h"
#include "Synthesizer/CSynth.h"
#include "Synthesizer/FSynth.h"
#include "Synthesizer/PitchMixer.h"
#include "Synthesizer/SpeechMixer.h"
#include "../../CVEDSP/Plot.h"
#include "../RFILE3/CVS3/CVS3.h"
#include "../RFILE3/CVS3/CVSRDLReader.h"
#include "Debug/ALblLog.h"
#include <unistd.h>

//#include "CVEDSP/DFT/SplitRadixGen.h"
//#include "CVEDSP/DFT/SplitRadix.h"

#define CDT_PATH "/tmp/Rocaloid_LuoTianYi_Build/Dict.cdt"
//#define CDT_PATH "/home/sleepwalking/Documents/Rocaloid/Rocaloid/RDesign/RocaloidEngine3/CDT3Example.cdt"
#define CVS_PATH "/home/sleepwalking/Documents/Rocaloid/Rocaloid/RDesign/RocaloidEngine3/CVS3example.cvs"
#define AUP_PATH "/tmp/cvedebug.txt"
#define WAV_PATH "/tmp/a.wav"

int main(void)
{
    chdir("/tmp/Rocaloid_LuoTianYi_Build");
    GenerateHanning(Hanning2048, 2048);
    GenerateHanning(Hanning1024, 1024);
    Boost_FloatAdd(Hanning2048, Hanning2048, 0.001, 2048);
    Boost_FloatAdd(Hanning1024, Hanning1024, 0.001, 1024);

    GNUPlot_Open();

    String_FromChars(CDTPath, CDT_PATH);
    CVEGlobal_LoadCDT(& CDTPath);
    String_Dtor(& CDTPath);

    SetSampleRate(44100);

    String_FromChars(CVSPath, CVS_PATH);

    String_FromChars(AupPath, AUP_PATH);
    ALblLog_Create(& AupPath);
    String_Dtor(& AupPath);

    CVS3 testcvs;
    CVS3_Ctor(& testcvs);
    CVSRDLReader_Open(& CVSPath);
    CVS3_Read(& testcvs);
    CVSRDLReader_Close();

    SpeechMixer test;
    SpeechMixer_Ctor(& test);
    SpeechMixer_SetSyllable(& test, testcvs.SyllableList + 0);
    SpeechMixer_SetConsonantRatio(& test, 1);

    float* Wave = (float*)malloc(sizeof(float) * SampleRate * 100);
    Boost_FloatSet(Wave, 0, SampleRate * 100);

    PSOLAFrame POut;
    PSOLAFrame_CtorSize(& POut, 1024);

    SpeechMixerSendback Ret, Ret2;
    FDFrame Out;
    FDFrame_CtorSize(& Out, 1024);

    int count = 0;
    Ret2.PSOLAFrameHopSize = 0;

    //ALblLog_Disable();
    float t;
    for(t = 0; t < 2.4;)
    {
        /*
        if(t > 0.5 && t < 0.7)
            ALblLog_Enable();
        if(t > 0.7)
            ALblLog_Disable();*/
        SpeechMixer_SetTime(& test, t);
        Ret = SpeechMixer_Synthesis(& test, & Out);

        PSOLAFrame_FromFDFrame(& POut, & Out);
        Boost_FloatDivArr(POut.Data, POut.Data, Hanning1024, 1024);
        PSOLAFrame_MixByRatio(Wave, &POut, count - Ret2.PSOLAFrameHopSize, count, count + Ret.PSOLAFrameHopSize, 1, MixNormal);
        count += Ret.PSOLAFrameHopSize;
        Ret2 = Ret;
        t = (float)count / 44100;
        ALblLog_Print("PLen: %d", Ret.PSOLAFrameHopSize);
        ALblLog_Print("Main: PSOLAMix at %d (%f sec)", count, t);
        ALblLog_SetTime(t);
    }
    PSOLAFrame_Dtor(& POut);

    FDFrame_Dtor(& Out);

    SpeechMixer_Dtor(& test);

    CVS3_Dtor(& testcvs);
    String_Dtor(& CVSPath);
    String_FromChars(Output, WAV_PATH);
    WriteWaveAll(& Output, Wave, SampleRate * 4, SampleRate);
    String_Dtor(& Output);

    GNUPlot_Close();
    ALblLog_Save();

    free(Wave);

    printf("Synthesis successfully finished.\n");
/*
    SRExpression Plan;
    SRExpressionCtor(& Plan);
    SRExpressionGenerator_L(& Plan, 0, 256);
    SplitRadix_Generator(& Plan, 0);

    SRExpressionDtor(& Plan);
*/
//    SplitRadix_RadixL_Generator_AVX(0, 512);
    return 0;
}
