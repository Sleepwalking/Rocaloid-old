#include "SList.h"
#include "RUtil/IO/FileUtil.h"
#include "RUtil/IO/StringStream.h"
#include "RFILE3/RDL.h"

_Constructor_ (SClass)
{
    ArrayType_Init(String, Dest -> FileList);
    String_Ctor(& Dest -> Phone);
}

_Destructor_ (SClass)
{
    ArrayType_ObjDtor(String, Dest -> FileList);
    ArrayType_Dtor(String, Dest -> FileList);
    String_Dtor(& Dest -> Phone);
}

_Constructor_ (SList)
{
    ArrayType_Init(String, Dest -> PitchList);
    ArrayType_Init(SClass, Dest -> PhoneList);
}

_Destructor_ (SList)
{
    ArrayType_ObjDtor(String, Dest -> PitchList);
    ArrayType_ObjDtor(SClass, Dest -> PhoneList);
    ArrayType_Dtor(String, Dest -> PitchList);
    ArrayType_Dtor(SClass, Dest -> PhoneList);
}

char* Tmp;
StringStream* Reader;

int TemplateReadFunc(SClass)
{
    TemplateReadFuncHead

    RDL_ReadIgnoreComment(& Dest -> Phone, Reader);

    RNext();
    Dest -> F1 = CFloatStr(& Buffer);
    RNext();
    Dest -> F2 = CFloatStr(& Buffer);
    RNext();
    Dest -> F3 = CFloatStr(& Buffer);

    //printf("%f %f %f\n", Dest -> F1, Dest -> F2, Dest -> F3);

    TemplateReadFuncEmbededDynamicList(String, Dest -> FileList);

    TemplateReadFuncNonLoopEnd
}

int TemplateReadFunc(SList)
{
    TemplateReadFuncHead

    RNext();
    IfBufferIsNot("SList")
        return 0;

    TemplateReadFuncLoop

    IfBufferIs("Pitch")
    {
        TemplateReadFuncEmbededDynamicList(String, Dest -> PitchList);
    }

    IfBufferIs("ClassList")
    {
        TemplateReadFuncStructuredDynamicList(SClass, Dest -> PhoneList, "Class");
    }

    TemplateReadFuncEnd
}

int SList_Load(SList* Dest, String* Src)
{
    int Len = GetFileLength(Src);
    if(Len < 0)
        return 0;
    Tmp = (char*)malloc(Len);
    LoadFileAll(Tmp, Src);
    Reader = (StringStream*)malloc(sizeof(StringStream));
    StringStream_Init(Reader, Tmp);

    int ret = SList_Read(Dest);

    free(Reader);
    free(Tmp);
    return ret;
}
