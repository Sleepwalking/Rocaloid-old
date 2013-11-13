#include <stdio.h>
#include "CDS.h"

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
    printf("Hello, world!\n");
    return 0;
}
