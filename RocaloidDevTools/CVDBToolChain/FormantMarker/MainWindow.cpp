#include "MainWindow.h"
#include <QGridLayout>
#include <QSlider>
#include <QPushButton>

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDebug>

#include "../../../RUtil/RUtil.h"
#include "../../../RUtil/IO/FileUtil.h"
#include "../../../RUtil/Misc/Converter.h"
#include "DSP.h"
#include "CONFIO.h"

#include <math.h>
#include <unistd.h>

#define ConnectScrolls()\
connect(F1Slider, SIGNAL(valueChanged(int)), SLOT(UpdateFilter(int)));\
connect(F2Slider, SIGNAL(valueChanged(int)), SLOT(UpdateFilter(int)));\
connect(F3Slider, SIGNAL(valueChanged(int)), SLOT(UpdateFilter(int)));\
connect(S1Slider, SIGNAL(valueChanged(int)), SLOT(UpdateFilter(int)));\
connect(S2Slider, SIGNAL(valueChanged(int)), SLOT(UpdateFilter(int)));\
connect(S3Slider, SIGNAL(valueChanged(int)), SLOT(UpdateFilter(int)));\
connect(SSlider, SIGNAL(valueChanged(int)), SLOT(UpdateFilter(int)))

MainWindow::MainWindow(QWidget*)
{
    CONFList = new QListView(this);
    QGridLayout* MainLayout = new QGridLayout(this);
    QGridLayout* WaveLayout = new QGridLayout(this);
    QPushButton* SaveButton = new QPushButton(this);
    QPushButton* ScaleInButton = new QPushButton(this);
    QPushButton* ScaleOutButton = new QPushButton(this);
    CONFModel = new QStandardItemModel(this);

    InnerWaveBox = new WaveBox(this);
    F1Slider = new QSlider(Qt::Horizontal, this);
    F2Slider = new QSlider(Qt::Horizontal, this);
    F3Slider = new QSlider(Qt::Horizontal, this);
    S1Slider = new QSlider(Qt::Horizontal, this);
    S2Slider = new QSlider(Qt::Horizontal, this);
    S3Slider = new QSlider(Qt::Horizontal, this);
    SSlider = new QSlider(Qt::Vertical, this);
    StatusLabel = new QLabel(this);

    MainLayout -> setColumnStretch(0, 3);
    MainLayout -> setColumnStretch(1, 7);
    MainLayout -> addWidget(CONFList, 0, 0, 9, 1);
    MainLayout -> addWidget(SaveButton, 9, 0, 1, 1);
    MainLayout -> addLayout(WaveLayout, 0, 1, 10, 1);
    WaveLayout -> addWidget(InnerWaveBox, 0, 0, 5, 20);
    WaveLayout -> addWidget(F1Slider, 6, 0, 1, 10);
    WaveLayout -> addWidget(F2Slider, 7, 0, 1, 10);
    WaveLayout -> addWidget(F3Slider, 8, 0, 1, 10);
    WaveLayout -> addWidget(S1Slider, 6, 10, 1, 9);
    WaveLayout -> addWidget(S2Slider, 7, 10, 1, 9);
    WaveLayout -> addWidget(S3Slider, 8, 10, 1, 9);
    WaveLayout -> addWidget(SSlider, 6, 19, 3, 1);
    WaveLayout -> addWidget(StatusLabel, 9, 0, 1, 20);
    WaveLayout -> addWidget(ScaleOutButton, 5, 18, 1, 1);
    WaveLayout -> addWidget(ScaleInButton, 5, 19, 1, 1);

    SaveButton -> setText(tr("Save WCONF"));
    ScaleInButton -> setText(tr("+"));
    ScaleOutButton -> setText(tr("-"));

    F1Slider -> setMaximum(5000);
    F2Slider -> setMaximum(5000);
    F3Slider -> setMaximum(5000);
    S1Slider -> setMaximum(200);
    S2Slider -> setMaximum(200);
    S3Slider -> setMaximum(200);
    SSlider -> setMaximum(300);

    F1Slider -> setValue(1000);
    F2Slider -> setValue(1500);
    F3Slider -> setValue(4000);
    S1Slider -> setValue(100);
    S2Slider -> setValue(100);
    S3Slider -> setValue(100);
    SSlider -> setValue(100);

    StatusLabel -> setText(tr("Wave not loaded."));

    ConnectScrolls();

    setLayout(MainLayout);
    setAcceptDrops(true);
    this -> setMinimumSize(500, 400);

    this -> InnerWaveBox -> SetWaveSize(120);
    this -> InnerWaveBox -> SetWaveNum(2);

    MainWave = (float*)malloc(sizeof(float) * 44100 * 20);

    float TestWave[120];
    Boost_FloatSet(TestWave, 0, 120);
    this -> InnerWaveBox -> LoadWave(TestWave, 0);
    this -> InnerWaveBox -> LoadWave(TestWave, 1);

    CONFList -> setModel(CONFModel);
    CONFList -> setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(CONFList, SIGNAL(clicked(QModelIndex)), SLOT(CONFSelect(QModelIndex)));
    connect(SaveButton, SIGNAL(clicked()), SLOT(WCONFSave()));
    connect(ScaleInButton, SIGNAL(clicked()), SLOT(ScaleIn()));
    connect(ScaleOutButton, SIGNAL(clicked()), SLOT(ScaleOut()));

    WCONF_Ctor(& Project);
    GlobalCONFModel = CONFModel;
    GlobalWindow = this;
    String_Ctor(& WCONFPath);
    GNUPlot_Open();
}

