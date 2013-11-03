#ifndef DEMAPPER_H
#define DEMAPPER_H

#include "../RUtil/RUtil.h"
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

#define GetFreqLayerIndex(Src, FPhoneIndex, EntryIndex) Src -> FreqLayerEntryList[FPhoneIndex].Index[EntryIndex]
#define GetFormantLayerIndex(Src, PhoneIndex, EntryIndex) Src -> FormantLayerEntryList[PhoneIndex].Index[EntryIndex]
#define GetFusedFormantLayerEntry(Src, PhoneIndex, EntryIndex) Src -> FormantLayerFusedList[PhoneIndex].EntryList[EntryIndex]

//Shortcuts SymbolLayer & FormantLayer
extern void Demapper_ConstructQuerySpace(CDTMappingQuerySpace* Dest, CDTMap* Src);

extern void Demapper_SetQuerySpace(CDTMappingQuerySpace* Src);
extern void Demapper_SetCDTMap(CDTMap* Src);

//Return: Index of DBLayer
extern int Demapper_QueryDBLayer(String* Name);
//Return: Index of SymbolLayer
extern int Demapper_QuerySymbolLayer(String* Name);
//Return: Index of FreqLayer
extern int Demapper_QueryFreqLayer(String* FPhone, float F0);

typedef struct
{
    int Index;
    int SubIndex;
    float Ratio;
    int Reach;
} Transition;
extern Transition Demapper_QueryFusedFormantLayer(String* Phone, float F0);

typedef struct
{
    int Index;
    int MatchRev;
} TransitionLayerQueryResult;
TransitionLayerQueryResult Demapper_QueryTransitionLayer(String* Phone1, String* Phone2);

#endif
