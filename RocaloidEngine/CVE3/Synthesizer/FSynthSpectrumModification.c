//ONLY included by FSynth.c
//BFWave:   Wave at original base freq.      2048
//TempWave: Wave after resample.             1024

float* OrigMEnv = FloatMalloc(1024);
Boost_FloatMulArr(Orig, BFWave.Data + 512, Hamming1024, 1024);
MagnitudeFromWave(OrigMEnv, Orig, 10);
ExtractFormantCPF(& OrigEnv, OrigMEnv, BF,1024);
CPF_Bake(OrigMEnv, & OrigEnv, 512);

Boost_FloatMulArr(Orig, TempWave.Data, Hamming1024, 1024);

RFFT(OrigRe, OrigIm, Orig, 10);
MagnitudeFromComplex(OrigMa, OrigRe, OrigIm, 1024);

SpectralEnvelopeFromMagnitude(OrigMa, OrigMa, Dest -> SynthFreq, 1024);
Boost_FloatAdd(OrigMa, OrigMa, 0.0001, 1024);
Boost_FloatDivArr(OrigRe, OrigRe, OrigMa, 512);
Boost_FloatDivArr(OrigIm, OrigIm, OrigMa, 512);

FECSOLAState PitchState;
FECSOLAFilter PitchFilter;
FECSOLAFilter_Ctor(& PitchFilter);

FECSOLAState_FromCVDB(& PitchState, & Dest -> SubSynth.Data);
FECSOLAFilter_GetFromFormantEnvelope(& PitchFilter, & OrigEnv, & PitchState);
PitchState.F0 = Dest -> SynthFreq;

//Reduce S0 for low freq.
if(BF > Dest -> SynthFreq)
    PitchState.S0 *= pow(Dest -> SynthFreq / BF, 1);

FECSOLAFilter_Bake(OrigMa, & PitchFilter, & PitchState, 1024);
Boost_FloatCopy(OrigMa + FreqToIndex1024(6000), OrigMEnv + FreqToIndex1024(6000), 512 - FreqToIndex1024(6000));

QuadHPF(OrigMa, Dest -> SynthFreq);

Boost_FloatMulArr(OrigRe, OrigRe, OrigMa, 512);
Boost_FloatMulArr(OrigIm, OrigIm, OrigMa, 512);

Reflect(Output -> Re, Output -> Im, OrigRe, OrigIm, 10);

FECSOLAFilter_Dtor(& PitchFilter);
free(OrigMEnv);
