#ifndef CVDB3IO_H
#define CVDB3IO_H

#include "../RUtil/IO/FileUtil.h"
#include "../RUtil/RUtil.h"
#include <stdint.h>

typedef struct
{
    char Identifier[4];
    uint16_t CVDBVersion;
    float F0;
    char Symbol[8];
    char Blank;
    char PhoneType;

    uint32_t PulseNum;
    uint32_t VOI;
    uint32_t WaveSize;

    float F1;
    float F2;
    float F3;
    float S1;
    float S2;
    float S3;
} CVDB3Header;

AutoClass
{
    CVDB3Header Header;
    uint32_t* PulseOffsets;
    float* Wave;
} EndClass(CVDB3);

extern void CVDB3_Load(CVDB3* Dest, String* Path);
extern void CVDB3_Write(String* Path, CVDB3* Src);

#endif
