#include "LCFECSOLA.h"
#include "../CVEDSP/Plot.h"

float Decay[2048];
float Filter0[1024];
float Filter1[1024];
float Filter2[1024];
float Filter3[1024];
float DecayLength = 0;

float S0[2048];
float S1[2048];
float S2[2048];
float S3[2048];
float S[2048];

float W[1024];
float W0[1024];
float W1[1024];

_Constructor_ (LCFECSOLAFilter)
{
    LCFECSOLAFilter_CtorSize(Dest, 512);
}

_Destructor_ (LCFECSOLAFilter)
{
    free(Dest -> F0Env);
    free(Dest -> F1Env);
    free(Dest -> F2Env);
    free(Dest -> F3Env);
    free(Dest -> ResidualEnv);
}

void LCFECSOLAFilter_GenerateDecay(float* Dest, int Size)
{
    int i;
    for(i = 0; i < Size; i ++)
    {
        float x = i * SampleRate / 1024;
        float x2 = x * x;
        float x3 = x2 * x;
        float x4 = x3 * x;
        float x5 = x4 * x;
        Dest[i] = 4.99789 + 0.00650003 * x - 8.17401e-6 * x2 + 3.00586e-9 * x3 - 4.61453e-13 * x4 + 2.5687e-17 * x5;
        if(Dest[i] < 0.01)
            Dest[i] = 0.01;
    }
}

void LCFECSOLAFilter_CtorSize(LCFECSOLAFilter* Dest, int Length)
{
    Dest -> Length = Length;
    Dest -> F0Env = FloatMalloc(Dest -> Length);
    Dest -> F1Env = FloatMalloc(Dest -> Length);
    Dest -> F2Env = FloatMalloc(Dest -> Length);
    Dest -> F3Env = FloatMalloc(Dest -> Length);
    Dest -> ResidualEnv = FloatMalloc(Dest -> Length);
    Boost_FloatSet(Dest -> F0Env, 0, Dest -> Length);
    Boost_FloatSet(Dest -> F1Env, 0, Dest -> Length);
    Boost_FloatSet(Dest -> F2Env, 0, Dest -> Length);
    Boost_FloatSet(Dest -> F3Env, 0, Dest -> Length);
}

#define FreqToIndex(x) ((x) * DestLen * 2 / SampleRate)
void LCFECSOLAFilter_MoveWindow(float* Dest, float* Window, float Freq, float Weight, float FWidth, int DestLen)
{
    Boost_FloatSet(W0, 0, DestLen);
    Boost_FloatSet(W1, 0, DestLen);
    if(Freq - FWidth / 2 < 0)
    {
        //       ^
        //       | F
        //       | |
        // |-------|-------|
        //.......0-|------------------->
        float MoveSrc = FreqToIndex(FWidth / 2 - Freq);
        Boost_FloatMul(W0, Window + (int)(MoveSrc + 0.0), Weight * (1.0 - (MoveSrc - floor(MoveSrc))), (int)FreqToIndex(Freq + FWidth / 2.0));
        Boost_FloatMul(W1, Window + (int)(MoveSrc + 1.0), Weight * (0.0 + (MoveSrc - floor(MoveSrc))), (int)FreqToIndex(Freq + FWidth / 2.0));
    }else
    {
        //       ^
        //       |           F
        //       |           |
        //       |   |-------|-------|
        //.......0-----------|------------>
        float MoveDest = FreqToIndex(Freq - FWidth / 2);
        Boost_FloatMul(W0 + (int)(MoveDest + 0.0), Window, Weight * (1.0 - (MoveDest - floor(MoveDest))), (int)FreqToIndex(FWidth));
        Boost_FloatMul(W1 + (int)(MoveDest + 1.0), Window, Weight * (0.0 + (MoveDest - floor(MoveDest))), (int)FreqToIndex(FWidth));
    }
    Boost_FloatAddArr(Dest, Dest, W0, DestLen);
    Boost_FloatAddArr(Dest, Dest, W1, DestLen);
}

int Debug = 0;
void LCFECSOLAFilter_MoveSubEnv(float* Dest, float* Env, float DeltaFreq, float Weight, int DestLen)
{
    Boost_FloatSet(W0, 0, DestLen);
    Boost_FloatSet(W1, 0, DestLen);
    if(FreqToIndex(DeltaFreq) < 0)
    {
        float MoveSrc = - FreqToIndex(DeltaFreq);
        Boost_FloatMul(W0, Env + (int)(MoveSrc) + 0, Weight * (1.0 - (MoveSrc - floor(MoveSrc))), DestLen - (int)(MoveSrc) - 0);
        Boost_FloatMul(W1, Env + (int)(MoveSrc) + 1, Weight * (0.0 + (MoveSrc - floor(MoveSrc))), DestLen - (int)(MoveSrc) - 1);
    }else
    {
        float MoveDest = FreqToIndex(DeltaFreq);
        Boost_FloatMul(W0 + (int)(MoveDest) + 0, Env, Weight * (1.0 - (MoveDest - floor(MoveDest))), DestLen - (int)(MoveDest) - 0);
        Boost_FloatMul(W1 + (int)(MoveDest) + 1, Env, Weight * (0.0 + (MoveDest - floor(MoveDest))), DestLen - (int)(MoveDest) - 1);
    }
    Boost_FloatAddArr(Dest, Dest, W0, DestLen);
    Boost_FloatAddArr(Dest, Dest, W1, DestLen);
}

#undef FreqToIndex

