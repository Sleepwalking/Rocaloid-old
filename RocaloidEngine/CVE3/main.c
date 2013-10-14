#include <stdio.h>
#include <malloc.h>
#include "CVEGlobal.h"
#include "DSPInclude.h"
#include "Synthesizer/CSynth.h"
#include "Synthesizer/FSynth.h"

int main(void)
{
    GenerateHamming(Hamming2048, 2048);
    GenerateHamming(Hamming1024, 1024);

    String_FromChars(CDTPath, "/home/sleepwalking/Documents/Rocaloid/Rocaloid/RDesign/RocaloidEngine3/CDT3Example.cdt");
    CVEGlobal_LoadCDT(& CDTPath);
    String_Dtor(& CDTPath);

    SetSampleRate(44100);
    float* Wave = (float*)malloc(sizeof(float) * SampleRate * 100);
    Boost_FloatSet(Wave, 0, SampleRate * 100);

    String_FromChars(SName, "pa_C3");
    /*
    CSynth CS;
    CSynth_Ctor(& CS);
    CSynth_SetSymbol(& CS, & SName);*/
    PSOLAFrame POut;
    PSOLAFrame_CtorSize(& POut, 1024);

    FSynth FreqGen;
    FSynth_Ctor(& FreqGen);
    FSynth_SetSymbol(& FreqGen, & SName);
    FSynth_SetVowelRatio(& FreqGen, 1);
    FSynth_SetConsonantRatio(& FreqGen, 1);
    FSynthSendback Ret, Ret2;
    FDFrame Out;
    FDFrame_CtorSize(& Out, 1024);

    //CSynthSendback Ret, Ret2;
    int count = 0;
    int i;
    Ret2.PSOLAFrameHopSize = 0;
    //Ret2.PSOLAFrameHopSize = 0;
    /*
    CSynth_SetVowelRatio(& CS, 1);
    CSynth_SetConsonantRatio(& CS, 1);*/

    for(i = 0; i < 3000; i ++)
    {
        FSynth_SetFrequency(& FreqGen, (float)i / 10 + 260);
        Ret = FSynth_Synthesis(& FreqGen, & Out);
        PSOLAFrame_FromFDFrame(& POut, & Out);
        Boost_FloatDivArr(POut.Data, POut.Data, Hamming1024, 1024);
        PSOLAFrame_MixByRatio(Wave, &POut, count - Ret2.PSOLAFrameHopSize, count, count + Ret.PSOLAFrameHopSize, 1, MixNormal);
        count += Ret.PSOLAFrameHopSize;
        Ret2 = Ret;
    }

    PSOLAFrame_Dtor(& POut);
    //CSynth_Dtor(& CS);

    FDFrame_Dtor(& Out);
    FSynth_Dtor(& FreqGen);

    String_Dtor(& SName);

    String_FromChars(Output, "/tmp/aN.wav");
    WriteWaveAll(& Output, Wave, SampleRate * 100, SampleRate);
    String_Dtor(& Output);

    free(Wave);
    printf("Hello World!\n");
    return 0;
}
