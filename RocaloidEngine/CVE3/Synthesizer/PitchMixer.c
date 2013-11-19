#include "PitchMixer.h"
#include "MixerMacro.h"
#include "../CVEDSP/Algorithm/Formant.h"
#include "../CVEDSP/Algorithm/FECSOLA.h"
#include "../CVEDSP/Plot.h"
#include "../DSPEx/LCFECSOLA.h"

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

    int TmpIndex           = Dest -> SubSynth1Index;
    Dest -> SubSynth1Index = Dest -> SubSynth2Index;
    Dest -> SubSynth2Index = TmpIndex;

    FormantLayerPartialEntry TmpEntry = Dest -> Entry1;
    Dest -> Entry1                    = Dest -> Entry2;
    Dest -> Entry2                    = TmpEntry;
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
        /*if(Target.SubIndex != Dest -> SubSynth2Index && Target.SubIndex + 1 == Dest -> SubSynth1Index)
        {
            PitchMixer_SwapSynth(Dest);
        }*/

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
            }else if(Target.SubIndex + 1 == Dest -> SubSynth1Index && Dest -> SubSynth1Index != - 1)
            {
                //Transition: SS1 -> SS2
                //Then SubSynth1 needs to be reloaded.
                PitchMixer_SwapSynth(Dest);
                Dest -> SubSynth1Index = Target.SubIndex;
                if(Target.Reach != 1)
                {
                    Dest -> Entry1 = GetFusedFormantLayerEntry((& CGQuerySpace), Target.Index, Dest -> SubSynth1Index);
                    FSynth_SetSymbol(& Dest -> SubSynth1, & Dest -> Entry1.Name);
                }
                Dest -> TransitionRatio = Target.Ratio;
                Dest -> ForwardTransition = 0;
            }else if(Target.SubIndex + 1 == Dest -> SubSynth2Index && Dest -> SubSynth2Index != - 1)
            {
                //SubSynth1 needs to be reloaded.
                //Transition: SS1 -> SS2
                Dest -> SubSynth1Index = Target.SubIndex;
                Dest -> Entry1 = GetFusedFormantLayerEntry((& CGQuerySpace), Target.Index, Dest -> SubSynth1Index);
                FSynth_SetSymbol(& Dest -> SubSynth1, & Dest -> Entry1.Name);
                Dest -> TransitionRatio = Target.Ratio;
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
/*
    if(Dest -> ForwardTransition)
        printf("SS1 -> SS2 at %f, Ratio: %f, SI1: %d, SI2: %d\n", Freq, Dest -> TransitionRatio, Dest -> SubSynth1Index, Dest -> SubSynth2Index);
    else
        printf("SS2 -> SS1 at %f, Ratio: %f, SI1: %d, SI2: %d\n", Freq, Dest -> TransitionRatio, Dest -> SubSynth1Index, Dest -> SubSynth2Index);
*/
    Dest -> SynthFreq = Freq;
}

void PitchMixer_SetLimitedFrequency(PitchMixer* Dest, float Freq)
{
    Dest -> LimitedFreq = Freq;
}


