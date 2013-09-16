#ifndef ARRAY_H
#define ARRAY_H

#include <malloc.h>
#define Array_Addition 100

#define Array_Resize(Type, Array, IndexNumber, Size, NewSize)\
    do{\
        (Array) = (Type*)realloc((Array), sizeof(Type) * (NewSize));\
        (Size) = NewSize;\
        if((NewSize) <= (IndexNumber))\
            (IndexNumber) = (NewSize) - 1;\
    }while(0)

#define Array_Push(Type, Array, IndexNumber, Size, Data)\
    do{\
        if((IndexNumber) > (Size) - 2)\
        {\
            (Array) = (Type*)realloc((Array), sizeof(Type) * ((Array_Addition) + (Size)));\
            (Size) += Array_Addition;\
        }\
        (Array)[++ IndexNumber] = Data;\
    }while(0)

#define Array_PushNull(Type, Array, IndexNumber, Size)\
    do{\
        if((IndexNumber) > (Size) - 2)\
        {\
            (Array) = (Type*)realloc((Array), sizeof(Type) * ((Array_Addition) + (Size)));\
            (Size) += Array_Addition;\
        }\
        (IndexNumber) ++;\
    }while(0)

#define Array_Pop(Type, Array, IndexNumber, Size)\
    ((Array)[IndexNumber --])

#define Array_Insert(Type, Array, IndexNumber, Size, Index, Data)\
    do{\
        int Array_i;\
        if((IndexNumber) > (Size) - 2)\
        {\
            (Array) = (Type*)realloc((Array), sizeof(Type) * ((Array_Addition) + (Size)));\
            (Size) += Array_Addition;\
        }\
        for(Array_i = (IndexNumber) + 1; Array_i > (Index); Array_i --)\
            (Array)[Array_i] = (Array)[Array_i - 1];\
        (Array)[Index] = Data;\
        (IndexNumber) ++;\
    }while(0)

#define Array_Remove(Type, Array, IndexNumber, Size, Index)\
    do{\
        int Array_i;\
        for(Array_i = (Index); Array_i < (IndexNumber); Array_i ++)\
            (Array)[Array_i] = (Array)[Array_i + 1];\
        (IndexNumber) --;\
    }while(0)

#define Array_RemoveRange(Type, Array, IndexNumber, Size, LIndex, HIndex)\
    do{\
        int Array_i;\
        int Array_RemoveAmount = (HIndex) - (LIndex) + 1;\
        for(Array_i = (LIndex); Array_i < (IndexNumber) - (HIndex - LIndex); Array_i ++)\
            (Array)[Array_i] = (Array)[Array_i + Array_RemoveAmount];\
        (IndexNumber) -= Array_RemoveAmount;\
    }while(0)

#define ArrayType_Define(Type, Name)\
    Type* Name;\
    int Name##_Index;\
    int Name##_Size

#define ArrayType_Ctor(Type, Name)\
    Type* Name = (Type*)malloc(sizeof(Type) * 10);\
    int Name##_Index = -1;\
    int Name##_Size = 10

#define ArrayType_Init(Type, Name)\
    Name = (Type*)malloc(sizeof(Type) * 10);\
    Name##_Index = -1;\
    Name##_Size = 10

#define ArrayType_Dtor(Type, Name)\
    free(Name)

#define ArrayType_ObjDtor(Type, Name);\
    do{\
        int Array_i;\
        for(Array_i = 0; Array_i <= Name##_Index; Array_i ++)\
            Type##_Dtor(Name + Array_i);\
    }while(0)

#define ArrayType_Resize(Type, Array, NewSize)\
    Array_Resize(Type, Array, Array##_Index, Array##_Size, NewSize)

#define ArrayType_Push(Type, Array, Data)\
    Array_Push(Type, Array, Array##_Index, Array##_Size, Data)

#define ArrayType_PushNull(Type, Array)\
    Array_PushNull(Type, Array, Array##_Index, Array##_Size)

#define ArrayType_Pop(Type, Array)\
    Array_Pop(Type, Array, Array##_Index, Array##_Size)

#define ArrayType_Insert(Type, Array, Index, Data)\
    Array_Insert(Type, Array, Array##_Index, Array##_Size, Index, Data)

#define ArrayType_Remove(Type, Array, Index)\
    Array_Remove(Type, Array, Array##_Index, Array##_Size, Index)

#define ArrayType_RemoveRange(Type, Array, LIndex, HIndex)\
    Array_RemoveRange(Type, Array, Array##_Index, Array##_Size, LIndex, HIndex)

#define Arg_ArrayType(Type, Array) Type* Array, int Array##_Index, int Array##_Size
#define FArg_ArrayType(Type, Array) Array, Array##_Index, Array##_Size

#endif
