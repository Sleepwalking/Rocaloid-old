#include "../Structure/String.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void CStrChars(String* Dest, const char* Src)
{
    String_SetChars(Dest, Src);
}

void CStrBool(String* Dest, int Src)
{
    if(Src)
        String_SetChars(Dest, "true");
    else
        String_SetChars(Dest, "false");
}

void CStrChar(String* Dest, char Src)
{
    String_AllocLength(Dest, 1);
    Dest -> Data[0] = Src;
    Dest -> Data_Index = 0;
}

void CStrByte(String* Dest, char Src)
{
    char buffer[20];
    sprintf((char*)buffer, "%d", (int)Src);
    String_SetChars(Dest, buffer);
}

void CStrInt(String* Dest, int Src)
{
    char buffer[20];
    sprintf((char*)buffer, "%d", Src);
    String_SetChars(Dest, buffer);
}

void CStrLong(String* Dest, long long Src)
{
    char buffer[20];
    sprintf((char*)buffer, "%lld", Src);
    String_SetChars(Dest, buffer);
}

void CStrFloat(String* Dest, float Src)
{
    char buffer[30];
    sprintf((char*)buffer, "%f", Src);
    String_SetChars(Dest, buffer);
}

void CStrDouble(String* Dest, double Src)
{
    char buffer[30];
    sprintf((char*)buffer, "%lf", Src);
    String_SetChars(Dest, buffer);
}

void CStrFloatF(String* Dest, float Src, const char* Format)
{
    char buffer[30];
    sprintf((char*)buffer, Format, Src);
    String_SetChars(Dest, buffer);
}

void CStrDoubleF(String* Dest, double Src, const char* Format)
{
    char buffer[30];
    sprintf((char*)buffer, Format, Src);
    String_SetChars(Dest, buffer);
}

int CBoolStr(String* Src)
{
    if(String_EqualChars(Src, "true"))
        return 1;
    return 0;
}

int CBoolChars(char* Src)
{
    if(! strcmp(Src, "true"))
        return 1;
    return 0;
}

char CCharStr(String* Src)
{
    return Src -> Data[0];
}

char CCharChars(const char* Src)
{
    return Src[0];
}

char CByteStr(String* Src)
{
    const char* chars = String_GetChars(Src);
    int ret = atoi(chars);
    return (char)ret;
}
char CByteChars(const char* Src)
{
    int ret = atoi(Src);
    return (char)ret;
}

short int CShortStr(String* Src)
{
    const char* chars = String_GetChars(Src);
    int ret = atoi(chars);
    return (short int)ret;
}
short int CShortChars(const char* Src)
{
    int ret = atoi(Src);
    return (short int)ret;
}

int CIntStr(String* Src)
{
    const char* chars = String_GetChars(Src);
    int ret = atoi(chars);
    return ret;
}
int CIntChars(const char* Src)
{
    int ret = atoi(Src);
    return ret;
}

unsigned int CUIntStr(String* Src)
{
    const char* chars = String_GetChars(Src);
    return (unsigned int)atol(chars);
}
unsigned int CUIntChars(const char* Src)
{
    return (unsigned int)atol(Src);
}

long CLongStr(String* Src)
{
    const char* chars = String_GetChars(Src);
    return atol(chars);
}
long CLongChars(const char* Src)
{
    return atol(Src);
}

float CFloatStr(String* Src)
{
    const char* chars = String_GetChars(Src);
    return atof(chars);
}
float CFloatChars(const char* Src)
{
    return atof(Src);
}

double CDoubleStr(String* Src)
{
    const char* chars = String_GetChars(Src);
    return atof(chars);
}
double CDoubleChars(const char* Src)
{
    return atof(Src);
}
