#ifndef PITCHMIXER_H
#define PITCHMIXER_H

#include "../DSPInclude.h"
#include "../../RUtil/RUtil.h"
#include "../DSPEx/FDFrame.h"
#include "../CVEGlobal.h"
#include "FSynth.h"

AutoClass
{
    FSynth SubSynth1;
    FSynth SubSynth2;
    float SynthFreq;
    String Phone;

    int SubSynth1Index;
    int SubSynth2Index;
    float TransitionRatio;
    int ForwardTransition;
    FormantLayerPartialEntry* Entry1;
    FormantLayerPartialEntry* Entry2;

    float LimitedFreq;
    int IsLimitedFreq;
} EndClass(PitchMixer);

typedef struct
{
    FECSOLAState FState;
    float PSOLAFrameHopSize;
    int BeforeVOT;
} PitchMixerSendback;

extern void PitchMixer_SetSymbol(PitchMixer* Dest, String* Symbol);
extern void PitchMixer_SetConsonantRatio(PitchMixer* Dest, float CRatio);
extern void PitchMixer_SetVowelRatio(PitchMixer* Dest, float VRatio);
extern void PitchMixer_SetSkipTime(PitchMixer* Dest, float STime);
extern void PitchMixer_Reset(PitchMixer* Dest);
extern void PitchMixer_SetFrequency(PitchMixer* Dest, float Freq);
extern void PitchMixer_SetLimitedFrequency(PitchMixer* Dest, float Freq);

extern PitchMixerSendback PitchMixer_Synthesis(PitchMixer* Dest, FDFrame* Output);
extern PitchMixerSendback PitchMixer_EmptySynthesis(PitchMixer* Dest);
extern float PitchMixer_GetVOT(PitchMixer* Dest);

#endif
