#include "Updater.h"
#include "Spliter.h"
#include "../../../CVEDSP/DSPBase/Filter.h"
#include "../../../RUtil/IO/FileUtil.h"
#include "../../../RUtil/Misc/Converter.h"

int Update(WCONF* Dest, String* FragDir)
{
    int i;
    SetSampleRate(44100);
    float* Wave = (float*)malloc(sizeof(float) * SampleRate * 20);
    String Path, Tmp;
    String_Ctor(& Path);
    String_Ctor(& Tmp);
    for(i = 0; i <= Dest -> SampleList_Index; i ++)
    {
        String_Copy(& Path, FragDir);
        String_JoinChars(& Path, "/");
        if(! String_EqualChars(& Dest -> SampleList[i].Consonant, "/"))
            String_Join(& Path, & Dest -> SampleList[i].Consonant);
        String_Join(& Path, & Dest -> SampleList[i].Vowel);
        CStrInt(& Tmp, Dest -> SampleList[i].Num);
        String_Join(& Path, & Tmp);
        String_JoinChars(& Path, ".wsp");
        int Length = LoadWaveAll(Wave, & Path);
        Dest -> SampleList[i].F0 = BaseFreqDetect(Wave, Length, 80);
        printf("%s: %fHz.\n", String_GetChars(& Path), Dest -> SampleList[i].F0);
    }
    String_Dtor(& Path);
    String_Dtor(& Tmp);
    free(Wave);
    return 1;
}
