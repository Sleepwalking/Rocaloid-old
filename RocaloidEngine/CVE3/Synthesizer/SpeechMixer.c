#include "SpeechMixer.h"
#include "MixerMacro.h"
#include "../CVEDSP/Algorithm/Formant.h"
#include "../CVEDSP/Plot.h"
#include "../CVEDSP/Interpolation.h"
#include "../DSPEx/LCFECSOLA.h"
#include "../Debug/ALblLog.h"

#define CVSData (Dest -> CurrentSyl)

_Constructor_ (SpeechMixer)
{
    PitchMixer_Ctor(& Dest -> SubSynth1);
    PitchMixer_Ctor(& Dest -> SubSynth2);
    SyllableVariator_Ctor(& Dest -> CurrentVar);

    Dest -> SubSynth1Index = - 1;
    Dest -> SubSynth2Index = - 1;

    ALblLog_Print("SpeechMixer Ctor");
}

_Destructor_ (SpeechMixer)
{
    PitchMixer_Dtor(& Dest -> SubSynth1);
    PitchMixer_Dtor(& Dest -> SubSynth2);
    SyllableVariator_Dtor(& Dest -> CurrentVar);
    ALblLog_Print("SpeechMixer Dtor");
}

void SpeechMixer_SetSyllable(SpeechMixer* Dest, Syllable* _Syllable)
{
    Dest -> CurrentSyl = _Syllable;
    SyllableVariator_LoadSyllable(& Dest -> CurrentVar, _Syllable);
    SpeechMixer_SetConsonantRatio(Dest, _Syllable -> ConsonantRatio);
    ALblLog_Print("SpeechMixer SetSyllable");
}

void SpeechMixer_SetConsonantRatio(SpeechMixer* Dest, float CRatio)
{
    PitchMixer_SetConsonantRatio(& Dest -> SubSynth1, CRatio);
    PitchMixer_SetConsonantRatio(& Dest -> SubSynth2, CRatio);
    ALblLog_Print("SpeechMixer SetConsonantRatio as %f", CRatio);
}

int SpeechMixer_QuerySyllablePhoneIndex(Syllable* Src, float Time)
{
    int i;
    for(i = 0; i <= Src -> TransitionPhoneList_Index; i ++)
        if(Src -> TransitionTickList[i] > Time)
            break;
    return i - 1;
}

void SpeechMixer_Swap(SpeechMixer* Dest)
{
    int TmpIndex = Dest -> SubSynth1Index;
    Dest -> SubSynth1Index = Dest -> SubSynth2Index;
    Dest -> SubSynth2Index = TmpIndex;
    PitchMixer TmpPitchMixer = Dest -> SubSynth1;
    Dest -> SubSynth1 = Dest -> SubSynth2;
    Dest -> SubSynth2 = TmpPitchMixer;
}

void SpeechMixer_Reset(SpeechMixer* Dest)
{
    PitchMixer_Reset(& Dest -> SubSynth1);
    PitchMixer_Reset(& Dest -> SubSynth2);
    Dest -> SubSynth1Index = - 1;
    Dest -> SubSynth2Index = - 1;
    ALblLog_Print("SpeechMixer Reset");
}

