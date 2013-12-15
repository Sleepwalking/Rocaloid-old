#ifndef ROUTINES_H
#define ROUTINES_H

#include "../../../RUtil/RUtil.h"

typedef int (*rFunc)();

extern String Dir;
extern String Dir_CVDB;
extern String Dir_BIN;
extern String Dir_FRAG;
extern String Dir_RAW;
extern String Dir_DEBUG;

extern int Config();
extern int GenSCONF();
extern int GenRecDictionary();
extern int Scan();
extern int Split();
extern int UpdateWCONF();
extern int Preprocess();
extern int GenCVDB();
extern int GenCDT();
extern int DebugWav();

#endif
