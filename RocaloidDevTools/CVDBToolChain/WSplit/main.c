#include <stdio.h>
#include "../../../RUtil/RUtil.h"
#include "Scanner.h"
#include "Spliter.h"
/*
    WSplit [Raw Data] -conf [SCONF] [-scan | -split] [FragDir] [-wconf] [WCONF] [-cds] [CDS]
*/

String RawPath;
String FragPath;
String SCONFPath;
String WCONFPath;
String CDSPath;

int GotRaw = 0;
int GotFrag = 0;
int GotSCONF = 0;
int GotWCONF = 0;
int GotCDS = 0;

int NextSCONF = 0;
int NextWCONF = 0;
int NextCDS = 0;
int NextFrag = 0;

int Task_Scan = 0;
int Task_Split = 0;

int main(int argc, char** argv)
{
    String_Ctor(& RawPath);
    String_Ctor(& FragPath);
    String_Ctor(& SCONFPath);
    String_Ctor(& WCONFPath);
    String_Ctor(& CDSPath);

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
            }else if(String_EqualChars(& Tmp, "-split"))
            {
                if(! GotFrag)
                    NextFrag = 1;
                else
                {
                    printf("Error: multiple fragment paths!\n");
                    return 1;
                }
                Task_Split = 1;
                if(Task_Scan)
                {
                    printf("Error: multiple tasks.\n");
                    return 1;
                }
            }else if(String_EqualChars(& Tmp, "-scan"))
            {
                Task_Scan = 1;
                if(Task_Split)
                {
                    printf("Error: multiple tasks.\n");
                    return 1;
                }
            }else if(String_EqualChars(& Tmp, "-wconf"))
            {
                if(! GotWCONF)
                    NextWCONF = 1;
                else
                {
                    printf("Error: multiple wconfs!\n");
                    return 1;
                }
            }else if(String_EqualChars(& Tmp, "-cds"))
            {
                if(! GotCDS)
                    NextCDS = 1;
                else
                {
                    printf("Error: multiple cdses!\n");
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
                NextSCONF = 0;
            }else if(NextWCONF)
            {
                String_SetChars(& WCONFPath, argv[i]);
                GotWCONF = 1;
                NextWCONF = 0;
            }else if(NextCDS)
            {
                String_SetChars(& CDSPath, argv[i]);
                GotCDS = 1;
                NextCDS = 0;
            }else if(NextFrag)
            {
                String_SetChars(& FragPath, argv[i]);
                GotFrag = 1;
                NextFrag = 0;
            }else if(! GotRaw)
            {
                String_SetChars(& RawPath, argv[i]);
                GotRaw = 1;
            }else
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

    SCONF Split;
    SCONF_Ctor(& Split);
    if(! SCONFReader_Open(& SCONFPath))
    {
        printf("Error: cannot open SCONF.\n");
        return 1;
    }
    if(! SCONF_Read(& Split))
    {
        printf("Error: wrong SCONF format.\n");
        return 1;
    }
    SCONFReader_Close();

    if(Task_Split)
    {
        if(! GotWCONF)
        {
            printf("Error: wconf not specified.\n");
            return 1;
        }
        if(! GotCDS)
        {
            printf("Error: cds not specified.\n");
            return 1;
        }
        CDS Scheme;
        WCONF SampleConf;
        CDS_Ctor(& Scheme);
        WCONF_Ctor(& SampleConf);
        CDSReader_Open(& CDSPath);
        CDS_Read(& Scheme);
        CDSReader_Close();

        WSplit(& SampleConf, & FragPath, & Split, & Scheme, & RawPath);
        WCONFWriter_Save();
        WCONF_Write(& SampleConf);
        WCONFWriter_Write(& WCONFPath);

        CDS_Dtor(& Scheme);
        WCONF_Dtor(& SampleConf);
        printf("WCONF generated.\n");
    }else if(Task_Scan)
    {
        Scan(& Split, & RawPath);
        SCONFWriter_Save();
        SCONF_Write(& Split);
        SCONFWriter_Write(& SCONFPath);
        printf("SCONF regenerated.\n");
    }else
    {
        printf("Rocaloid WSplit 0.2\n");
        printf("WSplit [Raw Data] -conf [SCONF] [-scan | -split] [FragDir] [-wconf] [WCONF] [-cds] [CDS]\n");
    }

    SCONF_Dtor(& Split);
    String_Dtor(& RawPath);
    String_Dtor(& FragPath);
    String_Dtor(& SCONFPath);
    String_Dtor(& WCONFPath);
    String_Dtor(& CDSPath);
    printf("WSplit Finished.\n");
    return 0;
}

