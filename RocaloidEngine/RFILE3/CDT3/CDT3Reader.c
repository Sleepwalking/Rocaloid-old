#include "CDT3Reader.h"
#include "RUtil/IO/FileUtil.h"
#include "RDL.h"
#include <malloc.h>

char* Temp;
int CDTLen;
StringStream* CReader;

int CDTReader_Open(String* Src)
{
    CDTLen = GetFileLength(Src);
    if(CDTLen == 0)
        return 0;
    Temp = (char*)malloc(CDTLen + 10);
    LoadFileAll(Temp, Src);

    CReader = (StringStream*)malloc(sizeof(StringStream));
    StringStream_Init(CReader, Temp);
    return 1;
}

void CDTReader_Close()
{
    free(Temp);
    free(CReader);
}

int TemplateReadFunc(SGtorSyllable)
{
    TemplateReadFuncHead

    RDL_ReadIgnoreComment(& Dest -> Syllable, CReader);

    RNext();
    Dest -> Type = CSyllableTypeStr(& Buffer);

    RNext();
    Dest -> EndingRatio = CFloatStr(& Buffer);

    RNext();
    Dest -> Extended = CVBBoolStr(& Buffer);

    TemplateReadFuncEmbededDynamicList(String, Dest -> PhoneList);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(DBLayerEntry)
{
    RDL_ReadIgnoreComment(& Dest -> Name, CReader);
    RDL_ReadIgnoreComment(& Dest -> FileAddr, CReader);
    return 1;
}

int TemplateReadFunc(SymbolLayerEntry)
{
    TemplateReadFuncHead

    RDL_ReadIgnoreComment(& Dest -> Name, CReader);

    RNext();
    Dest -> Type = CCharStr(& Buffer);

    RNext();
    Dest -> VOI = CIntStr(& Buffer);

    RNext();
    Dest -> VOT = CFloatStr(& Buffer);

    RNext();    Dest -> F0 = CFloatStr(& Buffer);

    RNext();    Dest -> F1 = CFloatStr(& Buffer);
    RNext();    Dest -> F2 = CFloatStr(& Buffer);
    RNext();    Dest -> F3 = CFloatStr(& Buffer);
    RNext();    Dest -> S1 = CFloatStr(& Buffer);
    RNext();    Dest -> S2 = CFloatStr(& Buffer);
    RNext();    Dest -> S3 = CFloatStr(& Buffer);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(FreqLayerEntry)
{
    TemplateReadFuncHead

    RDL_ReadIgnoreComment(& Dest -> FPhone, CReader);

    RNext();
    Dest -> F0 = CFloatStr(& Buffer);

    RDL_ReadIgnoreComment(& Dest -> Name, CReader);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(FormantLayerEntry)
{
    TemplateReadFuncHead

    RDL_ReadIgnoreComment(& Dest -> Phone, CReader);

    RNext();    Dest -> F0 = CFloatStr(& Buffer);

    RDL_ReadIgnoreComment(& Dest -> FPhone, CReader);

    RNext();    Dest -> F1 = CFloatStr(& Buffer);
    RNext();    Dest -> F2 = CFloatStr(& Buffer);
    RNext();    Dest -> F3 = CFloatStr(& Buffer);
    RNext();    Dest -> S1 = CFloatStr(& Buffer);
    RNext();    Dest -> S2 = CFloatStr(& Buffer);
    RNext();    Dest -> S3 = CFloatStr(& Buffer);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(TransitionLayerEntry)
{
    TemplateReadFuncHead

    RDL_ReadIgnoreComment(& Dest -> Phone1, CReader);
    RDL_ReadIgnoreComment(& Dest -> Phone2, CReader);

    RNext();
    Dest -> Ratio = CFloatStr(& Buffer);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(CDTMap)
{
    TemplateReadFuncHead
    TemplateReadFuncLoop

    IfBufferIs("DBLayerMap")
    {
        TemplateReadFuncDynamicList(DBLayerEntry, Dest -> DBLayerMap);
    }

    IfBufferIs("SymbolLayerMap")
    {
        TemplateReadFuncDynamicList(SymbolLayerEntry, Dest -> SymbolLayerMap);
    }

    IfBufferIs("FreqLayerMap")
    {
        TemplateReadFuncDynamicList(FreqLayerEntry, Dest -> FreqLayerMap);
    }

    IfBufferIs("FormantLayerMap")
    {
        TemplateReadFuncDynamicList(FormantLayerEntry, Dest -> FormantLayerMap);
    }

    IfBufferIs("TransitionLayerMap")
    {
        TemplateReadFuncDynamicList(TransitionLayerEntry, Dest -> TransitionLayerMap);
    }

    TemplateReadFuncEnd
}

int TemplateReadFunc(CDT3)
{
    TemplateReadFuncHead

    RNext();
    IfBufferIsNot("#CDT")
        return 0;
    RNext();
    IfBufferIsNot("3.0")
        return 0;

    RNext();
    IfBufferIsNot("CDT")
        return 0;

    TemplateReadFuncLoop

    IfBufferIs("Version")
    {
        RNext();
        Dest -> Version = CFloatStr(& Buffer);
    }

    IfBufferIs("SGtorList")
    {
        TemplateReadFuncDynamicList(SGtorSyllable, Dest -> SGtorList);
    }

    IfBufferIs("CDTMapping")
    {
        CDTMap_Read(& Dest -> CDTMapping);
    }

    IfBufferIs("PhoneticInfo")
    {
        //Not Implemented Yet.
    }

    TemplateReadFuncEnd
}
