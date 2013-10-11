#ifndef CVEGLOBAL_H
#define CVEGLOBAL_H

#include "RFILE3/CDT3/CDT3.h"
#include "RFILE3/CDT3/Demapper.h"

extern CDT3 CGDict;
extern CDTMappingQuerySpace CGQuerySpace;

extern void CVEGlobal_Init() __attribute((constructor));
extern void CVEGlobal_Exit() __attribute((destructor));

extern int CVEGlobal_LoadCDT(String* Path);

#endif
