#include "StringStream.h"
#include "../Structure/Array.h"

void StringStream_Init(StringStream* Dest, char* Ptr)
{
    Dest -> BasePtr = Ptr;
    Dest -> Offset = 0;
}

void StringStream_ReadWord(String* Dest, StringStream* Src)
{
    ArrayType_Ctor(char, tmp);
    char tmpchar;

    tmpchar = *(Src -> BasePtr + Src -> Offset);
    while(tmpchar == ' ' || tmpchar == '\t'|| tmpchar == '\n' || tmpchar == '\r')
    {
        Src -> Offset ++;
        tmpchar = *(Src -> BasePtr + Src -> Offset);
    }

    do
    {
        tmpchar = *(Src -> BasePtr + Src -> Offset);
        ArrayType_Push(char, tmp, tmpchar);
        Src -> Offset ++;
    }
    while(tmpchar != ' ' && tmpchar != '\t' && tmpchar != '\n' && tmpchar != '\r' && tmpchar != 0);

    tmp[tmp_Index] = 0;
    String_SetChars(Dest, tmp);
    ArrayType_Dtor(char, tmp);
}

void StringStream_ReadLine(String* Dest, StringStream* Src)
{
    ArrayType_Ctor(char, tmp);
    char tmpchar;

    do
    {
        tmpchar = *(Src -> BasePtr + Src -> Offset);
        ArrayType_Push(char, tmp, tmpchar);
        Src -> Offset ++;
    }
    while(tmpchar != '\n' && tmpchar != '\r' && tmpchar != 0);

    tmp[tmp_Index] = 0;
    String_SetChars(Dest, tmp);
    ArrayType_Dtor(char, tmp);
}

void StringStream_ReadAll(String* Dest, StringStream* Src)
{
    String_SetChars(Dest, Src -> BasePtr);
}
