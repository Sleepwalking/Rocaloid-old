#include "CVSRDLReader.h"
#include "../../../RUtil/IO/FileUtil.h"
#include "../RDL.h"
#include <malloc.h>

#define TemplateSimpleStructDef(A, B)\
    int TemplateReadFunc(A##B##Pair)\
    {\
        TemplateReadFuncHead\
        RNext();\
        Dest -> A = CFloatStr(& Buffer);\
        RNext();\
        Dest -> B = CFloatStr(& Buffer);\
        TemplateReadFuncNonLoopEnd;\
    } 

char* Temp;
int CVSLen;
StringStream* Reader;

int CVSRDLReader_Open(String* Src)
{
    CVSLen = GetFileLength(Src);
    if(CVSLen == 0)
        return 0;
    Temp = (char*)malloc(CVSLen + 10);
    LoadFileAll(Temp, Src);

    Reader = (StringStream*)malloc(sizeof(StringStream));
    StringStream_Init(Reader, Temp);
    return 1;
}

void CVSRDLReader_Close()
{
    free(Temp);
    free(Reader);
}

TemplateSimpleStructDef(Time, Ratio);
TemplateSimpleStructDef(Time, Freq);
TemplateSimpleStructDef(Time, Strength);
TemplateSimpleStructDef(Time, Volume);

int TemplateReadFunc(FormantInfo)
{
    TemplateReadFuncHead
    TemplateReadFuncLoop

    IfBufferIs("F1List")
    {
        TemplateReadFuncDynamicList(TimeFreqPair, Dest -> F1List);
    }

    IfBufferIs("F2List")
    {
        TemplateReadFuncDynamicList(TimeFreqPair, Dest -> F2List);
    }

    IfBufferIs("F3List")
    {
        TemplateReadFuncDynamicList(TimeFreqPair, Dest -> F3List);
    }

    IfBufferIs("S1List")
    {
        TemplateReadFuncDynamicList(TimeStrengthPair, Dest -> S1List);
    }

    IfBufferIs("S2List")
    {
        TemplateReadFuncDynamicList(TimeStrengthPair, Dest -> S2List);
    }

    IfBufferIs("S3List")
    {
        TemplateReadFuncDynamicList(TimeStrengthPair, Dest -> S3List);
    }

    TemplateReadFuncEnd
}

int TemplateReadFunc(EffectInfo)
{
    TemplateReadFuncHead
    TemplateReadFuncLoop

    IfBufferIs("EnvelopeList")
    {
        TemplateReadFuncDynamicList(TimeVolumePair, Dest -> EnvelopeList);
    }

    TemplateReadFuncEnd
}

int TemplateReadFunc(Syllable)
{
    TemplateReadFuncHead
    TemplateReadFuncLoop

    IfBufferIs("TransQ")
    {
        RNext();
        Dest -> TransitionQ = CIntStr(& Buffer) - 1;
    }

    IfBufferIs("TransPhoneList")
    {
        TemplateReadFuncEmbededStaticList(String, Dest -> TransitionPhoneList, Dest -> TransitionQ);
    }

    IfBufferIs("TransTickList")
    {
        TemplateReadFuncEmbededStaticList(float, Dest -> TransitionTickList, Dest -> TransitionQ);
    }

    IfBufferIs("TransRatioList")
    {
        TemplateReadFuncDynamicList(TimeRatioPair, Dest -> TransitionRatioList);
    }

    IfBufferIs("TransEndRatio")
    {
        RNext();
        Dest -> TransitionEndingRatio = CFloatStr(& Buffer);
    }

    IfBufferIs("ConsonantRatio")
    {
        RNext();
        Dest -> ConsonantRatio = CFloatStr(& Buffer);
    }

    IfBufferIs("FormantDeviation")
    {
        FormantInfo_Read(& Dest -> FormantDeviation);
    }

    IfBufferIs("Effects")
    {
        EffectInfo_Read(& Dest -> Effects);
    }

    IfBufferIs("FreqList")
    {
        TemplateReadFuncDynamicList(TimeFreqPair, Dest -> FreqList);
    }

    IfBufferIs("StartTime")
    {
        RNext();
        Dest -> StartTime = CFloatStr(& Buffer);
    }

    TemplateReadFuncEnd
}

int TemplateReadFunc(CVS3)
{
    TemplateReadFuncHead

    RNext();
    IfBufferIsNot("#CVS")
        return 0;
    RNext();
    IfBufferIsNot("3.0")
        return 0;

    RNext();
    IfBufferIsNot("CVS")
        return 0;

    TemplateReadFuncLoop

    IfBufferIs("SyllableList")
    {
        TemplateReadFuncStructuredDynamicList(Syllable, Dest -> SyllableList, "Syllable");
    }

    TemplateReadFuncEnd
}
