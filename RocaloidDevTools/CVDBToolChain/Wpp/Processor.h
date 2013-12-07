#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "../../../RUtil/RUtil.h"

extern int Balance(float* Wave, int Length);
extern int Normalize(float* Wave, int Length, float Magnitude);
extern int LPF(float* Wave, int Length, float Frequency);
extern int HPF(float* Wave, int Length, float Frequency);
extern int Harmonicize(float* Wave, int Length, float Factor, float F0);
extern int PitchCorrect(float* Wave, int Length, float F0, float NewF0);

extern float BaseFreqDetect(float* Wave, int Length);

#endif
