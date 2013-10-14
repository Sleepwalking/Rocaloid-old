#include "FDFrame.h"
#include <malloc.h>

_Constructor_ (FDFrame)
{
    Dest -> Re = (float*)malloc(1024 * sizeof(float));
    Dest -> Im = (float*)malloc(1024 * sizeof(float));
    Dest -> Length = 1024;
}

_Destructor_ (FDFrame)
{
    free(Dest -> Re);
    free(Dest -> Im);
}

void FDFrame_CtorSize(FDFrame* Dest, int Size)
{
    Dest -> Re = (float*)malloc(Size * sizeof(float));
    Dest -> Im = (float*)malloc(Size * sizeof(float));
    Dest -> Length = Size;
}

void FDFrame_Resize(FDFrame* Dest, int Size)
{
    Dest -> Re = (float*)realloc(Dest -> Re, Size * sizeof(float));
    Dest -> Im = (float*)realloc(Dest -> Im, Size * sizeof(float));
    Dest -> Length = Size;
}

int GetTransformPower(int TransformSize)
{
    int TransformPower = 0;
    switch (TransformSize)
    {
    case 512:
        TransformPower = 9;
        break;
    case 1024:
        TransformPower = 10;
        break;
    case 2048:
        TransformPower = 11;
        break;
    case 4096:
        TransformPower = 12;
        break;
    default:
        return - 1;
        break;
    }
    return TransformPower;
}

int FDFrame_FromPSOLAFrame(FDFrame *Dest, PSOLAFrame *Src)
{
    int TransformSize = Dest -> Length < Src -> Length ? Dest -> Length : Src -> Length;
    int TransformPower = GetTransformPower(TransformSize);
    if(TransformPower < 0)
        return - 1;
    RFFT(Dest -> Re, Dest -> Im, Src -> Data + Src -> Length / 2 - TransformSize / 2, TransformPower);
    return 1;
}

int PSOLAFrame_FromFDFrame(PSOLAFrame* Dest, FDFrame* Src)
{
    int TransformSize = Dest -> Length < Src -> Length ? Dest -> Length : Src -> Length;
    int TransformPower = GetTransformPower(TransformSize);
    if(TransformPower < 0)
        return - 1;
    Boost_FloatSet(Dest -> Data, 0, Dest -> Length);
    RIFFT(Dest -> Data + Dest -> Length / 2 - Src -> Length / 2, Src -> Re, Src -> Im, TransformPower);
    return 1;
}
