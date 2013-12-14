#include "Routines.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>

#include "../TCFILE/CDS.h"
#include "../TCFILE/SCONF.h"
#include "../TCFILE/WCONF.h"
#include "../../../RUtil/IO/FileStream.h"
#include "../../../RUtil/IO/FileUtil.h"

String Dir;
String Dir_CVDB;
String Dir_BIN;
String Dir_FRAG;
String Dir_RAW;
String Dir_DEBUG;

int LoadWCONF(WCONF* Dest, String* Path)
{
    if(! WCONFReader_Open(Path))
    {
        printf("Error: Cannot open WCONF.\n");
        return 0;
    }
    if(! WCONF_Read(Dest))
    {
        printf("Error: Wrong WCONF Format.\n");
        return 0;
    }
    WCONFReader_Close();
    return 1;
}

int LoadCDS(CDS* Dest, String* Path)
{
    if(! CDSReader_Open(Path))
    {
        printf("Error: Cannot find Scheme.cds!\n");
        return 0;
    }
    if(! CDS_Read(Dest))
    {
        printf("Error: Wrong CDS format!\n");
        return 0;
    }
    CDSReader_Close();
    return 1;
}

#include "GenCDT.h"

int Config()
{
    mode_t mode = S_IRUSR | S_IWUSR | S_IEXEC;

    mkdir(String_GetChars(& Dir), mode);
    mkdir(String_GetChars(& Dir_BIN), mode);
    mkdir(String_GetChars(& Dir_CVDB), mode);
    mkdir(String_GetChars(& Dir_FRAG), mode);
    mkdir(String_GetChars(& Dir_RAW), mode);
    mkdir(String_GetChars(& Dir_DEBUG), mode);

    printf("DB directory constructed.\n");

    return 1;
}

int GenSCONF()
{
    if(chdir(String_GetChars(& Dir)))
        return 0;
    String_FromChars(Path, "./Scheme.cds");

    CDS Scheme;
    CDS_Ctor(& Scheme);
    if(! LoadCDS(& Scheme, & Path))
        return 0;

    printf("CDS loaded.\n");

    SCONF Split;
    SCONF_Ctor(& Split);
    int i, j, k;
    for(i = 0; i <= Scheme.SrcVList_Index; i ++)
    {
        for(j = 0; j < Scheme.PitchStep; j ++)
        {
            ArrayType_PushNull(TickList_Type, Split.TickList);
            TickList_Type_Ctor(Split.TickList + Split.TickList_Index);
            Split.TickList[Split.TickList_Index].Time = 0;
            String_SetChars(& Split.TickList[Split.TickList_Index].Consonant, "/");
            String_Copy(& Split.TickList[Split.TickList_Index].Vowel, & Scheme.SrcVList[i].Vowel);
        }
    }
    for(i = 0; i <= Scheme.SrcCList_Index; i ++)
    {
        for(j = 0; j <= Scheme.SrcVList_Index; j ++)
        {
            if(String_GetChar(& Scheme.SrcVList[j].Vowel, 0) != '_')
                for(k = 0; k < Scheme.PitchStep; k ++)
                {
                    ArrayType_PushNull(TickList_Type, Split.TickList);
                    TickList_Type_Ctor(Split.TickList + Split.TickList_Index);
                    Split.TickList[Split.TickList_Index].Time = 0;
                    String_Copy(& Split.TickList[Split.TickList_Index].Consonant, Scheme.SrcCList + i);
                    String_Copy(& Split.TickList[Split.TickList_Index].Vowel, & Scheme.SrcVList[j].Vowel);
                }
        }
    }

    printf("SCONF data generated.\n");

    String_SetChars(& Path, "./Split.sconf");
    SCONFWriter_Save();
    if(! SCONF_Write(& Split))
    {
        printf("Error: invalid data.\n");
        return 0;
    }
    SCONFWriter_Write(& Path);

    printf("SCONF generated successfully in Split.sconf.\n");

    SCONF_Dtor(& Split);
    CDS_Dtor(& Scheme);
    String_Dtor(& Path);
    return 1;
}