void SpeechMixer_FormantVariation(FECSOLAState* Dest, SyllableVariator* Offset, float Time)
{
    Dest -> F1 += SyllableVariator_QueryF1(Offset, Time);
    Dest -> F2 += SyllableVariator_QueryF2(Offset, Time);
    Dest -> F3 += SyllableVariator_QueryF3(Offset, Time);
    Dest -> S1 *= SyllableVariator_QueryS1(Offset, Time);
    Dest -> S2 *= SyllableVariator_QueryS2(Offset, Time);
    Dest -> S3 *= SyllableVariator_QueryS3(Offset, Time);
}
void SpeechMixer_SetTime(SpeechMixer* Dest, float Time)
{
    //Step1: Reload SubSynth
    int BaseIndex = SpeechMixer_QuerySyllablePhoneIndex(CVSData, Time);
    if(BaseIndex == Dest -> SubSynth1Index)
    {
        //Normal Transition
        Dest -> TransitionRatio = SyllableVariator_QueryTransRatio(& Dest -> CurrentVar, Time);
        //Dest -> TransitionRatio = CosineInterpolate(0, 1, Dest -> TransitionRatio);
    }else if(BaseIndex == Dest -> SubSynth2Index)
    {
        //Next Phoneme
        //SS2 needs to be reloaded.
        SpeechMixer_Swap(Dest);
        SyllableVariator_LoadTrans(& Dest -> CurrentVar, Dest -> CurrentSyl, BaseIndex);
        Dest -> SubSynth2Index = BaseIndex + 1;
        PitchMixer_SetSymbol(& Dest -> SubSynth2, CVSData -> TransitionPhoneList + Dest -> SubSynth2Index);
        Dest -> TransitionRatio = 0;
        ALblLog_Print("SpeechMixer SetTime: Next Phoneme");
    }else
    {
        //Reload All
        Dest -> SubSynth1Index = BaseIndex;
        Dest -> SubSynth2Index = BaseIndex + 1;
        SyllableVariator_LoadTrans(& Dest -> CurrentVar, Dest -> CurrentSyl, BaseIndex);
        PitchMixer_SetSymbol(& Dest -> SubSynth1, CVSData -> TransitionPhoneList + Dest -> SubSynth1Index);
        PitchMixer_SetSymbol(& Dest -> SubSynth2, CVSData -> TransitionPhoneList + Dest -> SubSynth2Index);
        PitchMixer_SetLimitedFrequency(& Dest -> SubSynth1, CVSData -> FreqList[0].Freq); //Assuming first load
        Dest -> TransitionRatio = 0;
        ALblLog_Print("SpeechMixer SetTime: Reload All");
    }

    //Step2: Set Freq
    float SynthFreq = SyllableVariator_QueryF0(& Dest -> CurrentVar, Time);
    PitchMixer_SetFrequency(& Dest -> SubSynth1, SynthFreq);
    PitchMixer_SetFrequency(& Dest -> SubSynth2, SynthFreq);
    PitchMixer_SetConsonantRatio(& Dest -> SubSynth1, CVSData -> ConsonantRatio);
    PitchMixer_SetConsonantRatio(& Dest -> SubSynth2, CVSData -> ConsonantRatio);
    Dest -> CurrentTime = Time;
/*
    ALblLog_Print("SpeechMixer SetTime: SS1 = %s, SS2 = %s",
                  Dest -> SubSynth1.SubSynth1.SubSynth.Data.Header.Symbol,
                  Dest -> SubSynth2.SubSynth1.SubSynth.Data.Header.Symbol);
    //printf("TR: %f, SI1: %d, SI2: %d\n", Dest -> TransitionRatio, Dest -> SubSynth1Index, Dest -> SubSynth2Index);
*/
}

