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

String Dir;
String Dir_CVDB;
String Dir_BIN;
String Dir_FRAG;
String Dir_RAW;
String Dir_DEBUG;

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
    chdir(String_GetChars(& Dir));
    String_FromChars(Path, "./Scheme.cds");

    CDS Scheme;
    CDS_Ctor(& Scheme);
    if(! CDSReader_Open(& Path))
    {
        printf("Error: Cannot find Scheme.cds!\n");
        return 0;
    }
    if(! CDS_Read(& Scheme))
    {
        printf("Error: Wrong CDS format!\n");
        return 0;
    }
    CDSReader_Close();

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
    chdir(String_GetChars(& Dir));
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
    chdir(String_GetChars(& Dir));
    if(fork() == 0)
    {
        execl("./Bin/WSplit", "WSplit", "./Raw/raw.wav", "-conf", "./Split.sconf", "-scan", (char*)0);
        exit(0);
    }else
        wait(0);
    return 1;
}

int Split()
{
    chdir(String_GetChars(& Dir));
    if(fork() == 0)
    {
        execl("./Bin/WSplit", "WSplit", "./Raw/raw.wav", "-conf", "./Split.sconf", "-split", "./Frag/", "-wconf", "./Fragments.wconf", (char*)0);
        exit(0);
    }else
        wait(0);
    return 1;
}

int Preprocess()
{
    chdir(String_GetChars(& Dir));
    WCONF Frag;
    String File;
    String_FromChars(Path, "./Fragments.wconf");
    String_Ctor(& File);
    WCONF_Ctor(& Frag);
    WCONFReader_Open(& Path);
    WCONF_Read(& Frag);
    WCONFReader_Close();

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

        CStrFloat(& Tmp, Frag.AverageMagnitude);
        if(fork() == 0)
        {
            execl("./Bin/Wpp", "Wpp", String_GetChars(& File), "-normalize", String_GetChars(& Tmp), "-balance", (char*)0);
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
