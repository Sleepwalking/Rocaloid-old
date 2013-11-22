#include "CVS3.h"

_Constructor_ (TimeRatioPair) {Dest = Dest;}
_Destructor_ (TimeRatioPair) {Dest = Dest;}
_Constructor_ (TimeFreqPair) {Dest = Dest;}
_Destructor_ (TimeFreqPair) {Dest = Dest;}
_Constructor_ (TimeStrengthPair) {Dest = Dest;}
_Destructor_ (TimeStrengthPair) {Dest = Dest;}
_Constructor_ (TimeVolumePair) {Dest = Dest;}
_Destructor_ (TimeVolumePair) {Dest = Dest;}

_Constructor_ (FormantInfo)
{
    ArrayType_Init(TimeFreqPair, Dest -> F1List);
    ArrayType_Init(TimeFreqPair, Dest -> F2List);
    ArrayType_Init(TimeFreqPair, Dest -> F3List);

    ArrayType_Init(TimeStrengthPair, Dest -> S1List);
    ArrayType_Init(TimeStrengthPair, Dest -> S2List);
    ArrayType_Init(TimeStrengthPair, Dest -> S3List);
}

_Destructor_ (FormantInfo)
{
    ArrayType_Dtor(TimeFreqPair, Dest -> F1List);
    ArrayType_Dtor(TimeFreqPair, Dest -> F2List);
    ArrayType_Dtor(TimeFreqPair, Dest -> F3List);

    ArrayType_Dtor(TimeStrengthPair, Dest -> S1List);
    ArrayType_Dtor(TimeStrengthPair, Dest -> S2List);
    ArrayType_Dtor(TimeStrengthPair, Dest -> S3List);
}

_Constructor_ (EffectInfo)
{
    ArrayType_Init(TimeVolumePair, Dest -> EnvelopeList);
}

_Destructor_ (EffectInfo)
{
    ArrayType_Dtor(TimeVolumePair, Dest -> EnvelopeList);
}

_Constructor_ (Syllable)
{
    ArrayType_Init(String, Dest -> TransitionPhoneList);
    ArrayType_Init(float, Dest -> TransitionTickList);
    ArrayType_Init(TimeRatioPair, Dest -> TransitionRatioList);
    ArrayType_Init(TimeFreqPair, Dest -> FreqList);

    FormantInfo_Ctor(& Dest -> FormantDeviation);
    EffectInfo_Ctor(& Dest -> Effects);
}

_Destructor_ (Syllable)
{
    ArrayType_ObjDtor(String, Dest -> TransitionPhoneList);

    ArrayType_Dtor(String, Dest -> TransitionPhoneList);
    ArrayType_Dtor(float, Dest -> TransitionTickList);
    ArrayType_Dtor(TimeRatioPair, Dest -> TransitionRatioList);
    ArrayType_Dtor(TimeFreqPair, Dest -> FreqList);

    FormantInfo_Dtor(& Dest -> FormantDeviation);
    EffectInfo_Dtor(& Dest -> Effects);
    Dest -> StartTime = 0;
    Dest -> Duration = 0;
    Dest -> EndTime = 0;
}

_Constructor_ (CVS3)
{
    ArrayType_Init(Syllable, Dest -> SyllableList);
}

_Destructor_ (CVS3)
{
    ArrayType_ObjDtor(Syllable, Dest -> SyllableList);
    ArrayType_Dtor(Syllable, Dest -> SyllableList);
}
