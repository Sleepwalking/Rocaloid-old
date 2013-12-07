#include "Math.h"
#include <stdlib.h>

int FDecSorter(const void* a, const void* b)
{
    return *((float*)a) < *((float*)b);
}

int FIncSorter(const void* a, const void* b)
{
    return *((float*)a) > *((float*)b);
}

void Math_FloatIncSort(float* Dest, int Amount)
{
    qsort(Dest, Amount, sizeof(float), FIncSorter);
}

void Math_FloatDecSort(float* Dest, int Amount)
{
    qsort(Dest, Amount, sizeof(float), FDecSorter);
}
