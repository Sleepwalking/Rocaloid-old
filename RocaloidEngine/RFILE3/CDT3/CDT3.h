#ifndef CDT3_H
#define CDT3_H

#include "../../../RUtil/RUtil.h"

typedef enum
{
    V       = 0,
    VV      = 1,
    VVV     = 2,
    CV      = 3,
    CVV     = 4,
    CAV     = 5,
    CAVV    = 6
} SyllableType;

extern SyllableType CSyllableTypeStr(String* Dest);

AutoClass
{
    String Syllable;
    SyllableType Type;
    float EndingRatio;
    int Extended;

    ArrayType_Define(String, PhoneList);
} EndClass(SGtorSyllable);

AutoClass
{
    String Name;
    String FileAddr;
} EndClass(DBLayerEntry);

AutoClass
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
} EndClass(SymbolLayerEntry);

AutoClass
{
    String FPhone;
    float F0;
    String Name;
} EndClass(FreqLayerEntry);

AutoClass
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
} EndClass(FormantLayerEntry);

AutoClass
{
    String Phone1;
    String Phone2;
    float Ratio;
} EndClass(TransitionLayerEntry);

#define MappingArrayDEF(Layer)\
    Layer##Entry* Layer##Map;\
    int Layer##Map_Index;\
    int Layer##Map_Size

AutoClass
{
    MappingArrayDEF(DBLayer);
    MappingArrayDEF(SymbolLayer);
    MappingArrayDEF(FreqLayer);
    MappingArrayDEF(FormantLayer);
    MappingArrayDEF(TransitionLayer);
} EndClass(CDTMap);

AutoClass
{
    float Version;
    ArrayType_Define(SGtorSyllable, SGtorList);
    CDTMap CDTMapping;
} EndClass(CDT3);

#endif
