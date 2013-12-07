#include "Synthesizer.h"
#include "CVEGlobal.h"
#include "DSPInclude.h"
#include "../DSPEx/FDFrame.h"
#include <malloc.h>

_Constructor_ (Synthesizer)
{
    SpeechMixer_Ctor(& Dest -> SubSynth);
    Dest -> SynthBuffer = FloatMalloc(SampleRate * 1);
}

_Destructor_ (Synthesizer)
{
    SpeechMixer_Dtor(& Dest -> SubSynth);
    free(Dest -> SynthBuffer);
}

void SynthesizerSendback_Free(SynthesizerSendback *Dest)
{
    free(Dest -> Data);
}

void Synthesizer_SetCVS(Synthesizer *Dest, CVS3 *Src)
{
    Dest -> VocalScript = Src;
}

//The window that is applied to remained wave(SynthBuffer)
void Synthesizer_RightWindow(float* Dest, int Length)
{
    int i;
    if(Length < 10)
    printf("%d\n", Length);
    Boost_FloatSet(Dest + Length, 0, CVE_FFTSize - Length);
    for(i = 0; i < Length; i ++)
        Dest[i] *= 1.0f - (float)i / Length;
}

//The window that is applied to new wave(PSOLAFrame)
void Synthesizer_LeftWindow(float* Dest, int Length)
{
    int i;
    Boost_FloatSet(Dest, 0, CVE_FFTHalf - Length);
    for(i = 0; i < Length; i ++)
        Dest[i + CVE_FFTHalf - Length] *= (float)i / Length;
}

#define VocalScript (Dest -> VocalScript)
#define CurrentTime (Dest -> CurrentTime)
#define CurrentSylIndex (Dest -> CurrentSylIndex)
#define CurrentSyllable (VocalScript -> SyllableList[CurrentSylIndex])
#define NextSyllable (VocalScript -> SyllableList[CurrentSylIndex + 1])
#define SubSynth (Dest -> SubSynth)
#define SynthBuffer (Dest -> SynthBuffer)
#define BufferPos (Dest -> BufferPos)

void Synthesizer_PrepareSynthesis(Synthesizer* Dest, int FromIndex)
{
    CurrentSylIndex = FromIndex;
    CurrentTime = CurrentSyllable.StartTime;
    BufferPos = 0;
    Boost_FloatSet(SynthBuffer, 0, SampleRate);
    SpeechMixer_SetSyllable(& SubSynth, & CurrentSyllable);
}

SynthesizerSendback Synthesizer_Synthesis(Synthesizer *Dest)
{
    SynthesizerSendback Ret;
    FDFrame FVocalFrame;
    PSOLAFrame TVocalFrame;
    SpeechMixerSendback SubRet;
    FDFrame_CtorSize(& FVocalFrame, CVE_FFTSize);
    PSOLAFrame_CtorSize(& TVocalFrame, CVE_FFTSize);
    if(CurrentSylIndex == VocalScript -> SyllableList_Index)
    {
        //Last Syllable
        Ret.Finished = 1;
    }else if(CurrentTime < CurrentSyllable.EndTime && CurrentTime < NextSyllable.StartTime)
    {
        //Default Synthesis
        //Only CurrentTime is changed

        //Synthesize
        SpeechMixer_SetTime(& SubSynth, CurrentTime - CurrentSyllable.StartTime);
        SubRet = SpeechMixer_Synthesis(& SubSynth, & FVocalFrame);
        PSOLAFrame_FromFDFrame(& TVocalFrame, & FVocalFrame);
        Boost_FloatDivArr(TVocalFrame.Data, TVocalFrame.Data, Hanning1024, CVE_FFTSize);

        //Window
        Synthesizer_RightWindow(SynthBuffer, SubRet.PSOLAFrameHopSize);
        Synthesizer_LeftWindow(TVocalFrame.Data, SubRet.PSOLAFrameHopSize);
        Boost_FloatAddArr(SynthBuffer, SynthBuffer,
                          TVocalFrame.Data + (int)(CVE_FFTHalf - SubRet.PSOLAFrameHopSize),
                          CVE_FFTHalf + SubRet.PSOLAFrameHopSize);

        //Dump
        Ret.Finished = 0;
        Ret.Data = FloatMalloc(SubRet.PSOLAFrameHopSize);
        Ret.Length = SubRet.PSOLAFrameHopSize;
        Boost_FloatCopy(Ret.Data, SynthBuffer, Ret.Length);

        //Move
        Boost_FloatCopy(SynthBuffer, SynthBuffer + Ret.Length, CVE_FFTHalf);
        CurrentTime += (float)Ret.Length / SampleRate;
    }else if(CurrentSyllable.EndTime < NextSyllable.StartTime)
    {
        //Silence Synthesis
        //Switch to next syllable when finished.
        if(CurrentTime + (float)CVE_FFTHalf / SampleRate < NextSyllable.StartTime)
        {
            //Return Silence
            Ret.Data = FloatMalloc(CVE_FFTHalf);
            Ret.Finished = 0;
            Ret.Length = CVE_FFTHalf;
            Boost_FloatSet(Ret.Data, 0, CVE_FFTHalf);
        }else
        {
            //CT            NST   CT2
            //|--------Dumped------|-Moved|   (Ret.Data)
            //               |-Hop-|-Half-|
            //|----Silence---|-PSOLAFrame-|
            //...............~.~.~.~.~.~.~.   (SynthBuffer)

            //Synthesize
            SpeechMixer_Reset(& SubSynth);
            SpeechMixer_SetSyllable(& SubSynth, & NextSyllable);
            SpeechMixer_SetTime(& SubSynth, NextSyllable.StartTime - NextSyllable.StartTime);
            SubRet = SpeechMixer_Synthesis(& SubSynth, & FVocalFrame);
            PSOLAFrame_FromFDFrame(& TVocalFrame, & FVocalFrame);
            Boost_FloatDivArr(TVocalFrame.Data, TVocalFrame.Data, Hanning1024, CVE_FFTSize);

            //Window
            int SilenceLength = (NextSyllable.StartTime - CurrentTime) * SampleRate;
            Synthesizer_LeftWindow(TVocalFrame.Data, SubRet.PSOLAFrameHopSize);
            Boost_FloatSet(SynthBuffer, 0, SilenceLength);
            Boost_FloatCopy(SynthBuffer + SilenceLength,
                            TVocalFrame.Data + (int)(CVE_FFTHalf - SubRet.PSOLAFrameHopSize),
                            SubRet.PSOLAFrameHopSize + CVE_FFTHalf);

            //Dump
            Ret.Finished = 0;
            Ret.Data = FloatMalloc(SilenceLength + SubRet.PSOLAFrameHopSize);
            Ret.Length = SilenceLength + SubRet.PSOLAFrameHopSize;
            Boost_FloatCopy(Ret.Data, SynthBuffer, Ret.Length);

            //Move
            Boost_FloatCopy(SynthBuffer, SynthBuffer + Ret.Length, CVE_FFTHalf);

            CurrentSylIndex ++;
        }
        CurrentTime += (float)Ret.Length / SampleRate;
    }else
    {
        //Mix Synthesis
        //Synthesize CurrentSyllable first, then synthesize NextSyllable
        //    until CurrentSyllable ends.
        //Switch to next syllable when finished.
        Ret.Finished = 1;
    }
    FDFrame_Dtor(& FVocalFrame);
    PSOLAFrame_Dtor(& TVocalFrame);
    return Ret;
}
