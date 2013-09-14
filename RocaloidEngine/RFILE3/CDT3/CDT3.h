#ifndef CDT3_H
#define CDT3_H

#include "../RUtil/Structure/Array.h"
#include "../RUtil/Structure/String.h"

typedef enum
{
    V       = 0,
    VV      = 1,
    VVV     = 2,
    CV  	= 3,
    CVV     = 4,
    CAV     = 5,
    CAVV    = 6
} SyllableType;

extern SyllableType CSyllableTypeStr(String* Dest);

typedef struct
{
    String Syllable;
    SyllableType Type;
    float EndingRatio;
    int Extended;

    String* PhoneList;
    int PhoneList_Index;
    int PhoneList_Size;
} SGtorSyllable;

extern void SGtorSyllable_Ctor(SGtorSyllable* Dest);
extern void SGtorSyllable_Dtor(SGtorSyllable* Dest);

typedef struct
{
    String Name;
    String FileAddr;
} DBLayerEntry;

extern void DBLayerEntry_Ctor(DBLayerEntry* Dest);
extern void DBLayerEntry_Dtor(DBLayerEntry* Dest);

typedef struct
{
    String Name;
    char Type;
    int VOI;
    float VOT;
    float F0;

    float F1;
    float F2;
    float F3;
    float S1;
    float S2;
    float S3;
} SymbolLayerEntry;

extern void SymbolLayerEntry_Ctor(SymbolLayerEntry* Dest);
extern void SymbolLayerEntry_Dtor(SymbolLayerEntry* Dest);

typedef struct
{
    String FPhone;
    float F0;
    String Name;
} FreqLayerEntry;

extern void FreqLayerEntry_Ctor(FreqLayerEntry* Dest);
extern void FreqLayerEntry_Dtor(FreqLayerEntry* Dest);

typedef struct
{
    String Phone;
    float F0;
    String FPhone;

    float F1;
    float F2;
    float F3;
    float S1;
    float S2;
    float S3;
} FormantLayerEntry;

extern void FormantLayerEntry_Ctor(FormantLayerEntry* Dest);
extern void FormantLayerEntry_Dtor(FormantLayerEntry* Dest);

typedef struct
{
    String Phone1;
    String Phone2;
    float Ratio;
} TransitionLayerEntry;

extern void TransitionLayerEntry_Ctor(TransitionLayerEntry* Dest);
extern void TransitionLayerEntry_Dtor(TransitionLayerEntry* Dest);

#define MappingArrayDEF(Layer)\
    Layer##Entry* Layer##Map;\
    int Layer##Map_Index;\
    int Layer##Map_Size

typedef struct
{
    MappingArrayDEF(DBLayer);
    MappingArrayDEF(SymbolLayer);
    MappingArrayDEF(FreqLayer);
    MappingArrayDEF(FormantLayer);
    MappingArrayDEF(TransitionLayer);
} CDTMap;

extern void CDTMap_Ctor(CDTMap* Dest);
extern void CDTMap_Dtor(CDTMap* Dest);

typedef struct
{
    float Version;
    SGtorSyllable* SGtorList;
    int SGtorList_Index;
    int SGtorList_Size;
    CDTMap CDTMapping;
} CDT3;

extern void CDT3_Ctor(CDT3* Dest);
extern void CDT3_Dtor(CDT3* Dest);

#endif
