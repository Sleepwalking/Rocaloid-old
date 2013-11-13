#ifndef SCONF_H
#define SCONF_H

#include "../../../RUtil/RUtil.h"

AutoClass
{
    float Time;
    String Vowel;
    String Consonant;
} EndClass(TickList_Type);

AutoClass
{
    ArrayType_Define(TickList_Type, TickList);
} EndClass(SCONF);

extern int SCONFReader_Open(String* Src);
extern void SCONFReader_Close();

extern int TickList_Type_Read(TickList_Type* Dest);
extern int SCONF_Read(SCONF* Dest);

extern void SCONFWriter_Save();
extern void SCONFWriter_Write(String* Src);

extern int TickList_Type_Write(TickList_Type* Dest);
extern int SCONF_Write(SCONF* Dest);

#endif
