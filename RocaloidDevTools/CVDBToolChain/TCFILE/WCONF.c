#include "WCONF.h"
#include "../../../RUtil/IO/FileUtil.h"
#include "../../../RocaloidEngine/RFILE3/RDL.h"
#include <malloc.h>

_Constructor_ (WCONF)
{
    ArrayType_Init(SampleList_Type, Dest -> SampleList);
}

_Destructor_ (WCONF)
{
    ArrayType_ObjDtor(SampleList_Type, Dest -> SampleList);
    ArrayType_Dtor(SampleList_Type, Dest -> SampleList);
}

_Constructor_ (SampleList_Type)
{
    String_Ctor(& Dest -> Vowel);
    String_Ctor(& Dest -> Consonant);
}

_Destructor_ (SampleList_Type)
{
    String_Dtor(& Dest -> Vowel);
    String_Dtor(& Dest -> Consonant);
}

char* Temp;
int WCONFLen;
StringStream* Reader;

int WCONFReader_Open(String* Src)
{
    WCONFLen = GetFileLength(Src);
    if(WCONFLen == 0)
        return 0;
    Temp = (char*)malloc(WCONFLen + 10);
    LoadFileAll(Temp, Src);

    Reader = (StringStream*)malloc(sizeof(StringStream));
    StringStream_Init(Reader, Temp);
    return 1;
}

void WCONFReader_Close()
{
    free(Temp);
    free(Reader);
}

int TemplateReadFunc(SampleList_Type)
{
    TemplateReadFuncHead

    RDL_ReadIgnoreComment(& Dest -> Consonant, Reader);
    RDL_ReadIgnoreComment(& Dest -> Vowel, Reader);

    RNext();    Dest -> Num = CIntStr(& Buffer);
    RNext();    Dest -> F0  = CFloatStr(& Buffer);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(WCONF)
{
    TemplateReadFuncHead

    RNext();
    IfBufferIsNot("#WCONF")
        return 0;
    RNext();
    IfBufferIsNot("0.1")
        return 0;

    RNext();
    IfBufferIsNot("WCONF")
        return 0;

    TemplateReadFuncLoop

    IfBufferIs("AverageMagnitude")
    {
        RNext();
        Dest -> AverageMagnitude = CFloatStr(& Buffer);
    }

    IfBufferIs("SampleList")
    {
        TemplateReadFuncDynamicList(SampleList_Type, Dest -> SampleList);
    }

    TemplateReadFuncEnd
}

StringStream SWriter;

void WCONFWriter_Save()
{
    SWriter.BasePtr = (char*)malloc(5000);
    SWriter.Offset = 0;
    RDL_SetWriteStringStream(& SWriter);
    RDL_SetWriteInitialSize(5000);
}

void WCONFWriter_Write(String* Dest)
{
    RDL_WriteNewLine();
    WriteFileAll(Dest, SWriter.BasePtr, SWriter.Offset);
    free(SWriter.BasePtr);
}

#define WriteFloat(_Name) CStrFloatF(& Buffer, Src -> _Name, "%.3f"); RDL_WriteString(& Buffer)

int TemplateWriteFunc(SampleList_Type)
{
    String Buffer;
    String_Ctor(& Buffer);
    RDL_WriteChars(">");

    RDL_WriteString(& Src -> Consonant);
    RDL_WriteString(& Src -> Vowel);

    CStrInt(& Buffer, Src -> Num);
    RDL_WriteString(& Buffer);

    WriteFloat(F0);

    RDL_WriteNewLine();
    String_Dtor(& Buffer);
    return 1;
}

int TemplateWriteFunc(WCONF)
{
    RDL_WriteChars("#WCONF 0.1");
    RDL_WriteNewLine();
    TemplateWriteFuncHead("WCONF");

    RDL_WriteChars("AverageMagnitude");

    CStrFloat(& Buffer, Src -> AverageMagnitude);
    RDL_WriteString(& Buffer);
    RDL_WriteNewLine();

    RDL_WriteChars("\t#\tC\tV\tNum\tF0\t#");
    RDL_WriteNewLine();
    TemplateWriteFuncList(SampleList_Type, SampleList, "SampleList", 1);
    RDL_WriteNewLine();

    TemplateWriteFuncEnd
}
