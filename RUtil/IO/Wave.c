#include "Wave.h"
#include "FileStream.h"
#include <malloc.h>
#include <string.h>

void PCMWaveFile_Ctor(PCMWaveFile* Dest)
{
    Dest -> WriteCounter = 0;
    Dest -> WriteDataPosition = 0;
    FileStream_Ctor(&(Dest -> FStream));
}

void PCMWaveFile_Dtor(PCMWaveFile* Dest)
{
    FileStream_Dtor(&(Dest -> FStream));
}

int PCMWaveFile_Open(PCMWaveFile* Dest, String* Path)
{
#define WStream &(Dest -> FStream)
#define Header (Dest -> Header)
    int openState = FileStream_Open(WStream, Path, READONLY);
    if(! openState)
        return 0;

    char RIFFChars[5];
    char WAVEChars[5];
    char FACTChars[5];

    FileStream_ReadBuffer(RIFFChars, WStream, 4); //RIFF
    FileStream_ReadInt(WStream); //Size
    FileStream_ReadBuffer(WAVEChars, WStream, 4); //WAVE

    RIFFChars[4] = 0;
    WAVEChars[4] = 0;
    FACTChars[4] = 0;

    if(strcmp(RIFFChars, "RIFF"))
        return 0;
    if(strcmp(WAVEChars, "WAVE"))
        return 0;

    FileStream_ReadInt(WStream); //fmt
    int fmtSize = FileStream_ReadInt(WStream);
    FileStream_ReadShort(WStream); //FormatTag
    Header.channel = FileStream_ReadShort(WStream);
    Header.samplePerSecond = FileStream_ReadInt(WStream);
    Header.bytePerSecond = FileStream_ReadInt(WStream);
    Header.blockAlign = FileStream_ReadShort(WStream);
    Header.bitPerSample = FileStream_ReadShort(WStream);

    if(fmtSize == 16)
    {
        //No extra info
    }else
        FileStream_ReadShort(WStream); //Extra info
    FileStream_ReadBuffer(FACTChars, WStream, 4);

    if(! strcmp(FACTChars, "fact"))
    {
        int factSize = FileStream_ReadInt(WStream);
        FileStream_SetPosition(WStream, FileStream_GetPosition(WStream) + factSize + 4);
    }

    Header.dataSize = FileStream_ReadInt(WStream);
    Header.dataPosition = FileStream_GetPosition(WStream);
    Header.bytePerSample = Header.bitPerSample >> 3;
    Header.dataNum = Header.dataSize / Header.bytePerSample / Header.channel;

    return 1;
#undef WStream
#undef Header
}

int PCMWaveFile_Save(String* Dest, PCMWaveFile* Src)
{
#define WStream &(Src -> FStream)
#define Header (Src -> Header)
    int saveState = FileStream_Open(WStream, Dest, CREATE);
    if(! saveState)
        return 0;

    FileStream_WriteBuffer(WStream, "RIFF", 4);
    FileStream_Write(WStream, int, 0); //Size = 0 by default
    FileStream_WriteBuffer(WStream, "WAVE", 4);

    FileStream_WriteBuffer(WStream, "fmt ", 4);
    FileStream_Write(WStream, int, 16); //No extra
    FileStream_Write(WStream, short int, 1); //FormatTag = 0x0001
    FileStream_Write(WStream, short int, Header.channel);
    FileStream_Write(WStream, int, Header.samplePerSecond);
    FileStream_Write(WStream, int, Header.bytePerSecond);
    FileStream_Write(WStream, short int, Header.blockAlign);
    FileStream_Write(WStream, short int, Header.bitPerSample);

    FileStream_WriteBuffer(WStream, "data", 4);
    FileStream_Write(WStream, int, 0); //dataSize = 0 by default

    Src -> WriteDataPosition = FileStream_GetPosition(WStream);
    Src -> WriteCounter = 0;
    return 1;
#undef WStream
#undef Header
}

