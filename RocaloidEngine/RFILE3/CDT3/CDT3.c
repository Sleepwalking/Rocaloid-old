#include "CDT3.h"

SyllableType CSyllableTypeStr(String* Dest)
{
    if(String_EqualChars(Dest, "V"))
        return V;
    if(String_EqualChars(Dest, "VV"))
        return VV;
    if(String_EqualChars(Dest, "VVV"))
        return VVV;
    if(String_EqualChars(Dest, "CV"))
        return CV;
    if(String_EqualChars(Dest, "CVV"))
        return CVV;
    if(String_EqualChars(Dest, "CAV"))
        return CAV;
    if(String_EqualChars(Dest, "CAVV"))
        return CAVV;

    //Default
    return V;
}

_Constructor_ (SGtorSyllable)
{
    String_Ctor(& Dest -> Syllable);
    ArrayType_Init(String, Dest -> PhoneList);
}

_Destructor_ (SGtorSyllable)
{
    String_Dtor(& Dest -> Syllable);
    ArrayType_ObjDtor(String, Dest -> PhoneList);
    ArrayType_Dtor(String, Dest -> PhoneList);
}

_Constructor_ (DBLayerEntry)
{
    String_Ctor(& Dest -> Name);
    String_Ctor(& Dest -> FileAddr);
}

_Destructor_ (DBLayerEntry)
{
    String_Dtor(& Dest -> Name);
    String_Dtor(& Dest -> FileAddr);
}

_Constructor_ (SymbolLayerEntry)
{
    String_Ctor(& Dest -> Name);
}

_Destructor_ (SymbolLayerEntry)
{
    String_Dtor(& Dest -> Name);
}

_Constructor_ (FreqLayerEntry)
{
    String_Ctor(& Dest -> FPhone);
    String_Ctor(& Dest -> Name);
}

_Destructor_ (FreqLayerEntry)
{
    String_Dtor(& Dest -> FPhone);
    String_Dtor(& Dest -> Name);
}

_Constructor_ (FormantLayerEntry)
{
    String_Ctor(& Dest -> Phone);
    String_Ctor(& Dest -> FPhone);
}

_Destructor_ (FormantLayerEntry)
{
    String_Dtor(& Dest -> Phone);
    String_Dtor(& Dest -> FPhone);
}

_Constructor_ (TransitionLayerEntry)
{
    String_Ctor(& Dest -> Phone1);
    String_Ctor(& Dest -> Phone2);
}

_Destructor_ (TransitionLayerEntry)
{
    String_Dtor(& Dest -> Phone1);
    String_Dtor(& Dest -> Phone2);
}

_Constructor_ (CDTMap)
{
    ArrayType_Init(DBLayerEntry, Dest -> DBLayerMap);
    ArrayType_Init(SymbolLayerEntry, Dest -> SymbolLayerMap);
    ArrayType_Init(FreqLayerEntry, Dest -> FreqLayerMap);
    ArrayType_Init(FormantLayerEntry, Dest -> FormantLayerMap);
    ArrayType_Init(TransitionLayerEntry, Dest -> TransitionLayerMap);
}

_Destructor_ (CDTMap)
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

_Constructor_ (CDT3)
{
    ArrayType_Init(SGtorSyllable, Dest -> SGtorList);
    CDTMap_Ctor(& Dest -> CDTMapping);
}

_Destructor_ (CDT3)
{
    ArrayType_ObjDtor(SGtorSyllable, Dest -> SGtorList);
    ArrayType_Dtor(SGtorSyllable, Dest -> SGtorList);

    CDTMap_Dtor(& Dest -> CDTMapping);
}
