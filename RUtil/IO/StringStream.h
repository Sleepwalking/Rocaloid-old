#ifndef STRINGSTREAM_H
#define STRINGSTREAM_H

#include "../Structure/String.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef struct
{
    char* BasePtr;
    int Offset;
} StringStream;

extern void StringStream_Init(StringStream* Dest, char* Ptr);

extern void StringStream_ReadWord(String* Dest, StringStream* Src);
extern void StringStream_ReadLine(String* Dest, StringStream* Src);
extern void StringStream_ReadAll(String* Dest, StringStream* Src);

#ifdef __cplusplus
}
#endif
#endif
