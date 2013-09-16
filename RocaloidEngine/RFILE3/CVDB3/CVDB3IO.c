#include "CVDB3IO.h"
#include <malloc.h>
#include <string.h>

_Constructor_ (CVDB3)
{
    Dest -> PulseOffsets = (uint32_t*)malloc(4);
    Dest -> Wave = (float*)malloc(4);
}

_Destructor_ (CVDB3)
{
    free(Dest -> PulseOffsets);
    free(Dest -> Wave);
}

void CVDB3_Load(CVDB3* Dest, String* Path)
{
    uint32_t i;
    int FileLength = GetFileLength(Path);
    void* File = malloc(FileLength);
    LoadFileAll(File, Path);
    Dest -> Header = *(CVDB3Header*)File;
    Dest -> PulseOffsets = (uint32_t*)realloc(Dest -> PulseOffsets, 4 * Dest -> Header.PulseNum);
    Dest -> Wave = (float*)realloc(Dest -> Wave, 4 * Dest -> Header.WaveSize);

    File += sizeof(CVDB3Header);
    memcpy(Dest -> PulseOffsets, File, 4 * Dest -> Header.PulseNum);

    File += 4 * Dest -> Header.PulseNum;
    for(i = 0; i < Dest -> Header.WaveSize; i ++)
        Dest -> Wave[i] = (float)((int16_t*)File)[i] / 32767;

    File -= 4 * Dest -> Header.PulseNum;
    File -= sizeof(CVDB3Header);
    free(File);
}

void CVDB3_Write(String* Path, CVDB3* Src)
{
    uint32_t i;
    int FileLength = sizeof(CVDB3Header) + 4 * Src -> Header.PulseNum + 2 * Src -> Header.WaveSize;
    void* File = malloc(FileLength);
    *(CVDB3Header*)File = Src -> Header;

    File += sizeof(CVDB3Header);
    memcpy(File, Src -> PulseOffsets, 4 * Src -> Header.PulseNum);

    File += 4 * Src -> Header.PulseNum;
    for(i = 0; i < Src -> Header.WaveSize; i ++)
        ((int16_t*)File)[i] = (int16_t)(Src -> Wave[i] * 32767);

    File -= 4 * Src -> Header.PulseNum;
    File -= sizeof(CVDB3Header);
    WriteFileAll(Path, File, FileLength);
    free(File);
}
