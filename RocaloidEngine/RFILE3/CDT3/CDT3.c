#include "CDT3.h"

void SGtorSyllable_Ctor(SGtorSyllable* Dest)
{
    String_Ctor(& Dest -> Syllable);
    ArrayType_Init(String, Dest -> PhoneList);
}

void SGtorSyllable_Dtor(SGtorSyllable* Dest)
{
    String_Dtor(& Dest -> Syllable);
    ArrayType_ObjDtor(String, Dest -> PhoneList);
    ArrayType_Dtor(String, Dest -> PhoneList);
}

void DBLayerEntry_Ctor(DBLayerEntry* Dest)
{
    String_Ctor(& Dest -> Name);
    String_Ctor(& Dest -> FileAddr);
}

void DBLayerEntry_Dtor(DBLayerEntry* Dest)
{
    String_Dtor(& Dest -> Name);
    String_Dtor(& Dest -> FileAddr);
}

void SymbolLayerEntry_Ctor(SymbolLayerEntry* Dest)
{
    String_Ctor(& Dest -> Name);
}

void SymbolLayerEntry_Dtor(SymbolLayerEntry* Dest)
{
    String_Dtor(& Dest -> Name);
}

void FreqLayerEntry_Ctor(FreqLayerEntry* Dest)
{
    String_Ctor(& Dest -> FPhone);
    String_Ctor(& Dest -> Name);
}

void FreqLayerEntry_Dtor(FreqLayerEntry* Dest)
{
    String_Dtor(& Dest -> FPhone);
    String_Dtor(& Dest -> Name);
}

void FormantLayerEntry_Ctor(FormantLayerEntry* Dest)
{
    String_Ctor(& Dest -> Phone);
    String_Ctor(& Dest -> FPhone);
}

void FormantLayerEntry_Dtor(FormantLayerEntry* Dest)
{
    String_Dtor(& Dest -> Phone);
    String_Dtor(& Dest -> FPhone);
}

void TransitionLayerEntry_Ctor(TransitionLayerEntry* Dest)
{
    String_Ctor(& Dest -> Phone1);
    String_Ctor(& Dest -> Phone2);
}

void TransitionLayerEntry_Dtor(TransitionLayerEntry* Dest)
{
    String_Dtor(& Dest -> Phone1);
    String_Dtor(& Dest -> Phone2);
}

void CDTMap_Ctor(CDTMap* Dest)
{
    ArrayType_Init(DBLayerEntry, Dest -> DBLayerMap);
    ArrayType_Init(SymbolLayerEntry, Dest -> SymbolLayerMap);
    ArrayType_Init(FreqLayerEntry, Dest -> FreqLayerMap);
    ArrayType_Init(FormantLayerEntry, Dest -> FormantLayerMap);
    ArrayType_Init(TransitionLayerEntry, Dest -> TransitionLayerMap);
}

void CDTMap_Dtor(CDTMap* Dest)
{
    ArrayType_ObjDtor(DBLayerEntry, Dest -> DBLayerMap);
    ArrayType_ObjDtor(SymbolLayerEntry, Dest -> SymbolLayerMap);
    ArrayType_ObjDtor(FreqLayerEntry, Dest -> FreqLayerMap);
    ArrayType_ObjDtor(FormantLayerEntry, Dest -> FormantLayerMap);
    ArrayType_ObjDtor(TransitionLayerEntry, Dest -> TransitionLayerMap);

    ArrayType_Dtor(DBLayerEntry, Dest -> DBLayerMap);
    ArrayType_Dtor(SymbolLayerEntry, Dest -> SymbolLayerMap);
    ArrayType_Dtor(FreqLayerEntry, Dest -> FreqLayerMap);
    ArrayType_Dtor(FormantLayerEntry, Dest -> FormantLayerMap);
    ArrayType_Dtor(TransitionLayerEntry, Dest -> TransitionLayerMap);
}

void CDT3_Ctor(CDT3* Dest)
{
    ArrayType_Init(SGtorSyllable, Dest -> SGtorList);
    CDTMap_Ctor(& Dest -> CDTMapping);
}

void CDT3_Dtor(CDT3* Dest)
{
    ArrayType_ObjDtor(SGtorSyllable, Dest -> SGtorList);
    ArrayType_Dtor(SGtorSyllable, Dest -> SGtorList);

    CDTMap_Dtor(& Dest -> CDTMapping);
}
