#include "Interface.h"
#include "malloc.h"
#include "CVEDSP/DSPBase/Spectrum.h"
#include "CVEDSP/DSPBase/Filter.h"
#include "CVEDSP/DSPBase/Window.h"
#include "CVEDSP/DSPBase/LPC.h"
#include "CVEDSP/IntrinUtil/FloatArray.h"
#include "CVEDSP/IntrinUtil/Calculation.h"
#include "CVEDSP/Algorithm/Formant.h"
#include "CVEDSP/Algorithm/FECSOLA.h"
#include "CVEDSP/Algorithm/PSOLA.h"
#include "CVEDSP/Algorithm/BaseFreq.h"
#include "CVEDSP/DFT/FFT.h"
#include "CVEDSP/Interpolation.h"
#include "RUtil/RUtil.h"

#include "QTau/qtau/editor/Utils.h"
float BF;
int Length;
int SampleRate;

int Pulses[5000];
PSOLAFrame PFrames[5000];
PSOLAFrame ModifiedPFrames[5000];
PulseDescriptor PD;

int FirstRun = 1;

float GraphFactor;

float* GW;

void LoadWav(float* wave, char channels, int sampleRate, unsigned long totalSamples)
{
    int i;
    if(channels == 1)
    {
        SampleRate = sampleRate;
        Length = totalSamples - SampleRate;
        SetSampleRate(sampleRate);

        BF = GetBaseFrequencyFromWave(wave + Length / 2, 80, 1500, 13);

        qDebug() << "Length:"           << Length;
        qDebug() << "Fundamental Freq:" << BF;

        if(FirstRun)
            GW = (float*)malloc(4 * Length * 10);
        Boost_FloatCopy(GW, wave, totalSamples);

        ExtractPulsesByBaseFrequency(Pulses, &PD, wave, BF, Length);
        qDebug() << PD.Amount << "pulses extracted.";
        qDebug() << "VOT:" << (float)Pulses[PD.VoiceOnsetIndex] / SampleRate;

        if (FirstRun)
        {
            for (i = 0;i < 5000; ++i)
                PSOLAFrame_Ctor(&PFrames[i], 1024);

            for (i = 0;i < 5000; ++i)
                PSOLAFrame_Ctor(&ModifiedPFrames[i], 1024);

            FirstRun = 0;
        }

        for (i = 0; i < PD.Amount; ++i)
            PSOLAFrame_SecureGet(&PFrames[i], wave, Pulses[i] + 1024, Pulses[i]);
    }
}

FECSOLAState UpdateSpectrum1(float* DestArray, float* Src)
{
    int i;
    float* InterArray = (float*)malloc(4 * 10240);
    FECSOLAState Ret;

    //FECSOLAState test;
    //AnalyzeFECSOLAState(& test, GW + Length / 2, BF, 1024);

    int PredictionLen = FormantEnvelopeFromWave(InterArray, GW + Length / 2, BF, 5000, 50, 10);
    FormantDescriptor Fmt = AnalyzeFormantFromEnvelope(InterArray, 1024);
    qDebug() << "F1 = " << Fmt.F1;
    qDebug() << "F2 = " << Fmt.F2;
    qDebug() << "F3 = " << Fmt.F3;
    Ret.F1 = Fmt.F1;
    Ret.F2 = Fmt.F2;
    Ret.F3 = Fmt.F3;

    for(i = 0;i < 512;i ++)
        DestArray[i] = InterArray[(int)(i * PredictionLen / 512)] * 3;

    MagnitudeFromWave(InterArray, GW + Length / 2, 10);
    Ret.S1 = Boost_Sqr(InterArray[(int)Fmt.F1 * 1024 / SampleRate]) * 20;
    Ret.S2 = Boost_Sqr(InterArray[(int)Fmt.F2 * 1024 / SampleRate]) * 20;
    Ret.S3 = Boost_Sqr(InterArray[(int)Fmt.F3 * 1024 / SampleRate]) * 20;

    DestArray[(int)(Ret.F1 * 512 / 5000)] = 4;
    DestArray[(int)(Ret.F2 * 512 / 5000)] = 4;
    DestArray[(int)(Ret.F3 * 512 / 5000)] = 4;

//    Boost_FloatSet(DestArray, 0, 512);
    Boost_FloatMul(DestArray, DestArray, -0.5, 512);
    Boost_FloatAdd(DestArray, DestArray, 0.9, 512);
    free(InterArray);
    return Ret;
}

