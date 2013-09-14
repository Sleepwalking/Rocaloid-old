#ifndef CONVERTER_H
#define CONVERTER_H
#include "../Structure/String.h"
#include <stdlib.h>

void CStrChars(String* Dest, const char* Src);
void CStrBool(String* Dest, int Src);
void CStrChar(String* Dest, char Src);
void CStrByte(String* Dest, char Src);
void CStrInt(String* Dest, int Src);
void CStrLong(String* Dest, long long Src);
void CStrFloat(String* Dest, float Src);
void CStrDouble(String* Dest, double Src);
void CStrFloatF(String* Dest, float Src, const char* Format);
void CStrDoubleF(String* Dest, double Src, const char* Format);

int CBoolStr(String* Src);
int CVBBoolStr(String* Src);
int CBoolChars(char* Src);
int CVBBoolChars(char* Src);

char CCharStr(String* Src);
char CCharChars(const char* Src);

char CByteStr(String* Src);
char CByteChars(const char* Src);

short int CShortStr(String* Src);
short int CShortChars(const char* Src);

int CIntStr(String* Src);
int CIntChars(const char* Src);

unsigned int CUIntStr(String* Src);
unsigned int CUIntChars(const char* Src);

long CLongStr(String* Src);
long CLongChars(const char* Src);

float CFloatStr(String* Src);
float CFloatChars(const char* Src);

double CDoubleStr(String* Src);
double CDoubleChars(const char* Src);

#endif
