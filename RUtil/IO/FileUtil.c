#include "FileUtil.h"
#include "FileStream.h"
#include "Wave.h"

int64_t GetFileLength(String* Path)
{
    int64_t Ret;
    FileStream tmp;
    FileStream_Ctor(&tmp);
    Ret = FileStream_Open(&tmp, Path, READONLY);
    if(! Ret)
    {
        FileStream_Dtor(&tmp);
        return 0;
    }
    Ret = tmp.Length;
    FileStream_Dtor(&tmp);
    return Ret;
}

int64_t LoadFileAll(void* Dest, String* Path)
{
    int64_t Ret;
    FileStream tmp;
    FileStream_Ctor(&tmp);
    Ret = FileStream_Open(&tmp, Path, READONLY);
    if(! Ret)
        return 0;
    FileStream_ReadBuffer(Dest, &tmp, tmp.Length);
    Ret = tmp.Length;
    FileStream_Dtor(&tmp);
    return Ret;
}

int64_t LoadFileRange(void* Dest, String* Path, int64_t Start, int64_t End)
{
    int64_t Ret;
    FileStream tmp;
    FileStream_Ctor(&tmp);
    Ret = FileStream_Open(&tmp, Path, READONLY);
    if(! Ret)
        return 0;
    FileStream_SetPosition(&tmp, Start);
    FileStream_ReadBuffer(Dest, &tmp, End - Start);
    Ret = End - Start;
    FileStream_Dtor(&tmp);
    return Ret;
}

int WriteFileAll(String* Path, void* Src, int64_t size)
{
    int Ret;
    FileStream tmp;
    FileStream_Ctor(&tmp);
    Ret = FileStream_Open(&tmp, Path, CREATE);

    if(! Ret)
        return 0;
    FileStream_WriteBuffer(&tmp, Src, size);

    FileStream_Dtor(&tmp);
    return 1;
}

int LoadWaveAll(float* Dest, String* Path)
{
    int Ret;
    PCMWaveFile wave;
    PCMWaveFile_Ctor(&wave);
    if(! PCMWaveFile_Open(&wave, Path))
        return 0;
    Ret = wave.Header.dataNum;
    PCMWaveFile_FetchAllFloat(Dest, &wave);
    PCMWaveFile_Close(&wave);
    PCMWaveFile_Dtor(&wave);
    return Ret;
}

int WriteWaveAll(String* Dest, float* Src, int Size, int SampleRate)
{
    PCMWaveFile wave;
    PCMWaveFile_Ctor(&wave);
    wave.Header.channel = 1;
    wave.Header.samplePerSecond = SampleRate;
    wave.Header.bytePerSecond = SampleRate * 2;
    wave.Header.blockAlign = 2;
    wave.Header.bitPerSample = 16;
    wave.Header.bytePerSample = 2;

    if(! PCMWaveFile_Save(Dest, &wave))
        return 0;

    PCMWaveFile_WriteAllFloat(&wave, Src, Size);
    PCMWaveFile_FinishWrite(&wave);
    PCMWaveFile_Close(&wave);
    PCMWaveFile_Dtor(&wave);
    return 1;
}
