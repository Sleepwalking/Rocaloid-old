#ifndef VARIATIONLIST_H
#define VARIATIONLIST_H

#ifdef __cplusplus
extern "C"{
#endif

typedef struct
{
    float* Independent;
    int Independent_Index;
    int Independent_Size;
    float* Dependent;
    int Dependent_Index;
    int Dependent_Size;
} VariationList;

typedef struct
{
    float Weighted;
    int LowerIndex;
    float Ratio;
} TransResult;

extern void VariationList_Ctor(VariationList* Dest);
extern void VariationList_Dtor(VariationList* Dest);

extern void VariationList_AddPair(VariationList* Dest, float IndependentVar, float DependentVar);
extern void VariationList_Clear(VariationList* Dest);

extern TransResult VariationList_Query(VariationList* Dest, float IndependentVar);

#ifdef __cplusplus
}
#endif
#endif

