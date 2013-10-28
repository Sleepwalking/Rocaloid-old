//Re|Im 1 -> Tmp1

#ifdef _Synth1_
    FSynthSendback SubRet = FSynth_Synthesis(& Dest -> SubSynth1, & Tmp1);
    Mixer_SoleSynth_Prepare(1);
    FECSOLAFilter_GetFromCPF(& FFilter1, & CPF1, & SubRet.FState);
    Mixer_TransSynth_Bake(1);
#else
    Mixer_SoleSynth_Prepare(1);
    LCFECSOLAFilter_GetFromFormantEnvelope(& LCFilter1, Magn, & SubRet.FState);
    Mixer_TransSynth_Bake_LCFECSOLA(1);
    //GNUPlot_PlotFloat(Magn, 120);
    //getchar();
#endif

HopSize = (float)SubRet.PSOLAFrameHopSize * (1.0f - Ratio);
Boost_FloatMul(AvgMagn, Magn, 1.0f - Ratio, 513);

//Re|Im 2 -> Tmp2
#ifdef _Synth1_
    SubRet = FSynth_Synthesis(& Dest -> SubSynth2, & Tmp2);
    Mixer_SoleSynth_Prepare(2);
    FECSOLAFilter_GetFromCPF(& FFilter2, & CPF2, & SubRet.FState);
    Mixer_TransSynth_Bake(2);
#else
    SubRet = PitchMixer_Synthesis(& Dest -> SubSynth2, & Tmp2);
    Mixer_SoleSynth_Prepare(2);
    LCFECSOLAFilter_GetFromFormantEnvelope(& LCFilter2, Magn, & SubRet.FState);
    Mixer_TransSynth_Bake_LCFECSOLA(2);
#endif

HopSize += (float)SubRet.PSOLAFrameHopSize * Ratio;
Boost_FloatMul(Magn, Magn, Ratio, 513);
Boost_FloatAddArr(AvgMagn, AvgMagn, Magn, 513);

Boost_FloatMul(Tmp1.Re, Tmp1.Re, 1.0f - Ratio, 1024);
Boost_FloatMul(Tmp1.Im, Tmp1.Im, 1.0f - Ratio, 1024);
Boost_FloatMul(Tmp2.Re, Tmp2.Re,        Ratio, 1024);
Boost_FloatMul(Tmp2.Im, Tmp2.Im,        Ratio, 1024);
Boost_FloatAddArr(Output -> Re, Tmp1.Re, Tmp2.Re, 1024);
Boost_FloatAddArr(Output -> Im, Tmp1.Im, Tmp2.Im, 1024);

CPF1.ControlPointList_Index = 0;

MagnitudeFromComplex(Magn, Output -> Re, Output -> Im, 1024);
#ifdef _SpeechMixer_
    ExtractFormantCPF(& CPF1, Magn, Dest -> SubSynth1.SynthFreq, 1024);
#else
    ExtractFormantCPF(& CPF1, Magn, Dest -> SynthFreq, 1024);
#endif

CPF_Bake(Magn, & CPF1, 513);

#ifdef _SpeechMixer_
    //GNUPlot_SetTitleAndNumber("Trans", Dest -> SubSynth1.SynthFreq);
    //GNUPlot_PlotFloat(AvgMagn, 120);
    //getchar();
#endif

Boost_FloatAdd(Magn, Magn, 0.01, 513);
Boost_FloatDivArr(Magn, AvgMagn, Magn, 513);
#ifdef _Synth1
Boost_FloatMulArr(Output -> Re, Output -> Re, Magn, 513);
Boost_FloatMulArr(Output -> Im, Output -> Im, Magn, 513);
#endif
Reflect(Output -> Re, Output -> Im, Output -> Re, Output -> Im, 10);


