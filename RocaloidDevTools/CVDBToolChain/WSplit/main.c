#include <stdio.h>
#include "../../../RUtil/RUtil.h"
/*
    WSplit [Raw Data] -conf [SCONF] [-scan | -gwconf] [WCONF]
*/

String RawPath;
String SCONFPath;
String WCONFPath;

int GotRaw = 0;
int GotSCONF = 0;
int GotWCONF = 0;

int NextSCONF = 0;
int NextWCONF = 0;

int Task_Scan = 0;
int Task_GWCONF = 0;

int main(int argc, char** argv)
{
    String_Ctor(& RawPath);
    String_Ctor(& SCONFPath);
    String_Ctor(& WCONFPath);

    String Tmp;
    String_Ctor(& Tmp);
    int i;
    for(i = 1; i < argc; i ++)
    {
        String_SetChars(& Tmp, argv[i]);
        if(String_GetChar(& Tmp, 0) == '-')
        {
            if(String_EqualChars(& Tmp, "-conf"))
            {
                if(! GotSCONF)
                    NextSCONF = 1;
                else
                {
                    printf("Error: multiple sconfs!\n");
                    return 1;
                }
            }else if(String_EqualChars(& Tmp, "-gwconf"))
            {
                if(! GotWCONF)
                    NextWCONF = 1;
                else
                {
                    printf("Error: multiple wconfs!\n");
                    return 1;
                }
                Task_GWCONF = 1;
                if(Task_Scan)
                {
                    printf("Error: multiple tasks.\n");
                    return 1;
                }
            }else if(String_EqualChars(& Tmp, "-scan"))
            {
                Task_Scan = 1;
                if(Task_GWCONF)
                {
                    printf("Error: multiple tasks.\n");
                    return 1;
                }
            }else
            {
                printf("Error: unknown parameter.\n");
                return 1;
            }
        }else
        {
            if(NextSCONF)
            {
                String_SetChars(& SCONFPath, argv[i]);
                GotSCONF = 1;
            }
            else if(NextWCONF)
            {
                String_SetChars(& WCONFPath, argv[i]);
                GotWCONF = 1;
            }
            else if(! GotRaw)
            {
                String_SetChars(& RawPath, argv[i]);
                GotRaw = 1;
            }
            else
            {
                printf("Error: unrecognized parameter.\n");
                return 1;
            }
        }
    }
    String_Dtor(& Tmp);

    if(! GotRaw)
    {
        printf("Error: raw data not specified.\n");
        return 1;
    }
    if(! GotSCONF)
    {
        printf("Error: sconf not specified.\n");
        return 1;
    }
    if(Task_GWCONF)
    {
        if(! GotWCONF)
        {
            printf("Error: wconf not specified.\n");
            return 1;
        }
    }else if(Task_Scan)
    {
    }else
    {
        printf("Rocaloid WSplit 0.1\n");
        printf("WSplit [Raw Data] -conf [SCONF] [-scan | -gwconf] [WCONF]\n");
    }

    String_Dtor(& RawPath);
    String_Dtor(& SCONFPath);
    String_Dtor(& WCONFPath);
    printf("WSplit Finished.\n");
    return 0;
}

