#include <stdio.h>
#include <malloc.h>
#include "CVEGlobal.h"
#include "DSPInclude.h"
#include "Synthesizer/CSynth.h"
#include "Synthesizer/FSynth.h"
#include "Synthesizer/PitchMixer.h"
#include "Synthesizer/SpeechMixer.h"
#include "Synthesizer/Synthesizer.h"
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

    float* Wave = (float*)malloc(sizeof(float) * SampleRate * 20);
    Boost_FloatSet(Wave, 0, SampleRate * 10);

    ALblLog_Enable();
    int i = 0;
    Synthesizer MainSynth;
    Synthesizer_Ctor(& MainSynth);
    Synthesizer_SetCVS(& MainSynth, & testcvs);
    Synthesizer_PrepareSynthesis(& MainSynth, 0);
    SynthesizerSendback MainRet;
    MainRet.Finished = 0;
    do
    {
        ALblLog_SetTime((float)i / 44100);
        MainRet = Synthesizer_Synthesis(& MainSynth);
        if(MainRet.Finished)
            break;
        Boost_FloatCopy(Wave + i, MainRet.Data, MainRet.Length);
        i += MainRet.Length;
        SynthesizerSendback_Free(& MainRet);
    } while(1);
    Synthesizer_Dtor(& MainSynth);

    CVS3_Dtor(& testcvs);
    String_Dtor(& CVSPath);
    String_FromChars(Output, WAV_PATH);
    WriteWaveAll(& Output, Wave, SampleRate * 10, SampleRate);
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
