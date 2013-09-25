#include "Rand.h"
#include <stdlib.h>

float Random()
{
    return (float)(rand() % 200000) / 100000.0f - 1.0f;
}

int IntRandom(int Range)
{
    return rand() % Range - Range / 2;
}
