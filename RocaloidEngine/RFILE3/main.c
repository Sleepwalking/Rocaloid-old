#include <stdio.h>
#include "CVDB3/CVDB3IO.h"
#include "CDT3/CDT3.h"
#include <string.h>
#include <malloc.h>

int main(void)
{
    CVDB3 test;
    CVDB3_Ctor(&test);
    String_FromChars(Path, "/tmp/test.cvdb");

    CVDB3_Load(&test, &Path);
    CDT3 a;
    CDT3_Ctor(&a);
    CDT3_Dtor(&a);
/*
    memcpy(&test.Header.Identifier, "CVDB", 4);
    test.Header.CVDBVersion = 3;
    test.Header.F0 = 262;
    memcpy(&test.Header.Symbol, "d@\0", 3);
    test.Header.Blank = 0;
    test.Header.PhoneType = 'C';

    test.Header.PulseNum = 100;
    test.Header.VOI = 4;
    test.Header.WaveSize = 10000;

    test.Header.F1 = 1000;
    test.Header.F2 = 1500;
    test.Header.F3 = 4000;
    test.Header.S1 = 1;
    test.Header.S2 = 1;
    test.Header.S3 = 1;

    test.PulseOffsets = realloc(test.PulseOffsets, 4 * 100);
    test.Wave = realloc(test.Wave, 4 * 10000);

*/
    String_SetChars(&Path, "/tmp/test2.cvdb");

    CVDB3_Write(&Path, &test);

    String_Dtor(&Path);

    CVDB3_Dtor(&test);
    printf("Hello World!\n");
    return 0;
}

