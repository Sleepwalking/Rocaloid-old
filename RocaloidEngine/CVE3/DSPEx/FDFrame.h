#ifndef FDFRAME_H
#define FDFRAME_H

#include "../../RUtil/RUtil.h"
#include "../DSPInclude.h"

AutoClass
{
    float* Re;
    float* Im;
    int Length;
} EndClass(FDFrame);

extern void FDFrame_CtorSize(FDFrame* Dest, int Size);
extern void FDFrame_Resize(FDFrame* Dest, int Size);

extern int FDFrame_FromPSOLAFrame(FDFrame* Dest, PSOLAFrame* Src);
extern int PSOLAFrame_FromFDFrame(PSOLAFrame* Dest, FDFrame* Src);

#endif
