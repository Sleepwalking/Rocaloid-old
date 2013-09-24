#ifndef GFORMANT_H
#define GFORMANT_H

#include "RUtil/RUtil.h"
#include "GeneticSimulator.h"

AutoClass
{
    float* Data;
    float BaseFreq;
    int Length;
} EndClass(Wave);

extern void GFormant_LoadFileList(GeneticSimulator* Dest, String* Path);

extern float Random();

extern void GFormant_SetParam(void* Src);
extern void GFormant_Run(void* Result, void* Task);
extern float GFormant_Eval(void* Desc1, void* Desc2);
extern void GFormant_Mutate(void* Param);
extern void GFormant_Display(void* Param);

extern float WeightItg(float* Src, int From, int To);

#endif
