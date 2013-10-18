#include "FSynth.h"
#include "CVEDSP/DFT/FFT.h"
#include "CVEDSP/Algorithm/Formant.h"
#include "CVEDSP/Interpolation.h"
#include "CVEDSP/Plot.h"
#include "CVEGlobal.h"

#include "DSPEx/FECSOLAEx.h"

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

    CPF_Setup(OrigEnv);
    float* OrigRe = FloatMalloc(2048);
    float* OrigIm = FloatMalloc(2048);
    float* OrigMa = FloatMalloc(2048);
    float* Orig   = FloatMalloc(2048);

    Boost_FloatMulArr(Orig, BFWave.Data, Hanning2048, 2048);
    RFFT(OrigRe, OrigIm, Orig, 11);

    //Nyquist LPF
    if(! Ret.BeforeVOT && BF / Dest -> SynthFreq < 1.0f)
    {
        int LPF = FreqToIndex2048(22050 * BF / Dest -> SynthFreq);
        Boost_FloatSet(OrigRe + LPF, 0, 1024 - LPF);
        Boost_FloatSet(OrigIm + LPF, 0, 1024 - LPF);
        Reflect(OrigRe, OrigIm, OrigRe, OrigIm, 11);
        RIFFT(Orig, OrigRe, OrigIm, 11);
    }

    Boost_FloatDivArr(BFWave.Data, Orig, Hanning2048, 2048);

    if(Ret.BeforeVOT)
    {
        //Consonants
        Boost_FloatCopy(TempWave.Data, BFWave.Data + 512, 1024);
        Boost_FloatMulArr(TempWave.Data, TempWave.Data, Hanning1024, 1024);
        FDFrame_FromPSOLAFrame(Output, & TempWave);

        float FreqExpand = 1;
        int TransLast = CSynth_GetVOT(& Dest -> SubSynth) - Dest -> SubSynth.PlayPosition;
        if(TransLast < FSynth_ConsonantTransition)
            FreqExpand = TransLast / FSynth_ConsonantTransition
                       + BF / Dest -> SynthFreq * (1.0f - TransLast / FSynth_ConsonantTransition);
        Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize * FreqExpand;
    }else
    {
        FSynth_Resample(& TempWave, & BFWave, Dest -> SynthFreq / BF);
        Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize * BF / Dest -> SynthFreq;
        //Maintain Spectral Envelope
        #include "FSynthSpectrumModification.c"
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
