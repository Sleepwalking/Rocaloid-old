extern "C"
{
    #include "../TCFILE/WCONF.h"
}

WCONF Project;

void GetDir(String* Dest, String* Path)
{
    int i;
    int End;
    for(i = Path -> Data_Index; i > 0; i --)
        if(Path -> Data[i] == '/')
            break;
    End = i;
    Left(Dest, Path, End);
}

void UpdateCONFItem(QStandardItemModel* Model, int Index)
{

}
