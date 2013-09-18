#include <stdio.h>
#include "CVDB3/CVDB3IO.h"
#include "CDT3/CDT3.h"
#include "CDT3/CDT3Reader.h"
#include "CDT3/Demapper.h"
#include "CVS3/CVS3.h"
#include "CVS3/CVSRDLReader.h"
#include "CVS3/CVSRDLWriter.h"
#include "RDL.h"
#include <string.h>
#include <malloc.h>


int main(void)
{
    //CVDB3 test;
    //CVDB3_Ctor(&test);

    String_FromChars(Path, "/tmp/CVS3example.cvs");

    CVS3 test;
    CVS3_Ctor(& test);
    CVSRDLReader_Open(& Path);
    CVS3_Read(& test);
    CVSRDLReader_Close();

    CVSRDLWriter_Save();
    CVS3_Write(& test);
    String_SetChars(& Path, "/tmp/CVSOutput.cvs.txt");
    CVSRDLWriter_Write(& Path);

    CVS3_Dtor(& test);
    String_Dtor(&Path);

    /*
    CDTMappingQuerySpace test;
    CDTMappingQuerySpace_Ctor(& test);

    CDT3 a;
    CDT3_Ctor(&a);
    CDTReader_Open(&Path);
    int ret = CDT3_Read(&a);
    printf("Ret: %d\nVer: %f\n", ret, a.Version);

    Demapper_ConstructQuerySpace(&test, & a.CDTMapping);
    Demapper_SetCDTMap(& a.CDTMapping);
    Demapper_SetQuerySpace(& test);
    String_FromChars(QS, "a");
    String_FromChars(QS2, "a");
    DebugPrintf(d, Demapper_QueryFusedFormantLayer(& QS, 500).Index);
    DebugPrintf(d, Demapper_QueryFusedFormantLayer(& QS, 500).SubIndex);
    DebugPrintf(f, Demapper_QueryFusedFormantLayer(& QS, 500).Ratio);
    DebugPrintf(d, Demapper_QueryTransitionLayer(& QS, & QS2).Index);
    DebugPrintf(d, Demapper_QueryTransitionLayer(& QS, & QS2).MatchRev);
    String_Dtor(& QS);
    String_Dtor(& QS2);
    CDTMappingQuerySpace_Dtor(& test);

    CDTReader_Close();
    CDT3_Dtor(&a);

*/
    /*
    CVDB3_Load(&test, &Path);
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

    String_SetChars(&Path, "/tmp/test2.cvdb");

    CVDB3_Write(&Path, &test);


    CVDB3_Dtor(&test);
*/
    printf("Hello World!\n");
    return 0;
}

