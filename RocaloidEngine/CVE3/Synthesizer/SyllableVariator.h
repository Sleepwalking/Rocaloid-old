#ifndef SYLLABLEVARIATOR_H
#define SYLLABLEVARIATOR_H

#include "../../../RUtil/RUtil.h"
#include "../../../RUtil/Structure/VariationList.h"
#include "../../RFILE3/CVS3/CVS3.h"

AutoClass
{
    VariationList TransVariator;

    VariationList F0Variator;
    VariationList F1Variator;
    VariationList F2Variator;
    VariationList F3Variator;
    VariationList S1Variator;
    VariationList S2Variator;
    VariationList S3Variator;

    VariationList EnvVariator;
} EndClass(SyllableVariator);

extern void SyllableVariator_LoadSyllable(SyllableVariator* Dest, Syllable* Src);
extern void SyllableVariator_LoadTrans(SyllableVariator* Dest, Syllable* Src, int Index);

extern float SyllableVariator_QueryTransRatio(SyllableVariator* Src, float Time);

extern float SyllableVariator_QueryF0(SyllableVariator* Src, float Time);
extern float SyllableVariator_QueryF1(SyllableVariator* Src, float Time);
extern float SyllableVariator_QueryF2(SyllableVariator* Src, float Time);
extern float SyllableVariator_QueryF3(SyllableVariator* Src, float Time);
extern float SyllableVariator_QueryS1(SyllableVariator* Src, float Time);
extern float SyllableVariator_QueryS2(SyllableVariator* Src, float Time);
extern float SyllableVariator_QueryS3(SyllableVariator* Src, float Time);

extern float SyllableVariator_QueryEnv(SyllableVariator* Src, float Time);
#endif