MainWindow::~MainWindow()
{
    free(MainWave);
}

void MainWindow::resizeEvent(QResizeEvent*)
{
    this -> InnerWaveBox -> Redraw();
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    String Mime, Tmp, Path;
    String_Ctor(& Mime);
    String_Ctor(& Tmp);
    String_Ctor(& Path);
    String_SetChars(& Mime, event -> mimeData() -> text().toStdString().c_str());
    Mime.Data_Index -= 2;
    Left(& Tmp, & Mime, 7);
    if(String_EqualChars(& Tmp, "file://"))
    {
        MidFrom(& Path, & Mime, 7);
        Right(& Tmp, & Path, 4);
        /*
        if(String_EqualChars(& Tmp, ".wav") || String_EqualChars(& Tmp, ".wsp"))
        {
            LoadWave(& Path);
            GenerateSpectrum(this -> InnerWaveBox);
            UpdateFilter(1);
        }*/
        Right(& Tmp, & Path, 6);
        if(String_EqualChars(& Tmp, ".wconf"))
        {
            WCONF_Dtor(& Project);
            WCONF_Ctor(& Project);
            WCONFReader_Open(& Path);
            WCONF_Read(& Project);
            WCONFReader_Close();
            String_Copy(& WCONFPath, & Path);
            GetDir(& Tmp, & Path);
            chdir(String_GetChars(& Tmp));
            qDebug() << "WCONF loaded. " << Project.SampleList_Index + 1 << "items.";
            SetCONFNum(Project.SampleList_Index + 1);
            UpdateAllCONF();
        }
    }
    String_Dtor(& Mime);
    String_Dtor(& Tmp);
    String_Dtor(& Path);
}

void MainWindow::SetFormant(float F1, float F2, float F3, float S1, float S2, float S3, float Mul)
{
    F1Slider -> blockSignals(true);
    F2Slider -> blockSignals(true);
    F3Slider -> blockSignals(true);
    S1Slider -> blockSignals(true);
    S2Slider -> blockSignals(true);
    S3Slider -> blockSignals(true);
    SSlider -> blockSignals(true);

    F1Slider -> setValue(F1);
    F2Slider -> setValue(F2);
    F3Slider -> setValue(F3);
    S1Slider -> setValue(S1);
    S2Slider -> setValue(S2);
    S3Slider -> setValue(S3);
    SSlider -> setValue(Mul);

    F1Slider -> blockSignals(false);
    F2Slider -> blockSignals(false);
    F3Slider -> blockSignals(false);
    S1Slider -> blockSignals(false);
    S2Slider -> blockSignals(false);
    S3Slider -> blockSignals(false);
    SSlider -> blockSignals(false);
}

