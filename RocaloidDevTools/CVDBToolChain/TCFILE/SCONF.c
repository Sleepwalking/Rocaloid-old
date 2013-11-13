#include "SCONF.h"
#include "../../../RUtil/IO/FileUtil.h"
#include "../../../RocaloidEngine/RFILE3/RDL.h"
#include <malloc.h>

_Constructor_ (SCONF)
{
    ArrayType_Init(TickList_Type, Dest -> TickList);
}

_Destructor_ (SCONF)
{
    ArrayType_ObjDtor(TickList_Type, Dest -> TickList);
    ArrayType_Dtor(TickList_Type, Dest -> TickList);
}

_Constructor_ (TickList_Type)
{
    String_Ctor(& Dest -> Vowel);
    String_Ctor(& Dest -> Consonant);
}

_Destructor_ (TickList_Type)
{
    String_Dtor(& Dest -> Vowel);
    String_Dtor(& Dest -> Consonant);
}

char* Temp;
int SCONFLen;
StringStream* Reader;

int SCONFReader_Open(String* Src)
{
    SCONFLen = GetFileLength(Src);
    if(SCONFLen == 0)
        return 0;
    Temp = (char*)malloc(SCONFLen + 10);
    LoadFileAll(Temp, Src);

    Reader = (StringStream*)malloc(sizeof(StringStream));
    StringStream_Init(Reader, Temp);
    return 1;
}

void SCONFReader_Close()
{
    free(Temp);
    free(Reader);
}

int TemplateReadFunc(TickList_Type)
{
    TemplateReadFuncHead

    RNext();    Dest -> Time = CFloatStr(& Buffer);

    RDL_ReadIgnoreComment(& Dest -> Consonant, Reader);
    RDL_ReadIgnoreComment(& Dest -> Vowel, Reader);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(SCONF)
{
    TemplateReadFuncHead

    RNext();
    IfBufferIsNot("#SCONF")
        return 0;
    RNext();
    IfBufferIsNot("0.1")
        return 0;

    RNext();
    IfBufferIsNot("SCONF")
        return 0;

    TemplateReadFuncLoop

    IfBufferIs("TickList")
    {
        TemplateReadFuncDynamicList(TickList_Type, Dest -> TickList);
    }

    TemplateReadFuncEnd
}

StringStream SWriter;

void SCONFWriter_Save()
{
    SWriter.BasePtr = (char*)malloc(5000);
    SWriter.Offset = 0;
    RDL_SetWriteStringStream(& SWriter);
    RDL_SetWriteInitialSize(5000);
}

void SCONFWriter_Write(String* Dest)
{
    RDL_WriteNewLine();
    WriteFileAll(Dest, SWriter.BasePtr, SWriter.Offset);
    free(SWriter.BasePtr);
}

#define WriteFloat(_Name) CStrFloatF(& Buffer, Src -> _Name, "%.3f"); RDL_WriteString(& Buffer)

int TemplateWriteFunc(TickList_Type)
{
    String Buffer;
    String_Ctor(& Buffer);
    RDL_WriteChars(">");

    CStrInt(& Buffer, Src -> Time);
    RDL_WriteString(& Buffer);

    RDL_WriteString(& Src -> Consonant);
    RDL_WriteString(& Src -> Vowel);

    RDL_WriteNewLine();
    String_Dtor(& Buffer);
    return 1;
}

int TemplateWriteFunc(SCONF)
{
    RDL_WriteChars("#SCONF 0.1");
    RDL_WriteNewLine();
    TemplateWriteFuncHead("SCONF");

    RDL_WriteChars("\t#\tTime\tC\tV\t#");
    RDL_WriteNewLine();
    TemplateWriteFuncList(TickList_Type, TickList, "TickList", 1);
    RDL_WriteNewLine();

    TemplateWriteFuncEnd
}
