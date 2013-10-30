#define Mixer_SoleSynth_Prepare(Num)\
    MagnitudeFromComplex(Magn, Tmp##Num.Re, Tmp##Num.Im, Tmp##Num.Length);\
    ExtractFormantCPF(& CPF##Num, Magn, Dest -> SubSynth##Num.SynthFreq, CVE_FFTSize);\
    CPF_Bake(Magn, & CPF##Num, CVE_FFTHalf);\
    Boost_FloatCopy(TmpMagn, Magn, CVE_FFTHalf);\
    Boost_FloatAdd(Magn, Magn, 0.01, CVE_FFTHalf);\
    Boost_FloatDivArr(Tmp##Num.Re, Tmp##Num.Re, Magn, CVE_FFTHalf);\
    Boost_FloatDivArr(Tmp##Num.Im, Tmp##Num.Im, Magn, CVE_FFTHalf)\

#define Mixer_SoleSynth_Bake(Num)\
    FECSOLAFilter_Bake(Magn, & FFilter##Num, & DestState, CVE_FFTSize);\
    Boost_FloatCopy(Magn + FreqToIndex1024(6000), TmpMagn + FreqToIndex1024(6000), CVE_FFTHalf - FreqToIndex1024(6000));\
    Boost_FloatMulArr(Output -> Re, Tmp##Num.Re, Magn, CVE_FFTHalf);\
    Boost_FloatMulArr(Output -> Im, Tmp##Num.Im, Magn, CVE_FFTHalf);\
    Reflect(Output -> Re, Output -> Im, Output -> Re, Output -> Im, 10)

#define Mixer_SoleSynth_Bake_LCFECSOLA(Num)\
    LCFECSOLAFilter_Bake(Magn, & LCFilter##Num, & DestState);\
    Boost_FloatMulArr(Output -> Re, Tmp##Num.Re, Magn, CVE_FFTHalf);\
    Boost_FloatMulArr(Output -> Im, Tmp##Num.Im, Magn, CVE_FFTHalf);\
    Reflect(Output -> Re, Output -> Im, Output -> Re, Output -> Im, 10)

#define Mixer_TransSynth_Bake(Num)\
    FECSOLAFilter_Bake(Magn, & FFilter##Num, & DestState, CVE_FFTSize);\
    Boost_FloatCopy(Magn + FreqToIndex1024(6000), TmpMagn + FreqToIndex1024(6000), CVE_FFTHalf - FreqToIndex1024(6000));\
    Boost_FloatMulArr(Tmp##Num.Re, Tmp##Num.Re, Magn, CVE_FFTHalf);\
    Boost_FloatMulArr(Tmp##Num.Im, Tmp##Num.Im, Magn, CVE_FFTHalf);\
    Reflect(Tmp##Num.Re, Tmp##Num.Im, Tmp##Num.Re, Tmp##Num.Im, 10)

#define Mixer_TransSynth_Bake_LCFECSOLA(Num)\
    LCFECSOLAFilter_Bake(Magn, & LCFilter##Num, & DestState);\
    Boost_FloatMulArr(Tmp##Num.Re, Tmp##Num.Re, Magn, CVE_FFTHalf);\
    Boost_FloatMulArr(Tmp##Num.Im, Tmp##Num.Im, Magn, CVE_FFTHalf);\
    Reflect(Tmp##Num.Re, Tmp##Num.Im, Tmp##Num.Re, Tmp##Num.Im, 10)

#define PitchMixer_CreateState(_Dest, Num)\
    FECSOLAState_CreateFormant\
    (\
        _Dest,\
        Dest -> Entry##Num.F0, Dest -> Entry##Num.F1, Dest -> Entry##Num.F2, Dest -> Entry##Num.F3,\
        0                    , 0                    , 0                    , 0                    ,\
        1                    , Dest -> Entry##Num.S1, Dest -> Entry##Num.S2, Dest -> Entry##Num.S3 \
    )
