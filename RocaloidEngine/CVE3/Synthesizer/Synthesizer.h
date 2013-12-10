#ifndef SYNTHESIZER_H
#define SYNTHESIZER_H

#include "../../../RUtil/RUtil.h"
#include "../../RFILE3/CVS3/CVS3.h"
#include "SpeechMixer.h"

AutoClass
{
    SpeechMixer SubSynth;

    CVS3* VocalScript;
    float CurrentTime;
    int CurrentSylIndex;

    float* SynthBuffer;
    float* SynthMixBuffer;
    int BufferPos;
    int MixBufferPos;
} EndClass(Synthesizer);

typedef struct
{
    float* Data;
    int Length;
    int Finished;
} SynthesizerSendback;

extern void SynthesizerSendback_Free(SynthesizerSendback* Dest);

extern void Synthesizer_SetCVS(Synthesizer* Dest, CVS3* Src);
extern void Synthesizer_PrepareSynthesis(Synthesizer* Dest, int FromIndex);
extern SynthesizerSendback Synthesizer_Synthesis(Synthesizer* Dest);

#endif
