#define COMPILE_EXEC_RUTIL
#ifdef COMPILE_EXEC_RUTIL

#include <stdio.h>
#include <time.h>
#include "Structure/Array.h"
#include "Structure/String.h"
#include "Structure/VariationList.h"
#include "Misc/Converter.h"
#include "IO/FileStream.h"
#include "IO/FileUtil.h"
#include "IO/StringStream.h"
#include "IO/Wave.h"

int main(void)
{
    VariationList testList;
    VariationList_Ctor(& testList);
    VariationList_AddPair(& testList, 1, 2.5);
    VariationList_AddPair(& testList, 0.5, 2);
    VariationList_AddPair(& testList, 2, 5);
    VariationList_AddPair(& testList, 1.5, 10);
    float i;
    for(i = 0; i < 3; i += 0.1)
    {
        TransResult ret = VariationList_Query(& testList, i);
        printf("%f, %f, index: %d, ratio: %f\n", i, ret.Weighted, ret.LowerIndex, ret.Ratio);
    }

    VariationList_Dtor(& testList);
    return 0;
}

#endif