#define FreqToIndex(x) ((x) * Dest -> Length * 2 / SampleRate)
void LCFECSOLAFilter_GetFromCPF(LCFECSOLAFilter* Dest, CPF* Src, FECSOLAState* FState)
{
    float* E = FloatMalloc(Dest -> Length);
    CPF_Bake(E, Src, Dest -> Length);
    LCFECSOLAFilter_GetFromFormantEnvelope(Dest, E, FState);
    free(E);
}

void LCFECSOLAFilter_GetFromFormantEnvelope(LCFECSOLAFilter* Dest, float* Src, FECSOLAState* FState)
{
    Dest -> OrigState = *FState;
    int ResidualLength = FreqToIndex(LCFECSOLA_ResidualFreq);

    Boost_FloatSet(S0, 0, Dest -> Length);
    Boost_FloatSet(S1, 0, Dest -> Length);
    Boost_FloatSet(S2, 0, Dest -> Length);
    Boost_FloatSet(S3, 0, Dest -> Length);

    if(DecayLength != Dest -> Length)
    {
        DecayLength = Dest -> Length;
        LCFECSOLAFilter_GenerateDecay(Decay, DecayLength);
        GenerateHanning(Filter0, FreqToIndex(LCFECSOLA_L0));
        GenerateHanning(Filter1, FreqToIndex(LCFECSOLA_L1));
        GenerateHanning(Filter2, FreqToIndex(LCFECSOLA_L2));
        GenerateHanning(Filter3, FreqToIndex(LCFECSOLA_L3));
    }
    Boost_FloatDivArr(W, Src, Decay, Dest -> Length);

    LCFECSOLAFilter_MoveWindow(S0, Filter0, FState -> F0, FState -> S0, LCFECSOLA_L0, Dest -> Length);
    LCFECSOLAFilter_MoveWindow(S1, Filter1, FState -> F1, FState -> S1, LCFECSOLA_L1, Dest -> Length);
    LCFECSOLAFilter_MoveWindow(S2, Filter2, FState -> F2, FState -> S2, LCFECSOLA_L2, Dest -> Length);
    LCFECSOLAFilter_MoveWindow(S3, Filter3, FState -> F3, FState -> S3, LCFECSOLA_L3, Dest -> Length);

    Boost_FloatAdd(S0, S0, LCFECSOLA_SMinimum, ResidualLength);
    Boost_FloatAdd(S1, S1, LCFECSOLA_SMinimum, ResidualLength);
    Boost_FloatAdd(S2, S2, LCFECSOLA_SMinimum, ResidualLength);
    Boost_FloatAdd(S3, S3, LCFECSOLA_SMinimum, ResidualLength);

    Boost_FloatSet(S, 0, ResidualLength);
    Boost_FloatAddArr(S, S, S0, ResidualLength);
    Boost_FloatAddArr(S, S, S1, ResidualLength);
    Boost_FloatAddArr(S, S, S2, ResidualLength);
    Boost_FloatAddArr(S, S, S3, ResidualLength);

    Boost_FloatDivArr(S0, S0, S, ResidualLength);
    Boost_FloatDivArr(S1, S1, S, ResidualLength);
    Boost_FloatDivArr(S2, S2, S, ResidualLength);
    Boost_FloatDivArr(S3, S3, S, ResidualLength);

    Boost_FloatMulArr(Dest -> F0Env, S0, W, ResidualLength);
    Boost_FloatMulArr(Dest -> F1Env, S1, W, ResidualLength);
    Boost_FloatMulArr(Dest -> F2Env, S2, W, ResidualLength);
    Boost_FloatMulArr(Dest -> F3Env, S3, W, ResidualLength);


    Boost_FloatDiv(Dest -> F0Env, Dest -> F0Env, FState -> S0, ResidualLength);
    Boost_FloatDiv(Dest -> F1Env, Dest -> F1Env, FState -> S1, ResidualLength);
    Boost_FloatDiv(Dest -> F2Env, Dest -> F2Env, FState -> S2, ResidualLength);
    Boost_FloatDiv(Dest -> F3Env, Dest -> F3Env, FState -> S3, ResidualLength);

    Boost_FloatCopy(Dest -> ResidualEnv, W, Dest -> Length);
}

#undef  FreqToIndex
#define FreqToIndex(x) ((x) * Src -> Length * 2 / SampleRate)
void LCFECSOLAFilter_Bake(float* Dest, LCFECSOLAFilter* Src, FECSOLAState* FState)
{

    int ResidualLength = FreqToIndex(LCFECSOLA_ResidualFreq);
    Boost_FloatCopy(Dest, Src -> ResidualEnv, Src -> Length);
    Boost_FloatSet(Dest, 0, ResidualLength);
    LCFECSOLAFilter_MoveSubEnv(Dest, Src -> F2Env, FState -> F2 - Src -> OrigState.F2, FState -> S2, Src -> Length);
    LCFECSOLAFilter_MoveSubEnv(Dest, Src -> F0Env, FState -> F0 - Src -> OrigState.F0, FState -> S0, Src -> Length);
    LCFECSOLAFilter_MoveSubEnv(Dest, Src -> F1Env, FState -> F1 - Src -> OrigState.F1, FState -> S1, Src -> Length);
    LCFECSOLAFilter_MoveSubEnv(Dest, Src -> F3Env, FState -> F3 - Src -> OrigState.F3, FState -> S3, Src -> Length);
/*
        if(Src -> OrigState.F2 > 1900)
        {
            GNUPlot_PlotFloat(Dest, 120);
            WaitForDraw(15000);
            //GNUPlot_PlotFloat(W, 120);
            //getchar();
        }
*/
    Boost_FloatMulArr(Dest, Dest, Decay, Src -> Length);
}
