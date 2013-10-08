#ifndef CSPR_H
#define CSPR_H

#include "RUtil/RUtil.h"
#include "CVEDSP/Algorithm/Formant.h"
#include "CVEANN/Network/FeedForward.h"
#include <stdint.h>

AutoClass
{
    char Header[4];
    uint16_t Version;
    float DividingFreq;
    int32_t ClassNum;

    ArrayType_Define(FormantDescriptor, FormantClasses);
    FeedForward FFNetLow;
    FeedForward FFNetHigh;
} EndClass(CSPR);

extern int CSPR_Load(CSPR* Dest, String* Path);
extern int CSPR_Save(CSPR* Dest, String* Path);

#endif
