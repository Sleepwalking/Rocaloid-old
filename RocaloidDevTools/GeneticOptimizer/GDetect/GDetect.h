#ifndef GDETECT_H
#define GDETECT_H

#include "../RUtil/RUtil.h"
#include "../GeneticSimulator.h"

AutoClass
{
    float* Data;
    int Length;
} EndClass(GDWave);

extern void GDetect_LoadFileList(GeneticSimulator* Dest, String* Path);

extern void GDetect_SetParam(void* Src);
extern void GDetect_Run(void* Result, void* Task);
extern float GDetect_Eval(void* Desc1, void* Desc2);
extern void GDetect_Mutate(void* Param);
extern void GDetect_Display(void* Param);

#endif
