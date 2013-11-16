#ifndef CDS_H
#define CDS_H

#include "../../../RUtil/RUtil.h"

AutoClass
{
    String Vowel;

    float F1;
    float F2;
    float F3;

    float S1;
    float S2;
    float S3;
} EndClass(SrcVList_Type);

AutoClass
{
    String Vowel;
    String Src;

    float F1;
    float F2;
    float F3;

    float S1;
    float S2;
    float S3;
} EndClass(DestVList_Type);

AutoClass
{
    String Symbol;
    String Vowel;
} EndClass(DestCList_Type);

AutoClass
{
    int PitchStep;
    float DiphoneLen;
    float VowelLen;
    ArrayType_Define(SrcVList_Type, SrcVList);
    ArrayType_Define(String, SrcCList);
    ArrayType_Define(DestVList_Type, DestVList);
    ArrayType_Define(DestCList_Type, DestCList);
} EndClass(CDS);

extern int CDSReader_Open(String* Src);
extern void CDSReader_Close();

extern int SrcVList_Type_Read(SrcVList_Type* Dest);
extern int DestVList_Type_Read(DestVList_Type* Dest);
extern int DestCList_Type_Read(DestCList_Type* Dest);
extern int CDS_Read(CDS* Dest);

#endif
