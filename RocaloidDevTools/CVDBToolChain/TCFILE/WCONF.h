#ifndef WCONF_H
#define WCONF_H

#include "../../../RUtil/RUtil.h"

AutoClass
{
    String Vowel;
    String Consonant;
    int Num;
    float F0;

    float F1;
    float F2;
    float F3;
    float S1;
    float S2;
    float S3;
    float Mul;
} EndClass(SampleList_Type);

AutoClass
{
    float AverageMagnitude;
    ArrayType_Define(SampleList_Type, SampleList);
} EndClass(WCONF);

extern int WCONFReader_Open(String* Src);
extern void WCONFReader_Close();

extern int SampleList_Type_Read(SampleList_Type* Dest);
extern int WCONF_Read(WCONF* Dest);

extern void WCONFWriter_Save();
extern void WCONFWriter_Write(String* Src);

extern int SampleList_Type_Write(SampleList_Type* Dest);
extern int WCONF_Write(WCONF* Dest);

#endif
