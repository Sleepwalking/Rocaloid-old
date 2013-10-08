#ifndef TDATA_H
#define TDATA_H

#include "RUtil/RUtil.h"

AutoClass
{
    float BaseFreq;
    ArrayType_Define(float, Data);
} EndClass(Wave);

AutoClass
{
    ArrayType_Define(Wave, WaveList);
    ArrayType_Define(Wave, SpecList);
} EndClass(TData);

extern void TData_LoadFromString(TData* Dest, String* Src, int Size);

#endif
