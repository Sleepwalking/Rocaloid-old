#include "FECSOLAEx.h"

void FECSOLAState_FromCVDB(FECSOLAState* Dest, CVDB3* Src)
{
    Dest -> F0 = Src -> Header.F0;
    Dest -> F1 = Src -> Header.F1;
    Dest -> F2 = Src -> Header.F2;
    Dest -> F3 = Src -> Header.F3;

    Dest -> S0 = 1;
    Dest -> S1 = Src -> Header.S1;
    Dest -> S2 = Src -> Header.S2;
    Dest -> S3 = Src -> Header.S3;
}

#define SrcState CGDict.CDTMapping.SymbolLayerMap[FIndex]
void FECSOLAState_FromSymbolLayer(FECSOLAState* Dest, String* Src)
{
    int FIndex = Demapper_QuerySymbolLayer(Src);
    Dest -> F0 = SrcState.F0;
    Dest -> F1 = SrcState.F1;
    Dest -> F2 = SrcState.F2;
    Dest -> F3 = SrcState.F3;
    Dest -> S1 = SrcState.S1;
    Dest -> S2 = SrcState.S2;
    Dest -> S3 = SrcState.S3;
    Dest -> S0 = 1;
}
