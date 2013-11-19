#include "VariationList.h"
#include "Array.h"

void VariationList_Ctor(VariationList* Dest)
{
    ArrayType_Init(float, Dest -> Independent);
    ArrayType_Init(float, Dest -> Dependent);
}

void VariationList_Dtor(VariationList* Dest)
{
    ArrayType_Dtor(float, Dest -> Independent);
    ArrayType_Dtor(float, Dest -> Dependent);
}

void VariationList_AddPair(VariationList* Dest, float IndependentVar, float DependentVar)
{
    int Index;
    ArrayType_IncreaseSortFind(Index, float, Dest -> Independent, IndependentVar);
    ArrayType_Insert(float, Dest -> Dependent  , Index, DependentVar);
    ArrayType_Insert(float, Dest -> Independent, Index, IndependentVar);
}

void VariationList_Clear(VariationList* Dest)
{
    Dest -> Dependent_Index   = - 1;
    Dest -> Independent_Index = - 1;
}

TransResult VariationList_Query(VariationList* Dest, float IndependentVar)
{
    TransResult Ret;
    ArrayType_IncreaseSortFind(Ret.LowerIndex, float, Dest -> Independent, IndependentVar);
    Ret.LowerIndex --;
    if(Ret.LowerIndex < Dest -> Independent_Index)
    {
        Ret.Ratio = (IndependentVar - Dest -> Independent[Ret.LowerIndex]) /
                    (Dest -> Independent[Ret.LowerIndex + 1] - Dest -> Independent[Ret.LowerIndex]);
        Ret.Weighted = Dest -> Dependent[Ret.LowerIndex] * (1.0f - Ret.Ratio) +
                       Dest -> Dependent[Ret.LowerIndex + 1] * Ret.Ratio;
    }else
    {
        Ret.Ratio = 1;
        Ret.Weighted = Dest -> Dependent[Dest -> Dependent_Index];
    }
    return Ret;
}

