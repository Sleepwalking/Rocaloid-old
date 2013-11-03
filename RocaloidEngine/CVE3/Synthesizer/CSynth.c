#include "CSynth.h"
#include "../RFILE3/CDT3/Demapper.h"
#include "../CVEGlobal.h"
#include "../Debug/ALblLog.h"

_Constructor_ (CSynth)
{
    CVDB3_Ctor(& Dest -> Data);
    String_Ctor(& Dest -> Symbol);
    Dest -> FPlayIndex = 1;
    Dest -> PlayIndex = 1;
    Dest -> PlayPosition = 0;
    Dest -> ConsonantRatio = 1;
    Dest -> VowelRatio = 1;
}

_Destructor_ (CSynth)
{
    CVDB3_Dtor(& Dest -> Data);
    String_Dtor(& Dest -> Symbol);
}

void CSynth_SetSymbol(CSynth* Dest, String* Symbol)
{
    if(! String_Equal(Symbol, & Dest -> Symbol))
    {
        int LoadIndex = Demapper_QueryDBLayer(Symbol);
        CVDB3_Load(& Dest -> Data, & CGDict.CDTMapping.DBLayerMap[LoadIndex].FileAddr);
        Dest -> Data.Header.PulseNum -= 2;
        CSynth_Reset(Dest);
        printf("%s Loaded.\n", Dest -> Data.Header.Symbol);
        ALblLog_Print("CS Load on %d, FPI = %f", Dest -> PlayIndex, Dest -> FPlayIndex);
    }
}

void CSynth_SetConsonantRatio(CSynth* Dest, float CRatio)
{
    Dest -> ConsonantRatio = CRatio;
}

void CSynth_SetVowelRatio(CSynth* Dest, float VRatio)
{
    Dest -> VowelRatio = VRatio;
}

void CSynth_Reset(CSynth* Dest)
{
    Dest -> FPlayIndex = 1;
    Dest -> PlayIndex = 1;
    Dest -> PlayPosition = 0;
    Dest -> ConsonantRatio = 1;
    Dest -> VowelRatio = 1;

    unsigned int i;
    if(Dest -> Data.Header.PhoneType == 'V')
    {
        //Vowels should start after VOT
        Dest -> PlayIndex = Dest -> Data.Header.VOI;
        Dest -> PlayPosition = Dest -> Data.PulseOffsets[Dest -> PlayIndex];
        Dest -> FPlayIndex = Dest -> PlayIndex;
        ALblLog_Print("Load on %d, FPI = %f", Dest -> PlayIndex, Dest -> FPlayIndex);
    }
    for(i = 0; i < Dest -> Data.Header.PulseNum; i ++)
        if(Dest -> Data.PulseOffsets[i] > CSynth_GetVOT(Dest) + CSynth_CycleDelay)
            break;
    Dest -> CycleStart = i;
    Dest -> CycleLength = CSynth_CycleSample / (SampleRate / Dest -> Data.Header.F0);
}

//Find the nearest bin to PlayPosition.
void CSynth_UpdateIndex(CSynth* Dest)
{
    unsigned int i;
    unsigned int record = 0;
    int Min = 999;
    int Dist;
    for(i = 0; i < Dest -> Data.Header.PulseNum; i ++)
    {
        Dist = abs(Dest -> Data.PulseOffsets[i] - Dest -> PlayPosition);
        if(Dist < Min)
        {
            Min = Dist;
            record = i;
        }
    }
    Dest -> PlayIndex = record;
    //Dest -> PlayPosition = Dest -> Data.PulseOffsets[record];
    Dest -> FPlayIndex = record;
    ALblLog_Print("FPlayIndex = %f", Dest -> FPlayIndex);
}

#define DPlayIndex (Dest -> PlayIndex)
#define DPlayPos (Dest -> PlayPosition)
#define DPulseNum (Dest -> Data.Header.PulseNum)
#define DPulseOffsets (Dest -> Data.PulseOffsets)
#define DLength (DPulseOffsets[DPulseNum - 1])
CSynthSendback CSynth_Synthesis(CSynth* Dest, PSOLAFrame* Output)
{
    CSynthSendback Ret;
    float TRatio = 0;
    DPlayIndex = Dest -> FPlayIndex;
    //ALblLog_Print("Routine %d (%d, %f)", Ret.PSOLAFrameHopSize, DPlayIndex, Dest -> FPlayIndex);
    if(DPlayIndex > (signed int)(DPulseNum - Dest -> CycleLength))
    {
        //In transition
        PSOLAFrame Temp;
        PSOLAFrame_CtorSize(& Temp, Output -> Length);
        int ExceedLength = DPlayIndex - DPulseNum + Dest -> CycleLength;
        TRatio = (float)ExceedLength / Dest -> CycleLength;
        PSOLAFrame_SecureGet(Output,
                             Dest -> Data.Wave,
                             Dest -> Data.Header.WaveSize,
                             DPulseOffsets[DPlayIndex]);
        PSOLAFrame_SecureGet(& Temp,
                             Dest -> Data.Wave,
                             Dest -> Data.Header.WaveSize,
                             DPulseOffsets[Dest -> CycleStart + ExceedLength]);
        Boost_FloatMul(Temp.Data, Temp.Data, TRatio, Temp.Length);
        Boost_FloatMul(Output -> Data, Output -> Data, 1.0f - TRatio, Output -> Length);
        Boost_FloatAddArr(Output -> Data, Temp.Data, Output -> Data, Temp.Length);
        PSOLAFrame_Dtor(& Temp);
    }else
    {
        PSOLAFrame_SecureGet(Output,
                             Dest -> Data.Wave,
                             Dest -> Data.Header.WaveSize,
                             DPulseOffsets[DPlayIndex]);
    }
    if(/*Dest -> Data.Header.PhoneType == 'C' && */DPlayIndex < (signed int)Dest -> Data.Header.VOI)
    {
        //In Consonant
        Ret.PSOLAFrameHopSize = 512;//(DPulseOffsets[DPlayIndex + 1] - DPulseOffsets[DPlayIndex]);
        Ret.BeforeVOT = 1;
        DPlayPos += Ret.PSOLAFrameHopSize / Dest -> ConsonantRatio;
        ALblLog_Print("Before %d (%d, %f)", Ret.PSOLAFrameHopSize, DPlayIndex, Dest -> FPlayIndex);
        CSynth_UpdateIndex(Dest);
    }else
    {
        //In Cycle
        Ret.PSOLAFrameHopSize = DPulseOffsets[DPlayIndex + 1] - DPulseOffsets[DPlayIndex];
        ALblLog_Print("After %d (%d, %f)", Ret.PSOLAFrameHopSize, DPlayIndex, Dest -> FPlayIndex);
        Ret.BeforeVOT = 0;
        Dest -> FPlayIndex += 1.0f / Dest -> VowelRatio;
    }
    if(Dest -> FPlayIndex > DPulseNum)
        Dest -> FPlayIndex = Dest -> CycleStart + Dest -> CycleLength;

    return Ret;
}

float CSynth_GetVOT(CSynth* Dest)
{
    return Dest -> Data.PulseOffsets[Dest -> Data.Header.VOI] * Dest -> ConsonantRatio;
}
