#include "Processor.h"
#include "../../../CVEDSP/IntrinUtil/FloatArray.h"
#include "../../../CVEDSP/Algorithm/BaseFreq.h"
#include "../../../CVEDSP/Algorithm/PSOLA.h"
#include "../../../CVEDSP/DSPBase/Spectrum.h"
#include "../../../CVEDSP/DSPBase/Filter.h"
#include "../../../CVEDSP/DSPBase/TDEffects.h"
#include "../../../CVEDSP/DFT/FFT.h"
#include "../../../CVEDSP/DSPBase/TDAnalysis.h"
#include "../../../CVEDSP/Plot.h"
#include "../../../CVEDSP/FrameProcessor.h"
#include "../../../CVEDSP/Interpolation.h"
#include "../../../RUtil/Misc/Converter.h"
#include "../../../RUtil/Misc/Math.h"
#include <malloc.h>
#include <string.h>
#include "math.h"

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

float F0Global;
float FactorGlobal;
float Spectrum[8192];

#define FreqToIndex(x) ((x) * Amount / SampleRate)
void Processor_Harmonicizer(float* Wave, int Power)
{
    int Amount = pow(2, Power);
    RFFT(ProcessorTmp_Re, ProcessorTmp_Im, Wave,  Power);
    MagnitudeFromComplex(Spectrum, ProcessorTmp_Re, ProcessorTmp_Im, Amount);
    float InstF0 = GetBaseFrequencyFromSpectrum2(Spectrum, 50, 1500, Amount);
    if(abs(InstF0 - F0Global) > 10)
        InstF0 = F0Global;
    else
        F0Global = InstF0;
    float MaxCorr = - 999;
    int Period = SampleRate / InstF0;
    //Get the accurate F0.
    int i, j;
    for(i = SampleRate / InstF0 * 0.85; i < SampleRate / InstF0 * 1.15; i ++)
    {
        float InstCorr = CorrelationAt(Wave, Wave + i, 1024);
        if(InstCorr > MaxCorr)
        {
            MaxCorr = InstCorr;
            Period = i;
        }
    }
    InstF0 = SampleRate / Period;
    //For each harmonic below 6000 Hz
    for(i = 0; i < 6000 / InstF0; i ++)
    {
        int LFreq = FreqToIndex(i * InstF0);
        int HFreq = FreqToIndex(i * InstF0 + InstF0);
        for(j = LFreq; j < (HFreq + LFreq) / 2; j ++)
        {
            float Factor = CosineInterpolate(1, FactorGlobal, (float)(j - LFreq) / FreqToIndex(InstF0 / 2.0));
            if(Factor < 0) Factor = 0;
            ProcessorTmp_Re[j] *= Factor;
            ProcessorTmp_Im[j] *= Factor;
        }
        for(; j < HFreq; j ++)
        {
            float Factor = CosineInterpolate(FactorGlobal, 1, (float)(j - LFreq) / FreqToIndex(InstF0) * 2.0 - 1.0);
            if(Factor < 0) Factor = 0;
            ProcessorTmp_Re[j] *= Factor;
            ProcessorTmp_Im[j] *= Factor;
        }
    }
    RIFFT(Wave, ProcessorTmp_Re, ProcessorTmp_Im, Power);
}

int Harmonicize(float* Wave, int Length, float Factor, float F0)
{
    SetSampleRate(44100);
    F0Global = F0;
    FactorGlobal = Factor;
    Process(Wave, Wave, Processor_Harmonicizer, 13, Length + 22050);
    return 1;
}

int PitchCorrect(float* Wave, int Length, float F0, float NewF0)
{
    PulseDescriptor PD;
    ArrayType_Ctor(PSOLAFrame, FrameStorage);
    ArrayType_Ctor(int32_t, OrigPulses);
    ArrayType_Ctor(int32_t, NewPulses);
    ArrayType_Resize(PSOLAFrame, FrameStorage, 5000);
    ArrayType_Resize(int32_t, OrigPulses, 5000);
    ArrayType_Resize(int32_t, NewPulses, 5000);
    int i;
    for(i = 0; i < 5000; i ++)
        PSOLAFrame_CtorSize(FrameStorage + i, 1024);
    FrameStorage_Index = 4999;

    float DestPeriod = (float)SampleRate / NewF0;
    memset(OrigPulses, 0, 4 * 5000);
    ExtractPulsesByBaseFrequency(OrigPulses, & PD, Wave, F0, Length);
    memcpy(NewPulses, OrigPulses, 4 * 5000);
    for(i = 1; i < PD.Amount; i ++)
        PSOLAFrame_SecureGet(FrameStorage + i, Wave, Length + 1000, OrigPulses[i]);
    printf("%d PSOLA frames extracted.\n", PD.Amount);
    if(PD.VoiceOnsetIndex == 0)
        PD.VoiceOnsetIndex = 1;
    for(i = PD.VoiceOnsetIndex; i < PD.Amount; i ++)
    {
        float InstPeriod = (float)(OrigPulses[i + 1] - OrigPulses[i - 1]) / 2.0;
        if(InstPeriod <= 0)
            InstPeriod = DestPeriod;
        NewPulses[i] = NewPulses[i - 1] + (OrigPulses[i] - OrigPulses[i - 1]) * DestPeriod / InstPeriod;
    }
    Boost_FloatSet(Wave, 0, Length + 1000);
    printf("Resynthesizing...\n");
    PSOLA_Regenesis(Wave, FrameStorage, NewPulses, OrigPulses, PD.Amount);

    ArrayType_ObjDtor(PSOLAFrame, FrameStorage);
    ArrayType_Dtor(PSOLAFrame, FrameStorage);
    ArrayType_Dtor(int32_t, OrigPulses);
    ArrayType_Dtor(int32_t, NewPulses);
    return 1;
}

float BaseFreqDetect(float* Wave, int Length)
{
    SetSampleRate(44100);
    float InstF0;
    ArrayType_Ctor(float, F0List);

    int i;
    for(i = 0; i < Length - 8192; i += 4096)
        if(Boost_FloatMax(Wave, i, i + 8192) > 0.003)
        {
            InstF0 = GetBaseFrequencyFromWave(Wave + i, 50, 1500, 13);
            ArrayType_Push(float, F0List, InstF0);
        }
    Math_FloatDecSort(F0List, F0List_Index + 1);
    float Ret = F0List[F0List_Index / 2];
    ArrayType_Dtor(float, F0List);
    return Ret;
}
