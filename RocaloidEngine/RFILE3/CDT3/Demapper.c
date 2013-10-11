#include "Demapper.h"
#include <string.h>

#define FreqErrorAllowed 3
#define Mix(a, b, Ratio) (a) * (1.0f - (Ratio)) + (b) * (Ratio)
#define VERBOSE

CDTMappingQuerySpace* QuerySpace;
CDTMap* QueryMap;

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

void Demapper_FormantFusedListVerbose(CDTMappingQuerySpace* Src, int Index)
{
    int i;
    for(i = 0; i <= Src -> FormantLayerFusedList[Index].EntryList_Index; i ++)
    {
        #define PDest GetFusedFormantLayerEntry(Src, Index, i)
        printf("Phone: %s\tF0: %f\tName: %s\tF1: %f\tF2: %f\tF3: %f\tS1: %f\tS2: %f\tS3: %f\n",
               String_GetChars(& Src -> FormantLayerPhone[Index]),
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
                                                               & Src -> FormantLayerMap[GetFormantLayerIndex(Dest, i, j)].FPhone);
            ArrayType_PushNull(FormantLayerPartialEntry, Dest -> FormantLayerFusedList[i].EntryList);
            FormantLayerPartialEntry_Ctor(& TopOf(Dest -> FormantLayerFusedList[i].EntryList));
            Index = GetFormantLayerIndex(Dest, i, j);

            #define CopyDest GetFusedFormantLayerEntry(Dest, i, j)
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
            String_Copy(& CopyDest.Name, & Src -> FreqLayerMap[GetFreqLayerIndex(Dest, SymbolIndex, Match)].Name);
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

            SymbolIndex = Demapper_FindFreqLayerFreqQuerySpace(
                          Dest,
                          & Src -> FormantLayerMap[GetFormantLayerIndex(Dest, i, c)].FPhone);
            c ++;

            LowerEntry = & GetFusedFormantLayerEntry(Dest, i, j);
            UpperEntry = & GetFusedFormantLayerEntry(Dest, i, j + 1);
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
                FormantLayerPartialEntry_Ctor(& GetFusedFormantLayerEntry(Dest, i, j));

                #define CopyDest GetFusedFormantLayerEntry(Dest, i, j)
                String_Copy(& CopyDest.Name, & Src -> FreqLayerMap[GetFreqLayerIndex(Dest, SymbolIndex, k)].Name);

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
        #ifdef VERBOSE
        Demapper_FormantFusedListVerbose(Dest, i);
        #endif
    }
}

void Demapper_ConstructQuerySpace(CDTMappingQuerySpace* Dest, CDTMap* Src)
{
    Demapper_ConstructFreqQueryList(Dest, Src);
    Demapper_ConstructFormantQueryList(Dest, Src);
    Demapper_ConstructFormantFusedList(Dest, Src);
}

void Demapper_SetQuerySpace(CDTMappingQuerySpace* Src)
{
    QuerySpace = Src;
}

void Demapper_SetCDTMap(CDTMap* Src)
{
    QueryMap = Src;
}

//Return: Index of DBLayer
int Demapper_QueryDBLayer(String* Name)
{
    int i;
    for(i = 0; i <= QueryMap -> DBLayerMap_Index; i ++)
        if(String_Equal(& QueryMap -> DBLayerMap[i].Name, Name))
            return i;
    return - 1;
}

//Return: Index of SymbolLayer
int Demapper_QuerySymbolLayer(String* Name)
{
    int i;
    for(i = 0; i <= QueryMap -> SymbolLayerMap_Index; i ++)
        if(String_Equal(& QueryMap -> SymbolLayerMap[i].Name, Name))
            return i;
    return - 1;
}

//Return: Index of FreqLayer
int Demapper_QueryFreqLayer(String* FPhone, float F0)
{
    int Index, Match;
    Match = Demapper_FindFreqLayerFreqQuerySpace(QuerySpace, FPhone);
    if(Match == - 1)
        return - 1;
    ArrayType_IncreaseSortFind(Index, float, QuerySpace -> FreqLayerEntryList[Match].F0, F0);
    return GetFreqLayerIndex(QuerySpace, Match, Index - 1);
}

Transition Demapper_QueryFusedFormantLayer(String* Phone, float F0)
{
    Transition Ret;
    int Match, i;
    Match = Demapper_FindFormantLayerFreqQuerySpace(QuerySpace, Phone);
    Ret.Index = Match;
    if(Match == - 1)
    {
        Ret.SubIndex = - 1;
        return Ret;
    }
    for(i = 0; i <= QuerySpace -> FormantLayerFusedList[Match].EntryList_Index; i ++)
        if(GetFusedFormantLayerEntry(QuerySpace, Match, i).F0 > F0)
            break;
    Ret.SubIndex = i - 1;
    if(Ret.SubIndex < 0)
    {
        Ret.SubIndex = 0;
        Ret.Ratio = 0;
    }else
    {
        if(Ret.SubIndex == QuerySpace -> FormantLayerFusedList[Match].EntryList_Index)
        {
            //Reach Max
            Ret.Ratio = 0;
        }else
            Ret.Ratio = (F0 - GetFusedFormantLayerEntry(QuerySpace, Match, Ret.SubIndex).F0) /
                        (GetFusedFormantLayerEntry(QuerySpace, Match, Ret.SubIndex + 1).F0 -
                         GetFusedFormantLayerEntry(QuerySpace, Match, Ret.SubIndex + 0).F0);
    }
    return Ret;
}

//Return: Index of TransitionLayer
TransitionLayerQueryResult Demapper_QueryTransitionLayer(String* Phone1, String* Phone2)
{
    int i;
    TransitionLayerQueryResult Ret;
    Ret.Index = - 1;
    Ret.MatchRev = - 1;
    for(i = 0; i <= QueryMap -> TransitionLayerMap_Index; i ++)
    {
        if(! String_Equal(& QueryMap -> TransitionLayerMap[i].Phone1, Phone1))
        {
            if(! String_Equal(& QueryMap -> TransitionLayerMap[i].Phone1, Phone2))
                continue;
            else if(String_Equal(& QueryMap -> TransitionLayerMap[i].Phone2, Phone1))
            {
                Ret.MatchRev = 1;
                goto Matched;
            }else
                continue;
        }
        if(! String_Equal(& QueryMap -> TransitionLayerMap[i].Phone2, Phone2))
            continue;
        else
            Ret.MatchRev = 0;
        Matched:
        Ret.Index = i;
        break;
    }
    return Ret;
}
