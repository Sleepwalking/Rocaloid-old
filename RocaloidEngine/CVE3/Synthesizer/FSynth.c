#include "FSynth.h"
#include "CVEDSP/DFT/FFT.h"
#include "CVEDSP/Algorithm/Formant.h"
#include "CVEGlobal.h"
#include "CVEDSP/Interpolation.h"

#define FSynth_ConsonantTransition 1000

_Constructor_ (FSynth)
{
    CSynth_Ctor(& Dest -> SubSynth);
    Dest -> SynthFreq = 500;
}

_Destructor_ (FSynth)
{
    CSynth_Dtor(& Dest -> SubSynth);
}

void FSynth_SetSymbol(FSynth* Dest, String* Symbol)
{
    CSynth_SetSymbol(& Dest -> SubSynth, Symbol);
    Dest -> SynthFreq = Dest -> SubSynth.Data.Header.F0;
}

void FSynth_SetConsonantRatio(FSynth* Dest, float CRatio)
{
    CSynth_SetConsonantRatio(& Dest -> SubSynth, CRatio);
}

void FSynth_SetVowelRatio(FSynth* Dest, float VRatio)
{
    CSynth_SetVowelRatio(& Dest -> SubSynth, VRatio);
}

void FSynth_Reset(FSynth* Dest)
{
    CSynth_Reset(& Dest -> SubSynth);
    Dest -> SynthFreq = Dest -> SubSynth.Data.Header.F0;
}

void FSynth_SetFrequency(FSynth* Dest, float Freq)
{
    Dest -> SynthFreq = Freq;
}

void FSynth_Resample(PSOLAFrame* Dest, PSOLAFrame* Src, float Ratio)
{
    int i;
    float Offset;
    int SrcHalf = Src -> Length / 2;
    float* Center = Src -> Data + SrcHalf;
    for(i = 0; i < Dest -> Length; i ++)
    {
        Offset = (float)(i - Dest -> Length / 2) * Ratio;
        if(Offset > - SrcHalf && Offset < SrcHalf)
        {
            //In Src range: linear interpolation.
            int LOffset;
            LOffset = (int)(Offset + SrcHalf) - SrcHalf;
            Dest -> Data[i] = LinearInterpolate(Center[LOffset], Center[LOffset + 1], Offset - LOffset);
        }else
        {
            //Beyond Src range.
            Dest -> Data[i] = 0;
        }
    }
}

#define FreqToIndex2048(x) ((x) * 2048 / SampleRate)
#define FreqToIndex1024(x) ((x) * 1024 / SampleRate)

void QuadHPF(float* Dest, float Freq)
{
    int i;
    float UFreq = FreqToIndex1024(Freq);
    for(i = 0; i < FreqToIndex1024(Freq); i ++)
        Dest[i] *= i * i / UFreq / UFreq;
}

