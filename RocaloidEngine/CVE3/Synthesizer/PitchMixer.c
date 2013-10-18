#include "PitchMixer.h"
#include "CVEDSP/Algorithm/Formant.h"

_Constructor_(PitchMixer)
{
    FSynth_Ctor(& Dest -> SubSynth1);
    FSynth_Ctor(& Dest -> SubSynth2);
    String_Ctor(& Dest -> Phone);
    Dest -> IsLimitedFreq = 0;

    Dest -> SubSynth1Index = - 1;
    Dest -> SubSynth2Index = - 1;

    FSynth_SetVowelRatio(& Dest -> SubSynth1, 1);
    FSynth_SetConsonantRatio(& Dest -> SubSynth1, 1);
    FSynth_SetVowelRatio(& Dest -> SubSynth2, 1);
    FSynth_SetConsonantRatio(& Dest -> SubSynth2, 1);
}

_Destructor_(PitchMixer)
{
    FSynth_Dtor(& Dest -> SubSynth1);
    FSynth_Dtor(& Dest -> SubSynth2);
    String_Dtor(& Dest -> Phone);
}

void PitchMixer_SetSymbol(PitchMixer* Dest, String* Symbol)
{
    Transition TestTrans = Demapper_QueryFusedFormantLayer(Symbol, 300);
    FormantLayerPartialEntry TestEntry = GetFusedFormantLayerEntry((& CGQuerySpace), TestTrans.Index, TestTrans.SubIndex);
    int TestSymbol = Demapper_QuerySymbolLayer(& TestEntry.Name);
    if(CGDict.CDTMapping.SymbolLayerMap[TestSymbol].Type == 'C')
        Dest -> IsLimitedFreq = 1;
    else
        Dest -> IsLimitedFreq = 0;
    String_Copy(& Dest -> Phone, Symbol);
    Dest -> SubSynth1Index = - 1;
    Dest -> SubSynth2Index = - 1;
}

void PitchMixer_SetConsonantRatio(PitchMixer* Dest, float CRatio)
{
    FSynth_SetConsonantRatio(& Dest -> SubSynth1, CRatio);
    FSynth_SetConsonantRatio(& Dest -> SubSynth2, CRatio);
}

void PitchMixer_SetVowelRatio(PitchMixer* Dest, float VRatio)
{
    FSynth_SetVowelRatio(& Dest -> SubSynth1, VRatio);
    FSynth_SetVowelRatio(& Dest -> SubSynth2, VRatio);
}

void PitchMixer_Reset(PitchMixer* Dest)
{
    FSynth_Reset(& Dest -> SubSynth1);
    FSynth_Reset(& Dest -> SubSynth2);
    Dest -> SubSynth1Index = - 1;
    Dest -> SubSynth2Index = - 1;
}

void PitchMixer_SwapSynth(PitchMixer* Dest)
{
    FSynth Tmp        = Dest -> SubSynth1;
    Dest -> SubSynth1 = Dest -> SubSynth2;
    Dest -> SubSynth2 = Tmp;
}

