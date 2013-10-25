#include <stdio.h>
#include <malloc.h>
#include "CVEGlobal.h"
#include "DSPInclude.h"
#include "Synthesizer/CSynth.h"
#include "Synthesizer/FSynth.h"
#include "Synthesizer/PitchMixer.h"
#include "Synthesizer/SpeechMixer.h"
#include "CVEDSP/Plot.h"
#include "RFILE3/CVS3/CVS3.h"
#include "RFILE3/CVS3/CVSRDLReader.h"

int main(void)
{
    GenerateHanning(Hanning2048, 2048);
    GenerateHanning(Hanning1024, 1024);
    Boost_FloatAdd(Hanning2048, Hanning2048, 0.001, 2048);
    Boost_FloatAdd(Hanning1024, Hanning1024, 0.001, 1024);

    GNUPlot_Open();

    String_FromChars(CDTPath, "/home/sleepwalking/Documents/Rocaloid/Rocaloid/RDesign/RocaloidEngine3/CDT3Example.cdt");
    CVEGlobal_LoadCDT(& CDTPath);
    String_Dtor(& CDTPath);

    SetSampleRate(44100);

    String_FromChars(SName, "i");
    String_FromChars(CVSPath, "/home/sleepwalking/Documents/Rocaloid/Rocaloid/RDesign/RocaloidEngine3/CVS3example.cvs");
/*
    PitchMixer test;
    PitchMixer_Ctor(& test);
    PitchMixer_SetSymbol(& test, & SName);
    PitchMixer_SetLimitedFrequency(& test, 800);
*/
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
    //PitchMixerSendback Ret, Ret2;
    FDFrame Out;
    FDFrame_CtorSize(& Out, 1024);

    int count = 0;
    int i, f;
    Ret2.PSOLAFrameHopSize = 0;

    float t;
    /*
    for(t = 0; t < 0.8; t += 0.01)
    {
        SpeechMixer_SetTime(& test, t);
    }
*/
    //PitchMixer_SetLimitedFrequency(& test, 500);

    //for(i = 0; i < 1200; i ++)
    for(t = 0; t < 2.4;)
    {
        SpeechMixer_SetTime(& test, t);
        //PitchMixer_SetFrequency(& test, (float)i / 2 + 300);
        Ret = SpeechMixer_Synthesis(& test, & Out);

        PSOLAFrame_FromFDFrame(& POut, & Out);
        Boost_FloatDivArr(POut.Data, POut.Data, Hanning1024, 1024);
        PSOLAFrame_MixByRatio(Wave, &POut, count - Ret2.PSOLAFrameHopSize, count, count + Ret.PSOLAFrameHopSize, 1, MixNormal);
        count += Ret.PSOLAFrameHopSize;
        Ret2 = Ret;
        t = (float)count / 44100;
    }
    PSOLAFrame_Dtor(& POut);

    FDFrame_Dtor(& Out);

    SpeechMixer_Dtor(& test);
    //PitchMixer_Dtor(& test);
    String_Dtor(& SName);

    CVS3_Dtor(& testcvs);
    String_Dtor(& CVSPath);
    String_FromChars(Output, "/tmp/a.wav");
    WriteWaveAll(& Output, Wave, SampleRate * 4, SampleRate);
    String_Dtor(& Output);

    GNUPlot_Close();

    free(Wave);

    printf("Hello World\n");
    return 0;
}
