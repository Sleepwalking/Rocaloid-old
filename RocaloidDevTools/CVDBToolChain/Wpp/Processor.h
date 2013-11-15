#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../../../RUtil/RUtil.h"

extern int Balance(float* Wave, int Length);
extern int Normalize(float* Wave, int Length, float Magnitude);
extern int LPF(float* Wave, int Length, float Frequency);
extern int HPF(float* Wave, int Length, float Frequency);

#endif
