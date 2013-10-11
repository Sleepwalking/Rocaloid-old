#include <stdio.h>
#include <malloc.h>
#include "CVEGlobal.h"
#include "DSPInclude.h"
#include "Synthesizer/CSynth.h"

int main(void)
{
    String_FromChars(CDTPath, "/home/sleepwalking/Documents/Rocaloid/Rocaloid/RDesign/RocaloidEngine3/CDT3Example.cdt");
    CVEGlobal_LoadCDT(& CDTPath);
    String_Dtor(& CDTPath);

    SetSampleRate(44100);
    float* Wave = (float*)malloc(sizeof(float) * SampleRate * 50);
    Boost_FloatSet(Wave, 0, SampleRate * 50);

    String_FromChars(SName, "pa_A3");
    CSynth CS;
    CSynth_Ctor(& CS);
    CSynth_SetSymbol(& CS, & SName);
    PSOLAFrame Out;
    PSOLAFrame_CtorSize(& Out, 1024);

    CSynthSendback Ret, Ret2;
    int count = 0;
    int i;
    Ret2.PSOLAFrameLength = 0;
    for(i = 0; i < 10000; i ++)
    {
        Ret = CSynth_Synthesis(& CS, & Out);
        PSOLAFrame_MixByRatio(Wave, &Out, count - Ret2.PSOLAFrameLength, count, count + Ret.PSOLAFrameLength, 1, MixNormal);
        count += Ret.PSOLAFrameLength;
        Ret2 = Ret;
    }

    PSOLAFrame_Dtor(& Out);
    CSynth_Dtor(& CS);

    String_Dtor(& SName);

    String_FromChars(Output, "/tmp/a.wav");
    WriteWaveAll(& Output, Wave, SampleRate * 50, SampleRate);
    String_Dtor(& Output);

    free(Wave);
    printf("Hello World!\n");
    return 0;
}