void UpdateSpectrum2(float* DestArray, FECSOLAState paramsBefore, FECSOLAState paramsAfter)
{
    int i;
    float max = -999;
    FECSOLAFilter FormantFilter;
    FECSOLAFilter_CtorSize(&FormantFilter, 2048);
    CPF FormantCPF;
    CPF_Ctor(&FormantCPF);
    FormantCPF.UFreq = SampleRate / 2;
    CPF_AddControlFreq(& FormantCPF, 0, 0);

    paramsBefore.F0 = BF;
    paramsBefore.S0 = 1;
    paramsAfter.F0 = BF;
    paramsAfter.S0 = 1;

    float* Window = (float*)malloc(4 * 1024);
    float* InterArray = (float*)malloc(4 * 1024);
    GenerateHamming(Window, 1024);
    Boost_FloatMulArr(Window, Window, PFrames[PD.Amount / 2].Data, 1024);
    MagnitudeFromWave(InterArray, Window, 10);

    ExtractFormantCPF(& FormantCPF, InterArray, BF, 1024);
    Boost_FloatSet(Window, 0, 512);
    CPF_Bake(Window, & FormantCPF, 512);
    Boost_FloatAdd(Window, Window, 0.1, 512);
    Boost_FloatDivArr(InterArray, InterArray, Window, 512);

    FECSOLAFilter_GetFromFormantEnvelope(&FormantFilter, &FormantCPF, &paramsBefore);
    Boost_FloatSet(Window, 0, 512);
    FECSOLAFilter_Bake(Window, &FormantFilter, &paramsAfter, 1024);

    Boost_FloatMulArr(InterArray, InterArray, Window, 512);

    for(i = 0;i < 512;i ++)
        InterArray[i] = Window[i];//Boost_Ln(Window[i]) + 5;

    for(i = 0;i < 512;i ++)
    {
        if(InterArray[i] > max)
            max = InterArray[i];
    }

    for(i = 0;i < 512;i ++)
        DestArray[i] = InterArray[i / 4] / max * 3;

    Boost_FloatMul(DestArray, DestArray, -0.5, 512);
    Boost_FloatAdd(DestArray, DestArray, 0.9, 512);

    CPF_Dtor(&FormantCPF);
    FECSOLAFilter_Dtor(&FormantFilter);
    free(InterArray);
    free(Window);
}

float FRe[1024];
float FIm[1024];
float Magnitude[1024];
float Windowed[1024];
float Envelope[1024];
float ModifiedEnvelope[1024];
void Synthesis(float* DestWave, int sampleRate, FECSOLAState paramsBefore, FECSOLAState paramsAfter)
{
    int i;

    FECSOLAFilter FormantFilter;
    FECSOLAFilter_CtorSize(&FormantFilter, 2048);
    CPF FormantCPF;
    CPF_Ctor(&FormantCPF);
    FormantCPF.UFreq = SampleRate / 2;
    CPF_AddControlFreq(& FormantCPF, 0, 0);

    paramsBefore.F0 = BF;
    paramsBefore.S0 = 1;
    paramsAfter.F0 = BF;
    paramsAfter.S0 = 1;

    float* Window = (float*)malloc(4 * 1024);
    GenerateHamming(Window, 1024);

    Boost_FloatSet(DestWave, 0, Length + SampleRate);

    for(i = 0;i < PD.Amount; i++)
    {
        FormantCPF.ControlPointList_Index = - 1;
        CPF_AddControlFreq(& FormantCPF, 0, 0);

        ApplyWindow(Windowed, PFrames[i].Data, Window, 0, 1024);
        RFFT(FRe, FIm, Windowed, 10);

        MagnitudeFromComplex(Magnitude, FRe, FIm, 1024);

        ExtractFormantCPF(&FormantCPF, Magnitude, BF, 1024);
        CPF_Bake(Envelope, &FormantCPF, 512);

        Boost_FloatAdd(Envelope, Envelope, 0.1, 512);
        Boost_FloatDivArr(FRe, FRe, Envelope, 512);
        Boost_FloatDivArr(FIm, FIm, Envelope, 512);

        FECSOLAFilter_GetFromFormantEnvelope(&FormantFilter, &FormantCPF, &paramsBefore);
        FECSOLAFilter_Bake(ModifiedEnvelope, &FormantFilter, &paramsAfter, 1024);

        Boost_FloatCopy(ModifiedEnvelope + 139, Envelope + 139, 512 - 139);
        //int j;
        //for(j = 0;j < BF * 1024 / SampleRate;j ++)
        //    ModifiedEnvelope[j] = 0;

        Boost_FloatMulArr(FRe, FRe, ModifiedEnvelope, 512);
        Boost_FloatMulArr(FIm, FIm, ModifiedEnvelope, 512);
        Reflect(FRe, FIm, FRe, FIm, 10);

        RIFFT(Windowed, FRe, FIm, 10);

        Boost_FloatDivArr(ModifiedPFrames[i].Data, Windowed, Window, 1024);
    }

    PSOLA_Regenesis(DestWave, ModifiedPFrames, Pulses, Pulses, PD.Amount);

    CPF_Dtor(&FormantCPF);
    FECSOLAFilter_Dtor(&FormantFilter);
    free(Window);
}