int GenRecDictionary()
{
    if(chdir(String_GetChars(& Dir)))
        return 0;
    SCONF Split;
    SCONF_Ctor(& Split);
    String_FromChars(Path, "./Split.sconf");
    if(! SCONFReader_Open(& Path))
    {
        printf("Error: cannot find SCONF.\n");
        return 0;
    }
    if(! SCONF_Read(& Split))
    {
        printf("Error: wrong SCONF format.\n");
        return 0;
    }
    SCONFReader_Close();

    printf("CDS loaded.\n");

    String_SetChars(& Path, "./Record.txt");
    FileStream Writer;
    FileStream_Ctor(& Writer);
    FileStream_Open(& Writer, & Path, CREATE);

    String Tmp;
    String_Ctor(& Tmp);
    int i;
    for(i = 0; i <= Split.TickList_Index; i ++)
    {
        if(i != Split.TickList_Index)
            if(String_Equal(& Split.TickList[i].Consonant, & Split.TickList[i + 1].Consonant)
            && String_Equal(& Split.TickList[i].Vowel    , & Split.TickList[i + 1].Vowel))
                continue;
        if(String_EqualChars(& Split.TickList[i].Consonant, "/"))
            String_SetChars(& Tmp, "");
        else
            String_Copy(& Tmp, & Split.TickList[i].Consonant);
        String_Join(& Tmp, & Split.TickList[i].Vowel);
        FileStream_WriteStr(& Writer, & Tmp);
        if(i != Split.TickList_Index)
            FileStream_WriteChars(& Writer, " ");
    }
    String_Dtor(& Tmp);

    printf("Recording dictionary generated in Record.txt.\n");
    FileStream_Close(& Writer);
    FileStream_Dtor(& Writer);
    String_Dtor(& Path);
    SCONF_Dtor(& Split);
    return 1;
}

int Scan()
{
    if(chdir(String_GetChars(& Dir)))
        return 0;
    if(fork() == 0)
    {
        execl("./Bin/WSplit", "WSplit", "./Raw/raw.wav",
              "-conf", "./Split.sconf",
              "-scan", (char*)0);
        exit(0);
    }else
        wait(0);
    return 1;
}

int Split()
{
    if(chdir(String_GetChars(& Dir)))
        return 0;
    if(fork() == 0)
    {
        execl("./Bin/WSplit", "WSplit", "./Raw/raw.wav",
              "-conf", "./Split.sconf",
              "-cds", "./Scheme.cds",
              "-split", "./Frag/",
              "-wconf", "./Fragments.wconf", (char*)0);
        exit(0);
    }else
        wait(0);
    return 1;
}

int Preprocess()
{
    if(chdir(String_GetChars(& Dir)))
        return 0;
    WCONF Frag;
    String File;
    String_FromChars(Path, "./Fragments.wconf");
    String_Ctor(& File);
    WCONF_Ctor(& Frag);
    if(! LoadWCONF(& Frag, & Path))
        return 0;

    String Tmp;
    String_Ctor(& Tmp);
    int i;
    for(i = 0; i <= Frag.SampleList_Index; i ++)
    {
        String_SetChars(& File, "./Frag/");
        if(! String_EqualChars(& Frag.SampleList[i].Consonant, "/"))
            String_Join(& File, & Frag.SampleList[i].Consonant);
        String_Join(& File, & Frag.SampleList[i].Vowel);
        CStrInt(& Tmp, Frag.SampleList[i].Num);
        String_Join(& File, & Tmp);
        String_JoinChars(& File, ".wsp");
        printf("%s\n", String_GetChars(& File));

        CStrFloat(& Tmp, Frag.AverageMagnitude);
        if(fork() == 0)
        {
            execl("./Bin/Wpp", "Wpp", String_GetChars(& File),
                  "-normalize", String_GetChars(& Tmp),
                  "-balance", (char*)0);
            exit(0);
        }else
            wait(0);
    }
    String_Dtor(& Tmp);
    String_Dtor(& Path);
    String_Dtor(& File);
    WCONF_Dtor(& Frag);
    return 1;
}

