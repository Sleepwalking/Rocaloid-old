#include "FileStream.h"
#include "../Structure/Array.h"
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

char fModes[5][5] = {"rb", "wb", "rwb+", "ab+", "wb+"};
int Ret;

void FileStream_Ctor(FileStream* Dest)
{
    Dest -> IsOpen = 0;
    Dest -> FilePtr = 0;
}

void FileStream_Dtor(FileStream* Dest)
{
    if(Dest -> IsOpen)
        fclose(Dest -> FStream);
}

void FileStream_RefreshLength(FileStream* Dest)
{
    fseek(Dest -> FStream, 0, SEEK_END);
    Dest -> Length = ftell(Dest -> FStream);
    fseek(Dest -> FStream, Dest -> FilePtr, SEEK_SET);
}

int FileStream_Open(FileStream* Dest, String* Path, OpenMode FileMode)
{
    return FileStream_OpenChars(Dest, String_GetChars(Path), FileMode);
}

int FileStream_OpenChars(FileStream* Dest, const char* Path, OpenMode FileMode)
{
    const char* chars = Path;
    const char* fmode = fModes[FileMode];
    Dest -> FStream = fopen(chars, fmode);

    Dest -> IsOpen = 1;
    if(Dest -> FStream == 0)
        Dest -> IsOpen = 0;
    Dest -> FilePtr = 0;

    if(Dest -> IsOpen)
        FileStream_RefreshLength(Dest);
    return Dest -> IsOpen;
}

void FileStream_Close(FileStream* Dest)
{
    if(Dest -> IsOpen)
    {
        Dest -> IsOpen = 0;
        fclose(Dest -> FStream);
    }
}

int FileStream_Flush(FileStream* Dest)
{
    if(fflush(Dest -> FStream) == 0)
        return 1;
    return 0;
}

void FileStream_SetPosition(FileStream* Dest, int64_t Position)
{
    Dest -> FilePtr = Position;
    fseek(Dest -> FStream, Dest -> FilePtr, SEEK_SET);
}

int64_t FileStream_GetPosition(FileStream* Dest)
{
    return Dest -> FilePtr;
}

int64_t FileStream_GetLength(FileStream* Dest)
{
    return Dest -> Length;
}

char FileStream_ReadChar(FileStream* Src)
{
    char tmp;
    Ret = fread(&tmp, 1, 1, Src -> FStream);
    Src -> FilePtr ++;
    fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    return tmp;
}

short int FileStream_ReadShort(FileStream* Src)
{
    short int tmp;
    Ret = fread(&tmp, sizeof(short int), 1, Src -> FStream);
    Src -> FilePtr += sizeof(short int);
    fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    return tmp;
}

int FileStream_ReadBool(FileStream* Src)
{
    int tmp;
    Ret = fread(&tmp, sizeof(int), 1, Src -> FStream);
    Src -> FilePtr += sizeof(int);
    fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    return tmp;
}

int FileStream_ReadInt(FileStream* Src)
{
    int tmp;
    Ret = fread(&tmp, sizeof(int), 1, Src -> FStream);
    Src -> FilePtr += sizeof(int);
    fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    return tmp;
}

unsigned int FileStream_ReadUInt(FileStream* Src)
{
    unsigned int tmp;
    Ret = fread(&tmp, sizeof(unsigned int), 1, Src -> FStream);
    Src -> FilePtr += sizeof(unsigned int);
    fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    return tmp;
}

float FileStream_ReadFloat(FileStream* Src)
{
    float tmp;
    Ret = fread(&tmp, sizeof(float), 1, Src -> FStream);
    Src -> FilePtr += sizeof(float);
    fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    return tmp;
}

double FileStream_ReadDouble(FileStream* Src)
{
    double tmp;
    Ret = fread(&tmp, sizeof(double), 1, Src -> FStream);
    Src -> FilePtr += sizeof(double);
    fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    return tmp;
}

int64_t FileStream_ReadLong(FileStream* Src)
{
    int64_t tmp;
    Ret = fread(&tmp, sizeof(int64_t), 1, Src -> FStream);
    Src -> FilePtr += sizeof(int64_t);
    fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    return tmp;
}

uint64_t FileStream_ReadULong(FileStream* Src)
{
    uint64_t tmp;
    Ret = fread(&tmp, sizeof(uint64_t), 1, Src -> FStream);
    Src -> FilePtr += sizeof(uint64_t);
    fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    return tmp;
}

