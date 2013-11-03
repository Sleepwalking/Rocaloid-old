#ifndef CVSRDLWRITER_H
#define CVSRDLWRITER_H

#include "CVS3.h"
#include "../RUtil/RUtil.h"

extern void CVSRDLWriter_Save();
extern void CVSRDLWriter_Write(String* Dest);

extern int TimeRatioPair_Write(TimeRatioPair* Src);
extern int TimeFreqPair_Write(TimeFreqPair* Src);
extern int TimeStrengthPair_Write(TimeStrengthPair* Src);
extern int TimeVolumePair_Write(TimeVolumePair* Src);

extern int FormantInfo_Write(FormantInfo* Src);
extern int EffectInfo_Write(EffectInfo* Src);
extern int Syllable_Write(Syllable* Src);
extern int CVS3_Write(CVS3* Src);

#endif
