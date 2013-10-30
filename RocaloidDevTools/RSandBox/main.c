#include <stdio.h>
#include "CVEDSP/Interpolation.h"
#include "CVEDSP/Algorithm/PSOLA.h"
#include "CVEDSP/IntrinUtil/Calculation.h"

#include <xmmintrin.h>

void FSynth_Resample(PSOLAFrame* Dest, PSOLAFrame* Src, float Ratio)
{
    int i;
    float Offset;
    int SrcHalf = Src -> Length / 2;
    float* Center = Src -> Data + SrcHalf;
    float IRatio;

    Offset = (float)(0 - Dest -> Length / 2) * Ratio;
    if(Offset > - SrcHalf + 1)
    {
        //No bound checking
        for(i = 0; i < Dest -> Length; i ++)
        {
            //In Src range: linear interpolation.
            int LOffset;
            LOffset = _mm_cvtss_si32(_mm_set_ss(Offset + SrcHalf)) - SrcHalf;
            IRatio = Offset - LOffset;
            Dest -> Data[i] = Center[LOffset] * (1.0f - IRatio) + Center[LOffset + 1] * (IRatio);
            Offset += Ratio;
        }
    }else
    {
        //Bound checking
        for(i = 0; i < Dest -> Length; i ++)
        {
            if(Offset > - SrcHalf + 1 && Offset < SrcHalf - 1)
            {
                //In Src range: linear interpolation.
                int LOffset;
                LOffset = Boost_FloatToInt(Offset + SrcHalf) - SrcHalf;
                Dest -> Data[i] = Center[LOffset] * (1 - Offset + LOffset) + Center[LOffset + 1] * (Offset - LOffset);
            }
            else
            {
                //Beyond Src range.
                Dest -> Data[i] = 0;
            }
            Offset += Ratio;
        }
    }
}

int main(void)
{
    PSOLAFrame a, b;
    PSOLAFrame_CtorSize(& a, 2048);
    PSOLAFrame_CtorSize(& b, 2048);
    int i, j;
    for(i = 0; i < 2048; i ++)
    {
        a.Data[i] = i;
    }
    for(j = 0; j < 1000; j ++)
        FSynth_Resample(& b, & a, 0.8);
    PSOLAFrame_Dtor(& a);
    PSOLAFrame_Dtor(& b);
    printf("s\n");
    return 0;
}

