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

int CSPR_Load(CSPR* Dest, String* Path)
{
    int i;
    int Pos;
    int Len = GetFileLength(Path);
    if(Len <= 0)
        return Len;
    char* Tmp = (char*)malloc(Len);
    LoadFileAll(Tmp, Path);
    memcpy(Dest -> Header, Tmp, 4);
    Dest -> Version = *(uint16_t*)(Tmp + 4);
    if(Dest -> Version != 1)
    {
        free(Tmp);
        return 0;
    }
    Dest -> DividingFreq = *(float*)(Tmp + 6);
    Dest -> ClassNum = *(int32_t*)(Tmp + 10);

    Pos = 14 + Dest -> ClassNum * sizeof(FormantDescriptor);
    ArrayType_Resize(FormantDescriptor, Dest -> FormantClasses, Dest -> ClassNum);
    Dest -> FormantClasses_Index = Dest -> ClassNum - 1;

    memcpy(Dest -> FormantClasses, Tmp + 14, Pos - 14);

    int LayerSize[3];
    LayerSize[0] = *(int*)(Tmp + Pos); Pos += 4;
    LayerSize[1] = *(int*)(Tmp + Pos); Pos += 4;
    LayerSize[2] = Dest -> ClassNum;

    FeedForward_SetLayer(& Dest -> FFNetLow, LayerSize, 3);
    //Read Layer 1
    for(i = 0; i < LayerSize[1]; i ++)
    {
        memcpy(Dest -> FFNetLow.Layers[1].W[i], Tmp + Pos, LayerSize[0] * sizeof(float));
        Pos += LayerSize[0] * sizeof(float);
    }
    //Read Layer 2
    for(i = 0; i < LayerSize[2]; i ++)
    {
        memcpy(Dest -> FFNetLow.Layers[2].W[i], Tmp + Pos, LayerSize[1] * sizeof(float));
        Pos += LayerSize[1] * sizeof(float);
    }

    LayerSize[0] = *(int*)(Tmp + Pos); Pos += 4;
    LayerSize[1] = *(int*)(Tmp + Pos); Pos += 4;

    FeedForward_SetLayer(& Dest -> FFNetHigh, LayerSize, 3);
    //Read Layer 1
    for(i = 0; i < LayerSize[1]; i ++)
    {
        memcpy(Dest -> FFNetHigh.Layers[1].W[i], Tmp + Pos, LayerSize[0] * sizeof(float));
        Pos += LayerSize[0] * sizeof(float);
    }
    //Read Layer 2
    for(i = 0; i < LayerSize[2]; i ++)
    {
        memcpy(Dest -> FFNetHigh.Layers[2].W[i], Tmp + Pos, LayerSize[1] * sizeof(float));
        Pos += LayerSize[1] * sizeof(float);
    }

    free(Tmp);
    return 1;
}

int CSPR_Save(String *Dest, CSPR *Src)
{
    int i;
    int Size = 14;
    char* Tmp = (char*)malloc(1024 * 1024);

    //Header, Version, DividingFreq, ClassNum
    memcpy(Tmp, Src -> Header, 4);
    *(uint16_t*)(Tmp + 4) = Src -> Version;
    *(float*)(Tmp + 6) = Src -> DividingFreq;
    *(int32_t*)(Tmp + 10) = Src -> ClassNum;

    Size += sizeof(FormantDescriptor) * (Src -> FormantClasses_Index + 1);
    memcpy(Tmp + 14, Src -> FormantClasses, Size - 14);

    int L1Size = Src -> FFNetLow.Layers[0].O_Index + 1;
    int L2Size = Src -> FFNetLow.Layers[1].O_Index + 1;
    int L3Size = Src -> FFNetLow.Layers[2].O_Index + 1;
    *(int32_t*)(Tmp + Size) = L1Size;
    Size += 4;

    *(int32_t*)(Tmp + Size) = L2Size;
    Size += 4;

    //Write Layer 1
    for(i = 0; i < L2Size; i ++)
    {
        memcpy(Tmp + Size, Src -> FFNetLow.Layers[1].W[i], L1Size * sizeof(float));
        Size += L1Size * sizeof(float);
    }

    //Write Layer 2
    for(i = 0; i < L3Size; i ++)
    {
        memcpy(Tmp + Size, Src -> FFNetLow.Layers[2].W[i], L2Size * sizeof(float));
        Size += L2Size * sizeof(float);
    }

    L1Size = Src -> FFNetHigh.Layers[0].O_Index + 1;
    L2Size = Src -> FFNetHigh.Layers[1].O_Index + 1;
    L3Size = Src -> FFNetHigh.Layers[2].O_Index + 1;
    *(int32_t*)(Tmp + Size) = L1Size;
    Size += 4;
    *(int32_t*)(Tmp + Size) = L2Size;
    Size += 4;

    //Write Layer 1
    for(i = 0; i < L2Size; i ++)
    {
        memcpy(Tmp + Size, Src -> FFNetHigh.Layers[1].W[i], L1Size * sizeof(float));
        Size += L1Size * sizeof(float);
    }

    //Write Layer 2
    for(i = 0; i < L3Size; i ++)
    {
        memcpy(Tmp + Size, Src -> FFNetHigh.Layers[2].W[i], L2Size * sizeof(float));
        Size += L2Size * sizeof(float);
    }

    int Ret = WriteFileAll(Dest, Tmp, Size);
    free(Tmp);
    return Ret;
}