SpeechMixerSendback SpeechMixer_Synthesis(SpeechMixer* Dest, FDFrame* Output)
{
    SpeechMixerSendback Ret;

    float MixRatio;
    #if SpeechMixer_TransitionLayerEnabled == 1
        String* Phone1 = CVSData -> TransitionPhoneList + Dest -> SubSynth1Index;
        String* Phone2 = CVSData -> TransitionPhoneList + Dest -> SubSynth2Index;
        TransitionLayerQueryResult QRsut = Demapper_QueryTransitionLayer(Phone1, Phone2);
        if(QRsut.Index < 0)
            MixRatio = 1.0f;
        else
        {
            MixRatio = CGDict.CDTMapping.TransitionLayerMap[QRsut.Index].Ratio;
            if(QRsut.MatchRev)
                MixRatio = 1.0f - MixRatio;
        }
    #else
        MixRatio = 0;
    #endif

    //ALblLog_Print("SpeechMixer Synthesis: MixRatio = %f, TransitionRatio = %f", MixRatio, Dest -> TransitionRatio);

    FDFrame Tmp1, Tmp2;
    FDFrame_CtorSize(& Tmp1, CVE_FFTSize);
    FDFrame_CtorSize(& Tmp2, CVE_FFTSize);

    CPF_Setup(CPF1);
    CPF_Setup(CPF2);
    LCFECSOLAFilter LCFilter1, LCFilter2;
    LCFECSOLAFilter_Ctor(& LCFilter1);
    LCFECSOLAFilter_Ctor(& LCFilter2);
    FECSOLAState DestState;
    float* Magn = FloatMalloc(CVE_FFTSize);
    float* TmpMagn = FloatMalloc(CVE_FFTSize);
    float* AvgMagn = FloatMalloc(CVE_FFTSize);
    float HopSize;

    PitchMixerSendback SubRet;

    #if SpeechMixer_SkipSynth == 1
        SubRet = PitchMixer_Synthesis(& Dest -> SubSynth1, Output);
        Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize;
        Ret.BeforeVOT = SubRet.BeforeVOT;
        Ret.FState = SubRet.FState;
        goto JMP_SkipSynth;
    #else
        SubRet = PitchMixer_Synthesis(& Dest -> SubSynth1, & Tmp1);
    #endif

    if(SubRet.BeforeVOT)
    {
        Boost_FloatCopy(Output -> Re, Tmp1.Re, Tmp1.Length);
        Boost_FloatCopy(Output -> Im, Tmp1.Im, Tmp1.Length);
        Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize;
        Ret.BeforeVOT = 1;
        Dest -> CurrentVar.TransVariator.Independent[0] = (float)PitchMixer_GetVOT(& Dest -> SubSynth1) / SampleRate;
    }else
    {
        PitchMixerSendback SubRet2 = PitchMixer_EmptySynthesis(& Dest -> SubSynth2);
        FECSOLAState_Transition(& DestState, & SubRet.FState, & SubRet2.FState, Dest -> TransitionRatio);
        SpeechMixer_FormantVariation(& DestState, & Dest -> CurrentVar, Dest -> CurrentTime);
        if(Dest -> TransitionRatio < MixRatio)
        {
            //Sole Synth: SubSynth1
            Mixer_SoleSynth_Prepare(1);
            LCFECSOLAFilter_GetFromCPF(& LCFilter1, & CPF1, & SubRet.FState);
            Mixer_SoleSynth_Bake_LCFECSOLA(1);
            Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize;
            Ret.BeforeVOT = 0;
            Ret.FState = DestState;
        }else
        {
            //Trans Synth
            float Ratio = (Dest -> TransitionRatio - MixRatio) / (1.0f - MixRatio);
            //ALblLog_Print("SpeechMixer Synthesis: Ratio = %f", Ratio);
            #ifdef SpeechMixer_Linear
                Boost_FloatMul(Tmp1.Re, Tmp1.Re, 1.0f - Ratio, CVE_FFTSize);
                Boost_FloatMul(Tmp1.Im, Tmp1.Im, 1.0f - Ratio, CVE_FFTSize);
                HopSize = SubRet.PSOLAFrameHopSize * (1.0f - Ratio);
                SubRet = PitchMixer_Synthesis(& Dest -> SubSynth2, & Tmp2);
                Boost_FloatMul(Tmp2.Re, Tmp2.Re, Ratio, CVE_FFTSize);
                Boost_FloatMul(Tmp2.Im, Tmp2.Im, Ratio, CVE_FFTSize);
                Boost_FloatAddArr(Output -> Re, Tmp1.Re, Tmp2.Re, CVE_FFTSize);
                Boost_FloatAddArr(Output -> Im, Tmp1.Im, Tmp2.Im, CVE_FFTSize);
                HopSize += SubRet.PSOLAFrameHopSize * (Ratio);
            #endif
            #ifdef SpeechMixer_FECSOLA
                #define _SpeechMixer_
                #include "MixerTransition.h"
                #undef _SpeechMixer_
            #endif
            //ALblLog_Print("SpeechMixer Synthesis: F1 = %f, F2 = %f, F3 = %f", DestState.F1, DestState.F2, DestState.F3);
            Ret.PSOLAFrameHopSize = HopSize;
            Ret.BeforeVOT = 0;
            Ret.FState = DestState;
        }
    }

    #if SpeechMixer_SkipSynth == 1
    JMP_SkipSynth:
    #endif

    Boost_FloatMul(Output -> Re, Output -> Re,
                   SyllableVariator_QueryEnv(& Dest -> CurrentVar, Dest -> CurrentTime),
                   CVE_FFTSize);
    Boost_FloatMul(Output -> Im, Output -> Im,
                   SyllableVariator_QueryEnv(& Dest -> CurrentVar, Dest -> CurrentTime),
                   CVE_FFTSize);

    free(Magn);
    free(TmpMagn);
    free(AvgMagn);
    CPF_Dtor(& CPF1);
    CPF_Dtor(& CPF2);
    LCFECSOLAFilter_Dtor(& LCFilter1);
    LCFECSOLAFilter_Dtor(& LCFilter2);
    FDFrame_Dtor(& Tmp1);
    FDFrame_Dtor(& Tmp2);
    return Ret;
}

