#ifndef CVS3_H
#define CVS3_H

#include "RUtil/RUtil.h"

AutoClass
{
    float Time;
    float Ratio;
} EndClass(TimeRatioPair);

AutoClass
{
    float Time;
    float Freq;
} EndClass(TimeFreqPair);

AutoClass
{
    float Time;
    float Strength;
} EndClass(TimeStrengthPair);

AutoClass
{
    float Time;
    float Volume;
} EndClass(TimeVolumePair);

AutoClass
{
    ArrayType_Define(TimeFreqPair, F1List);
    ArrayType_Define(TimeFreqPair, F2List);
    ArrayType_Define(TimeFreqPair, F3List);

    ArrayType_Define(TimeStrengthPair, S1List);
    ArrayType_Define(TimeStrengthPair, S2List);
    ArrayType_Define(TimeStrengthPair, S3List);
} EndClass(FormantInfo);

AutoClass
{
    ArrayType_Define(TimeVolumePair, EnvelopeList);
} EndClass(EffectInfo);

AutoClass
{
    int TransitionQ;
    ArrayType_Define(String, TransitionPhoneList);
    ArrayType_Define(float, TransitionTickList);
    ArrayType_Define(TimeRatioPair, TransitionRatioList);
    float TransitionEndingRatio;
    float ConsonantRatio;

    FormantInfo FormantDeviation;
    EffectInfo Effects;
    ArrayType_Define(TimeFreqPair, FreqList);

    float StartTime;
} EndClass(Syllable);

AutoClass
{
    ArrayType_Define(Syllable, SyllableList);
} EndClass(CVS3);

#endif
