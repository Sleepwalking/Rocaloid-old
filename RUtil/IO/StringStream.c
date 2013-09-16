#include "StringStream.h"
#include "../Structure/Array.h"

void StringStream_Init(StringStream* Dest, char* Ptr)
{
    Dest -> BasePtr = Ptr;
    Dest -> Offset = 0;
}

void StringStream_ReadWord(String* Dest, StringStream* Src)
{
    char tmpchar;
    Dest -> Data_Index = - 1;

    tmpchar = *(Src -> BasePtr + Src -> Offset);
    while(tmpchar == ' ' || tmpchar == '\t'|| tmpchar == '\n' || tmpchar == '\r')
    {
        Src -> Offset ++;
        tmpchar = *(Src -> BasePtr + Src -> Offset);
    }

    do
    {
        tmpchar = *(Src -> BasePtr + Src -> Offset);
        ArrayType_Push(char, Dest -> Data, tmpchar);
        Src -> Offset ++;
    }
    while(tmpchar != ' ' && tmpchar != '\t' && tmpchar != '\n' && tmpchar != '\r' && tmpchar != 0);

    Dest -> Data[Dest -> Data_Index --] = 0;
}

void StringStream_ReadLine(String* Dest, StringStream* Src)
{
    char tmpchar;
    Dest -> Data_Index = - 1;

    do
    {
        tmpchar = *(Src -> BasePtr + Src -> Offset);
        ArrayType_Push(char, Dest -> Data, tmpchar);
        Src -> Offset ++;
    }
    while(tmpchar != '\n' && tmpchar != '\r' && tmpchar != 0);

    Dest -> Data[Dest -> Data_Index --] = 0;
}

void StringStream_ReadAll(String* Dest, StringStream* Src)
{
    String_SetChars(Dest, Src -> BasePtr);
}
