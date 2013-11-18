#include "CVEGlobal.h"
#include "../RFILE3/CDT3/CDT3Reader.h"
#include "../../CVEDSP/DSPBase/Window.h"

CDT3 CGDict;
CDTMappingQuerySpace CGQuerySpace;
float Hanning2048[2048];
float Hanning1024[1024];

void CVEGlobal_Init()
{
    CDT3_Ctor(& CGDict);
    CDTMappingQuerySpace_Ctor(& CGQuerySpace);
}

void CVEGlobal_Exit()
{
    CDT3_Dtor(& CGDict);
    CDTMappingQuerySpace_Dtor(& CGQuerySpace);
}

int CVEGlobal_LoadCDT(String* Path)
{
    if(! CDTReader_Open(Path))
        return 0;
    if(! CDT3_Read(& CGDict))
        return - 1;

    Demapper_ConstructQuerySpace(& CGQuerySpace, & CGDict.CDTMapping);
    Demapper_SetCDTMap(& CGDict.CDTMapping);
    Demapper_SetQuerySpace(& CGQuerySpace);

    CDTReader_Close();

    return 1;
}
