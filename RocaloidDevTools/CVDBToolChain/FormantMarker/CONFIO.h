extern "C"
{
    #include "../TCFILE/WCONF.h"

}

MainWindow* GlobalWindow;
WCONF Project;
int CONFNum = 0;
int CurrentIndex = 0;
String WCONFPath;
QStandardItemModel* GlobalCONFModel;

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

void SetCONFNum(int Num)
{
    int i;
    for(i = 0; i < CONFNum; i ++)
        delete GlobalCONFModel -> item(i);
    CONFNum = Num;
    for(i = 0; i < CONFNum; i ++)
        GlobalCONFModel -> setItem(i, new QStandardItem(QString("")));
    GlobalCONFModel -> setRowCount(Num);
}

void UpdateCONFItem(int Index)
{
    String Joined, Tmp;
    String_Ctor(& Joined);
    String_Ctor(& Tmp);
    CStrInt(& Joined, Index);
    String_JoinChars(& Joined, ".\t");
    String_Join(& Joined, & Project.SampleList[Index].Consonant);
    String_JoinChars(& Joined, "\t");
    String_Join(& Joined, & Project.SampleList[Index].Vowel);
    String_JoinChars(& Joined, "\t");
    CStrInt(& Tmp, Project.SampleList[Index].Num);
    String_Join(& Joined, & Tmp);
    GlobalCONFModel -> item(Index) -> setData(String_GetChars(& Joined), Qt::EditRole);
    String_Dtor(& Joined);
    String_Dtor(& Tmp);
}

void UpdateAllCONF()
{
    int i;
    for(i = 0; i < Project.SampleList_Index + 1; i ++)
        UpdateCONFItem(i);
}

void LoadWave(String* Path)
{
    MainWave = (float*)realloc(MainWave, sizeof(float) * GetFileLength(Path) / 2);
    MainWaveLen = LoadWaveAll(MainWave, Path);
    qDebug() << "Wave loaded. Length: " << MainWaveLen;
}

void SelectIndex(int Index)
{
    CurrentIndex = Index;
    String_FromChars(Path, "./Frag/");
    String Tmp;
    String_Ctor(& Tmp);
    CStrInt(& Tmp, Project.SampleList[Index].Num);
    if(! String_EqualChars(& Project.SampleList[Index].Consonant, "/"))
        String_Join(& Path, & Project.SampleList[Index].Consonant);
    String_Join(& Path, & Project.SampleList[Index].Vowel);
    String_Join(& Path, & Tmp);
    String_JoinChars(& Path, ".wsp");
    LoadWave(& Path);
    F0 = Project.SampleList[Index].F0;
    String_Dtor(& Tmp);
    String_Dtor(& Path);
}
