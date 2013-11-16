#include "CDS.h"
#include "../../../RUtil/IO/FileUtil.h"
#include "../../../RocaloidEngine/RFILE3/RDL.h"
#include <malloc.h>

_Constructor_ (SrcVList_Type)
{
    String_Ctor(& Dest -> Vowel);
}

_Destructor_ (SrcVList_Type)
{
    String_Dtor(& Dest -> Vowel);
}

_Constructor_ (DestVList_Type)
{
    String_Ctor(& Dest -> Vowel);
    String_Ctor(& Dest -> Src);
}

_Destructor_ (DestVList_Type)
{
    String_Dtor(& Dest -> Vowel);
    String_Dtor(& Dest -> Src);
}

_Constructor_ (DestCList_Type)
{
    String_Ctor(& Dest -> Symbol);
    String_Ctor(& Dest -> Vowel);
}

_Destructor_ (DestCList_Type)
{
    String_Dtor(& Dest -> Symbol);
    String_Dtor(& Dest -> Vowel);
}

_Constructor_ (CDS)
{
    ArrayType_Init(SrcVList_Type, Dest -> SrcVList);
    ArrayType_Init(String, Dest -> SrcCList);
    ArrayType_Init(DestVList_Type, Dest -> DestVList);
    ArrayType_Init(DestCList_Type, Dest -> DestCList);
}

_Destructor_ (CDS)
{
    ArrayType_ObjDtor(SrcVList_Type, Dest -> SrcVList);
    ArrayType_ObjDtor(String, Dest -> SrcCList);
    ArrayType_ObjDtor(DestVList_Type, Dest -> DestVList);
    ArrayType_ObjDtor(DestCList_Type, Dest -> DestCList);

    ArrayType_Dtor(SrcVList_Type, Dest -> SrcVList);
    ArrayType_Dtor(String, Dest -> SrcCList);
    ArrayType_Dtor(DestVList_Type, Dest -> DestVList);
    ArrayType_Dtor(DestCList_Type, Dest -> DestCList);
}

char* Temp;
int CDSLen;
StringStream* Reader;

int CDSReader_Open(String* Src)
{
    CDSLen = GetFileLength(Src);
    if(CDSLen == 0)
        return 0;
    Temp = (char*)malloc(CDSLen + 10);
    LoadFileAll(Temp, Src);

    Reader = (StringStream*)malloc(sizeof(StringStream));
    StringStream_Init(Reader, Temp);
    return 1;
}

void CDSReader_Close()
{
    free(Temp);
    free(Reader);
}

int TemplateReadFunc(SrcVList_Type)
{
    TemplateReadFuncHead

    RDL_ReadIgnoreComment(& Dest -> Vowel, Reader);

    RNext();    Dest -> F1 = CFloatStr(& Buffer);
    RNext();    Dest -> F2 = CFloatStr(& Buffer);
    RNext();    Dest -> F3 = CFloatStr(& Buffer);
    RNext();    Dest -> S1 = CFloatStr(& Buffer);
    RNext();    Dest -> S2 = CFloatStr(& Buffer);
    RNext();    Dest -> S3 = CFloatStr(& Buffer);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(DestVList_Type)
{
    TemplateReadFuncHead

    RDL_ReadIgnoreComment(& Dest -> Vowel, Reader);
    RDL_ReadIgnoreComment(& Dest -> Src, Reader);

    RNext();    Dest -> F1 = CFloatStr(& Buffer);
    RNext();    Dest -> F2 = CFloatStr(& Buffer);
    RNext();    Dest -> F3 = CFloatStr(& Buffer);
    RNext();    Dest -> S1 = CFloatStr(& Buffer);
    RNext();    Dest -> S2 = CFloatStr(& Buffer);
    RNext();    Dest -> S3 = CFloatStr(& Buffer);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(DestCList_Type)
{
    TemplateReadFuncHead

    RDL_ReadIgnoreComment(& Dest -> Symbol, Reader);
    RDL_ReadIgnoreComment(& Dest -> Vowel, Reader);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(CDS)
{
    TemplateReadFuncHead

    RNext();
    IfBufferIsNot("#CDS")
        return 0;
    RNext();
    IfBufferIsNot("0.11")
        return 0;

    RNext();
    IfBufferIsNot("CDS")
        return 0;

    TemplateReadFuncLoop

    IfBufferIs("PitchStep")
    {
        RNext();
        Dest -> PitchStep = CIntStr(& Buffer);
    }

    IfBufferIs("DiphoneLen")
    {
        RNext();
        Dest -> DiphoneLen = CFloatStr(& Buffer);
    }

    IfBufferIs("VowelLen")
    {
        RNext();
        Dest -> VowelLen = CFloatStr(& Buffer);
    }

    IfBufferIs("SrcVList")
    {
        TemplateReadFuncDynamicList(SrcVList_Type, Dest -> SrcVList);
    }

    IfBufferIs("SrcCList")
    {
        TemplateReadFuncEmbededDynamicList(String, Dest -> SrcCList);
    }

    IfBufferIs("DestVList")
    {
        TemplateReadFuncDynamicList(DestVList_Type, Dest -> DestVList);
    }

    IfBufferIs("DestCList")
    {
        TemplateReadFuncDynamicList(DestCList_Type, Dest -> DestCList);
    }

    TemplateReadFuncEnd
}
