#ifndef INTERFACE_H
#define INTERFACE_H
#include "CVEDSP/Algorithm/FECSOLA.h"
/*
typedef struct FECSOLAState
{
    union {
        float array[12];

        struct {
            float F0; //Frequency of Formant 1
            float F1; //Frequency of Formant 2
            float F2; //Frequency of Formant 3
            float F3; //Frequency of Formant 4

            float L0; //Width of Formant 1
            float L1; //Width of Formant 2
            float L2; //Width of Formant 3
            float L3; //Width of Formant 4

            float S0; //Strength of Formant 1
            float S1; //Strength of Formant 2
            float S2; //Strength of Formant 3
            float S3; //Strength of Formant 4
        };
    };
} FECSOLAState;
*/
#ifdef __cplusplus
extern "C" {
#endif

void Test();

void LoadWav(float* wave, char channels, int sampleRate, unsigned long totalSamples);
FECSOLAState UpdateSpectrum1(float* DestArray, float* Src); // 512 floats
void UpdateSpectrum2(float* DestArray, FECSOLAState paramsBefore, FECSOLAState paramsAfter); // 512 floats
void Synthesis(float* DestWave, int sampleRate, FECSOLAState paramsBefore, FECSOLAState paramsAfter); // dest wave is 10 seconds

#ifdef __cplusplus
}
#endif

#endif // INTERFACE_H