void FileStream_ReadString(String* Dest, FileStream* Src)
{
    char tmpchar;
    ArrayType_Ctor(char, tmp);

    do
    {
        Ret = fread(&tmpchar, 1, 1, Src -> FStream);
        ArrayType_Push(char, tmp, tmpchar);
        Src -> FilePtr ++;
        fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    }
    while(tmpchar != 0 && Src -> FilePtr < Src -> Length - 1);

    String_SetChars(Dest, tmp);
    FileStream_SetPosition(Src, Src -> FilePtr);
    ArrayType_Dtor(char, tmp);
}

int FileStream_ReadChars(char* Dest, FileStream* Src)
{
    int count = 0;
    char tmpchar;

    do
    {
        Ret = fread(&tmpchar, 1, 1, Src -> FStream);
        Dest[count ++] = tmpchar;
        Src -> FilePtr ++;
        fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    }
    while(tmpchar != 0 && Src -> FilePtr < Src -> Length - 1);

    FileStream_SetPosition(Src, Src -> FilePtr);
    return count;
}

void FileStream_ReadBuffer(void* Dest, FileStream* Src, int64_t ByteCount)
{
    Ret = fread(Dest, 1, ByteCount, Src -> FStream);
    Src -> FilePtr += ByteCount;
    fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
}

void FileStream_WriteChars(FileStream* Dest, const char* Src)
{
    int Len = strlen(Src);
    fwrite(Src, 1, Len, Dest -> FStream);
    Dest -> FilePtr += Len;
    fseek(Dest -> FStream, Dest -> FilePtr, SEEK_SET);
}

void FileStream_WriteBuffer(FileStream* Dest, const char* Src, int64_t Length)
{
    fwrite(Src, 1, Length, Dest -> FStream);
    Dest -> FilePtr += Length;
    fseek(Dest -> FStream, Dest -> FilePtr, SEEK_SET);
}

void FileStream_ReadWord(String* Dest, FileStream* Src)
{
    ArrayType_Ctor(char, tmp);
    char tmpchar;

    Ret = fread(&tmpchar, 1, 1, Src -> FStream);
    while(tmpchar == ' ' || tmpchar == '\t' || tmpchar == '\n' || tmpchar == '\r')
    {
        Src -> FilePtr ++;
        fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
        Ret = fread(&tmpchar, 1, 1, Src -> FStream);
    }

    fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    do
    {
        Ret = fread(&tmpchar, 1, 1, Src -> FStream);
        ArrayType_Push(char, tmp, tmpchar);
        Src -> FilePtr ++;
        fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    }
    while(tmpchar != ' ' && tmpchar != '\t' && tmpchar != '\n' && tmpchar != '\r' && tmpchar != 0 && Src -> FilePtr < Src -> Length);

    tmp[tmp_Index] = 0;
    String_SetChars(Dest, tmp);
    ArrayType_Dtor(char, tmp);
}

void FileStream_ReadLine(String* Dest, FileStream* Src)
{
    ArrayType_Ctor(char, tmp);
    char tmpchar;

    do
    {
        Ret = fread(&tmpchar, 1, 1, Src -> FStream);
        ArrayType_Push(char, tmp, tmpchar);
        Src -> FilePtr ++;
        fseek(Src -> FStream, Src -> FilePtr, SEEK_SET);
    }
    while(tmpchar != '\n' && tmpchar != '\r' && tmpchar != 0 && Src -> FilePtr < Src -> Length);

    tmp[tmp_Index] = 0;
    String_SetChars(Dest, tmp);
    ArrayType_Dtor(char, tmp);
}

void FileStream_ReadAll(String* Dest, FileStream* Src)
{
    String_AllocLength(Dest, Src -> Length);
    fseek(Src -> FStream, 0, SEEK_SET);
    Ret = fread(Dest -> Data, 1, Src -> Length, Src -> FStream);
    Dest -> Data_Index = Src -> Length - 1;
}

void FileStream_WriteStr(FileStream* Dest, String* Src)
{
    FileStream_WriteChars(Dest, String_GetChars(Src));
}

void FileStream_WriteLine(FileStream* Dest, String* Src)
{
    FileStream_WriteChars(Dest, String_GetChars(Src));
    FileStream_Write(Dest, char, '\n');
}
