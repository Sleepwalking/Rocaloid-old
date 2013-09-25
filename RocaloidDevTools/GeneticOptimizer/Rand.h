#ifndef RAND_H
#define RAND_H

extern float Random();
extern int IntRandom(int Range);

#define RandRange(Para, Width, LowerLimit, UpperLimit)\
    P -> Para += Random() * Width;\
    if(P -> Para < LowerLimit)\
        P -> Para = LowerLimit + Random() * Width;\
    if(P -> Para > UpperLimit)\
        P -> Para = UpperLimit + Random() * Width;

#define IntRandRange(Para, Width, LowerLimit, UpperLimit)\
    P -> Para += IntRandom(Width);\
    if(P -> Para < LowerLimit)\
        P -> Para = LowerLimit + IntRandom(Width);\
    if(P -> Para > UpperLimit)\
        P -> Para = UpperLimit + IntRandom(Width);

#endif
