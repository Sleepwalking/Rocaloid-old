//ONLY included by FSynth.c

Boost_FloatMulArr(Orig, TempWave.Data, Hamming1024, 1024);

RFFT(OrigRe, OrigIm, Orig, 10);
MagnitudeFromComplex(OrigMa, OrigRe, OrigIm, 1024);

SpectralEnvelopeFromMagnitude(OrigMa, OrigMa, Dest -> SynthFreq, 1024);
Boost_FloatAdd(OrigMa, OrigMa, 0.01, 1024);
Boost_FloatDivArr(OrigRe, OrigRe, OrigMa, 512);
Boost_FloatDivArr(OrigIm, OrigIm, OrigMa, 512);

FECSOLAState PitchState;
FECSOLAFilter PitchFilter;
FECSOLAFilter_Ctor(& PitchFilter);
float* OrigMEnv = FloatMalloc(512);
CPF_Bake(OrigMEnv, & OrigEnv, 512);

FECSOLAState_FromCVDB(& PitchState, & Dest -> SubSynth.Data);
FECSOLAFilter_GetFromFormantEnvelope(& PitchFilter, & OrigEnv, & PitchState);
PitchState.F0 = Dest -> SynthFreq;
PitchState.S1 *= pow(Dest -> SynthFreq / BF, 1);
PitchState.S2 *= pow(Dest -> SynthFreq / BF, 1);
PitchState.S3 *= pow(Dest -> SynthFreq / BF, 2);
FECSOLAFilter_Bake(OrigMa, & PitchFilter, & PitchState, 1024);
Boost_FloatCopy(OrigMa + FreqToIndex1024(6000), OrigMEnv + FreqToIndex1024(6000), 512 - FreqToIndex1024(6000));

Boost_FloatCopy(OrigMa, OrigMEnv, 512);

QuadHPF(OrigMa, Dest -> SynthFreq);

Boost_FloatMul(OrigMa, OrigMa, 0.02, 512);
Boost_FloatMul(Dest -> EnvMomentum, Dest -> EnvMomentum, 0.98, 512);
Boost_FloatAddArr(OrigMa, OrigMa, Dest -> EnvMomentum, 512);
Boost_FloatCopy(Dest -> EnvMomentum, OrigMa, 512);

Boost_FloatMulArr(OrigRe, OrigRe, OrigMa, 512);
Boost_FloatMulArr(OrigIm, OrigIm, OrigMa, 512);

Reflect(Output -> Re, Output -> Im, OrigRe, OrigIm, 10);

FECSOLAFilter_Dtor(& PitchFilter);
free(OrigMEnv);

