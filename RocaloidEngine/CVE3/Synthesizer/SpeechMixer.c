#include "SpeechMixer.h"
#include "MixerMacro.h"
#include "CVEDSP/Algorithm/Formant.h"
#include "CVEDSP/Plot.h"

#define CVSData (Dest -> OnSynth)

_Constructor_ (SpeechMixer)
{
    PitchMixer_Ctor(& Dest -> SubSynth1);
    PitchMixer_Ctor(& Dest -> SubSynth2);

    Dest -> SubSynth1Index = - 1;
    Dest -> SubSynth2Index = - 1;
}

_Destructor_ (SpeechMixer)
{
    PitchMixer_Dtor(& Dest -> SubSynth1);
    PitchMixer_Dtor(& Dest -> SubSynth2);
}

void SpeechMixer_SetSyllable(SpeechMixer* Dest, const Syllable* _Syllable)
{
    Dest -> OnSynth = _Syllable;
}

void SpeechMixer_SetConsonantRatio(SpeechMixer* Dest, float CRatio)
{
    PitchMixer_SetConsonantRatio(& Dest -> SubSynth1, CRatio);
    PitchMixer_SetConsonantRatio(& Dest -> SubSynth2, CRatio);
}

int SpeechMixer_QuerySyllablePhoneIndex(const Syllable* Src, float Time)
{
    int i;
    for(i = 0; i < Src -> TransitionQ; i ++)
        if(Src -> TransitionTickList[i] > Time)
            break;
    return i - 1;
}

