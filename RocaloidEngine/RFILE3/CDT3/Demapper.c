#include "Demapper.h"
#include <string.h>

#define FreqErrorAllowed 3
#define Mix(a, b, Ratio) (a) * (1.0f - (Ratio)) + (b) * (Ratio)

_Constructor_ (FormantLayerPartialEntry)
{
    memset(Dest, sizeof(FormantLayerPartialEntry), 1);
    String_Ctor(& Dest -> Name);
}

_Destructor_ (FormantLayerPartialEntry)
{
    String_Dtor(& Dest -> Name);
}

_Constructor_ (FormantLayerFusedQuerySpace)
{
    ArrayType_Init(FormantLayerPartialEntry, Dest -> EntryList);
}

_Destructor_ (FormantLayerFusedQuerySpace)
{
    ArrayType_ObjDtor(FormantLayerPartialEntry, Dest -> EntryList);
    ArrayType_Dtor(FormantLayerPartialEntry, Dest -> EntryList);
}

_Constructor_ (FreqQuerySpace)
{
    ArrayType_Init(float, Dest -> F0);
    ArrayType_Init(int, Dest -> Index);
}

_Destructor_ (FreqQuerySpace)
{
    ArrayType_Dtor(float, Dest -> F0);
    ArrayType_Dtor(int, Dest -> Index);
}

_Constructor_ (CDTMappingQuerySpace)
{
    ArrayType_Init(FreqQuerySpace, Dest -> FreqLayerEntryList);
    ArrayType_Init(FreqQuerySpace, Dest -> FormantLayerEntryList);
    ArrayType_Init(FormantLayerFusedQuerySpace, Dest -> FormantLayerFusedList);
    ArrayType_Init(String, Dest -> FreqLayerFPhone);
    ArrayType_Init(String, Dest -> FormantLayerPhone);
}

_Destructor_ (CDTMappingQuerySpace)
{
    ArrayType_ObjDtor(FreqQuerySpace, Dest -> FreqLayerEntryList);
    ArrayType_ObjDtor(FreqQuerySpace, Dest -> FormantLayerEntryList);
    ArrayType_ObjDtor(FormantLayerFusedQuerySpace, Dest -> FormantLayerFusedList);
    ArrayType_ObjDtor(String, Dest -> FreqLayerFPhone);
    ArrayType_ObjDtor(String, Dest -> FormantLayerPhone);

    ArrayType_Dtor(FreqQuerySpace, Dest -> FreqLayerEntryList);
    ArrayType_Dtor(FreqQuerySpace, Dest -> FormantLayerEntryList);
    ArrayType_Dtor(FormantLayerFusedQuerySpace, Dest -> FormantLayerFusedList);
    ArrayType_Dtor(String, Dest -> FreqLayerFPhone);
    ArrayType_Dtor(String, Dest -> FormantLayerPhone);
}

int Demapper_FindFreqLayerFreqQuerySpace(CDTMappingQuerySpace* Src, const String* FPhone)
{
    int i;
    for(i = 0; i <= Src -> FreqLayerFPhone_Index; i ++)
        if(String_Equal(FPhone, Src -> FreqLayerFPhone + i))
            return i;
    return - 1;
}

int Demapper_FindFormantLayerFreqQuerySpace(CDTMappingQuerySpace* Src, const String* Phone)
{
    int i;
    for(i = 0; i <= Src -> FormantLayerPhone_Index; i ++)
        if(String_Equal(Phone, Src -> FormantLayerPhone + i))
            return i;
    return - 1;
}