void PitchMixer_SetFrequency(PitchMixer* Dest, float Freq)
{
    Transition Target;
    if(Dest -> IsLimitedFreq)
    {
        Target = Demapper_QueryFusedFormantLayer(& Dest -> Phone, Dest -> LimitedFreq);
        if(Target.SubIndex + 0 != Dest -> SubSynth1Index)
        {
            //SubSynth1 needs to be reloaded.
            Dest -> SubSynth1Index = Target.SubIndex + 0;
            Dest -> Entry1 = GetFusedFormantLayerEntry((& CGQuerySpace), Target.Index, Dest -> SubSynth1Index);
            FSynth_SetSymbol(& Dest -> SubSynth1, & Dest -> Entry1.Name);
        }
        Dest -> TransitionRatio = 0;
        FSynth_SetFrequency(& Dest -> SubSynth1, Freq);
        //Diphones only need one Synth
        /*
        if(Target.SubIndex + 1 != Dest -> SubSynth2Index && Target.Reach != 1)
        {
            //SubSynth2 needs to be reloaded.
            Dest -> SubSynth2Index = Target.SubIndex + 1;
            Dest -> Entry2 = GetFusedFormantLayerEntry((& CGQuerySpace), Target.Index, Dest -> SubSynth2Index);
            FSynth_SetSymbol(& Dest -> SubSynth2, & Dest -> Entry2.Name);
        }*/
        /*
        if(Target.Reach == 1)
            Dest -> TransitionRatio = 0;
        else
        {
            Dest -> TransitionRatio = (Freq - Dest -> Entry1.F0) / (Dest -> Entry2.F0 - Dest -> Entry1.F0);
            if(Freq < Dest -> Entry1.F0)
                Dest -> TransitionRatio = 0;
            if(Freq > Dest -> Entry2.F0)
                Dest -> TransitionRatio = 1;
        }*/
    }else
    {
        Target = Demapper_QueryFusedFormantLayer(& Dest -> Phone, Freq);
        if(Target.SubIndex + 0 == Dest -> SubSynth1Index && Target.SubIndex + 1 == Dest -> SubSynth2Index)
        {
            //Normal Transition: SS1 -> SS2
            Dest -> TransitionRatio = Target.Ratio;
            Dest -> ForwardTransition = 1;
        }else if(Target.SubIndex + 1 == Dest -> SubSynth1Index && Target.SubIndex + 0 == Dest -> SubSynth2Index)
        {
            //Normal Transition: SS2 -> SS1
            Dest -> TransitionRatio = 1.0f - Target.Ratio;
            Dest -> ForwardTransition = 0;
        }else
        {
            //At least one of the SubSynths is not on its Index.
            if(Target.SubIndex == Dest -> SubSynth1Index)
            {
                //SubSynth2 needs to be reloaded.
                //Transition: SS1 -> SS2
                Dest -> SubSynth2Index = Target.SubIndex + 1;
                if(Target.Reach != 1)
                {
                    Dest -> Entry2 = GetFusedFormantLayerEntry((& CGQuerySpace), Target.Index, Dest -> SubSynth2Index);
                    FSynth_SetSymbol(& Dest -> SubSynth2, & Dest -> Entry2.Name);
                }
                Dest -> TransitionRatio = Target.Ratio;
                Dest -> ForwardTransition = 1;
            }else if(Target.SubIndex == Dest -> SubSynth2Index)
            {
                //SubSynth1 needs to be reloaded.
                //Transition: SS2 -> SS1
                Dest -> SubSynth1Index = Target.SubIndex + 1;
                if(Target.Reach != 1)
                {
                    Dest -> Entry1 = GetFusedFormantLayerEntry((& CGQuerySpace), Target.Index, Dest -> SubSynth1Index);
                    FSynth_SetSymbol(& Dest -> SubSynth1, & Dest -> Entry1.Name);
                }
                Dest -> TransitionRatio = 1.0f - Target.Ratio;
                Dest -> ForwardTransition = 0;
            }else
            {
                //Both SubSynth1 and SubSynth2 needs to be reloaded.
                //Transition: SS1 -> SS2
                Dest -> SubSynth1Index = Target.SubIndex + 0;
                Dest -> SubSynth2Index = Target.SubIndex + 1;
                Dest -> Entry1 = GetFusedFormantLayerEntry((& CGQuerySpace), Target.Index, Dest -> SubSynth1Index);
                FSynth_SetSymbol(& Dest -> SubSynth1, & Dest -> Entry1.Name);
                if(Target.Reach != 1)
                {
                    Dest -> Entry2 = GetFusedFormantLayerEntry((& CGQuerySpace), Target.Index, Dest -> SubSynth2Index);
                    FSynth_SetSymbol(& Dest -> SubSynth2, & Dest -> Entry2.Name);
                }
                Dest -> TransitionRatio = Target.Ratio;
                Dest -> ForwardTransition = 1;
            }
        }
        FSynth_SetFrequency(& Dest -> SubSynth1, Freq);
        FSynth_SetFrequency(& Dest -> SubSynth2, Freq);
    }
    //printf("SS1 -> SS2 at %f, Ratio: %f\n", Freq, Dest -> TransitionRatio);
    Dest -> SynthFreq = Freq;
}

void PitchMixer_SetLimitedFrequency(PitchMixer* Dest, float Freq)
{
    Dest -> LimitedFreq = Freq;
}

