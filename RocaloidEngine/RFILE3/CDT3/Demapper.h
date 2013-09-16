#ifndef DEMAPPER_H
#define DEMAPPER_H

#include "RUtil/RUtil.h"
#include "CDT3.h"

AutoClass
{
    float F0;
    String Name;

    float F1;
    float F2;
    float F3;
    float S1;
    float S2;
    float S3;
} EndClass(FormantLayerPartialEntry);

AutoClass
{
    ArrayType_Define(FormantLayerPartialEntry, EntryList);
} EndClass(FormantLayerFusedQuerySpace);

AutoClass
{
    ArrayType_Define(float, F0);
    ArrayType_Define(int, Index);
} EndClass(FreqQuerySpace);

AutoClass
{
    ArrayType_Define(FreqQuerySpace, FreqLayerEntryList);
    ArrayType_Define(String, FreqLayerFPhone);

    ArrayType_Define(FreqQuerySpace, FormantLayerEntryList);
    ArrayType_Define(String, FormantLayerPhone);

    ArrayType_Define(FormantLayerFusedQuerySpace, FormantLayerFusedList);
} EndClass(CDTMappingQuerySpace);

extern void Demapper_ConstructQuerySpace(CDTMappingQuerySpace* Dest, CDTMap* Src);

#endif
