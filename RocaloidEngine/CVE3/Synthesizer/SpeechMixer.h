#ifndef SPEECHMIXER_H
#define SPEECHMIXER_H

#include "../DSPInclude.h"
#include "../../RUtil/RUtil.h"
#include "../DSPEx/FDFrame.h"
#include "../CVEGlobal.h"
#include "../RFILE3/CVS3/CVS3.h"
#include "PitchMixer.h"

AutoClass
{
    PitchMixer SubSynth1;
    PitchMixer SubSynth2;

    int SubSynth1Index;
    int SubSynth2Index;
    float TransitionRatio;

    const Syllable* OnSynth;
} EndClass(SpeechMixer);

typedef struct
{
    FECSOLAState FState;
    int PSOLAFrameHopSize;
    int BeforeVOT;
} SpeechMixerSendback;

extern void SpeechMixer_SetSyllable(SpeechMixer* Dest, const Syllable* _Syllable);
extern void SpeechMixer_SetConsonantRatio(SpeechMixer* Dest, float CRatio);
extern void SpeechMixer_SetTime(SpeechMixer* Dest, float Time);
extern void SpeechMixer_Reset(SpeechMixer* Dest);

extern SpeechMixerSendback SpeechMixer_Synthesis(SpeechMixer* Dest, FDFrame* Output);

#endif
