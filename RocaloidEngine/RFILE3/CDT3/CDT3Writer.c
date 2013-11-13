#include "CDT3Writer.h"
#include "../RUtil/IO/FileUtil.h"
#include "../RDL.h"
#include <malloc.h>

StringStream CWriter;

void CDTWriter_Save()
{
    CWriter.BasePtr = (char*)malloc(5000);
    CWriter.Offset = 0;
    RDL_SetWriteStringStream(& CWriter);
    RDL_SetWriteInitialSize(5000);
}

void CDTWriter_Write(String* Dest)
{
    RDL_WriteNewLine();
    WriteFileAll(Dest, CWriter.BasePtr, CWriter.Offset);
    free(CWriter.BasePtr);
}

#define SylTypeCase(T) case T: String_SetChars(& Buffer, #T); break
int TemplateWriteFunc(SGtorSyllable)
{
    String Buffer;
    String_Ctor(& Buffer);
    RDL_WriteChars(">");

    RDL_WriteString(& Src -> Syllable);

    switch(Src -> Type)
    {
        SylTypeCase(V);
        SylTypeCase(VV);
        SylTypeCase(VVV);
        SylTypeCase(CV);
        SylTypeCase(CVV);
        SylTypeCase(CAV);
        SylTypeCase(CAVV);
        default: break;
    }
    RDL_WriteString(& Buffer);

    CStrInt(& Buffer, Src -> EndingRatio);
    RDL_WriteString(& Buffer);

    CStrBool(& Buffer, Src -> Extended);
    RDL_WriteString(& Buffer);

    TemplateWriteFuncEmbededStaticList(String, PhoneList);
    RDL_WriteChars("End");

    RDL_WriteNewLine();
    String_Dtor(& Buffer);
    return 1;
}

int TemplateWriteFunc(DBLayerEntry)
{
    String Buffer;
    String_Ctor(& Buffer);
    RDL_WriteChars(">");

    RDL_WriteString(& Src -> Name);
    RDL_WriteString(& Src -> FileAddr);

    RDL_WriteNewLine();
    String_Dtor(& Buffer);
    return 1;
}
#define WriteFloat(_Name) CStrFloatF(& Buffer, Src -> _Name, "%.2f"); RDL_WriteString(& Buffer)
#define WriteInt(_Name) CStrInt(& Buffer, Src -> _Name); RDL_WriteString(& Buffer)

int TemplateWriteFunc(SymbolLayerEntry)
{
    String Buffer;
    String_Ctor(& Buffer);
    RDL_WriteChars(">");

    RDL_WriteString(& Src -> Name);

    String_SetCharsN(& Buffer, & Src -> Type, 1);
    RDL_WriteString(& Buffer);

    CStrInt(& Buffer, Src -> VOI); RDL_WriteString(& Buffer);

    WriteFloat(VOT);
    WriteFloat(F0);

    WriteInt(F1);
    WriteInt(F2);
    WriteInt(F3);
    WriteFloat(S1);
    WriteFloat(S2);
    WriteFloat(S3);

    RDL_WriteNewLine();
    String_Dtor(& Buffer);
    return 1;
}

int TemplateWriteFunc(FreqLayerEntry)
{
    String Buffer;
    String_Ctor(& Buffer);
    RDL_WriteChars(">");

    RDL_WriteString(& Src -> FPhone);
    WriteFloat(F0);
    RDL_WriteString(& Src -> Name);

    RDL_WriteNewLine();
    String_Dtor(& Buffer);
    return 1;
}

int TemplateWriteFunc(FormantLayerEntry)
{
    String Buffer;
    String_Ctor(& Buffer);
    RDL_WriteChars(">");

    RDL_WriteString(& Src -> Phone);
    WriteFloat(F0);

    RDL_WriteString(& Src -> FPhone);

    WriteInt(F1);
    WriteInt(F2);
    WriteInt(F3);
    WriteFloat(S1);
    WriteFloat(S2);
    WriteFloat(S3);

    RDL_WriteNewLine();
    String_Dtor(& Buffer);
    return 1;
}

int TemplateWriteFunc(TransitionLayerEntry)
{
    String Buffer;
    String_Ctor(& Buffer);
    RDL_WriteChars(">");

    RDL_WriteString(& Src -> Phone1);
    RDL_WriteString(& Src -> Phone2);
    WriteFloat(Ratio);

    RDL_WriteNewLine();
    String_Dtor(& Buffer);
    return 1;
}

#define TemplateWriteFuncLayerDef(_L) \
    TemplateWriteFuncList(_L##LayerEntry, _L##LayerMap, # _L "LayerMap", 1);\
    RDL_WriteNewLine()

int TemplateWriteFunc(CDTMap)
{
    TemplateWriteFuncHead("CDTMapping");

    RDL_WriteChars("\t#\tName\tFile Address\t#");
    RDL_WriteNewLine();
    TemplateWriteFuncLayerDef(DB);

    RDL_WriteChars("\t#\tName\tType\tVOI\tVOT\tF0\tF1\tF2\tF3\tS1\tS2\tS3\t#");
    RDL_WriteNewLine();
    TemplateWriteFuncLayerDef(Symbol);

    RDL_WriteChars("\t#\tFPhone\tF0\tName\t#");
    RDL_WriteNewLine();
    TemplateWriteFuncLayerDef(Freq);

    RDL_WriteChars("\t#\tPhone\tF0\tFPhone\tF1\tF2\tF3\tS1\tS2\tS3\t#");
    RDL_WriteNewLine();
    TemplateWriteFuncLayerDef(Formant);

    RDL_WriteChars("\t#\tPhone1\tPhone2\tRatio\t#");
    RDL_WriteNewLine();
    TemplateWriteFuncLayerDef(Transition);

    TemplateWriteFuncEnd
}

int TemplateWriteFunc(CDT3)
{
    RDL_WriteChars("#CDT 3.0");
    RDL_WriteNewLine();
    TemplateWriteFuncHead("CDT");

    RDL_WriteChars("Version");
    CStrFloat(& Buffer, Src -> Version);
    RDL_WriteString(& Buffer);
    RDL_WriteNewLine();

    RDL_WriteChars("\t#\tSyl\tType\tETR\tExt\tPList\t#");
    RDL_WriteNewLine();
    TemplateWriteFuncList(SGtorSyllable, SGtorList, "SGtorList", 1);
    RDL_WriteNewLine();

    CDTMap_Write(& Src -> CDTMapping);

    RDL_WriteChars("PhoneticInfo");
    RDL_WriteNewLine();
    RDL_WriteChars("End");
    RDL_WriteNewLine();

    TemplateWriteFuncEnd
}
