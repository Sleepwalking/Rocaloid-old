#ifndef FSYNTH_H
#define FSYNTH_H

//Tone(Freq) Synthesizer

#include "../../RUtil/RUtil.h"
#include "../DSPInclude.h"
#include "../DSPEx/FDFrame.h"
#include "CSynth.h"

#define FSynth_ConsonantTransition 1000

AutoClass
{
    CSynth SubSynth;
    float SynthFreq;
} EndClass(FSynth);

typedef struct
{
    int PSOLAFrameHopSize;
    int BeforeVOT;
    FECSOLAState FState;
} FSynthSendback;

extern void FSynth_SetSymbol(FSynth* Dest, String* Symbol);
extern void FSynth_SetConsonantRatio(FSynth* Dest, float CRatio);
extern void FSynth_SetVowelRatio(FSynth* Dest, float VRatio);
extern void FSynth_Reset(FSynth* Dest);
extern void FSynth_SetFrequency(FSynth* Dest, float Freq);

extern FSynthSendback FSynth_Synthesis(FSynth* Dest, FDFrame* Output);
extern float FSynth_GetVOT(FSynth* Dest);

#endif
