#include "Synthesizer.h"
#include "CVEGlobal.h"
#include "DSPInclude.h"
#include "../DSPEx/FDFrame.h"
#include <malloc.h>

_Constructor_ (Synthesizer)
{
    SpeechMixer_Ctor(& Dest -> SubSynth);
    Dest -> SynthBuffer    = FloatMalloc(SampleRate * 1);
    Dest -> SynthMixBuffer = FloatMalloc(SampleRate * 1);
}

_Destructor_ (Synthesizer)
{
    SpeechMixer_Dtor(& Dest -> SubSynth);
    free(Dest -> SynthBuffer);
    free(Dest -> SynthMixBuffer);
}

void SynthesizerSendback_Free(SynthesizerSendback *Dest)
{
    free(Dest -> Data);
}

void Synthesizer_SetCVS(Synthesizer *Dest, CVS3 *Src)
{
    Dest -> VocalScript = Src;
}

//The window applied to remained wave(SynthBuffer)
void Synthesizer_RightWindow(float* Dest, int Length)
{
    int i;
    if(Length < 10)
    printf("%d\n", Length);
    Boost_FloatSet(Dest + Length, 0, CVE_FFTSize - Length);
    for(i = 0; i < Length; i ++)
        Dest[i] *= 1.0f - (float)i / Length;
}

//The window applied to new wave(PSOLAFrame)
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
#define SynthMixBuffer (Dest -> SynthMixBuffer)
#define MixBufferPos (Dest -> MixBufferPos)

void Synthesizer_PrepareSynthesis(Synthesizer* Dest, int FromIndex)
{
    CurrentSylIndex = FromIndex;
    CurrentTime = CurrentSyllable.StartTime;
    BufferPos = 0;
    Boost_FloatSet(SynthBuffer, 0, SampleRate);
    SpeechMixer_SetSyllable(& SubSynth, & CurrentSyllable);
}

#define SynthesisBlock(Time)\
    do\
    {\
        SpeechMixer_SetTime(& SubSynth, (Time));\
        SubRet = SpeechMixer_Synthesis(& SubSynth, & FVocalFrame);\
        PSOLAFrame_FromFDFrame(& TVocalFrame, & FVocalFrame);\
        Boost_FloatDivArr(TVocalFrame.Data, TVocalFrame.Data, Hanning1024, CVE_FFTSize);\
    } while(0)

#define WindowBlock(Buffer)\
    do\
    {\
        Synthesizer_RightWindow((Buffer), SubRet.PSOLAFrameHopSize);\
        Synthesizer_LeftWindow(TVocalFrame.Data, SubRet.PSOLAFrameHopSize);\
        Boost_FloatAddArr((Buffer), (Buffer),\
                        TVocalFrame.Data + (int)(CVE_FFTHalf - SubRet.PSOLAFrameHopSize),\
                        CVE_FFTHalf + SubRet.PSOLAFrameHopSize);\
    } while(0)

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
        if(CurrentTime > CurrentSyllable.EndTime)
            Ret.Finished = 1;
        else
            goto DefaultSynthesis;
    }else if(CurrentTime < CurrentSyllable.EndTime && CurrentTime < NextSyllable.StartTime)
    {
        //Default Synthesis
        //Only CurrentTime is changed
        DefaultSynthesis:

        //Synthesize
        SynthesisBlock(CurrentTime - CurrentSyllable.StartTime);

        //Window
        WindowBlock(SynthBuffer);

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
            SynthesisBlock(NextSyllable.StartTime - NextSyllable.StartTime);

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
        //|---------Dumped----------|-------To Buffer-----|
        //                    ~~~~~~~~~~~~~         (Syl 2)
        //               ~~~~~~~~~~~~               (Syl 2)
        //       ~~~~~~~~~~~~                       (Syl 2)
        //   ~~~~~~~~~~~~                           (Syl 2)
        //~~~~~~~~~~~                               (Syl 2)
        //           ~~~~~~~~~~~                    (Syl 1)
        //     ~~~~~~~~~~~~                         (Syl 1)
        //~~~~~~~~~~~                               (Syl 1)
        //-----\_____                               (Right Window)
        //~~~~~~~~~~~...............................(Synth Buffer)

        //Synthesize
        BufferPos    = 0;
        MixBufferPos = 0;
        SubRet.PSOLAFrameHopSize = 0;
        Boost_FloatSet(SynthBuffer   , 0, SampleRate * 1);
        Boost_FloatSet(SynthMixBuffer, 0, SampleRate * 1);
        //Synthesize CurrentSyllable
        while(CurrentTime < CurrentSyllable.EndTime)
        {
            SynthesisBlock(CurrentTime - CurrentSyllable.StartTime);
            WindowBlock(SynthBuffer + BufferPos);
            BufferPos += SubRet.PSOLAFrameHopSize;
            CurrentTime += (float)SubRet.PSOLAFrameHopSize / SampleRate;
        }
        Synthesizer_RightWindow(SynthBuffer + BufferPos, SubRet.PSOLAFrameHopSize);

        SpeechMixer_Reset(& SubSynth);
        SpeechMixer_SetSyllable(& SubSynth, & NextSyllable);
        CurrentTime = NextSyllable.StartTime;
        //Synthesizer NextSyllable
        while(CurrentTime < CurrentSyllable.EndTime + (float)CVE_FFTHalf / SampleRate)
        {
            SynthesisBlock(CurrentTime - NextSyllable.StartTime);
            WindowBlock(SynthMixBuffer + MixBufferPos);
            MixBufferPos += SubRet.PSOLAFrameHopSize;
            CurrentTime += (float)SubRet.PSOLAFrameHopSize / SampleRate;
        }

        //Mix
        Boost_FloatAddArr(SynthBuffer, SynthBuffer, SynthMixBuffer, MixBufferPos + CVE_FFTHalf);

        //Dump
        Ret.Finished = 0;
        Ret.Data = FloatMalloc(MixBufferPos);
        Ret.Length = MixBufferPos;
        Boost_FloatCopy(Ret.Data, SynthBuffer, Ret.Length);

        //Move
        Boost_FloatCopy(SynthBuffer, SynthBuffer + Ret.Length, CVE_FFTHalf);
        Boost_FloatSet(SynthBuffer + CVE_FFTHalf, 0, SampleRate * 1 - CVE_FFTHalf);

        CurrentSylIndex ++;
    }
    FDFrame_Dtor(& FVocalFrame);
    PSOLAFrame_Dtor(& TVocalFrame);
    return Ret;
}
