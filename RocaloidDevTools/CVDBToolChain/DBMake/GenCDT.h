#include "../../../RocaloidEngine/RFILE3/CDT3/CDT3.h"
#include "../../../RocaloidEngine/RFILE3/CDT3/CDT3Writer.h"
#include "../../../RocaloidEngine/RFILE3/CVDB3/CVDB3IO.h"

int GenCDT()
{
    chdir(String_GetChars(& Dir));

    String_FromChars(CDSPath, "./Scheme.cds");
    String_FromChars(WCONFPath, "./Fragments.wconf");
    String_FromChars(CDTPath, "./Dict.cdt");
    CDS Scheme;
    WCONF Frag;
    CDS_Ctor(& Scheme);
    WCONF_Ctor(& Frag);
    if(! LoadCDS(& Scheme, & CDSPath))
        return 1;
    if(! LoadWCONF(& Frag, & WCONFPath))
        return 1;

    CDT3 Output;
    CDT3_Ctor(& Output);
    CVDB3 DFrag;
    CVDB3_Ctor(& DFrag);
    Output.Version = 0.1;

    String File, Name, Tmp;
    String_Ctor(& File);
    String_Ctor(& Name);
    String_Ctor(& Tmp);
    int i;
    for(i = 0; i <= Frag.SampleList_Index; i ++)
    {
        int Vowel = String_EqualChars(& Frag.SampleList[i].Consonant, "/");
        int SrcVIndex = CDS_SearchByVowel(& Scheme, & Frag.SampleList[i].Vowel);
        String_SetChars(& File, "CVDB/");
        String_SetChars(& Name, "");
        if(! Vowel)
            String_Join(& Name, & Frag.SampleList[i].Consonant);
        String_Join(& Name, & Frag.SampleList[i].Vowel);
        CStrInt(& Tmp, Frag.SampleList[i].Num);
        String_Join(& Name, & Tmp);

        String_Join(& File, & Name);
        String_JoinChars(& File, ".cvdb");

        CVDB3_Load(& DFrag, & File);

        //DBLayer
        ArrayType_PushNull(DBLayerEntry, Output.CDTMapping.DBLayerMap);
        DBLayerEntry* DestDBEntry =
                Output.CDTMapping.DBLayerMap + Output.CDTMapping.DBLayerMap_Index;
        DBLayerEntry_Ctor(DestDBEntry);
        String_Copy(& DestDBEntry -> Name, & Name);
        String_Copy(& DestDBEntry -> FileAddr, & File);

        //SymbolLayer
        ArrayType_PushNull(SymbolLayerEntry, Output.CDTMapping.SymbolLayerMap);
        SymbolLayerEntry* DestSymbolEntry =
                Output.CDTMapping.SymbolLayerMap + Output.CDTMapping.SymbolLayerMap_Index;
        SymbolLayerEntry_Ctor(DestSymbolEntry);
        String_Copy(& DestSymbolEntry -> Name, & Name);
        if(Vowel)
            DestSymbolEntry -> Type = 'V';
        else
            DestSymbolEntry -> Type = 'C';
        DestSymbolEntry -> VOI = DFrag.Header.VOI;
        DestSymbolEntry -> VOT = (float)DFrag.PulseOffsets[DFrag.Header.VOI] / 44100;
        DestSymbolEntry -> F0 = DFrag.Header.F0; //Frag.SampleList[i].F0;
        DestSymbolEntry -> F1 = Scheme.SrcVList[SrcVIndex].F1;
        DestSymbolEntry -> F2 = Scheme.SrcVList[SrcVIndex].F2;
        DestSymbolEntry -> F3 = Scheme.SrcVList[SrcVIndex].F3;
        DestSymbolEntry -> S1 = Scheme.SrcVList[SrcVIndex].S1;
        DestSymbolEntry -> S2 = Scheme.SrcVList[SrcVIndex].S2;
        DestSymbolEntry -> S3 = Scheme.SrcVList[SrcVIndex].S3;

        //FreqLayerMap
        ArrayType_PushNull(FreqLayerEntry, Output.CDTMapping.FreqLayerMap);
        FreqLayerEntry* DestFreqEntry =
                Output.CDTMapping.FreqLayerMap + Output.CDTMapping.FreqLayerMap_Index;
        FreqLayerEntry_Ctor(DestFreqEntry);
        String_Copy(& DestFreqEntry -> Name, & Name);
        Name.Data_Index --;
        String_Copy(& DestFreqEntry -> FPhone, & Name);
        DestFreqEntry -> F0 = DFrag.Header.F0; //Frag.SampleList[i].F0;

        //FormantLayerMap
        //Uncomment to generate one entry for each combination.
        //if(i == 0 || (! String_Equal(& Frag.SampleList[i].Consonant, & Frag.SampleList[i - 1].Consonant))
        //          || (! String_Equal(& Frag.SampleList[i].Vowel    , & Frag.SampleList[i - 1].Vowel    )))
        {
            ArrayType_PushNull(FormantLayerEntry, Output.CDTMapping.FormantLayerMap);
            FormantLayerEntry* DestFormantEntry =
                    Output.CDTMapping.FormantLayerMap + Output.CDTMapping.FormantLayerMap_Index;
            FormantLayerEntry_Ctor(DestFormantEntry);
            String_Copy(& DestFormantEntry -> Phone , & Name);
            String_Copy(& DestFormantEntry -> FPhone, & Name);
            DestFormantEntry -> F0 = DFrag.Header.F0; //Frag.SampleList[i].F0;
            DestFormantEntry -> F1 = Scheme.SrcVList[SrcVIndex].F1;
            DestFormantEntry -> F2 = Scheme.SrcVList[SrcVIndex].F2;
            DestFormantEntry -> F3 = Scheme.SrcVList[SrcVIndex].F3;
            DestFormantEntry -> S1 = Scheme.SrcVList[SrcVIndex].S1;
            DestFormantEntry -> S2 = Scheme.SrcVList[SrcVIndex].S2;
            DestFormantEntry -> S3 = Scheme.SrcVList[SrcVIndex].S3;
        }
    }
    CVDB3_Dtor(& DFrag);
    String_Dtor(& File);
    String_Dtor(& Name);
    String_Dtor(& Tmp);

    CDTWriter_Save();
    CDT3_Write(& Output);
    CDTWriter_Write(& CDTPath);
    CDT3_Dtor(& Output);
    CDS_Dtor(& Scheme);
    WCONF_Dtor(& Frag);
    String_Dtor(& CDSPath);
    String_Dtor(& WCONFPath);
    String_Dtor(& CDTPath);
    return 1;
}
