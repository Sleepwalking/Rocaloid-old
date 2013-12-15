#ifndef SPLITER_H
#define SPLITER_H

#include "../../../RUtil/RUtil.h"
#include "../TCFILE/SCONF.h"
#include "../TCFILE/WCONF.h"
#include "../TCFILE/CDS.h"

extern float BaseFreqDetect(float* Wave, int Length, float LowFreq);
extern int WSplit(WCONF* Dest, String* FragPath, SCONF* Src, CDS* Scheme, String* Raw);

#endif