void PCMWaveFile_FinishWrite(PCMWaveFile* Dest)
{
#define WStream &(Dest -> FStream)
#define Header (Dest -> Header)
    int fileSize = FileStream_GetPosition(WStream);

    FileStream_SetPosition(WStream, 4); //Size
    FileStream_Write(WStream, int, fileSize - 8);
    int dataSize = Dest -> WriteCounter * Header.channel * Header.bitPerSample * 8;

    FileStream_SetPosition(WStream, Dest -> WriteDataPosition - 4); //dataSize
    FileStream_Write(WStream, int, dataSize);
    FileStream_Flush(WStream);

    FileStream_Close(WStream);
#undef WStream
#undef Header
}

void PCMWaveFile_Close(PCMWaveFile* Dest)
{
    FileStream_Close(&(Dest -> FStream));
}

int PCMWaveFile_FetchAll(char* Dest, PCMWaveFile* Src)
{
#define WStream &(Src -> FStream)
#define Header (Src -> Header)
    FileStream_SetPosition(WStream, Header.dataPosition);
    FileStream_ReadBuffer(Dest, WStream, Header.dataSize);
    return Header.dataSize;
#undef WStream
#undef Header
}

int PCMWaveFile_FetchAllFloat(float* Dest, PCMWaveFile* Src)
{
#define WStream &(Src -> FStream)
#define Header (Src -> Header)
    int Ret = 0;
    if(Header.bitPerSample == 8)
    {
        int i;
        char* tmp = (char*)malloc(Header.dataSize);
        PCMWaveFile_FetchAll(tmp, Src);
        Ret = Header.dataSize;
        for(i = 0; i < Ret; i ++)
            Dest[i] = (float)tmp[i] / 127;
        free(tmp);
    }else if(Header.bitPerSample == 16)
    {
        int i;
        short int* tmp = (short int*)malloc(Header.dataSize);
        PCMWaveFile_FetchAll((char*)tmp, Src);
        Ret = Header.dataSize / 2;
        for(i = 0; i < Ret; i ++)
            Dest[i] = (float)tmp[i] / 32767;
        free(tmp);
    }
    return Ret;
#undef WStream
#undef Header
}

int PCMWaveFile_FetchAllFloatStereo(float* DestL, float* DestR, PCMWaveFile* Src)
{
#define WStream &(Src -> FStream)
#define Header (Src -> Header)
    int Ret = 0;
    if(Header.bitPerSample == 8)
    {
        int i;
        char* tmp = (char*)malloc(Header.dataSize);
        PCMWaveFile_FetchAll(tmp, Src);
        Ret = Header.dataSize / 2;
        for(i = 0; i < Ret; i ++)
        {
            DestL[i] = (float)tmp[i * 2] / 127;
            DestR[i] = (float)tmp[i * 2 + 1] / 127;
        }
        free(tmp);
    }else if(Header.bitPerSample == 16)
    {
        int i;
        short int* tmp = (short int*)malloc(Header.dataSize);
        PCMWaveFile_FetchAll((char*)tmp, Src);
        Ret = Header.dataSize / 4;
        for(i = 0; i < Ret; i ++)
        {
            DestL[i] = (float)tmp[i * 2] / 32767;
            DestR[i] = (float)tmp[i * 2 + 1] / 32767;
        }
        free(tmp);
    }
    return Ret;
#undef WStream
#undef Header
}

#define WStream &(Src -> FStream)
#define Header (Src -> Header)
float PCMWaveFile_FetchAt(PCMWaveFile* Src, int Position)
{
    FileStream_SetPosition(WStream, Header.dataPosition + Position * Header.bytePerSample);
    if(Header.bitPerSample == 8)
        return (float)FileStream_ReadChar(WStream) / 127;
    if(Header.bitPerSample == 16)
        return (float)FileStream_ReadShort(WStream) / 32767;
    return 0;
}