int GenCVDB()
{
    if(chdir(String_GetChars(& Dir)))
        return 0;
    WCONF Frag;
    String FileIn, FileOut, PathOut;
    String_Ctor(& FileIn);
    String_Ctor(& FileOut);
    String_Ctor(& PathOut);
    String_FromChars(Path, "./Fragments.wconf");
    WCONF_Ctor(& Frag);
    if(! LoadWCONF(& Frag, & Path))
        return 0;
    time_t WCONFTime = GetLastModifyTime(& Path);

    String_SetChars(& Path, "./Scheme.cds");
    CDS Scheme;
    CDS_Ctor(& Scheme);
    if(! LoadCDS(& Scheme, & Path))
        return 0;

    printf("CDS loaded.\n");

    String_SetChars(& PathOut, "./CVDB/");
    String Tmp, F1Str, F2Str, F3Str, LenStr;
    String_Ctor(& Tmp);
    String_Ctor(& F1Str);
    String_Ctor(& F2Str);
    String_Ctor(& F3Str);
    String_Ctor(& LenStr);
    int i;
    for(i = 0; i <= Frag.SampleList_Index; i ++)
    {
        int Vowel = String_EqualChars(& Frag.SampleList[i].Consonant, "/");
        //CDS is unused yet.
        int SrcVIndex = CDS_SearchByVowel(& Scheme, & Frag.SampleList[i].Vowel);

        String_SetChars(& FileIn, "./Frag/");
        String_Copy(& FileOut, & PathOut);
        if(! Vowel)
        {
            String_Join(& FileIn, & Frag.SampleList[i].Consonant);
            String_Join(& FileOut, & Frag.SampleList[i].Consonant);
        }
        String_Join(& FileIn, & Frag.SampleList[i].Vowel);
        String_Join(& FileOut, & Frag.SampleList[i].Vowel);
        CStrInt(& Tmp, Frag.SampleList[i].Num);
        String_Join(& FileIn, & Tmp);
        String_Join(& FileOut, & Tmp);
        String_JoinChars(& FileIn, ".wsp");
        String_JoinChars(& FileOut, ".cvdb");
        time_t WSPTime = GetLastModifyTime(& FileIn);
        time_t CVDBTime = GetLastModifyTime(& FileOut);
        if(CVDBTime > 0 && CVDBTime > WSPTime && CVDBTime > WCONFTime)
            continue;

        if(Vowel)
            CStrFloat(& LenStr, Scheme.VowelLen);
        else
            CStrFloat(& LenStr, Scheme.DiphoneLen);
        CStrFloat(& Tmp, Frag.SampleList[i].F0);
        CStrFloat(& F1Str, Frag.SampleList[i].F1);
        CStrFloat(& F2Str, Frag.SampleList[i].F2);
        CStrFloat(& F3Str, Frag.SampleList[i].F3);
        pid_t Branch = fork();
        if(Branch == 0)
        {
            if(Vowel)
                execl("./Bin/CMin", "CMin", String_GetChars(& FileIn), "-V",
                      "-F0", String_GetChars(& Tmp),
                      "-F1", String_GetChars(& F1Str),
                      "-F2", String_GetChars(& F2Str),
                      "-F3", String_GetChars(& F3Str),
                      "-L", String_GetChars(& LenStr),
                      "-o", String_GetChars(& PathOut), (char*)0);
            else
                execl("./Bin/CMin", "CMin", String_GetChars(& FileIn), "-C",
                      "-F0", String_GetChars(& Tmp),
                      "-F1", String_GetChars(& F1Str),
                      "-F2", String_GetChars(& F2Str),
                      "-F3", String_GetChars(& F3Str),
                      "-L", String_GetChars(& LenStr),
                      "-o", String_GetChars(& PathOut), (char*)0);
            exit(0);
        }else
        {
            int code;
            waitpid(Branch, & code, 0);
            printf("Ret: %d\n", code);
        }
    }
    String_Dtor(& Tmp);
    String_Dtor(& F1Str);
    String_Dtor(& F2Str);
    String_Dtor(& F3Str);
    String_Dtor(& LenStr);
    String_Dtor(& Path);
    String_Dtor(& FileIn);
    String_Dtor(& FileOut);
    String_Dtor(& PathOut);
    CDS_Dtor(& Scheme);
    WCONF_Dtor(& Frag);
    return 1;
}

int DebugWav()
{
    if(chdir(String_GetChars(& Dir)))
        return 0;
    WCONF Frag;
    String FileIn, FileOut;
    String_Ctor(& FileIn);
    String_Ctor(& FileOut);
    String_FromChars(Path, "./Fragments.wconf");
    WCONF_Ctor(& Frag);
    if(! LoadWCONF(& Frag, & Path))
        return 0;

    String_SetChars(& FileOut, "./Debug");
    String Tmp;
    String_Ctor(& Tmp);
    int i;
    for(i = 0; i <= Frag.SampleList_Index; i ++)
    {
        int Vowel = String_EqualChars(& Frag.SampleList[i].Consonant, "/");

        String_SetChars(& FileIn, "./CVDB/");
        if(! Vowel)
            String_Join(& FileIn, & Frag.SampleList[i].Consonant);
        String_Join(& FileIn, & Frag.SampleList[i].Vowel);
        CStrInt(& Tmp, Frag.SampleList[i].Num);
        String_Join(& FileIn, & Tmp);
        String_JoinChars(& FileIn, ".cvdb");

        if(fork() == 0)
        {
            execl("./Bin/C2Wav", "C2Wav", String_GetChars(& FileIn), "-I",
                  "-o", String_GetChars(& FileOut), (char*)0);
            exit(0);
        }else
            wait(0);
    }
    String_Dtor(& Tmp);
    String_Dtor(& Path);
    String_Dtor(& FileIn);
    String_Dtor(& FileOut);
    WCONF_Dtor(& Frag);
    return 1;
}
