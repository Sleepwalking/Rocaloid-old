#include <stdio.h>

#include "../../../RUtil/RUtil.h"
#include "../../../RUtil/IO/FileUtil.h"

#include "../../../RocaloidEngine/RFILE3/CVDB3/CVDB3IO.h"

void GetFileName(String* Dest, String* Path)
{
    int i;
    int End, Start;
    for(i = Path -> Data_Index; i > 0; i --)
        if(Path -> Data[i] == '.')
            break;
    End = i;
    for(; i > - 1; i --)
        if(Path -> Data[i] == '/')
            break;
    Start = i;
    Mid(Dest, Path, Start + 1, End - Start - 1);
}

int Arg_NextOutput = 0;
int Arg_ExtractOnly = 0;
int Arg_Inspect = 0;
int main(int ArgQ, char** ArgList)
{
    uint32_t i;
    String_FromChars(OutputPath, ".");
    String_FromChars(Path, ArgList[1]);
    ArrayType_Ctor(String, ArgStrList);
    for(i = 0; i < (uint32_t)ArgQ; i ++)
    {
        ArrayType_PushNull(String, ArgStrList);
        String_Ctor(ArgStrList + i);
        String_SetChars(ArgStrList + i, ArgList[i]);
        if(String_GetChar(ArgStrList + i, 0) == '-')
            UpperCase(ArgStrList + i, ArgStrList +i);
    }
    for(i = 2; i < (uint32_t)ArgQ; i ++)
    {
        if(String_EqualChars(ArgStrList + i, "-E"))
        {
            Arg_ExtractOnly = 1;
        }else if(String_EqualChars(ArgStrList + i, "-I"))
        {
            Arg_Inspect = 1;
        }else if(String_EqualChars(ArgStrList + i, "-O"))
        {
            Arg_NextOutput = 1;
        }else if(Arg_NextOutput)
        {
            Arg_NextOutput = 0;
            if(OutputPath.Data_Index > 0)
            {
                printf("Error: Multiple output path specified.\n");
                return 1;
            }
            String_Copy(& OutputPath, ArgStrList + i);
        }
    }

    String SymbolName;
    String_Ctor(& SymbolName);
    GetFileName(& SymbolName, & Path);

    CVDB3 Input;
    CVDB3_Ctor(& Input);
    CVDB3_Load(& Input, & Path);

    if(! Arg_ExtractOnly)
    {
        for(i = 0; i < Input.Header.PulseNum; i ++)
            Input.Wave[Input.PulseOffsets[i]] = 1;
        Input.Wave[Input.PulseOffsets[Input.Header.VOI]] = - 1;
    }
    if(Arg_Inspect)
    {
        printf("Length: %d samples, %fs, %d pulses.\n", Input.Header.WaveSize, (float)Input.Header.WaveSize / 44100, Input.Header.PulseNum);
        if(Input.Header.PhoneType == 'C')
            printf("Phone Type: Consonant.\n");
        else
            printf("Phone Type: Vowel.\n");
        printf("Fundamental Frequency: %fHz.\n", Input.Header.F0);
        printf("VOT: %f.\n", (float)Input.PulseOffsets[Input.Header.VOI] / 44100);
        printf("F1: %fHz, S1: %f.\n", Input.Header.F1, Input.Header.S1);
        printf("F2: %fHz, S2: %f.\n", Input.Header.F2, Input.Header.S2);
        printf("F3: %fHz, S3: %f.\n", Input.Header.F3, Input.Header.S3);
    }

    String_JoinChars(& SymbolName, ".wav");
    String_JoinChars(& OutputPath, "/");
    String_Join(& OutputPath, & SymbolName);
    WriteWaveAll(& OutputPath, Input.Wave, Input.Header.WaveSize, 44100);

    printf("Finished.\n");
    CVDB3_Dtor(& Input);
    String_Dtor(& SymbolName);
    String_Dtor(& Path);
    String_Dtor(& OutputPath);
    ArrayType_ObjDtor(String, ArgStrList);
    ArrayType_Dtor(String, ArgStrList);
    return 0;
}