PitchMixerSendback PitchMixer_Synthesis(PitchMixer* Dest, FDFrame* Output)
{
    PitchMixerSendback Ret;
    FDFrame Tmp1, Tmp2;
    FDFrame_CtorSize(& Tmp1, CVE_FFTSize);
    FDFrame_CtorSize(& Tmp2, CVE_FFTSize);

    CPF_Setup(CPF1);
    CPF_Setup(CPF2);
#ifdef PitchMixer_LCEnabled
    LCFECSOLAFilter LCFilter1, LCFilter2;
    LCFECSOLAFilter_Ctor(& LCFilter1);
    LCFECSOLAFilter_Ctor(& LCFilter2);
#else
    FECSOLAFilter FFilter1, FFilter2;
    FECSOLAFilter_Ctor(& FFilter1);
    FECSOLAFilter_Ctor(& FFilter2);
#endif
    FECSOLAState State1, State2;
    FECSOLAState DestState;
    float* Magn = FloatMalloc(CVE_FFTSize);
    float* TmpMagn = FloatMalloc(CVE_FFTSize);
    float* AvgMagn = FloatMalloc(CVE_FFTSize);
    float HopSize;
    float Ratio;

    #if PitchMixer_SkipSynth == 1
        FSynthSendback _SubRet = FSynth_Synthesis(& Dest -> SubSynth1, Output);
        Ret.PSOLAFrameHopSize = _SubRet.PSOLAFrameHopSize;
        Ret.BeforeVOT = _SubRet.BeforeVOT;
        Ret.FState = _SubRet.FState;
        goto JMP_SkipSynth;
    #endif

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
            Mixer_SoleSynth_Prepare(1);
            #ifdef PitchMixer_LCEnabled
                LCFECSOLAFilter_GetFromFormantEnvelope(& LCFilter1, Magn, & SubRet.FState);
                PitchMixer_CreateState(DestState, 1);
                Mixer_SoleSynth_Bake_LCFECSOLA(1);
            #else
                FECSOLAFilter_GetFromCPF(& FFilter1, & CPF1, & SubRet.FState);
                PitchMixer_CreateState(DestState, 1);
                Mixer_SoleSynth_Bake(1);
            #endif
        }
        Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize;
        Ret.BeforeVOT = SubRet.BeforeVOT;
        goto SynthesisFinished;
    }else
    {
        PitchMixer_CreateState(State1, 1);
        PitchMixer_CreateState(State2, 2);
        FECSOLAState_Transition(& DestState, & State1, & State2, Dest -> TransitionRatio);

        if(Dest -> SubSynth1Index < Dest -> SubSynth2Index)
        {
            //SubSynth1: LF
            //SubSynth2: HF
            if(Dest -> TransitionRatio < PitchMixer_TransitionRatio)
            {
                //Sole Synth: SubSynth1
                FSynthSendback SubRet = FSynth_Synthesis(& Dest -> SubSynth1, & Tmp1);
                Mixer_SoleSynth_Prepare(1);
                #ifdef PitchMixer_LCEnabled
                    LCFECSOLAFilter_GetFromFormantEnvelope(& LCFilter1, Magn, & SubRet.FState);
                    Mixer_SoleSynth_Bake_LCFECSOLA(1);
                #else
                    FECSOLAFilter_GetFromCPF(& FFilter1, & CPF1, & SubRet.FState);
                    Mixer_SoleSynth_Bake(1);
                #endif

                Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize;
                Ret.BeforeVOT = 0;
                goto SynthesisFinished;
            }else
            {
                //Trans Synth
                Ratio = (Dest -> TransitionRatio - PitchMixer_TransitionRatio) / (1.0f - PitchMixer_TransitionRatio);
            }
        }else
        {
            //SubSynth1: HF
            //SubSynth2: LF
            if(Dest -> TransitionRatio > 1.0f - PitchMixer_TransitionRatio)
            {
                //Sole Synth: SubSynth2
                FSynthSendback SubRet = FSynth_Synthesis(& Dest -> SubSynth2, & Tmp2);
                Mixer_SoleSynth_Prepare(2);
                #ifdef PitchMixer_LCEnabled
                    LCFECSOLAFilter_GetFromFormantEnvelope(& LCFilter2, Magn, & SubRet.FState);
                    Mixer_SoleSynth_Bake_LCFECSOLA(2);
                #else
                    FECSOLAFilter_GetFromCPF(& FFilter2, & CPF2, & SubRet.FState);
                    Mixer_SoleSynth_Bake(2);
                #endif
                Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize;
                Ret.BeforeVOT = 0;
                goto SynthesisFinished;
            }else
            {
                //Trans Synth
                Ratio = (Dest -> TransitionRatio) / (1.0f - PitchMixer_TransitionRatio);
            }
        }
    }

    //Transition Synthesis

    #define _PitchMixer_
    #include "MixerPitchTransition.h"
    #undef _PitchMixer_

    Ret.PSOLAFrameHopSize = (int)HopSize;
    Ret.BeforeVOT = 0;

    SynthesisFinished:
    Ret.FState = DestState;

    #if PitchMixer_SkipSynth == 1
    JMP_SkipSynth:
    #endif


    free(Magn);
    free(TmpMagn);
    free(AvgMagn);
    CPF_Dtor(& CPF1);
    CPF_Dtor(& CPF2);
#ifdef PitchMixer_LCEnabled
    LCFECSOLAFilter_Dtor(& LCFilter1);
    LCFECSOLAFilter_Dtor(& LCFilter2);
#else
    FECSOLAFilter_Dtor(& FFilter1);
    FECSOLAFilter_Dtor(& FFilter2);
#endif
    FDFrame_Dtor(& Tmp1);
    FDFrame_Dtor(& Tmp2);
    return Ret;
}

PitchMixerSendback PitchMixer_EmptySynthesis(PitchMixer* Dest)
{
    PitchMixerSendback Ret;

    FECSOLAState State1, State2;
    if(! Dest -> IsLimitedFreq)
    {
        PitchMixer_CreateState(State1, 1);
        PitchMixer_CreateState(State2, 2);
        FECSOLAState_Transition(& Ret.FState, & State1, & State2, Dest -> TransitionRatio);
    }

    return Ret;
}

float PitchMixer_GetVOT(PitchMixer* Dest)
{
    return FSynth_GetVOT(& Dest -> SubSynth1);
}
