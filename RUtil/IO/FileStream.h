#ifndef FILESTREAM_H
#define FILESTREAM_H

#include "../Structure/String.h"
#include <stdio.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"{
#endif

typedef enum
{
    READONLY = 0,
    WRITEONLY = 1,
    READWRITE = 2,
    APPEND = 3,
    CREATE = 4
} OpenMode;

typedef struct
{
    OpenMode FileMode;
    int IsOpen;
    int64_t FilePtr;
    FILE* FStream;
    int64_t Length;
} FileStream;

extern void FileStream_Ctor(FileStream* Dest);
extern void FileStream_Dtor(FileStream* Dest);

extern int FileStream_Open(FileStream* Dest, String* Path, OpenMode FileMode);
extern int FileStream_OpenChars(FileStream* Dest, const char* Path, OpenMode FileMode);
extern void FileStream_Close(FileStream* Dest);
extern int FileStream_Flush(FileStream* Dest);

extern void FileStream_SetPosition(FileStream* Dest, int64_t Position);
extern int64_t FileStream_GetPosition(FileStream* Dest);
extern int64_t FileStream_GetLength(FileStream* Dest);

extern char FileStream_ReadChar(FileStream* Src);
extern short int FileStream_ReadShort(FileStream* Src);
extern int FileStream_ReadBool(FileStream* Src);
extern int FileStream_ReadInt(FileStream* Src);
extern unsigned int FileStream_ReadUInt(FileStream* Src);
extern float FileStream_ReadFloat(FileStream* Src);
extern double FileStream_ReadDouble(FileStream* Src);
extern int64_t FileStream_ReadLong(FileStream* Src);
extern uint64_t FileStream_ReadULong(FileStream* Src);
extern void FileStream_ReadString(String* Dest, FileStream* Src);
extern int FileStream_ReadChars(char* Dest, FileStream* Src);
extern void FileStream_ReadBuffer(void* Dest, FileStream* Src, int64_t ByteCount);

#define FileStream_Write(Stream, Type, Data)\
    do{\
        Type FileStream_tmp = Data;\
        fwrite(&FileStream_tmp, sizeof(Type), 1, (Stream) -> FStream);\
        (Stream) -> FilePtr += sizeof(Type);\
        fseek((Stream) -> FStream, (Stream) -> FilePtr, SEEK_SET);\
    } while(0)

extern void FileStream_WriteChars(FileStream* Dest, const char* Src);
extern void FileStream_WriteBuffer(FileStream* Dest, const char* Src, int64_t Length);

extern void FileStream_ReadWord(String* Dest, FileStream* Src);
extern void FileStream_ReadLine(String* Dest, FileStream* Src);
extern void FileStream_ReadAll(String* Dest, FileStream* Src);

extern void FileStream_WriteStr(FileStream* Dest, String* Src);
extern void FileStream_WriteLine(FileStream* Dest, String* Src);

#ifdef __cplusplus
}
#endif
#endif