#define PitchMixer_SoleSynth_Prepare(Num)\
    MagnitudeFromComplex(Magn, Tmp##Num.Re, Tmp##Num.Im, Tmp##Num.Length);\
    ExtractFormantCPF(& CPF##Num, Magn, Dest -> SubSynth##Num.SynthFreq, 1024);\
    CPF_Bake(Magn, & CPF##Num, 512);\
    Boost_FloatCopy(TmpMagn, Magn, 512);\
    Boost_FloatAdd(Magn, Magn, 0.01, 512);\
    Boost_FloatDivArr(Tmp##Num.Re, Tmp##Num.Re, Magn, 512);\
    Boost_FloatDivArr(Tmp##Num.Im, Tmp##Num.Im, Magn, 512)\

#define PitchMixer_SoleSynth_Bake(Num)\
    FECSOLAFilter_Bake(Magn, & FFilter##Num, & DestState, 1024);\
    Boost_FloatCopy(Magn + FreqToIndex1024(6000), TmpMagn + FreqToIndex1024(6000), 512 - FreqToIndex1024(6000));\
    Boost_FloatMulArr(Output -> Re, Tmp##Num.Re, Magn, 512);\
    Boost_FloatMulArr(Output -> Im, Tmp##Num.Im, Magn, 512);\
    Reflect(Output -> Re, Output -> Im, Output -> Re, Output -> Im, 10)

#define PitchMixer_TransSynth_Bake(Num)\
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
        0, 0, 0, 0,\
        1                , Dest -> Entry##Num.S1, Dest -> Entry##Num.S2, Dest -> Entry##Num.S3\
    )

PitchMixerSendback PitchMixer_Synthesis(PitchMixer* Dest, FDFrame* Output)
{
    PitchMixerSendback Ret;
    FDFrame Tmp1, Tmp2;
    FDFrame_CtorSize(& Tmp1, 1024);
    FDFrame_CtorSize(& Tmp2, 1024);

    CPF_Setup(CPF1);
    CPF_Setup(CPF2);
    FECSOLAFilter FFilter1, FFilter2;
    FECSOLAFilter_Ctor(& FFilter1);
    FECSOLAFilter_Ctor(& FFilter2);
    FECSOLAState State1, State2;
    FECSOLAState DestState;
    float* Magn = FloatMalloc(1024);
    float* TmpMagn = FloatMalloc(1024);
    if(Dest -> IsLimitedFreq)
    {
        //Diphone Mix
        FSynthSendback SubRet = FSynth_Synthesis(& Dest -> SubSynth1, & Tmp1);
        if(SubRet.BeforeVOT)
        {
            Boost_FloatCopy(Output -> Re, Tmp1.Re, Tmp1.Length);
            Boost_FloatCopy(Output -> Im, Tmp1.Im, Tmp1.Length);
        }else
        {
            PitchMixer_SoleSynth_Prepare(1);
            FECSOLAFilter_GetFromFormantEnvelope(& FFilter1, & CPF1, & SubRet.FState);
            PitchMixer_CreateState(DestState, 1);
            PitchMixer_SoleSynth_Bake(1);
        }
        Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize;
        Ret.BeforeVOT = SubRet.BeforeVOT;
    }else
    {
        PitchMixer_CreateState(State1, 1);
        PitchMixer_CreateState(State2, 2);
        FECSOLAState_Transition(& DestState, & State1, & State2, Dest -> TransitionRatio);

        if(Dest -> ForwardTransition)
        {
            //SubSynth1: LF
            //SubSynth2: HF
            if(Dest -> TransitionRatio < 0.8)
            {
                //Sole Synth: SubSynth1
                FSynthSendback SubRet = FSynth_Synthesis(& Dest -> SubSynth1, & Tmp1);
                PitchMixer_SoleSynth_Prepare(1);
                FECSOLAFilter_GetFromFormantEnvelope(& FFilter1, & CPF1, & SubRet.FState);
                PitchMixer_SoleSynth_Bake(1);

                Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize;
                Ret.BeforeVOT = 0;
            }else
            {
                //Trans Synth
                //Re|Im 1 -> Tmp1
                float HopSize;
                float Ratio = (Dest -> TransitionRatio - 0.8) / 0.2;

                FSynthSendback SubRet = FSynth_Synthesis(& Dest -> SubSynth1, & Tmp1);
                PitchMixer_SoleSynth_Prepare(1);
                FECSOLAFilter_GetFromFormantEnvelope(& FFilter1, & CPF1, & SubRet.FState);
                PitchMixer_TransSynth_Bake(1);
                HopSize = (float)SubRet.PSOLAFrameHopSize * (1.0f - Ratio);

                //Re|Im 2 -> Tmp2
                SubRet = FSynth_Synthesis(& Dest -> SubSynth2, & Tmp2);
                PitchMixer_SoleSynth_Prepare(2);
                FECSOLAFilter_GetFromFormantEnvelope(& FFilter2, & CPF2, & SubRet.FState);
                PitchMixer_TransSynth_Bake(2);
                HopSize += (float)SubRet.PSOLAFrameHopSize * Ratio;

                Boost_FloatMul(Tmp1.Re, Tmp1.Re, 1.0f - Ratio, 1024);
                Boost_FloatMul(Tmp2.Re, Tmp2.Re,        Ratio, 1024);
                Boost_FloatMul(Tmp1.Im, Tmp1.Im, 1.0f - Ratio, 1024);
                Boost_FloatMul(Tmp2.Im, Tmp2.Im,        Ratio, 1024);
                Boost_FloatAddArr(Output -> Re, Tmp1.Re, Tmp2.Re, 1024);
                Boost_FloatAddArr(Output -> Im, Tmp1.Im, Tmp2.Im, 1024);

                Ret.PSOLAFrameHopSize = (int)HopSize;
                Ret.BeforeVOT = 0;
            }
        }else
        {
            //SubSynth1: HF
            //SubSynth2: LF
            if(Dest -> TransitionRatio > 0.2)
            {
                //Sole Synth: SubSynth2
                FSynthSendback SubRet = FSynth_Synthesis(& Dest -> SubSynth2, & Tmp2);
                PitchMixer_SoleSynth_Prepare(2);
                FECSOLAFilter_GetFromFormantEnvelope(& FFilter2, & CPF2, & SubRet.FState);
                PitchMixer_SoleSynth_Bake(2);

                Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize;
                Ret.BeforeVOT = 0;
            }else
            {
                //Trans Synth
                //Re|Im 1 -> Tmp1
                float HopSize;
                float Ratio = Dest -> TransitionRatio / 0.2;

                FSynthSendback SubRet = FSynth_Synthesis(& Dest -> SubSynth1, & Tmp1);
                PitchMixer_SoleSynth_Prepare(1);
                FECSOLAFilter_GetFromFormantEnvelope(& FFilter1, & CPF1, & SubRet.FState);
                PitchMixer_TransSynth_Bake(1);
                HopSize = (float)SubRet.PSOLAFrameHopSize * (1.0f - Ratio);

                //Re|Im 2 -> Tmp2
                SubRet = FSynth_Synthesis(& Dest -> SubSynth2, & Tmp2);
                PitchMixer_SoleSynth_Prepare(2);
                FECSOLAFilter_GetFromFormantEnvelope(& FFilter2, & CPF2, & SubRet.FState);
                PitchMixer_TransSynth_Bake(2);
                HopSize += (float)SubRet.PSOLAFrameHopSize * Ratio;

                Boost_FloatMul(Tmp1.Re, Tmp1.Re, 1.0f - Ratio, 1024);
                Boost_FloatMul(Tmp2.Re, Tmp2.Re,        Ratio, 1024);
                Boost_FloatMul(Tmp1.Im, Tmp1.Im, 1.0f - Ratio, 1024);
                Boost_FloatMul(Tmp2.Im, Tmp2.Im,        Ratio, 1024);
                Boost_FloatAddArr(Output -> Re, Tmp1.Re, Tmp2.Re, 1024);
                Boost_FloatAddArr(Output -> Im, Tmp1.Im, Tmp2.Im, 1024);

                Ret.PSOLAFrameHopSize = (int)HopSize;
                Ret.BeforeVOT = 0;
            }
        }
    }
    free(Magn);
    free(TmpMagn);
    CPF_Dtor(& CPF1);
    CPF_Dtor(& CPF2);
    FECSOLAFilter_Dtor(& FFilter1);
    FECSOLAFilter_Dtor(& FFilter2);
    FDFrame_Dtor(& Tmp1);
    FDFrame_Dtor(& Tmp2);
    return Ret;
}

float PitchMixer_GetVOT(PitchMixer* Dest)
{
    return FSynth_GetVOT(& Dest -> SubSynth1);
}