float SpeechMixer_QuerySyllableFreq(const Syllable* Src, float Time)
{
    int i;
    for(i = 0; i <= Src -> FreqList_Index; i ++)
        if(Src -> FreqList[i].Time > Time)
            goto Found;
    return Src -> FreqList[Src -> FreqList_Index].Freq;
    Found:
    i --;
    float Ratio = (Time - Src -> FreqList[i].Time) / (Src -> FreqList[i + 1].Time - Src -> FreqList[i].Time);
    return Ratio * Src -> FreqList[i + 1].Freq + (1.0f - Ratio) * Src -> FreqList[i].Freq;
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

void SpeechMixer_SetTime(SpeechMixer* Dest, float Time)
{
    //Step1: Reload SubSynth
    int BaseIndex = SpeechMixer_QuerySyllablePhoneIndex(CVSData, Time);
    if(BaseIndex == Dest -> SubSynth1Index)
    {
        //Normal Transition
        Dest -> TransitionRatio = (Time - CVSData -> TransitionTickList[BaseIndex]) /
                                  (CVSData -> TransitionTickList[BaseIndex + 1] -
                                   CVSData -> TransitionTickList[BaseIndex]);
    }else if(BaseIndex == Dest -> SubSynth2Index)
    {
        //Next Phoneme
        //SS2 needs to be reloaded.
        SpeechMixer_Swap(Dest);
        Dest -> SubSynth2Index = BaseIndex + 1;
        PitchMixer_SetSymbol(& Dest -> SubSynth2, CVSData -> TransitionPhoneList + Dest -> SubSynth2Index);
        Dest -> TransitionRatio = 0;
    }else
    {
        //Reload All
        Dest -> SubSynth1Index = BaseIndex;
        Dest -> SubSynth2Index = BaseIndex + 1;
        PitchMixer_SetSymbol(& Dest -> SubSynth1, CVSData -> TransitionPhoneList + Dest -> SubSynth1Index);
        PitchMixer_SetSymbol(& Dest -> SubSynth2, CVSData -> TransitionPhoneList + Dest -> SubSynth2Index);
        PitchMixer_SetLimitedFrequency(& Dest -> SubSynth1, CVSData -> FreqList[0].Freq); //Assuming first load
        Dest -> TransitionRatio = 0;
    }

    //Step2: Set Freq
    float SynthFreq = SpeechMixer_QuerySyllableFreq(CVSData, Time);
    PitchMixer_SetFrequency(& Dest -> SubSynth1, SynthFreq);
    PitchMixer_SetFrequency(& Dest -> SubSynth2, SynthFreq);

    printf("TR: %f, SI1: %d, SI2: %d\n", Dest -> TransitionRatio, Dest -> SubSynth1Index, Dest -> SubSynth2Index);
}

void SpeechMixer_Reset(SpeechMixer* Dest)
{
    PitchMixer_Reset(& Dest -> SubSynth1);
    PitchMixer_Reset(& Dest -> SubSynth2);
    Dest -> SubSynth1Index = - 1;
    Dest -> SubSynth2Index = - 1;
}

SpeechMixerSendback SpeechMixer_Synthesis(SpeechMixer* Dest, FDFrame* Output)
{
    SpeechMixerSendback Ret;
    String* Phone1 = CVSData -> TransitionPhoneList + Dest -> SubSynth1Index;
    String* Phone2 = CVSData -> TransitionPhoneList + Dest -> SubSynth2Index;
    TransitionLayerQueryResult QRsut = Demapper_QueryTransitionLayer(Phone1, Phone2);
    float MixRatio;
    if(QRsut.Index < 0)
        MixRatio = 1.0f;
    else
    {
        MixRatio = CGDict.CDTMapping.TransitionLayerMap[QRsut.Index].Ratio;
        if(QRsut.MatchRev)
            MixRatio = 1.0f - MixRatio;
    }

    FDFrame Tmp1, Tmp2;
    FDFrame_CtorSize(& Tmp1, 1024);
    FDFrame_CtorSize(& Tmp2, 1024);

    CPF_Setup(CPF1);
    CPF_Setup(CPF2);
    FECSOLAFilter FFilter1, FFilter2;
    FECSOLAFilter_Ctor(& FFilter1);
    FECSOLAFilter_Ctor(& FFilter2);
    FECSOLAState DestState;
    float* Magn = FloatMalloc(1024);
    float* TmpMagn = FloatMalloc(1024);
    float* AvgMagn = FloatMalloc(1024);
    float HopSize;

    MixRatio = 0;

    PitchMixerSendback SubRet = PitchMixer_Synthesis(& Dest -> SubSynth1, & Tmp1);
    if(SubRet.BeforeVOT)
    {
        Boost_FloatCopy(Output -> Re, Tmp1.Re, Tmp1.Length);
        Boost_FloatCopy(Output -> Im, Tmp1.Im, Tmp1.Length);
        Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize;
        Ret.BeforeVOT = 1;
    }else
    {
        PitchMixerSendback SubRet2 = PitchMixer_EmptySynthesis(& Dest -> SubSynth2);
        FECSOLAState_Transition(& DestState, & SubRet.FState, & SubRet2.FState, Dest -> TransitionRatio);
        if(Dest -> TransitionRatio < MixRatio)
        {
            //Sole Synth: SubSynth1
            Mixer_SoleSynth_Prepare(1);
            FECSOLAFilter_GetFromFormantEnvelope(& FFilter1, & CPF1, & SubRet.FState);
            Mixer_SoleSynth_Bake(1);
            Ret.PSOLAFrameHopSize = SubRet.PSOLAFrameHopSize;
            Ret.BeforeVOT = 0;
            Ret.FState = DestState;
        }else
        {
            //Trans Synth
            //float Ratio = Dest -> TransitionRatio;
            float Ratio = (Dest -> TransitionRatio - MixRatio) / (1.0f - MixRatio);
            Boost_FloatMul(Tmp1.Re, Tmp1.Re, 1.0f - Ratio, 1024);
            Boost_FloatMul(Tmp1.Im, Tmp1.Im, 1.0f - Ratio, 1024);
            HopSize = SubRet.PSOLAFrameHopSize * (1.0f - Ratio);
            SubRet = PitchMixer_Synthesis(& Dest -> SubSynth2, & Tmp2);
            Boost_FloatMul(Tmp2.Re, Tmp2.Re, Ratio, 1024);
            Boost_FloatMul(Tmp2.Im, Tmp2.Im, Ratio, 1024);
            Boost_FloatAddArr(Output -> Re, Tmp1.Re, Tmp2.Re, 1024);
            Boost_FloatAddArr(Output -> Im, Tmp1.Im, Tmp2.Im, 1024);
            HopSize += SubRet.PSOLAFrameHopSize * (Ratio);
/*
            #define _SpeechMixer_
            #include "MixerPitchTransition.h"
            #undef _SpeechMixer_*/
            Ret.PSOLAFrameHopSize = (int)HopSize;
            Ret.BeforeVOT = 0;
            Ret.FState = DestState;
        }
    }

    free(Magn);
    free(TmpMagn);
    free(AvgMagn);
    CPF_Dtor(& CPF1);
    CPF_Dtor(& CPF2);
    FECSOLAFilter_Dtor(& FFilter1);
    FECSOLAFilter_Dtor(& FFilter2);
    FDFrame_Dtor(& Tmp1);
    FDFrame_Dtor(& Tmp2);
    return Ret;
}

