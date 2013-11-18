#include "CVSRDLWriter.h"
#include "../../../RUtil/IO/FileUtil.h"
#include "../RDL.h"
#include <malloc.h>

#define TemplateSimpleStructWriteDef(A, B)\
    int TemplateWriteFunc(A##B##Pair)\
    {\
        String Buffer;\
        String_Ctor(& Buffer);\
        RDL_WriteNewLine();\
        RDL_WriteChars(">");\
        CStrFloat(& Buffer, Src -> A);\
        RDL_WriteString(& Buffer);\
        CStrFloat(& Buffer, Src -> B);\
        RDL_WriteString(& Buffer);\
        String_Dtor(& Buffer);\
        return 1;\
    }

StringStream CWriter;

void CVSRDLWriter_Save()
{
    CWriter.BasePtr = (char*)malloc(5000);
    CWriter.Offset = 0;
    RDL_SetWriteStringStream(& CWriter);
    RDL_SetWriteInitialSize(5000);
}

void CVSRDLWriter_Write(String* Dest)
{
    RDL_WriteNewLine();
    WriteFileAll(Dest, CWriter.BasePtr, CWriter.Offset);
    free(CWriter.BasePtr);
}

TemplateSimpleStructWriteDef(Time, Ratio);
TemplateSimpleStructWriteDef(Time, Freq);
TemplateSimpleStructWriteDef(Time, Strength);
TemplateSimpleStructWriteDef(Time, Volume);

int TemplateWriteFunc(FormantInfo)
{
    TemplateWriteFuncHead("FormantDeviation");

    TemplateWriteFuncList(TimeFreqPair, F1List, "F1List", 0); RDL_WriteNewLine();
    TemplateWriteFuncList(TimeFreqPair, F2List, "F2List", 0); RDL_WriteNewLine();
    TemplateWriteFuncList(TimeFreqPair, F3List, "F3List", 0); RDL_WriteNewLine();

    TemplateWriteFuncList(TimeStrengthPair, S1List, "S1List", 0); RDL_WriteNewLine();
    TemplateWriteFuncList(TimeStrengthPair, S2List, "S2List", 0); RDL_WriteNewLine();
    TemplateWriteFuncList(TimeStrengthPair, S3List, "S3List", 0);

    TemplateWriteFuncEnd
}

int TemplateWriteFunc(EffectInfo)
{
    TemplateWriteFuncHead("Effects");

    TemplateWriteFuncList(TimeVolumePair, EnvelopeList, "EnvelopeList", 0);
    RDL_WriteNewLine();

    TemplateWriteFuncEnd
}

int TemplateWriteFunc(Syllable)
{
    TemplateWriteFuncHead("Syllable");

    RDL_WriteChars("TransQ");
    CStrInt(& Buffer, Src -> TransitionQ + 1);
    RDL_WriteString(& Buffer);
    RDL_WriteNewLine();

    RDL_WriteChars("TransPhoneList");
    TemplateWriteFuncEmbededStaticList(String, TransitionPhoneList);
    RDL_WriteNewLine();

    RDL_WriteChars("TransTickList");
    TemplateWriteFuncEmbededStaticList(float, TransitionTickList);
    RDL_WriteNewLine();

    TemplateWriteFuncList(TimeRatioPair, TransitionRatioList, "TransRatioList", 0);
    RDL_WriteNewLine();

    RDL_WriteChars("TransEndRatio");
    CStrFloat(& Buffer, Src -> TransitionEndingRatio);
    RDL_WriteString(& Buffer);
    RDL_WriteNewLine();

    RDL_WriteChars("ConsonantRatio");
    CStrFloat(& Buffer, Src -> ConsonantRatio);
    RDL_WriteString(& Buffer);
    RDL_WriteNewLine();

    FormantInfo_Write(& Src -> FormantDeviation);

    TemplateWriteFuncList(TimeFreqPair, FreqList, "FreqList", 0);
    RDL_WriteNewLine();

    EffectInfo_Write(& Src -> Effects);

    RDL_WriteChars("StartTime");
    CStrFloat(& Buffer, Src -> StartTime);
    RDL_WriteString(& Buffer);

    TemplateWriteFuncEnd
}

int TemplateWriteFunc(CVS3)
{
    RDL_WriteChars("#CVS 3.0");
    RDL_WriteNewLine();
    TemplateWriteFuncHead("CVS");

    TemplateWriteFuncList(Syllable, SyllableList, "SyllableList", 1);
    RDL_WriteNewLine();

    TemplateWriteFuncEnd
}
