#include "TData.h"
#include "../../../RUtil/IO/FileUtil.h"
#include "../../../CVEDSP/Algorithm/Formant.h"
#include "../../../CVEDSP/DSPBase/LPC.h"
#include "../../../CVEDSP/Algorithm/BaseFreq.h"
#include "../../../CVEDSP/DSPBase/Spectrum.h"

_Constructor_ (Wave)
{
    ArrayType_Init(float, Dest -> Data);
}

_Destructor_ (Wave)
{
    ArrayType_Dtor(float, Dest -> Data);
}

_Constructor_ (TData)
{
    ArrayType_Init(Wave, Dest -> WaveList);
    ArrayType_Init(Wave, Dest -> SpecList);
}

_Destructor_ (TData)
{
    ArrayType_ObjDtor(Wave, Dest -> WaveList);
    ArrayType_ObjDtor(Wave, Dest -> SpecList);

    ArrayType_Dtor(Wave, Dest -> WaveList);
    ArrayType_Dtor(Wave, Dest -> SpecList);
}

void TData_LoadFromString(TData* Dest, String* Src, int Size)
{
    int i;
    ArrayType_ObjDtor(Wave, Dest -> WaveList);
    ArrayType_ObjDtor(Wave, Dest -> SpecList);

    ArrayType_Resize(Wave, Dest -> WaveList, Size);
    ArrayType_Resize(Wave, Dest -> SpecList, Size);
    Dest -> WaveList_Index = Size - 1;
    Dest -> SpecList_Index = Size - 1;

    float* LPC = (float*)malloc(sizeof(float) * 100);
    float* Spectrum = (float*)malloc(sizeof(float) * 1024);

    for(i = 0; i < Size; i ++)
    {
        int Len;
        Wave_Ctor(Dest -> WaveList + i);
        Wave_Ctor(Dest -> SpecList + i);
        Len = 44100 * 5;
        ArrayType_Resize(float, Dest -> WaveList[i].Data, Len);
        Len = LoadWaveAll(Dest -> WaveList[i].Data, Src + i);
        Dest -> WaveList[i].Data_Index = Len - 1;

        ArrayType_Resize(float, Dest -> SpecList[i].Data, 1024);

        LPCFromWave(LPC, Dest -> WaveList[i].Data + Len / 2, 1024, 50);
        SpectralEnvelopeFromLPC(Dest -> SpecList[i].Data, LPC, 50, 10);
        NormalizeSpectrum(Dest -> SpecList[i].Data, 105);

        Dest -> WaveList[i].BaseFreq = GetBaseFrequencyFromWave(Dest -> WaveList[i].Data + Len / 2, 80, 1500, 13);
        Dest -> SpecList[i].BaseFreq = Dest -> WaveList[i].BaseFreq;
    }
    free(LPC);
    free(Spectrum);
}