FSynthSendback FSynth_Synthesis(FSynth* Dest, FDFrame* Output)
{
    FSynthSendback Ret;
    PSOLAFrame BFWave;
    PSOLAFrame_CtorSize(& BFWave, 2048);
    PSOLAFrame TempWave;
    PSOLAFrame_CtorSize(& TempWave, 1024);

    float BF = Dest -> SubSynth.Data.Header.F0;
    CSynth_SetVowelRatio(& Dest -> SubSynth, Dest -> SynthFreq / BF);
    CSynthSendback SubRet = CSynth_Synthesis(& Dest -> SubSynth, & BFWave);
    Ret.BeforeVOT = SubRet.BeforeVOT;

    CPF OrigEnv;
    CPF_Ctor(& OrigEnv);
    OrigEnv.UFreq = SampleRate / 2;
    CPF_AddControlFreq(& OrigEnv, 0, 0);
    float* OrigRe = (float*)malloc(sizeof(float) * 2048);
    float* OrigIm = (float*)malloc(sizeof(float) * 2048);
    float* OrigMa = (float*)malloc(sizeof(float) * 2048);
    float* Orig = (float*)malloc(sizeof(float) * 2048);

    Boost_FloatMulArr(Orig, BFWave.Data, Hamming2048, 2048);
    RFFT(OrigRe, OrigIm, BFWave.Data, 11);
    MagnitudeFromComplex(OrigMa, OrigRe, OrigIm, 2048);
    ExtractFormantCPF(& OrigEnv, OrigMa, BF, 2048);

    //Nyquist LPF

    if(! Ret.BeforeVOT && BF / Dest -> SynthFreq < 1.0f)
    {
        int LPF = FreqToIndex2048(22050 * BF / Dest -> SynthFreq);
        Boost_FloatSet(OrigRe + LPF, 0, 1024 - LPF);
        Boost_FloatSet(OrigIm + LPF, 0, 1024 - LPF);
        Reflect(OrigRe, OrigIm, OrigRe, OrigIm, 11);
        RIFFT(Orig, OrigRe, OrigIm, 11);
    }
    Boost_FloatDivArr(BFWave.Data, Orig, Hamming2048, 2048);

    if(Ret.BeforeVOT)
    {
        //Consonants
        float FreqExpand = 1;
        int TransLast = CSynth_GetVOT(& Dest -> SubSynth) - Dest -> SubSynth.PlayPosition;
        Boost_FloatCopy(TempWave.Data, BFWave.Data + 512, 1024);
        if(TransLast < FSynth_ConsonantTransition)
            FreqExpand = TransLast / FSynth_ConsonantTransition
                       + BF / Dest -> SynthFreq * (1.0f - TransLast / FSynth_ConsonantTransition);
        Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize * FreqExpand;
        Boost_FloatMulArr(TempWave.Data, TempWave.Data, Hamming1024, 1024);
        FDFrame_FromPSOLAFrame(Output, & TempWave);
    }else
    {
        FSynth_Resample(& TempWave, & BFWave, Dest -> SynthFreq / BF);
        Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize * BF / Dest -> SynthFreq;
        FDFrame_FromPSOLAFrame(Output, & TempWave);

        CPF ResampleEnv;
        CPF_Ctor(& ResampleEnv);
        ResampleEnv.UFreq = SampleRate / 2;
        CPF_AddControlFreq(& ResampleEnv, 0, 0);

        Boost_FloatMulArr(Orig, TempWave.Data, Hamming1024, 1024);

        RFFT(OrigRe, OrigIm, Orig, 10);
        MagnitudeFromComplex(OrigMa, OrigRe, OrigIm, 1024);
        ExtractFormantCPF(& ResampleEnv, OrigMa, Dest -> SynthFreq, 1024);
        CPF_Bake(OrigMa, & ResampleEnv, 512);
        Boost_FloatAdd(OrigMa, OrigMa, 0.01, 1024);
        Boost_FloatDivArr(OrigRe, OrigRe, OrigMa, 512);
        Boost_FloatDivArr(OrigIm, OrigIm, OrigMa, 512);

        FECSOLAState PitchState;
        FECSOLAFilter PitchFilter;
        FECSOLAFilter_Ctor(& PitchFilter);
        float* OrigMEnv = (float*)malloc(sizeof(float) * 512);
        CPF_Bake(OrigMEnv, & OrigEnv, 512);

        PitchState.F0 = BF;
        PitchState.F1 = Dest -> SubSynth.Data.Header.F1;
        PitchState.F2 = Dest -> SubSynth.Data.Header.F2;
        PitchState.F3 = Dest -> SubSynth.Data.Header.F3;
        PitchState.S0 = 1;
        PitchState.S1 = Dest -> SubSynth.Data.Header.S1;
        PitchState.S2 = Dest -> SubSynth.Data.Header.S2;
        PitchState.S3 = Dest -> SubSynth.Data.Header.S3;
        FECSOLAFilter_GetFromFormantEnvelope(& PitchFilter, & OrigEnv, & PitchState);
        PitchState.F0 = Dest -> SynthFreq;
        PitchState.S1 *= Dest -> SynthFreq / BF;
        PitchState.S2 *= Dest -> SynthFreq / BF;
        PitchState.S3 *= Dest -> SynthFreq / BF;
//        PitchState.F1 += (Dest -> SynthFreq - BF) / 2;
        Boost_FloatSet(OrigMa, 0, 1024);
        FECSOLAFilter_Bake(OrigMa, & PitchFilter, & PitchState, 1024);

        QuadHPF(OrigMa, Dest -> SynthFreq);

        Boost_FloatCopy(OrigMa + 117, OrigMEnv + 117, 512 - 117);

        Boost_FloatMulArr(OrigRe, OrigRe, OrigMa, 512);
        Boost_FloatMulArr(OrigIm, OrigIm, OrigMa, 512);


        Reflect(OrigRe, OrigIm, OrigRe, OrigIm, 10);
        Boost_FloatCopy(Output -> Re, OrigRe, 1024);
        Boost_FloatCopy(Output -> Im, OrigIm, 1024);

        FECSOLAFilter_Dtor(& PitchFilter);
        free(OrigMEnv);
        CPF_Dtor(& ResampleEnv);
    }

    CPF_Dtor(& OrigEnv);
    free(Orig); free(OrigRe); free(OrigIm); free(OrigMa);

    if(Ret.PSOLAFrameHopSize > 512)
        Ret.PSOLAFrameHopSize = 512;

    PSOLAFrame_Dtor(& BFWave);
    PSOLAFrame_Dtor(& TempWave);
    return Ret;
}

float FSynth_GetVOT(FSynth* Dest)
{
    return CSynth_GetVOT(& Dest -> SubSynth);
}