float PCMWaveFile_FetchLAt(PCMWaveFile* Src, int Position)
{
    FileStream_SetPosition(WStream, Header.dataPosition + Position * Header.bytePerSample * 2);
    if(Header.bitPerSample == 8)
        return (float)FileStream_ReadChar(WStream) / 127;
    if(Header.bitPerSample == 16)
        return (float)FileStream_ReadShort(WStream) / 32767;
    return 0;
}

float PCMWaveFile_FetchRAt(PCMWaveFile* Src, int Position)
{
    FileStream_SetPosition(WStream, Header.dataPosition + Position * Header.bytePerSample * 2 + Header.bytePerSample);
    if(Header.bitPerSample == 8)
        return (float)FileStream_ReadChar(WStream) / 127;
    if(Header.bitPerSample == 16)
        return (float)FileStream_ReadShort(WStream) / 32767;
    return 0;
}
#undef WStream
#undef Header

#define WStream &(Dest -> FStream)
#define Header (Dest -> Header)
void PCMWaveFile_WriteAll(PCMWaveFile* Dest, char* Src, int Size)
{
    FileStream_WriteBuffer(&(Dest -> FStream), Src, Size);
    Dest -> WriteCounter = Size / Header.bytePerSample;
}

void PCMWaveFile_WriteAllFloat(PCMWaveFile* Dest, float* Src, int Size)
{
    if(Header.bitPerSample == 8)
    {
        char* tmp = (char*)malloc(Size);
        int i;
        for(i = 0;i < Size;i ++)
            tmp[i] = (char)(Src[i] * 127);
        PCMWaveFile_WriteAll(Dest, tmp, Size);
        free(tmp);
    }else if(Header.bitPerSample == 16)
    {
        short int* tmp = (short int*)malloc(Size * sizeof(short int));
        int i;
        for(i = 0;i < Size;i ++)
            tmp[i] = (short int)(Src[i] * 32767);
        PCMWaveFile_WriteAll(Dest, (char*)tmp, Size * 2);
        free(tmp);
    }
}

void PCMWaveFile_WriteAllFloatStereo(PCMWaveFile* Dest, float* SrcL, float* SrcR, int Size)
{
    if(Header.bitPerSample == 8)
    {
        char* tmp = (char*)malloc(Size * 2);
        int i;
        for(i = 0;i < Size;i ++)
        {
            tmp[i * 2 + 0] = (char)(SrcL[i] * 127);
            tmp[i * 2 + 1] = (char)(SrcR[i] * 127);
        }
        PCMWaveFile_WriteAll(Dest, tmp, Size * 2);
        free(tmp);
    }else if(Header.bitPerSample == 16)
    {
        short int* tmp = (short int*)malloc(Size * sizeof(short int) * 2);
        int i;
        for(i = 0;i < Size;i ++)
        {
            tmp[i * 2 + 0] = (short int)(SrcL[i] * 32767);
            tmp[i * 2 + 1] = (short int)(SrcR[i] * 32767);
        }
        PCMWaveFile_WriteAll(Dest, (char*)tmp, Size * 4);
        free(tmp);
    }
}

void PCMWaveFile_Write(PCMWaveFile* Dest, float Data)
{
    if(Header.bitPerSample == 8)
        FileStream_Write(WStream, char, (char)(Data * 127));
    if(Header.bitPerSample == 16)
        FileStream_Write(WStream, short int, (short int)(Data * 32767));
    Dest -> WriteCounter ++;
}

void PCMWaveFile_WriteStereo(PCMWaveFile* Dest, float DataL, float DataR)
{
    if(Header.bitPerSample == 8)
    {
        FileStream_Write(WStream, char, (char)(DataL * 127));
        FileStream_Write(WStream, char, (char)(DataR * 127));
    }
    if(Header.bitPerSample == 16)
    {
        FileStream_Write(WStream, short int, (short int)(DataL * 32767));
        FileStream_Write(WStream, short int, (short int)(DataR * 32767));
    }
    Dest -> WriteCounter ++;
}

#undef WStream
#undef Header
