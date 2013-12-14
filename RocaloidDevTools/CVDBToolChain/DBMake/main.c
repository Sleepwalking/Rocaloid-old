#include <stdio.h>
#include "../../../RUtil/RUtil.h"
#include "Routines.h"

/*
    DBMake [dir] [-config | -gsconf | -grecdict | -scan | -split | -prep | -gcvdb | -gcdt | -gcdb | -dbg-wav]
*/

rFunc Operation;
int GotDir = 0;
int GotOperation = 0;

int main(int argc, char** argv)
{
    String Arg;
    String_Ctor(& Arg);
    String_Ctor(& Dir);
    String_Ctor(& Dir_CVDB);
    String_Ctor(& Dir_BIN);
    String_Ctor(& Dir_FRAG);
    String_Ctor(& Dir_RAW);
    String_Ctor(& Dir_DEBUG);
    int i;
    for(i = 1; i < argc; i ++)
    {
        String_SetChars(& Arg, argv[i]);
        if(String_GetChar(& Arg, 0) == '-')
        {
            if(String_EqualChars(& Arg, "-config"))
            {
                Operation = Config;
            }else if(String_EqualChars(& Arg, "-gsconf"))
            {
                Operation = GenSCONF;
            }else if(String_EqualChars(& Arg, "-grecdict"))
            {
                Operation = GenRecDictionary;
            }else if(String_EqualChars(& Arg, "-scan"))
            {
                Operation = Scan;
            }else if(String_EqualChars(& Arg, "-split"))
            {
                Operation = Split;
            }else if(String_EqualChars(& Arg, "-prep"))
            {
                Operation = Preprocess;
            }else if(String_EqualChars(& Arg, "-gcvdb"))
            {
                Operation = GenCVDB;
            }else if(String_EqualChars(& Arg, "-gcdt"))
            {
                Operation = GenCDT;
            }else if(String_EqualChars(& Arg, "-dbg-wav"))
            {
                Operation = DebugWav;
            }else
            {
                printf("Error: Invalid parameter.\n");
                return 1;
            }
            if(GotOperation)
            {
                printf("Error: Multiple operations specified!\n");
                return 1;
            }else
                GotOperation = 1;
        }else
        {
            String_Copy(& Dir, & Arg);
            if(GotDir)
            {
                printf("Error: Multiple directories specified!\n");
                return 1;
            }else
                GotDir = 1;
        }
    }

    if(! GotOperation || ! GotDir)
    {
        printf("Rocaloid DBMake 0.16  2013.12.12B\n");
        printf("DBMake [dir] [-config | -gsconf | -grecdict | -scan | -split | -prep | -gcvdb | -gcdt | -gcdb | -dbg-wav]\n");
        return 0;
    }

    String_Copy(& Dir_BIN, & Dir);
    String_Copy(& Dir_CVDB, & Dir);
    String_Copy(& Dir_DEBUG, & Dir);
    String_Copy(& Dir_FRAG, & Dir);
    String_Copy(& Dir_RAW, & Dir);
    String_JoinChars(& Dir_BIN, "/Bin");
    String_JoinChars(& Dir_CVDB, "/CVDB");
    String_JoinChars(& Dir_DEBUG, "/Debug");
    String_JoinChars(& Dir_FRAG, "/Frag");
    String_JoinChars(& Dir_RAW, "/Raw");
    int Ret = Operation();

    String_Dtor(& Arg);
    String_Dtor(& Dir);
    if(Ret)
        printf("Finished.\n");
    else
        printf("Failed.\n");
    return 0;
}
