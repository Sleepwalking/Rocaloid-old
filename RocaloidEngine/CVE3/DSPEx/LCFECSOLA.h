#ifndef LCFECSOLA_H
#define LCFECSOLA_H

//Linear Combination - Formant Envelope Components Shift and OverLap Add

#include "../../RUtil/RUtil.h"
#include "../CVEGlobal.h"
#include "../DSPInclude.h"

#define LCFECSOLA_ResidualFreq 5000

AutoClass
{
    float* F0Env;
    float* F1Env;
    float* F2Env;
    float* F3Env;
    float* ResidualEnv;

    FECSOLAState OrigState;
    int Length;
} EndClass(LCFECSOLAFilter);

extern void LCFECSOLAFilter_CtorSize(LCFECSOLAFilter* Dest, int Length);
extern void LCFECSOLAFilter_GetFromCPF(LCFECSOLAFilter* Dest, CPF* Src, FECSOLAState* FState);
extern void LCFECSOLAFilter_GetFromFormantEnvelope(LCFECSOLAFilter* Dest, float* Src, FECSOLAState* FState);
extern void LCFECSOLAFilter_Bake(float* Dest, LCFECSOLAFilter* Src, FECSOLAState* FState);

#endif
