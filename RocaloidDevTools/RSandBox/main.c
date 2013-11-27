#include <stdio.h>
#include "CVEDSP/Interpolation.h"
#include "CVEDSP/Algorithm/PSOLA.h"
#include "CVEDSP/IntrinUtil/Calculation.h"
#include "RFILE3/CVDB3/CVDB3IO.h"

int main(void)
{
    CVDB3 DFrag;
    CVDB3_Ctor(& DFrag);
    String_FromChars(DPath, "/tmp/Rocaloid_LuoTianYi_Build/CVDB/a0.cvdb");
    CVDB3_Load(& DFrag, & DPath);
    float* Wave = (float*)malloc(sizeof(float) * 44100 * 10);
    ArrayType_Ctor(PSOLAFrame, PList);
    int i;
    for(i = 0; i < (int)DFrag.Header.PulseNum; i ++)
    {
        ArrayType_PushNull(PSOLAFrame, PList);
        PSOLAFrame_Ctor(PList + PList_Index);
        PSOLAFrame_SecureGet(PList + PList_Index, DFrag.Wave, DFrag.Header.WaveSize, DFrag.PulseOffsets[i]);
    }
    PSOLA_Regenesis(Wave, PList, (int*)DFrag.PulseOffsets, (int*)DFrag.PulseOffsets, (int)DFrag.Header.PulseNum);

    String_FromChars(WPath, "/tmp/Resynth.wav");
    WriteWaveAll(& WPath, Wave, 44100 * 2, 44100);
    String_Dtor(& WPath);
    ArrayType_ObjDtor(PSOLAFrame, PList);
    ArrayType_Dtor(PSOLAFrame, PList);
    free(Wave);
    String_Dtor(& DPath);
    CVDB3_Dtor(& DFrag);
    printf("Finished.\n");
    return 0;
}

