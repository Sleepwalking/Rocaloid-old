float* MainWave;
int MainWaveLen = 0;
float F0 = 0;

#include "../../../CVEDSP/Algorithm/Formant.h"
#include "../../../CVEDSP/Algorithm/BaseFreq.h"
#include "../../../CVEDSP/DSPBase/ControlPointFilter.h"
#include "../../../CVEDSP/DSPBase/Spectrum.h"
#include "../../../CVEDSP/DSPBase/Filter.h"
#include "../../../CVEDSP/DSPBase/Window.h"
#include "../../../CVEDSP/IntrinUtil/FloatArray.h"
#include "../../../RocaloidEngine/CVE3/DSPEx/LCFECSOLA.h"

#define FreqToIndex(x) ((x) * 1024 / SampleRate)

float DSP_Decay[2048];
float DSP_Filter0[1024];
float DSP_Filter1[1024];
float DSP_Filter2[1024];
float DSP_Filter3[1024];
float DSP_DecayLength = 0;

float DSP_S0[2048];
float DSP_S1[2048];
float DSP_S2[2048];
float DSP_S3[2048];
float DSP_S[2048];

float DSP_W[1024];

void SpectrumEnvelopeFromWave(float* Dest, float* Wave, float F0)
{
    float Hamming[1024];
    float TmpWave[1024];
    GenerateHamming(Hamming, 1024);
    Boost_FloatMulArr(TmpWave, Hamming, Wave, 1024);
    MagnitudeFromWave(TmpWave, TmpWave, 10);

    CPF EnvelopeFeature;
    CPF_Ctor(& EnvelopeFeature);
    CPF_AddControlFreq(& EnvelopeFeature, 0, 0);
    ExtractFormantCPF(& EnvelopeFeature, TmpWave, F0, 1024);
    CPF_Bake(Dest, & EnvelopeFeature, 512);
    CPF_Dtor(& EnvelopeFeature);
}

void GenerateSpectrum(WaveBox* Dest)
{
    int i;
    float TmpWave[1024];
    float AvgWave[1024];
    SetSampleRate(44100);
    Boost_FloatSet(AvgWave, 0, 1024);
    F0 = GetBaseFrequencyFromSpectrum(TmpWave, 80, 1500, 1024);
    qDebug() << "F0 = " << F0;
    for(i = 0; i < 5; i ++)
    {
        SpectrumEnvelopeFromWave(TmpWave, MainWave + MainWaveLen / 3 + i * 1024, F0);
        Boost_FloatAddArr(AvgWave, AvgWave, TmpWave, 1024);
    }

    if(DSP_DecayLength != 512)
    {
        DSP_DecayLength = 512;
        LCFECSOLAFilter_GenerateDecay(DSP_Decay, DSP_DecayLength);
        GenerateHanning(DSP_Filter0, FreqToIndex(1000));
        GenerateHanning(DSP_Filter1, FreqToIndex(1000));
        GenerateHanning(DSP_Filter2, FreqToIndex(1000));
        GenerateHanning(DSP_Filter3, FreqToIndex(2000));
    }
    Boost_FloatDivArr(TmpWave, AvgWave, DSP_Decay, 1024);
    Boost_FloatMul(TmpWave, TmpWave, 0.1, 1024);

    Dest -> LoadWave(TmpWave, 0);
    Dest -> Redraw();
}

void GenerateFilterStrength(float* Dest, float F0, float F1, float F2, float F3, float S0, float S1, float S2, float S3)
{
    int ResidualLength = FreqToIndex(LCFECSOLA_ResidualFreq);

    Boost_FloatSet(DSP_S0, 0, 512);
    Boost_FloatSet(DSP_S1, 0, 512);
    Boost_FloatSet(DSP_S2, 0, 512);
    Boost_FloatSet(DSP_S3, 0, 512);

    LCFECSOLAFilter_MoveWindow(DSP_S0, DSP_Filter0, F0, S0, 1000, 512);
    LCFECSOLAFilter_MoveWindow(DSP_S1, DSP_Filter1, F1, S1, 1000, 512);
    LCFECSOLAFilter_MoveWindow(DSP_S2, DSP_Filter2, F2, S2, 1000, 512);
    LCFECSOLAFilter_MoveWindow(DSP_S3, DSP_Filter3, F3, S3, 2000, 512);

    Boost_FloatAdd(DSP_S0, DSP_S0, 0.03, ResidualLength);
    Boost_FloatAdd(DSP_S1, DSP_S1, 0.03, ResidualLength);
    Boost_FloatAdd(DSP_S2, DSP_S2, 0.03, ResidualLength);
    Boost_FloatAdd(DSP_S3, DSP_S3, 0.03, ResidualLength);

    Boost_FloatSet(DSP_S, 0, ResidualLength);

    Boost_FloatAddArr(DSP_S, DSP_S, DSP_S0, ResidualLength);
    Boost_FloatAddArr(DSP_S, DSP_S, DSP_S1, ResidualLength);
    Boost_FloatAddArr(DSP_S, DSP_S, DSP_S2, ResidualLength);
    Boost_FloatAddArr(DSP_S, DSP_S, DSP_S3, ResidualLength);

    Boost_FloatMul(Dest, DSP_S, 0.3, 1024);
}
