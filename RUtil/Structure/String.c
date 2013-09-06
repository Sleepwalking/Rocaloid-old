#include "String.h"
#include "Array.h"
#include "../Memory.h"
#include <string.h>

//#define BOOST

#ifdef BOOST
    #define memcpy Boost_Memcpy
#endif

void String_Ctor(String* Dest)
{
    Dest -> Data = (char*)malloc(10);
    Dest -> Data_Index = - 1;
    Dest -> Data_Size = 10;
}

void String_Dtor(String* Dest)
{
    free(Dest -> Data);
}

void String_Copy(String* Dest, String* Src)
{
    ArrayType_Resize(char, Dest -> Data, Src -> Data_Index + 1);
    memcpy(Dest -> Data, Src -> Data, Src -> Data_Index + 1);
    Dest -> Data_Index = Src -> Data_Index;
}

void String_SetChars(String* Dest, const char* Chars)
{
    int Len = strlen(Chars);
    ArrayType_Resize(char, Dest -> Data, Len);
    memcpy(Dest -> Data, Chars, Len);
    Dest -> Data_Index = Len - 1;
}

const char* String_GetChars(String* Dest)
{
    ArrayType_Push(char, Dest -> Data, 0);
    Dest -> Data_Index --;
    return Dest -> Data;
}

int String_GetLength(String* Src)
{
    return Src -> Data_Index + 1;
}

void String_AllocLength(String* Dest, int Length)
{
    ArrayType_Resize(char, Dest -> Data, Length);
}

char String_GetChar(String* Dest, int Index)
{
    return Dest -> Data[Index];
}

void String_SetChar(String* Dest, int Index, char Data)
{
    Dest -> Data[Index] = Data;
}

void String_Join(String* Dest, String* Src)
{
    ArrayType_Resize(char, Dest -> Data, Dest -> Data_Index + Src -> Data_Index + 2 + Dest -> Data_Index / 10);
    memcpy(Dest -> Data + Dest -> Data_Index + 1, Src -> Data, Src -> Data_Index + 1);
    Dest -> Data_Index += Src -> Data_Index + 1;
}

void String_JoinChars(String* Dest, const char* Src)
{
    int Len = strlen(Src);
    ArrayType_Resize(char, Dest -> Data, Dest -> Data_Index + Len + 1 + Dest -> Data_Index / 10);
    memcpy(Dest -> Data + Dest -> Data_Index + 1, Src, Len);
    Dest -> Data_Index += Len;
}

int String_Equal(String* Str1, String* Str2)
{
    return ! strcmp(String_GetChars(Str1), String_GetChars(Str2));
}

int String_EqualChars(String* Str1, const char* Str2)
{
    return ! strcmp(String_GetChars(Str1), Str2);
}

//------------------------------------------------------------

void Mid(String* Dest, String* Src, int From, int Count)
{
    int i;
    if(Count + From > Src -> Data_Index)
        Count = Src -> Data_Index - From + 1;
    if(Count < 0)
        Count = 0;
    String_AllocLength(Dest, Count);
    for(i = 0;i < Count;i ++)
        Dest -> Data[i] = Src -> Data[From + i];
}

void MidFrom(String* Dest, String* Src, int From)
{
    int i;
    int Count = Src -> Data_Index - From + 1;
    if(Count < 0)
        Count = 0;
    String_AllocLength(Dest, Count);
    for(i = 0;i < Count;i ++)
        Dest -> Data[i] = Src -> Data[From + i];
}

void Right(String* Dest, String* Src, int Count)
{
    int i;
    if(Src -> Data_Index - Count < - 1)
        Count = Src -> Data_Index + 1;
    int From = Src -> Data_Index + 1 - Count;
    if(Count < 0)
        Count = 0;
    String_AllocLength(Dest, Count);
    for(i = 0;i < Count;i ++)
        Dest -> Data[i] = Src -> Data[From + i];
}

void Left(String* Dest, String* Src, int Count)
{
    int i;
    if(Count > Dest -> Data_Index + 1)
        Count = Dest -> Data_Index + 1;
    if(Count < 0)
        Count = 0;
    String_AllocLength(Dest, Count);
    for(i = 0;i < Count;i ++)
        Dest -> Data[i] = Src -> Data[i];
}

