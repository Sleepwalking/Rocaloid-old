#ifndef CSYNTH_H
#define CSYNTH_H

//Consecutive Synthesizer
#include "RUtil/RUtil.h"
#include "RFILE3/CVDB3/CVDB3IO.h"
#include "DSPInclude.h"

AutoClass
{
    String Symbol;
    unsigned int PlayIndex;
    unsigned int PlayPosition;
    float ConsonantRatio;
    CVDB3 Data;

    //Synth Control
    unsigned int CycleStart;
    unsigned int CycleLength;
} EndClass(CSynth);

typedef struct
{
    unsigned int PSOLAFrameLength;
} CSynthSendback;

extern void CSynth_SetSymbol(CSynth* Dest, String* Symbol);
extern void CSynth_SetConsonantRatio(CSynth* Dest, float CRatio);
extern void CSynth_Reset(CSynth* Dest);

extern CSynthSendback CSynth_Synthesis(CSynth* Dest, PSOLAFrame* Output);
extern float CSynth_GetVOT(CSynth* Dest);

#endif
