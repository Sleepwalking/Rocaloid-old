#include "../Structure/String.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

inline float Math_FloatPower10(int Power)
{
    int i;
    float TmpFloat = 1;
    if(Power >= 0)
        for(i = 0; i < Power; i ++)
            TmpFloat *= 10;
    else
        for(i = 0; i < - Power; i ++)
            TmpFloat *= 0.1;
    return TmpFloat;
}

float Math_CFloatChars(char* Src, int Length)
{
    int i, DeciPos, Sign;
    float Accumulator = 0;
    float Power;

    //Get Sign
    if(*Src == '-')
        Sign = 1;
    else
        Sign = 0;
    DeciPos = Length - Sign;

    //Find Float Point
    for(i = Sign; i < Length; i ++)
        if(Src[i] == '.')
            DeciPos = i - Sign;

    //Accumulate
    Power = Math_FloatPower10(DeciPos - Sign - 1 + Sign);
    for(i = Sign; i < Length; i ++)
    {
        if(Src[i] == '.')
        {
            DeciPos ++;
            continue;
        }
        Accumulator += Power * (Src[i] - '0');
        Power *= 0.1;
    }
    return Accumulator;
}

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

int CVBBoolStr(String* Src)
{
    if(String_EqualChars(Src, "True"))
        return 1;
    return 0;
}

int CVBBoolChars(char* Src)
{
    if(! strcmp(Src, "True"))
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
    return Math_CFloatChars(Src -> Data, Src -> Data_Index + 1);
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