void MainWindow::UpdateFilter(int)
{
    float TmpWave[1024];
    float F1 = F1Slider -> value();
    float F2 = F2Slider -> value();
    float F3 = F3Slider -> value();
    float S1 = (float)S1Slider -> value() / 100;
    float S2 = (float)S2Slider -> value() / 100;
    float S3 = (float)S3Slider -> value() / 100;
    float S = (float)SSlider -> value() / 100;

    Project.SampleList[CurrentIndex].F1 = F1;
    Project.SampleList[CurrentIndex].F2 = F2;
    Project.SampleList[CurrentIndex].F3 = F3;
    Project.SampleList[CurrentIndex].S1 = S1;
    Project.SampleList[CurrentIndex].S2 = S2;
    Project.SampleList[CurrentIndex].S3 = S3;
    Project.SampleList[CurrentIndex].Mul = S;

    String StatusStr, TmpStr;
    String_Ctor(& StatusStr);
    String_Ctor(& TmpStr);
    if(MainWaveLen > 0)
    {
        CStrFloatF(& TmpStr, F0, "%.2f");
        String_SetChars(& StatusStr, "F0: ");
        String_Join(& StatusStr, & TmpStr);
        String_JoinChars(& StatusStr, ", F1: ");
        CStrFloatF(& TmpStr, F1, "%.2f");
        String_Join(& StatusStr, & TmpStr);
        String_JoinChars(& StatusStr, ", F2: ");
        CStrFloatF(& TmpStr, F2, "%.2f");
        String_Join(& StatusStr, & TmpStr);
        String_JoinChars(& StatusStr, ", F3: ");
        CStrFloatF(& TmpStr, F3, "%.2f");
        String_Join(& StatusStr, & TmpStr);
        String_JoinChars(& StatusStr, ", S0: ");
        CStrFloatF(& TmpStr, 1, "%.2f");
        String_Join(& StatusStr, & TmpStr);
        String_JoinChars(& StatusStr, ", S1: ");
        CStrFloatF(& TmpStr, S1, "%.2f");
        String_Join(& StatusStr, & TmpStr);
        String_JoinChars(& StatusStr, ", S2: ");
        CStrFloatF(& TmpStr, S2, "%.2f");
        String_Join(& StatusStr, & TmpStr);
        String_JoinChars(& StatusStr, ", S3: ");
        CStrFloatF(& TmpStr, S3, "%.2f");
        String_Join(& StatusStr, & TmpStr);
        StatusLabel -> setText(tr(String_GetChars(& StatusStr)));
        GenerateFilterStrength(TmpWave, F0, F1, F2, F3, S, S1 * S, S2 * S, S3 * S);
        InnerWaveBox -> LoadWave(TmpWave, 1);
        InnerWaveBox -> Redraw();
    }
    String_Dtor(& TmpStr);
    String_Dtor(& StatusStr);
}

void MainWindow::CONFSelect(QModelIndex QMI)
{
    int Index = QMI.row();
    qDebug() << Index;
    SelectIndex(Index);
    SetFormant(Project.SampleList[Index].F1,
               Project.SampleList[Index].F2,
               Project.SampleList[Index].F3,
               Project.SampleList[Index].S1 * 100,
               Project.SampleList[Index].S2 * 100,
               Project.SampleList[Index].S3 * 100,
               Project.SampleList[Index].Mul * 100);
    GenerateSpectrum(this -> InnerWaveBox);
    UpdateFilter(1);
}

void MainWindow::WCONFSave()
{
    WCONFWriter_Save();
    WCONF_Write(& Project);
    WCONFWriter_Write(& WCONFPath);
    StatusLabel -> setText(tr("WCONF Saved."));
}

void MainWindow::ScaleIn()
{
    Scale *= 1.1;
    GenerateSpectrum(this -> InnerWaveBox);
    UpdateFilter(1);
}

void MainWindow::ScaleOut()
{
    Scale /= 1.1;
    GenerateSpectrum(this -> InnerWaveBox);
    UpdateFilter(1);
}
