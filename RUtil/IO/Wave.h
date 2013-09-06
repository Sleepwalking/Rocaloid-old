#ifndef WAVE_H
#define WAVE_H

#include "FileStream.h"
#include "../Structure/String.h"
#include "../Structure/Array.h"

typedef struct
{
    //Required while writing
    short int channel;
    int samplePerSecond;
    int bytePerSecond;
    short int blockAlign;
    short int bitPerSample;

    //Temporary data while reading
    int dataSize;
    int dataPosition;
    int dataNum;
    int bytePerSample;
} PCMWaveHeader;

typedef struct
{
    PCMWaveHeader Header;
    int WriteCounter;
    int WriteDataPosition;
    FileStream FStream;
} PCMWaveFile;

extern void PCMWaveFile_Ctor(PCMWaveFile* Dest);
extern void PCMWaveFile_Dtor(PCMWaveFile* Dest);

extern int PCMWaveFile_Open(PCMWaveFile* Dest, String* Path);
extern int PCMWaveFile_Save(String* Dest, PCMWaveFile* Src);

extern void PCMWaveFile_FinishWrite(PCMWaveFile* Dest);
extern void PCMWaveFile_Close(PCMWaveFile* Dest);

extern int PCMWaveFile_FetchAll(char* Dest, PCMWaveFile* Src);
extern int PCMWaveFile_FetchAllFloat(float* Dest, PCMWaveFile* Src);
extern int PCMWaveFile_FetchAllFloatStereo(float* DestL, float* DestR, PCMWaveFile* Src);
extern float PCMWaveFile_FetchAt(PCMWaveFile* Src, int Position);
extern float PCMWaveFile_FetchLAt(PCMWaveFile* Src, int Position);
extern float PCMWaveFile_FetchRAt(PCMWaveFile* Src, int Position);

extern void PCMWaveFile_WriteAll(PCMWaveFile* Dest, char* Src, int Size);
extern void PCMWaveFile_WriteAllFloat(PCMWaveFile* Dest, float* Src, int Size);
extern void PCMWaveFile_WriteAllFloatStereo(PCMWaveFile* Dest, float* SrcL, float* SrcR, int Size);
extern void PCMWaveFile_Write(PCMWaveFile* Dest, float Data);
extern void PCMWaveFile_WriteStereo(PCMWaveFile* Dest, float DataL, float DataR);

#endif
