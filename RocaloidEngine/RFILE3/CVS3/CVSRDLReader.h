#ifndef CVSRDLREADER_H
#define CVSRDLREADER_H

#include "CVS3.h"
#include "../../../RUtil/RUtil.h"

extern int CVSRDLReader_Open(String* Src);
extern void CVSRDLReader_Close();

extern int TimeRatioPair_Read(TimeRatioPair* Dest);
extern int TimeFreqPair_Read(TimeFreqPair* Dest);
extern int TimeStrengthPair_Read(TimeStrengthPair* Dest);
extern int TimeVolumePair_Read(TimeVolumePair* Dest);

extern int FormantInfo_Read(FormantInfo* Dest);
extern int EffectInfo_Read(EffectInfo* Dest);
extern int Syllable_Read(Syllable* Dest);
extern int CVS3_Read(CVS3* Dest);

#endif
