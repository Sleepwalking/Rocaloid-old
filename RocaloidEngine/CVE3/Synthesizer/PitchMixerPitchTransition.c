//ONLY included by PitchMixer.c

//Re|Im 1 -> Tmp1
FSynthSendback SubRet = FSynth_Synthesis(& Dest -> SubSynth1, & Tmp1);
PitchMixer_SoleSynth_Prepare(1);
FECSOLAFilter_GetFromFormantEnvelope(& FFilter1, & CPF1, & SubRet.FState);
PitchMixer_TransSynth_Bake(1);
HopSize = (float)SubRet.PSOLAFrameHopSize * (1.0f - Ratio);
Boost_FloatMul(AvgMagn, Magn, 1.0f - Ratio, 512);

//Re|Im 2 -> Tmp2
SubRet = FSynth_Synthesis(& Dest -> SubSynth2, & Tmp2);
PitchMixer_SoleSynth_Prepare(2);
FECSOLAFilter_GetFromFormantEnvelope(& FFilter2, & CPF2, & SubRet.FState);
PitchMixer_TransSynth_Bake(2);
HopSize += (float)SubRet.PSOLAFrameHopSize * Ratio;
Boost_FloatMul(Magn, Magn, Ratio, 512);
Boost_FloatAddArr(AvgMagn, AvgMagn, Magn, 512);

Boost_FloatMul(Tmp1.Re, Tmp1.Re, 1.0f - Ratio, 1024);
Boost_FloatMul(Tmp2.Re, Tmp2.Re,        Ratio, 1024);
Boost_FloatMul(Tmp1.Im, Tmp1.Im, 1.0f - Ratio, 1024);
Boost_FloatMul(Tmp2.Im, Tmp2.Im,        Ratio, 1024);
Boost_FloatAddArr(Output -> Re, Tmp1.Re, Tmp2.Re, 1024);
Boost_FloatAddArr(Output -> Im, Tmp1.Im, Tmp2.Im, 1024);

CPF1.ControlPointList_Index = 0;

MagnitudeFromComplex(Magn, Output -> Re, Output -> Im, 1024);
ExtractFormantCPF(& CPF1, Magn, Dest -> SynthFreq, 1024);
CPF_Bake(Magn, & CPF1, 512);
Boost_FloatAdd(Magn, Magn, 0.01, 512);
Boost_FloatDivArr(Magn, AvgMagn, Magn, 512);
Boost_FloatMulArr(Output -> Re, Output -> Re, Magn, 512);
Boost_FloatMulArr(Output -> Im, Output -> Im, Magn, 512);
Reflect(Output -> Re, Output -> Im, Output -> Re, Output -> Im, 10);