void UpperCase(String* Dest, String* Src)
{
    int i;
    int Len = Src -> Data_Index + 1;
    String_AllocLength(Dest, Len);
    for(i = 0;i < Len;i ++)
        if(Src -> Data[i] >= 'a' && Src -> Data[i] <= 'z')
            Dest -> Data[i] = Src -> Data[i] + ('A' - 'a');
        else
            Dest -> Data[i] = Src -> Data[i];
}

void LowerCase(String* Dest, String* Src)
{
    int i;
    int Len = Src -> Data_Index + 1;
    String_AllocLength(Dest, Len);
    for(i = 0;i < Len;i ++)
        if(Src -> Data[i] >= 'A' && Src -> Data[i] <= 'Z')
            Dest -> Data[i] = Src -> Data[i] + ('a' - 'A');
        else
            Dest -> Data[i] = Src -> Data[i];
}

int InStrFrom(String* Whole, String* Part, int From)
{
    int i, j;
    int End = Whole -> Data_Index - Part -> Data_Index;
    int PartLen = Part -> Data_Index + 1;

    ArrayType_Push(char, Whole -> Data, 0);
    Whole -> Data_Index --;
    ArrayType_Push(char, Part -> Data, 0);
    Part -> Data_Index --;

    for(i = From;i <= End;i ++)
    {
        for(j = 0;j < PartLen;j ++)
            if(Part -> Data[j] != Whole -> Data[i + j])
                goto cont;
        return i;
        cont:;
    }
    return -1;
}

int InStr(String* Whole, String* Part)
{
    return InStrFrom(Whole, Part, 0);
}

int InStrRevFrom(String* Whole, String* Part, int From)
{
    int i, j;
    int End = Whole -> Data_Index - Part -> Data_Index;
    int PartLen = Part -> Data_Index + 1;
    From = From > End ? End : From;

    ArrayType_Push(char, Whole -> Data, 0);
    Whole -> Data_Index --;
    ArrayType_Push(char, Part -> Data, 0);
    Part -> Data_Index --;

    for(i = From;i >= 0;i --)
    {
        for(j = 0;j < PartLen;j ++)
            if(Part -> Data[j] != Whole -> Data[i + j])
                goto cont;
        return i;
        cont:;
    }
    return -1;
}

int InStrRev(String* Whole, String* Part)
{
    return InStrRevFrom(Whole, Part, Whole -> Data_Index + 1);
}

void Trim(String* Dest, String* Src)
{
    int Start, End, i, SrcLen, RetLen;
    SrcLen = Src -> Data_Index + 1;
    Start = 0;
    End = 0;
    for(i = 0;i < SrcLen;i ++)
        if(Src -> Data[i] != ' ' && Src -> Data[i] != '\t')
        {
            Start = i;
            break;
        }
    for(i = SrcLen - 1;i >= 0;i --)
        if(Src -> Data[i] != ' ' && Src -> Data[i] != '\t')
        {
            End = i;
            break;
        }
    RetLen = End - Start + 1;
    String_AllocLength(Dest, RetLen);
    for(i = 0;i < RetLen;i ++)
        Dest -> Data[i] = Src -> Data[i + Start];
}

void LTrim(String* Dest, String* Src)
{
    int Start, End, i, SrcLen, RetLen;
    SrcLen = Src -> Data_Index + 1;
    Start = 0;
    End = 0;
    for(i = SrcLen - 1;i >= 0;i --)
        if(Src -> Data[i] != ' ' && Src -> Data[i] != '\t')
        {
            End = i;
            break;
        }
    RetLen = End - Start + 1;
    String_AllocLength(Dest, RetLen);
    for(i = 0;i < RetLen;i ++)
        Dest -> Data[i] = Src -> Data[i + Start];
}

void RTrim(String* Dest, String* Src)
{
    int Start, End, i, SrcLen, RetLen;
    SrcLen = Src -> Data_Index + 1;
    Start = 0;
    End = SrcLen - 1;
    for(i = 0;i < SrcLen;i ++)
        if(Src -> Data[i] != ' ' && Src -> Data[i] != '\t')
        {
            Start = i;
            break;
        }
    RetLen = End - Start + 1;
    String_AllocLength(Dest, RetLen);
    for(i = 0;i < RetLen;i ++)
        Dest -> Data[i] = Src -> Data[i + Start];
}
