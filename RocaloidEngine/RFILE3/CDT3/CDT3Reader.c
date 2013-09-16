#include "CDT3Reader.h"
#include "RUtil/Structure/Array.h"
#include "RUtil/IO/FileUtil.h"
#include "RUtil/IO/StringStream.h"
#include "RUtil/Misc/Converter.h"
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

    ReadIgnoreRDLComment(& Dest -> Syllable, CReader);

    RNext();
    Dest -> Type = CSyllableTypeStr(& Buffer);

    RNext();
    Dest -> EndingRatio = CFloatStr(& Buffer);

    RNext();
    Dest -> Extended = CVBBoolStr(& Buffer);

    TemplateReadFuncEmbededDynamicList(String, PhoneList);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(DBLayerEntry)
{
    ReadIgnoreRDLComment(& Dest -> Name, CReader);
    ReadIgnoreRDLComment(& Dest -> FileAddr, CReader);
    return 1;
}

int TemplateReadFunc(SymbolLayerEntry)
{
    TemplateReadFuncHead

    ReadIgnoreRDLComment(& Dest -> Name, CReader);

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

    ReadIgnoreRDLComment(& Dest -> FPhone, CReader);

    RNext();
    Dest -> F0 = CFloatStr(& Buffer);

    ReadIgnoreRDLComment(& Dest -> Name, CReader);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(FormantLayerEntry)
{
    TemplateReadFuncHead

    ReadIgnoreRDLComment(& Dest -> Phone, CReader);

    RNext();    Dest -> F0 = CFloatStr(& Buffer);

    ReadIgnoreRDLComment(& Dest -> FPhone, CReader);

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

    ReadIgnoreRDLComment(& Dest -> Phone1, CReader);
    ReadIgnoreRDLComment(& Dest -> Phone2, CReader);

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
        TemplateReadFuncDynamicList(DBLayerEntry, DBLayerMap);
    }

    IfBufferIs("SymbolLayerMap")
    {
        TemplateReadFuncDynamicList(SymbolLayerEntry, SymbolLayerMap);
    }

    IfBufferIs("FreqLayerMap")
    {
        TemplateReadFuncDynamicList(FreqLayerEntry, FreqLayerMap);
    }

    IfBufferIs("FormantLayerMap")
    {
        TemplateReadFuncDynamicList(FormantLayerEntry, FormantLayerMap);
    }

    IfBufferIs("TransitionLayerMap")
    {
        TemplateReadFuncDynamicList(TransitionLayerEntry, TransitionLayerMap);
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
        TemplateReadFuncDynamicList(SGtorSyllable, SGtorList);
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
