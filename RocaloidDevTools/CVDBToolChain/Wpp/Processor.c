#include "Processor.h"
#include "../../../CVEDSP/IntrinUtil/FloatArray.h"
#include "../../../CVEDSP/Algorithm/BaseFreq.h"
#include "../../../CVEDSP/DSPBase/Spectrum.h"
#include "../../../CVEDSP/DSPBase/Filter.h"
#include "../../../CVEDSP/DSPBase/TDEffects.h"
#include "../../../CVEDSP/FrameProcessor.h"
#include "../../../RUtil/Misc/Converter.h"
#include <malloc.h>

int Balance(float* Wave, int Length)
{
    float* AveragedWave = (float*)malloc(sizeof(float) * Length);
    MovingAverage(AveragedWave, Wave, 1, 1000, Length);
    Boost_FloatSubArr(Wave, Wave, AveragedWave, Length);
    free(AveragedWave);
    return 1;
}

#define Step 1000
#define HalfStep 500
int Normalize(float* Wave, int Length, float Magnitude)
{
    // 0(Copy) 1       2       3       4       5
    //     0       1       2       3       4
    //     |       |       |       |       |
    // |   |   |   |   |   |   |   |   |   |   |
    //---------------------------------------------
    int i, j;
    float Min, Max, Factor;
    ArrayType_Ctor(float, Level);
    for(i = HalfStep; i < Length - HalfStep; i += Step)
    {
        Min = Boost_FloatMin(Wave, i, i + Step);
        Max = Boost_FloatMax(Wave, i, i + Step);
        if(i == HalfStep)
            ArrayType_Push(float, Level, Max - Min);
        ArrayType_Push(float, Level, Max - Min);
    }
    for(i = 0; i < Level_Index - 1; i ++)
    {
        for(j = 0; j < Step; j ++)
        {
            Factor = Level[i] * (1.0f - (float)j / Step) + Level[i + 1] * j / Step;
            Wave[i * Step + j] *= Magnitude / (Factor > Magnitude ? Factor : Magnitude);
        }
    }
    ArrayType_Dtor(float, Level);
    return 1;
}

int LPF(float* Wave, int Length, float Frequency)
{
    SetSampleRate(44100);
    GenerateLowPass(ProcessorTmp_Filter, Frequency, 512);
    Process(Wave, Wave, Processor_Filter, 10, Length);
    return 1;
}

int HPF(float* Wave, int Length, float Frequency)
{
    SetSampleRate(44100);
    GenerateHighPass(ProcessorTmp_Filter, Frequency, 512);
    Process(Wave, Wave, Processor_Filter, 10, Length);
    return 1;
}
