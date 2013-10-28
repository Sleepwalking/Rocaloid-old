#ifndef ALBLLOG_H
#define ALBLLOG_H

//Logs runtime information into Audacity label format.

#include "RUtil/RUtil.h"
#include <stdarg.h>

extern void ALblLog_Create(String* Dest);
extern void ALblLog_Print(const char* Format, ...);
extern void ALblLog_SetTime(float Time);
extern void ALblLog_Save();

#endif
