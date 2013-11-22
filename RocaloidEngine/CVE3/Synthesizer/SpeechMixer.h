#ifndef SPEECHMIXER_H
#define SPEECHMIXER_H

#include "../../RUtil/RUtil.h"
#include "../RFILE3/CVS3/CVS3.h"
#include "../DSPInclude.h"
#include "../DSPEx/FDFrame.h"
#include "../CVEGlobal.h"
#include "PitchMixer.h"
#include "SyllableVariator.h"

AutoClass
{
    PitchMixer SubSynth1;
    PitchMixer SubSynth2;

    int SubSynth1Index;
    int SubSynth2Index;
    float TransitionRatio;

    float CurrentTime;
    SyllableVariator CurrentVar;
    Syllable* CurrentSyl;
} EndClass(SpeechMixer);

typedef struct
{
    FECSOLAState FState;
    int PSOLAFrameHopSize;
    int BeforeVOT;
} SpeechMixerSendback;

extern void SpeechMixer_SetSyllable(SpeechMixer* Dest, Syllable* _Syllable);
extern void SpeechMixer_SetConsonantRatio(SpeechMixer* Dest, float CRatio);
extern void SpeechMixer_SetTime(SpeechMixer* Dest, float Time);
extern void SpeechMixer_Reset(SpeechMixer* Dest);

extern SpeechMixerSendback SpeechMixer_Synthesis(SpeechMixer* Dest, FDFrame* Output);

#endif
