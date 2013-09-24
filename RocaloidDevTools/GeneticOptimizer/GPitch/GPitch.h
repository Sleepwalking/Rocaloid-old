#ifndef GPITCH_H
#define GPITCH_H

#include "RUtil/RUtil.h"
#include "GeneticSimulator.h"

AutoClass
{
    float* Data;
    int Length;
} EndClass(GPWave);

extern void GPitch_LoadFileList(GeneticSimulator* Dest, String* Path);

extern void GPitch_SetParam(void* Src);
extern void GPitch_Run(void* Result, void* Task);
extern float GPitch_Eval(void* Desc1, void* Desc2);
extern void GPitch_Mutate(void* Param);
extern void GPitch_Display(void* Param);

#endif
