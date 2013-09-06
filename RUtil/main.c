#include <stdio.h>
#include <time.h>
#include "Structure/Array.h"
#include "Structure/String.h"
#include "Misc/Converter.h"
#include "IO/FileStream.h"
#include "IO/FileUtil.h"
#include "IO/StringStream.h"
#include "IO/Wave.h"

int main(void)
{
    int t1, t2;
    String test;
    String_Ctor(&test);
    t1 = clock();

    PCMWaveFile wave;
    PCMWaveFile_Ctor(&wave);
    String_SetChars(&test, "/tmp/sounds.wav");
    int ret;
    ret = PCMWaveFile_Open(&wave, &test);
    printf("Open Status: %d\n", ret);

    float* Data1 = malloc(4 * 44100 * 10);
    float* Data2 = malloc(4 * 44100 * 10);
    ret = PCMWaveFile_FetchAllFloatStereo(Data1, Data2, &wave);
    printf("Size: %d\n", ret);

    String_SetChars(&test, "/tmp/sound2.wav");

    WriteWaveAll(&test, Data1, 10000, 48000);

    PCMWaveFile_Dtor(&wave);
    free(Data1);
    free(Data2);

    t2 = clock();
    printf("Time: %d\n", t2 - t1);
    String_Dtor(&test);
    return 0;
}