void Demapper_ConstructFreqQueryList(CDTMappingQuerySpace* Dest, CDTMap* Src)
{
    int i;
    int Match, InsertPos;
    for(i = 0; i <= Src -> FreqLayerMap_Index; i ++)
    {
        Match = Demapper_FindFreqLayerFreqQuerySpace(Dest, & Src -> FreqLayerMap[i].FPhone);
        if(Match == - 1)
        {
            //No match, need to construct.
            ArrayType_PushObj(String, Dest -> FreqLayerFPhone, & Src -> FreqLayerMap[i].FPhone);
            ArrayType_PushNull(FreqQuerySpace, Dest -> FreqLayerEntryList);
            FreqQuerySpace_Ctor(& TopOf(Dest -> FreqLayerEntryList));
            Match = Dest -> FreqLayerFPhone_Index;
        }
        //Insert by increasing trend.
        ArrayType_IncreaseSortFind(InsertPos, float,
                                   Dest -> FreqLayerEntryList[Match].F0,
                                   Src -> FreqLayerMap[i].F0);
        ArrayType_Insert(float, Dest -> FreqLayerEntryList[Match].F0, InsertPos, Src -> FreqLayerMap[i].F0);
        ArrayType_Insert(int, Dest -> FreqLayerEntryList[Match].Index, InsertPos, i);
    }
}

void Demapper_ConstructFormantQueryList(CDTMappingQuerySpace* Dest, CDTMap* Src)
{
    int i;
    int Match, InsertPos;
    for(i = 0; i <= Src -> FormantLayerMap_Index; i ++)
    {
        Match = Demapper_FindFormantLayerFreqQuerySpace(Dest, & Src -> FormantLayerMap[i].Phone);
        if(Match == - 1)
        {
            //No match, need to construct.
            ArrayType_PushObj(String, Dest -> FormantLayerPhone, & Src -> FormantLayerMap[i].Phone);
            ArrayType_PushNull(FreqQuerySpace, Dest -> FormantLayerEntryList);
            FreqQuerySpace_Ctor(& TopOf(Dest -> FormantLayerEntryList));
            Match = Dest -> FormantLayerPhone_Index;
        }
        //Insert by increasing trend.
        ArrayType_IncreaseSortFind(InsertPos, float,
                                   Dest -> FormantLayerEntryList[Match].F0,
                                   Src -> FormantLayerMap[i].F0);
        ArrayType_Insert(float, Dest -> FormantLayerEntryList[Match].F0, InsertPos, Src -> FormantLayerMap[i].F0);
        ArrayType_Insert(int, Dest -> FormantLayerEntryList[Match].Index, InsertPos, i);
    }
}

