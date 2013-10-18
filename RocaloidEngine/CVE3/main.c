#include <stdio.h>
#include <malloc.h>
#include "CVEGlobal.h"
#include "DSPInclude.h"
#include "Synthesizer/CSynth.h"
#include "Synthesizer/FSynth.h"
#include "Synthesizer/PitchMixer.h"
#include "CVEDSP/Plot.h"

int main(void)
{
    GenerateHanning(Hanning2048, 2048);
    GenerateHanning(Hanning1024, 1024);
    Boost_FloatAdd(Hanning2048, Hanning2048, 0.001, 2048);
    Boost_FloatAdd(Hanning1024, Hanning1024, 0.001, 1024);

    //GNUPlot_Open();

    String_FromChars(CDTPath, "/home/sleepwalking/Documents/Rocaloid/Rocaloid/RDesign/RocaloidEngine3/CDT3Example.cdt");
    CVEGlobal_LoadCDT(& CDTPath);
    String_Dtor(& CDTPath);

    SetSampleRate(44100);

    String_FromChars(SName, "a");

    PitchMixer test;
    PitchMixer_Ctor(& test);
    PitchMixer_SetSymbol(& test, & SName);
    PitchMixer_SetLimitedFrequency(& test, 800);

    float* Wave = (float*)malloc(sizeof(float) * SampleRate * 100);
    Boost_FloatSet(Wave, 0, SampleRate * 100);

    PSOLAFrame POut;
    PSOLAFrame_CtorSize(& POut, 1024);

    PitchMixerSendback Ret, Ret2;
    FDFrame Out;
    FDFrame_CtorSize(& Out, 1024);

    int count = 0;
    int i;
    Ret2.PSOLAFrameHopSize = 0;

    PitchMixer_SetLimitedFrequency(& test, 500);
    for(i = 0; i < 6000; i ++)
    {
        PitchMixer_SetFrequency(& test, i / 15 + 200);
        Ret = PitchMixer_Synthesis(& test, & Out);

        PSOLAFrame_FromFDFrame(& POut, & Out);
        Boost_FloatDivArr(POut.Data, POut.Data, Hanning1024, 1024);
        PSOLAFrame_MixByRatio(Wave, &POut, count - Ret2.PSOLAFrameHopSize, count, count + Ret.PSOLAFrameHopSize, 1, MixNormal);
        count += Ret.PSOLAFrameHopSize;
        Ret2 = Ret;
    }
    PSOLAFrame_Dtor(& POut);

    FDFrame_Dtor(& Out);

    PitchMixer_Dtor(& test);
    String_Dtor(& SName);

    String_FromChars(Output, "/tmp/aN.wav");
    WriteWaveAll(& Output, Wave, SampleRate * 100, SampleRate);
    String_Dtor(& Output);

    //GNUPlot_Close();

    free(Wave);

    printf("Hello World\n");
    return 0;
}
