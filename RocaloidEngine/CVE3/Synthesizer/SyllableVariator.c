#include "SyllableVariator.h"

_Constructor_ (SyllableVariator)
{
    VariationList_Ctor(& Dest -> TransVariator);

    VariationList_Ctor(& Dest -> F0Variator);
    VariationList_Ctor(& Dest -> F1Variator);
    VariationList_Ctor(& Dest -> F2Variator);
    VariationList_Ctor(& Dest -> F3Variator);
    VariationList_Ctor(& Dest -> S1Variator);
    VariationList_Ctor(& Dest -> S2Variator);
    VariationList_Ctor(& Dest -> S3Variator);

    VariationList_Ctor(& Dest -> EnvVariator);
}

_Destructor_ (SyllableVariator)
{
    VariationList_Dtor(& Dest -> TransVariator);

    VariationList_Dtor(& Dest -> F0Variator);
    VariationList_Dtor(& Dest -> F1Variator);
    VariationList_Dtor(& Dest -> F2Variator);
    VariationList_Dtor(& Dest -> F3Variator);
    VariationList_Dtor(& Dest -> S1Variator);
    VariationList_Dtor(& Dest -> S2Variator);
    VariationList_Dtor(& Dest -> S3Variator);

    VariationList_Dtor(& Dest -> EnvVariator);
}

void SyllableVariator_LoadSyllable(SyllableVariator* Dest, Syllable* Src)
{
#define FAddPair(Num, Descriptor, Independent) \
    for(i = 0; i <= Src -> FormantDeviation.Descriptor##Num##List_Index; i ++) \
        VariationList_AddPair(& Dest -> Descriptor##Num##Variator, \
        Src -> FormantDeviation.Descriptor##Num##List[i].Time, \
        Src -> FormantDeviation.Descriptor##Num##List[i].Independent)

    int i;
    VariationList_Clear(& Dest -> TransVariator);
    VariationList_Clear(& Dest -> F0Variator);
    VariationList_Clear(& Dest -> F1Variator);
    VariationList_Clear(& Dest -> F2Variator);
    VariationList_Clear(& Dest -> F3Variator);
    VariationList_Clear(& Dest -> S1Variator);
    VariationList_Clear(& Dest -> S2Variator);
    VariationList_Clear(& Dest -> S3Variator);
    VariationList_Clear(& Dest -> EnvVariator);

    for(i = 0; i <= Src -> FreqList_Index; i ++)
        VariationList_AddPair(& Dest -> F0Variator,
                              Src -> FreqList[i].Time,
                              Src -> FreqList[i].Freq);

    for(i = 0; i <= Src -> Effects.EnvelopeList_Index; i ++)
        VariationList_AddPair(& Dest -> EnvVariator,
                              Src -> Effects.EnvelopeList[i].Time,
                              Src -> Effects.EnvelopeList[i].Volume);

    FAddPair(1, F, Freq);
    FAddPair(2, F, Freq);
    FAddPair(3, F, Freq);
    FAddPair(1, S, Strength);
    FAddPair(2, S, Strength);
    FAddPair(3, S, Strength);

#undef FAddPair
}

void SyllableVariator_LoadTrans(SyllableVariator* Dest, Syllable* Src, int Index)
{
    int i;
    float LTime, HTime;
    VariationList_Clear(& Dest -> TransVariator);
    VariationList_AddPair(& Dest -> TransVariator, Src -> TransitionTickList[Index], 0);
    if(Index < Src -> TransitionPhoneList_Index - 1)
        VariationList_AddPair(& Dest -> TransVariator, Src -> TransitionTickList[Index + 1], 1);
    else
    {
        Index = Src -> TransitionPhoneList_Index - 1;
        VariationList_AddPair(& Dest -> TransVariator, Src -> TransitionTickList[Index + 1], Src -> TransitionEndingRatio);
    }
    LTime = Src -> TransitionTickList[Index + 0];
    HTime = Src -> TransitionTickList[Index + 1];
    for(i = 0; i <= Src -> TransitionRatioList_Index; i ++)
        if(Src -> TransitionRatioList[i].Time > LTime && Src -> TransitionRatioList[i].Time < HTime)
            VariationList_AddPair(& Dest -> TransVariator, Src -> TransitionRatioList[i].Time, Src -> TransitionRatioList[i].Ratio);
}

float SyllableVariator_QueryTransRatio(SyllableVariator* Src, float Time)
{
    return VariationList_Query(& Src -> TransVariator, Time).Weighted;
}

float SyllableVariator_QueryEnv(SyllableVariator* Src, float Time)
{
    return VariationList_Query(& Src -> EnvVariator, Time).Weighted;
}

#define FDefVariator(Descriptor, Num) \
    float SyllableVariator_Query##Descriptor##Num(SyllableVariator* Src, float Time) \
    { \
        return VariationList_Query(& Src -> Descriptor##Num##Variator, Time).Weighted; \
    }

FDefVariator(F, 0)
FDefVariator(F, 1)
FDefVariator(F, 2)
FDefVariator(F, 3)
FDefVariator(S, 1)
FDefVariator(S, 2)
FDefVariator(S, 3)
