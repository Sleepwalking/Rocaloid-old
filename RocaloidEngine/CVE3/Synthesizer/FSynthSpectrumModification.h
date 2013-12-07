//ONLY included by FSynth.c
//BFWave:   Wave at original base freq.      2048
//TempWave: Wave after resample.             1024

float* OrigMEnv = FloatMalloc(CVE_FFTSize);
Boost_FloatMulArr(Orig, BFWave.Data + 512, Hanning1024, CVE_FFTSize);
MagnitudeFromWave(OrigMEnv, Orig, 10); //Performance: Change to static form
ExtractFormantCPF(& OrigEnv, OrigMEnv, BF,CVE_FFTSize);
CPF_Bake(OrigMEnv, & OrigEnv, CVE_FFTHalf);

Boost_FloatMulArr(Orig, TempWave.Data, Hanning1024, CVE_FFTSize);

RFFT(OrigRe, OrigIm, Orig, 10);
#if FSynth_SkipSynth == 0
MagnitudeFromComplex(OrigMa, OrigRe, OrigIm, CVE_FFTHalf);

SpectralEnvelopeFromMagnitude(OrigMa, OrigMa, Dest -> SynthFreq, CVE_FFTSize);
Boost_FloatAdd(OrigMa, OrigMa, 0.00001, CVE_FFTHalf);
Boost_FloatDivArr(OrigRe, OrigRe, OrigMa, CVE_FFTHalf);
Boost_FloatDivArr(OrigIm, OrigIm, OrigMa, CVE_FFTHalf);

FECSOLAState PitchState;
#ifdef FSynth_LCEnabled
    LCFECSOLAFilter PitchFilter;
    LCFECSOLAFilter_Ctor(& PitchFilter);
#else
    FECSOLAFilter PitchFilter;
    FECSOLAFilter_Ctor(& PitchFilter);
#endif
String_FromChars(Symbol, Dest -> SubSynth.Data.Header.Symbol);
FECSOLAState_FromSymbolLayer(& PitchState, & Symbol);
String_Dtor(& Symbol);

#ifdef FSynth_LCEnabled
    LCFECSOLAFilter_GetFromFormantEnvelope(& PitchFilter, OrigMEnv, & PitchState);
#else
    FECSOLAFilter_GetFromCPF(& PitchFilter, & OrigEnv, & PitchState);
#endif
PitchState.F0 = Dest -> SynthFreq;

//Reduce S0 for low freq.

if(BF > Dest -> SynthFreq)
    PitchState.S0 *= pow(Dest -> SynthFreq / BF, 1);

#ifdef FSynth_LCEnabled
    LCFECSOLAFilter_Bake(OrigMa, & PitchFilter, & PitchState);
#else
    FECSOLAFilter_Bake(OrigMa, & PitchFilter, & PitchState, CVE_FFTSize);
    Boost_FloatCopy(OrigMa + FreqToIndex1024(6000), OrigMEnv + FreqToIndex1024(6000), CVE_FFTHalf - FreqToIndex1024(6000));
#endif

QuadHPF(OrigMa, Dest -> SynthFreq);

Boost_FloatMulArr(OrigRe, OrigRe, OrigMa, CVE_FFTHalf);
Boost_FloatMulArr(OrigIm, OrigIm, OrigMa, CVE_FFTHalf);

Reflect(OrigRe, OrigIm, OrigRe, OrigIm, 10);
Boost_FloatCopy(Output -> Re, OrigRe, CVE_FFTSize);
Boost_FloatCopy(Output -> Im, OrigIm, CVE_FFTSize);

Ret.FState = PitchState;

#ifdef FSynth_LCEnabled
    LCFECSOLAFilter_Dtor(& PitchFilter);
#else
    FECSOLAFilter_Dtor(& PitchFilter);
#endif
#else
Boost_FloatCopy(Output -> Re, OrigRe, CVE_FFTSize);
Boost_FloatCopy(Output -> Im, OrigIm, CVE_FFTSize);
#endif
free(OrigMEnv);
