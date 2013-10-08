#ifndef SLIST_H
#define SLIST_H

#include "RUtil/RUtil.h"
#include "RUtil/Structure/String.h"

AutoClass
{
    String Phone;
    float F1;
    float F2;
    float F3;
    ArrayType_Define(String, FileList);
} EndClass(SClass);

AutoClass
{
    ArrayType_Define(String, PitchList);
    ArrayType_Define(SClass, PhoneList);
} EndClass(SList);

extern int SList_Load(SList* Dest, String* Src);

#endif
