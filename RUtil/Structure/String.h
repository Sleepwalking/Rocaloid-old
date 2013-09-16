#ifndef STRING_H
#define STRING_H

typedef struct
{
    char* Data;
    int Data_Index;
    int Data_Size;
} String;

extern void String_Ctor(String* Dest);
extern void String_Dtor(String* Dest);

extern void String_SetChars(String* Dest, const char* Chars);
extern void String_SetCharsN(String* Dest, const char* Chars, int Length);
extern const char* String_GetChars(String* Dest);

extern void String_Copy(String* Dest, const String* Src);

extern int String_GetLength(String* Src);
extern void String_AllocLength(String* Dest, int Length);

extern char String_GetChar(String* Dest, int Index);
extern void String_SetChar(String* Dest, int Index, char Data);

extern void String_Join(String* Dest, const String* Src);
extern void String_JoinChars(String* Dest, const char* Src);

extern int String_Equal(const String* Str1, const String* Str2);
extern int String_EqualChars(const String* Str1, const char* Str2);

#define String_FromChars(name, chars)\
    String name;\
    do\
    {\
        String_Ctor(&name);\
        String_SetChars(&name, chars);\
    } while(0)

//------------------------------------------------------------------

extern void Mid(String* Dest, const String* Src, int From, int Count);
extern void MidFrom(String* Dest, const String* Src, int From);
extern void Right(String* Dest, const String* Src, int Count);
extern void Left(String* Dest, const String* Src, int Count);

extern void UpperCase(String* Dest, const String* Src);
extern void LowerCase(String* Dest, const String* Src);

extern int InStrFrom(String* Whole, String* Part, int From);
extern int InStr(String* Whole, String* Part);
extern int InStrRevFrom(String* Whole, String* Part, int From);
extern int InStrRev(String* Whole, String* Part);

extern void Trim(String* Dest, const String* Src);
extern void LTrim(String* Dest, const String* Src);
extern void RTrim(String* Dest, const String* Src);

#endif
