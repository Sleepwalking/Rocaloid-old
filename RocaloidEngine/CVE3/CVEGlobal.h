#ifndef CVEGLOBAL_H
#define CVEGLOBAL_H

#include "RFILE3/CDT3/CDT3.h"
#include "RFILE3/CDT3/Demapper.h"

extern CDT3 CGDict;
extern CDTMappingQuerySpace CGQuerySpace;
extern float Hanning2048[];
extern float Hanning1024[];

extern void CVEGlobal_Init() __attribute((constructor));
extern void CVEGlobal_Exit() __attribute((destructor));

extern int CVEGlobal_LoadCDT(String* Path);

#define FreqToIndex2048(x) ((x) * 2048 / SampleRate)
#define FreqToIndex1024(x) ((x) * 1024 / SampleRate)

#define FloatMalloc(Size) (float*)malloc(sizeof(float) * Size)

#define CPF_Setup(Name)\
    CPF Name;\
    do\
    {\
        CPF_Ctor(& Name);\
        Name.UFreq = SampleRate / 2;\
        CPF_AddControlFreq(& Name, 0, 0);\
    } while(0)

#endif
