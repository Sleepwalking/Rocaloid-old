#include <stdio.h>
#include "CDS.h"
#include "SCONF.h"
#include "WCONF.h"

int main()
{

    CDS Test;
    CDS_Ctor(& Test);
    String_FromChars(Path, "/tmp/CDSExample.cds");
    CDSReader_Open(& Path);
    CDS_Read(& Test);
    CDSReader_Close();

    String_Dtor(& Path);
    CDS_Dtor(& Test);
/*
    SCONF Test;
    SCONF_Ctor(& Test);
    String_FromChars(Path, "/tmp/SCONFExample.sconf");
    SCONFReader_Open(& Path);
    SCONF_Read(& Test);
    SCONFReader_Close();

    String_SetChars(& Path, "/tmp/SCONFOutput.sconf");
    SCONFWriter_Save();
    SCONF_Write(& Test);
    SCONFWriter_Write(& Path);

    String_Dtor(& Path);
    SCONF_Dtor(& Test);*/
/*
    WCONF Test;
    WCONF_Ctor(& Test);
    String_FromChars(Path, "/tmp/WCONFExample.wconf");
    WCONFReader_Open(& Path);
    WCONF_Read(& Test);
    WCONFReader_Close();

    String_SetChars(& Path, "/tmp/WCONFOutput.wconf");
    WCONFWriter_Save();
    WCONF_Write(& Test);
    WCONFWriter_Write(& Path);

    String_Dtor(& Path);
    WCONF_Dtor(& Test);*/
    printf("Hello, world!\n");
    return 0;
}
