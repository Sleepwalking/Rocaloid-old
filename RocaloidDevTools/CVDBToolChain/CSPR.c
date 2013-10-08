#include "CSPR.h"
#include <string.h>
#include <malloc.h>
#include "RUtil/IO/FileUtil.h"

_Constructor_ (CSPR)
{
    ArrayType_Init(FormantDescriptor, Dest -> FormantClasses);
    FeedForward_Ctor(& Dest -> FFNetLow);
    FeedForward_Ctor(& Dest -> FFNetHigh);
    memcpy(Dest -> Header, "CSPR", 4);
    Dest -> Version = 1;
}

_Destructor_ (CSPR)
{
    ArrayType_Dtor(FormantDescriptor, Dest -> FormantClasses);
    FeedForward_Dtor(& Dest -> FFNetLow);
    FeedForward_Dtor(& Dest -> FFNetHigh);
}

extern int CSPR_Save(CSPR *Dest, String *Path)
{
    int i;
    int Size = 14;
    char* Tmp = (char*)malloc(1024 * 1024);

    //Header, Version, DividingFreq, ClassNum
    memcpy(Tmp, Dest, Size);

    Size += sizeof(FormantDescriptor) * (Dest -> FormantClasses_Index + 1);
    memcpy(Tmp + 14, Dest -> FormantClasses, Size - 14);

    int L1Size = Dest -> FFNetLow.Layers[0].O_Index + 1;
    int L2Size = Dest -> FFNetLow.Layers[1].O_Index + 1;
    int L3Size = Dest -> FFNetLow.Layers[2].O_Index + 1;
    *(int32_t*)(Tmp + Size) = L1Size;
    Size += 4;

    //Write Layer 1
    for(i = 0; i < L2Size; i ++)
    {
        memcpy(Tmp + Size, Dest -> FFNetLow.Layers[1].W[i], L1Size * sizeof(float));
        Size += L1Size * sizeof(float);
    }

    //Write Layer 2
    for(i = 0; i < L3Size; i ++)
    {
        memcpy(Tmp + Size, Dest -> FFNetLow.Layers[2].W[i], L2Size * sizeof(float));
        Size += L2Size * sizeof(float);
    }

    L1Size = Dest -> FFNetHigh.Layers[0].O_Index + 1;
    L2Size = Dest -> FFNetHigh.Layers[1].O_Index + 1;
    L3Size = Dest -> FFNetHigh.Layers[2].O_Index + 1;
    *(int32_t*)(Tmp + Size) = L1Size;
    Size += 4;

    //Write Layer 1
    for(i = 0; i < L2Size; i ++)
    {
        memcpy(Tmp + Size, Dest -> FFNetHigh.Layers[1].W[i], L1Size * sizeof(float));
        Size += L1Size * sizeof(float);
    }

    //Write Layer 2
    for(i = 0; i < L3Size; i ++)
    {
        memcpy(Tmp + Size, Dest -> FFNetHigh.Layers[2].W[i], L2Size * sizeof(float));
        Size += L2Size * sizeof(float);
    }

    WriteFileAll(Path, Tmp, Size);
    free(Tmp);
    return 1;
}
