#define Mixer_SoleSynth_Prepare(Num)\
    MagnitudeFromComplex(Magn, Tmp##Num.Re, Tmp##Num.Im, Tmp##Num.Length);\
    ExtractFormantCPF(& CPF##Num, Magn, Dest -> SubSynth##Num.SynthFreq, 1024);\
    CPF_Bake(Magn, & CPF##Num, 512);\
    Boost_FloatCopy(TmpMagn, Magn, 512);\
    Boost_FloatAdd(Magn, Magn, 0.01, 512);\
    Boost_FloatDivArr(Tmp##Num.Re, Tmp##Num.Re, Magn, 512);\
    Boost_FloatDivArr(Tmp##Num.Im, Tmp##Num.Im, Magn, 512)\

#define Mixer_SoleSynth_Bake(Num)\
    FECSOLAFilter_Bake(Magn, & FFilter##Num, & DestState, 1024);\
    Boost_FloatCopy(Magn + FreqToIndex1024(6000), TmpMagn + FreqToIndex1024(6000), 512 - FreqToIndex1024(6000));\
    Boost_FloatMulArr(Output -> Re, Tmp##Num.Re, Magn, 513);\
    Boost_FloatMulArr(Output -> Im, Tmp##Num.Im, Magn, 513);\
    Reflect(Output -> Re, Output -> Im, Output -> Re, Output -> Im, 10)

#define Mixer_TransSynth_Bake(Num)\
    FECSOLAFilter_Bake(Magn, & FFilter##Num, & DestState, 1024);\
    Boost_FloatCopy(Magn + FreqToIndex1024(6000), TmpMagn + FreqToIndex1024(6000), 512 - FreqToIndex1024(6000));\
    Boost_FloatMulArr(Tmp##Num.Re, Tmp##Num.Re, Magn, 512);\
    Boost_FloatMulArr(Tmp##Num.Im, Tmp##Num.Im, Magn, 512);\
    Reflect(Tmp##Num.Re, Tmp##Num.Im, Tmp##Num.Re, Tmp##Num.Im, 10)

#define PitchMixer_CreateState(_Dest, Num)\
    FECSOLAState_CreateFormant\
    (\
        _Dest,\
        Dest -> Entry##Num.F0, Dest -> Entry##Num.F1, Dest -> Entry##Num.F2, Dest -> Entry##Num.F3,\
        0                    , 0                    , 0                    , 0                    ,\
        1                    , Dest -> Entry##Num.S1, Dest -> Entry##Num.S2, Dest -> Entry##Num.S3 \
    )
