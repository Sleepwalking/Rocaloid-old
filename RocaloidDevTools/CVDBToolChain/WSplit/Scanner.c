#include "Scanner.h"
#include "../../../CVEDSP/IntrinUtil/FloatArray.h"
#include "../../../CVEDSP/Algorithm/BaseFreq.h"
#include "../../../CVEDSP/DSPBase/Spectrum.h"
#include "../../../CVEDSP/DSPBase/Filter.h"
#include "../../../RUtil/IO/FileUtil.h"
#include <malloc.h>

float Spec[256];
int Scan(SCONF* Dest, String* Raw)
{
    int WaveSize = GetFileLength(Raw) / 2;
    float* Wave = (float*)malloc(sizeof(float) * WaveSize);
    if(! (WaveSize = LoadWaveAll(Wave, Raw)))
    {
        printf("Error: cannot open raw data.\n");
        return 0;
    }
    printf("Raw data loaded, length: %.2fs.\n", (float)WaveSize / 44100);

    int Position = 512;
    int Step = 1024;
    int Count = 0;

    int Onset = 0;
    int Keep = 0;
    int OffsetTime = 0;
    SetSampleRate(44100);
    printf("Scanning...\n");
    while(Count <= Dest -> TickList_Index && Position + Step < WaveSize)
    {
        MagnitudeFromWave(Spec, Wave + Position, 8);
        int State = Boost_FloatSum(Spec + 3, 50) > 1.5;
        printf("%d", State);
        if(! Onset)
        {
            Keep += State;
            if(State == 0)
                Keep = 0;
            if(Keep > 3)
            {
                Onset = 1;
                Keep = 0;
                if(Count == 0)
                {
                    Dest -> TickList[Count ++].Time = (float)Position / 44100;
                }else
                {
                    printf(".");
                    Dest -> TickList[Count ++].Time = (float)(Position + OffsetTime) / 44100 / 2;
                }
            }
        }else
        {
            Keep += 1 - State;
            if(State == 1)
                Keep = 0;
            if(Keep > 3)
            {
                Onset = 0;
                Keep = 0;
                OffsetTime = Position;
                if(Count == Dest -> TickList_Index)
                {
                    printf(".");
                    Dest -> TickList[Count ++].Time = (float)(Position + OffsetTime) / 44100 / 2;
                }
            }
        }
        Position += Step;
    }

    printf("\nScan finished.\n");

    free(Wave);
    return 1;
}