void Demapper_ConstructFormantFusedList(CDTMappingQuerySpace* Dest, CDTMap* Src)
{
    int i, j, k, c;
    int SymbolIndex;
    for(i = 0; i <= Dest -> FormantLayerPhone_Index; i ++)
    {
        ArrayType_PushNull(FormantLayerFusedQuerySpace, Dest -> FormantLayerFusedList);
        FormantLayerFusedQuerySpace_Ctor(& TopOf(Dest -> FormantLayerFusedList));
        //For each QuerySpace
        //1. Fill original map
        for(j = 0; j <= Dest -> FormantLayerEntryList[i].Index_Index; j ++)
        {
            int Index, Match;
            SymbolIndex = Demapper_FindFreqLayerFreqQuerySpace(Dest,
                                                               & Src -> FormantLayerMap[Dest -> FormantLayerEntryList[i].Index[j]].FPhone);
            ArrayType_PushNull(FormantLayerPartialEntry, Dest -> FormantLayerFusedList[i].EntryList);
            FormantLayerPartialEntry_Ctor(& TopOf(Dest -> FormantLayerFusedList[i].EntryList));
            Index = Dest -> FormantLayerEntryList[i].Index[j];

#define CopyDest Dest -> FormantLayerFusedList[i].EntryList[j]
#define CopySrc Src -> FormantLayerMap[Index]
            CopyDest.F0 = CopySrc.F0;
            CopyDest.F1 = CopySrc.F1;
            CopyDest.F2 = CopySrc.F2;
            CopyDest.F3 = CopySrc.F3;
            CopyDest.S1 = CopySrc.S1;
            CopyDest.S2 = CopySrc.S2;
            CopyDest.S3 = CopySrc.S3;
            //Copy Symbol Name
            ArrayType_IncreaseSortFind(Match, float,
                                       Dest -> FreqLayerEntryList[SymbolIndex].F0,
                                       Dest -> FormantLayerEntryList[i].F0[j] + FreqErrorAllowed);
            if(Match > 0) Match --;
            String_Copy(& CopyDest.Name, & Src -> FreqLayerMap[Dest -> FreqLayerEntryList[SymbolIndex].Index[Match]].Name);
#undef CopyDest
#undef CopySrc
        }

        //2. Insert FreqEntries into intervals
        c = 0;
        for(j = 0; j < Dest -> FormantLayerFusedList[i].EntryList_Index; j ++)
        {
            int LowerIndex, UpperIndex;
            FormantLayerPartialEntry* LowerEntry;
            FormantLayerPartialEntry* UpperEntry;
            float Ratio;

            SymbolIndex = Demapper_FindFreqLayerFreqQuerySpace(Dest,
                                                               & Src -> FormantLayerMap[Dest -> FormantLayerEntryList[i].Index[c]].FPhone);
            c ++;

            LowerEntry = & Dest -> FormantLayerFusedList[i].EntryList[j];
            UpperEntry = & Dest -> FormantLayerFusedList[i].EntryList[j + 1];
            ArrayType_IncreaseSortFind(LowerIndex, float,
                                       Dest -> FreqLayerEntryList[SymbolIndex].F0,
                                       LowerEntry -> F0 + FreqErrorAllowed);

            ArrayType_IncreaseSortFind(UpperIndex, float,
                                       Dest -> FreqLayerEntryList[SymbolIndex].F0,
                                       UpperEntry -> F0 - FreqErrorAllowed);

            for(k = LowerIndex; k < UpperIndex; k ++)
            {
                //For each FreqEntry to be inserted
                j ++;
                ArrayType_InsertNull(FormantLayerPartialEntry, Dest -> FormantLayerFusedList[i].EntryList, j);
                FormantLayerPartialEntry_Ctor(& Dest -> FormantLayerFusedList[i].EntryList[j]);

#define CopyDest Dest -> FormantLayerFusedList[i].EntryList[j]
                String_Copy(& CopyDest.Name, & Src -> FreqLayerMap[Dest -> FreqLayerEntryList[SymbolIndex].Index[k]].Name);
                CopyDest.F0 = Dest -> FreqLayerEntryList[SymbolIndex].F0[k];
                Ratio = (CopyDest.F0 - LowerEntry -> F0) / (UpperEntry -> F0 - LowerEntry -> F0);
                CopyDest.F1 = Mix(LowerEntry -> F1, UpperEntry -> F1, Ratio);
                CopyDest.F2 = Mix(LowerEntry -> F2, UpperEntry -> F2, Ratio);
                CopyDest.F3 = Mix(LowerEntry -> F3, UpperEntry -> F3, Ratio);
                CopyDest.S1 = Mix(LowerEntry -> S1, UpperEntry -> S1, Ratio);
                CopyDest.S2 = Mix(LowerEntry -> S2, UpperEntry -> S2, Ratio);
                CopyDest.S3 = Mix(LowerEntry -> S3, UpperEntry -> S3, Ratio);
#undef CopyDest
            }
        }

        for(j = 0; j <= Dest -> FormantLayerFusedList[i].EntryList_Index; j ++)
        {
#define PDest Dest -> FormantLayerFusedList[i].EntryList[j]
            printf("Phone: %s\tF0: %f\tName: %s\tF1: %f\tF2: %f\tF3: %f\tS1: %f\tS2: %f\tS3: %f\n",
                   String_GetChars(& Dest -> FormantLayerPhone[i]),
                   PDest.F0,
                   String_GetChars(& PDest.Name),
                   PDest.F1,
                   PDest.F2,
                   PDest.F3,
                   PDest.S1,
                   PDest.S2,
                   PDest.S3);
#undef PDest
        }
    }
}

void Demapper_ConstructQuerySpace(CDTMappingQuerySpace* Dest, CDTMap* Src)
{
    Demapper_ConstructFreqQueryList(Dest, Src);
    Demapper_ConstructFormantQueryList(Dest, Src);
    Demapper_ConstructFormantFusedList(Dest, Src);
}
