#include <stdio.h>
#include "../../../RUtil/RUtil.h"
#include "../../../RUtil/IO/FileUtil.h"
#include "Processor.h"
#include <malloc.h>

/*
    Wpp Wave [-balance] [-normalize magnitude] [-lpf frequency] [-hpf frequency] [-f0 frequency]
*/

typedef enum
{
    P_Balance = 0,
    P_Normalize = 1,
    P_LPF = 2,
    P_HPF = 3
} Process;

int GotWave = 0;
int GotF0 = 0;
int NextNormalize = 0;
int NextLPF = 0;
int NextHPF = 0;
int NextF0 = 0;
float Normalize_Magnitude = 0;
float HPF_Frequency = 0;
float LPF_Frequency = 0;
float F0 = 0;

String WavePath;
int main(int argc, char** argv)
{
    int i;
    String Tmp;
    String_Ctor(& Tmp);
    String_Ctor(& WavePath);
    ArrayType_Ctor(Process, ProcessList);
    for(i = 1; i < argc; i ++)
    {
        String_SetChars(& Tmp, argv[i]);
        if(String_GetChar(& Tmp, 0) == '-')
        {
            if(String_EqualChars(& Tmp, "-balance"))
                ArrayType_Push(Process, ProcessList, P_Balance);
            else if(String_EqualChars(& Tmp, "-normalize"))
            {
                ArrayType_Push(Process, ProcessList, P_Normalize);
                NextNormalize = 1;
            }else if(String_EqualChars(& Tmp, "-lpf"))
            {
                ArrayType_Push(Process, ProcessList, P_LPF);
                NextLPF = 1;
            }else if(String_EqualChars(& Tmp, "-hpf"))
            {
                ArrayType_Push(Process, ProcessList, P_HPF);
                NextHPF = 1;
            }else if(String_EqualChars(& Tmp, "-f0"))
            {
                NextF0 = 1;
            }else
            {
                printf("Error: Invalid parameter.\n");
                return 1;
            }
        }else
        {
            if(NextNormalize)
            {
                Normalize_Magnitude = CFloatStr(& Tmp);
                NextNormalize = 0;
            }else if(NextLPF)
            {
                LPF_Frequency = CFloatStr(& Tmp);
                NextLPF = 0;
            }else if(NextHPF)
            {
                HPF_Frequency = CFloatStr(& Tmp);
                NextHPF = 0;
            }else if(NextF0)
            {
                F0 = CFloatStr(& Tmp);
                NextF0 = 0;
                if(! GotF0)
                    GotF0 = 1;
                else
                {
                    printf("Error: Multiple f0 specified.\n");
                    return 1;
                }
            }else if(! GotWave)
            {
                String_Copy(& WavePath, & Tmp);
                GotWave = 1;
            }else
            {
                printf("Error: Multiple waves.\n");
                return 1;
            }
        }
    }
    String_Dtor(& Tmp);

    int WaveSize = GetFileLength(& WavePath) / 2;
    float* Wave = (float*)malloc(sizeof(float) * WaveSize);
    if(! (WaveSize = LoadWaveAll(Wave, & WavePath)))
    {
        printf("Error: cannot open wave.\n");
        return 0;
    }
    printf("Wave loaded, length: %.2fs.\n", (float)WaveSize / 44100);

    for(i = 0; i <= ProcessList_Index; i ++)
    {
        if(ProcessList[i] == P_Balance)
        {
            Balance(Wave, WaveSize);
        }else if(ProcessList[i] == P_Normalize)
        {
            Normalize(Wave, WaveSize, Normalize_Magnitude * 2);
        }else if(ProcessList[i] == P_LPF)
        {
            LPF(Wave, WaveSize, LPF_Frequency);
        }else if(ProcessList[i] == P_HPF)
        {
            HPF(Wave, WaveSize, HPF_Frequency);
        }
    }

    if(! WriteWaveAll(& WavePath, Wave, WaveSize, 44100))
    {
        printf("Error: Cannot write wave.\n");
        return 1;
    }
    printf("Saved.\n");

    free(Wave);
    ArrayType_Dtor(Process, ProcessList);
    String_Dtor(& WavePath);
    printf("Wpp finished.\n");
    return 0;
}

