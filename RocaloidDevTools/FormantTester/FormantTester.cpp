#include "FormantTester.h"
#include "ui_rocatool_window.h"
#include "tools/CVEDSP/FreqDomain/Filter.h"

#include "editor/Utils.h"
#include "spectrum.h"

#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QToolBar>
#include <QGridLayout>

#include <QUrl>
#include <QFileInfo>
#include <QFile>
#include <QMimeData>
#include <qevent.h>

#include "editor/audio/Player.h"
#include "editor/audio/Codec.h"
#include "editor/audio/CodecBase.h"

const QString playStr = QObject::tr("Play");
const QString stopStr = QObject::tr("Stop");

const QString CONST_ROCATOOL_NAME = QObject::tr("Formant Tester");

const int SPECTRUM_FLOATS = 512;


inline QLabel* makeLabel(const QString &txt, Qt::Alignment align, QWidget *parent = 0)
{
    QLabel *l = new QLabel(txt, parent);
    l->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    l->setMinimumWidth(50);
    l->setAlignment(align);

    return l;
}

inline QLabel* makeLeftLabel (const QString &txt, QWidget *parent = 0) { return makeLabel(txt, Qt::AlignRight, parent); }
inline QLabel* makeRightLabel(const QString &txt, QWidget *parent = 0) { return makeLabel(txt, Qt::AlignLeft,  parent); }

inline QSlider* makeSlider(int max, QWidget *parent = 0)
{
    QSlider *s = new QSlider(Qt::Horizontal, parent);
    s->setMaximum(max);
    return s;
}

inline QSlider* makeFreqSlider    (QWidget *parent = 0) { return makeSlider(6000, parent); }
inline QSlider* makeStrengthSlider(QWidget *parent = 0) { return makeSlider(30,   parent); }

inline void makeRowOfSliders(int row, QGridLayout *gl, const QString &txt, QSlider *bS, QLabel *bL, QSlider *aS, QLabel *aL)
{
    QLabel *rl1 = makeLeftLabel(txt);
    QLabel *rl2 = makeLeftLabel(txt);

    gl->addWidget(rl1, row, 0, 1, 1);
    gl->addWidget(bS,  row, 1, 1, 1);
    gl->addWidget(bL,  row, 2, 1, 1);
    gl->addWidget(rl2, row, 3, 1, 1);
    gl->addWidget(aS,  row, 4, 1, 1);
    gl->addWidget(aL,  row, 5, 1, 1);
}

//---------------------------------------------

inline void U8toFloat(const quint8* data, float *dst, int dstLen, bool stereo)
{
    int srcI = 0;
    int srcIinc = stereo ? 2 : 1;

    for (int i = 0; i < dstLen; ++i)
    {
        dst[i] = ((float)data[srcI] - 128.f) / 127.f;
        srcI += srcIinc;
    }
}

inline void S16toFloat(const qint16 *data, float *dst, int dstLen, bool stereo)
 {
     int srcI = 0;
     int srcIinc = stereo ? 2 : 1;

     for (int i = 0; i < dstLen; ++i)
     {
         dst[i] = (float)data[srcI] / 32767.f;
         srcI += srcIinc;
     }
 }

inline void FloattoFloat(const float *data, float *dst, int dstLen, bool stereo)
{
    int    srcI = 0;
    int    srcIinc = stereo ? 2 : 1*4;

    for (int i = 0; i < dstLen; ++i)
    {
        dst[i] = data[srcI];
        srcI += srcIinc;
    }
}

inline qtauAudioSource* transformWaveToFloats(qtauAudioSource &as)
{
    QAudioFormat f = as.getAudioFormat();

    qint64 tenSeconds = f.sampleRate() * 10;
    qint64 samples = qMin(as.size() / (f.sampleSize() / 8 * f.channelCount()), tenSeconds); // NOTE: max 10 seconds

    QByteArray ba(samples * 4 + f.sampleRate() * 4, '\0'); //One extra second for safety.

    switch (f.sampleType())
    {
    case QAudioFormat::UnSignedInt: U8toFloat((quint8*)as.buffer().data(), (float*)ba.data(), samples, f.channelCount() > 1);
        break;
    case QAudioFormat::SignedInt:  S16toFloat((qint16*)as.buffer().data(), (float*)ba.data(), samples, f.channelCount() > 1);
        break;
    case QAudioFormat::Float:    FloattoFloat((float*) as.buffer().data(), (float*)ba.data(), samples, f.channelCount() > 1);
        break;
    default:
        vsLog::e("Unknown audiosource sample format!");
    }

    f.setSampleType(QAudioFormat::Float);
    f.setSampleSize(32);
    f.setChannelCount(1);

    QBuffer b(&ba);

    return new qtauAudioSource(b, f);
}

inline QWidget* setupSpectrum(Spectrum *sp, QWidget *parent = 0)
{
    QWidget *result = new QWidget(parent);
    result->setContentsMargins(5, 5, 5, 5);
    result->setMinimumSize(200, 200);
    result->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *vbl = new QVBoxLayout();
    vbl->addWidget(sp);
    result->setLayout(vbl);

    return result;
}


//========================================================================
//========================================================================


RocaTool::RocaTool(QWidget *parent) :
    QMainWindow(parent), wavBefore(0), wavAfter(0), needsSynthesis(false), playing(false), ui(new Ui::RocaWindow)
{
    ui->setupUi(this);
    setWindowTitle(CONST_ROCATOOL_NAME);
    setAcceptDrops(true);
    player = new qtmmPlayer(this);
    qtauCodecRegistry::instance()->addCodec(new qtauWavCodecFactory());

    // ---------- creating UI --------------------
    QGridLayout *gl = new QGridLayout();

    spectrumBefore = new Spectrum(this);
    spectrumAfter  = new Spectrum(this);
    QWidget *spectrumBeforePanel = setupSpectrum(spectrumBefore, this);
    QWidget *spectrumAfterPanel  = setupSpectrum(spectrumAfter,  this);

    bF1 = makeFreqSlider(this);
    bF2 = makeFreqSlider(this);
    bF3 = makeFreqSlider(this);
    aF1 = makeFreqSlider(this);
    aF2 = makeFreqSlider(this);
    aF3 = makeFreqSlider(this);

    bS1 = makeStrengthSlider(this);
    bS2 = makeStrengthSlider(this);
    bS3 = makeStrengthSlider(this);
    aS1 = makeStrengthSlider(this);
    aS2 = makeStrengthSlider(this);
    aS3 = makeStrengthSlider(this);

    aF1->setValue(1000);
    bF1->setValue(1000);
    aF2->setValue(1500);
    bF2->setValue(1500);
    aF3->setValue(4000);
    bF3->setValue(4000);

    aS1->setValue(10);
    bS1->setValue(10);
    aS2->setValue(10);
    bS2->setValue(10);
    aS3->setValue(10);
    bS3->setValue(10);

    bF1val = makeRightLabel("1000", this);
    bF2val = makeRightLabel("1500", this);
    bF3val = makeRightLabel("4000", this);
    aF1val = makeRightLabel("1000", this);
    aF2val = makeRightLabel("1500", this);
    aF3val = makeRightLabel("4000", this);

    bS1val = makeRightLabel("1", this);
    bS2val = makeRightLabel("1", this);
    bS3val = makeRightLabel("1", this);
    aS1val = makeRightLabel("1", this);
    aS2val = makeRightLabel("1", this);
    aS3val = makeRightLabel("1", this);

    QLabel *befLbl = new QLabel("Before");
    QLabel *aftLbl = new QLabel("After");
    befLbl->setAlignment(Qt::AlignCenter);
    aftLbl->setAlignment(Qt::AlignCenter);

    gl->addWidget(befLbl, 0, 1, 1, 1);
    gl->addWidget(aftLbl,  0, 4, 1, 1);

    makeRowOfSliders(1, gl, "F1", bF1, bF1val, aF1, aF1val);
    makeRowOfSliders(2, gl, "F2", bF2, bF2val, aF2, aF2val);
    makeRowOfSliders(3, gl, "F3", bF3, bF3val, aF3, aF3val);

    makeRowOfSliders(4, gl, "S1", bS1, bS1val, aS1, aS1val);
    makeRowOfSliders(5, gl, "S2", bS2, bS2val, aS2, aS2val);
    makeRowOfSliders(6, gl, "S3", bS3, bS3val, aS3, aS3val);

    gl->addWidget(spectrumBeforePanel, 7, 0, 1, 3);
    gl->addWidget(spectrumAfterPanel,  7, 3, 1, 3);

    soundLevel = new QSlider(Qt::Horizontal, this);
    soundLevel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    soundLevel->setMaximum(100);
    soundLevel->setValue(50);
    player->setVolume(50);

    QLabel *volumePic = new QLabel(this);
    volumePic->setPixmap(QPixmap(":/images/speaker.png"));

    QToolBar *tb = new QToolBar(this);
    tb->addAction(ui->actionPlay);
    tb->addWidget(soundLevel);
    tb->addWidget(volumePic);
    tb->setFloatable(false);
    addToolBar(tb);

    ui->actionPlay->setEnabled(false);
    //--------------------------------------------

    // --------- binding widgets -----------------
    connect(ui->actionQuit, SIGNAL(triggered()), SLOT(close()));
    connect(ui->actionPlay, SIGNAL(triggered()), SLOT(onPlay()));

    connect(soundLevel, SIGNAL(valueChanged(int)), SLOT(onVolumeSet(int)));
    connect(player, SIGNAL(playbackEnded()), SLOT(onPlaybackEnded()));

    connect(bF1, SIGNAL(valueChanged(int)), SLOT(onbF1(int)));
    connect(bF2, SIGNAL(valueChanged(int)), SLOT(onbF2(int)));
    connect(bF3, SIGNAL(valueChanged(int)), SLOT(onbF3(int)));

    connect(aF1, SIGNAL(valueChanged(int)), SLOT(onaF1(int)));
    connect(aF2, SIGNAL(valueChanged(int)), SLOT(onaF2(int)));
    connect(aF3, SIGNAL(valueChanged(int)), SLOT(onaF3(int)));

    connect(bS1, SIGNAL(valueChanged(int)), SLOT(onbS1(int)));
    connect(bS2, SIGNAL(valueChanged(int)), SLOT(onbS2(int)));
    connect(bS3, SIGNAL(valueChanged(int)), SLOT(onbS3(int)));

    connect(aS1, SIGNAL(valueChanged(int)), SLOT(onaS1(int)));
    connect(aS2, SIGNAL(valueChanged(int)), SLOT(onaS2(int)));
    connect(aS3, SIGNAL(valueChanged(int)), SLOT(onaS3(int)));
    //--------------------------------------------

    ui->centralwidget->setLayout(gl);
}

RocaTool::~RocaTool()
{
    //
}

qtauAudioSource* RocaTool::loadAudio(const QString &fileName)
{
    qtauAudioSource *result = 0;

    QFileInfo fi(fileName);
    QFile f(fileName);

    if (fi.suffix() == "wav" && f.open(QFile::ReadOnly))
    {
        result = codecForExt("wav", f, this);

        if (result)
        {
            if (!result->cacheAll())
            {
                vsLog::e("Could not parse " + fileName);
                delete result;
                result = 0;
            }
        }
        else
            vsLog::e("No codec for wav");

        f.close();
    }
    else
        vsLog::e("Could not open " + fileName);

    return result;
}

void RocaTool::onLoadWav(QString fileName)
{
//     1) load .wav file
//     2) transform it to floats
//     3) send float-wave to cvedsp by LoadWav
//     4) prepare spectrum buffers
//     5) fill spectrum buffer of base audio by UpdateSpectrum1
//     6) copy spectrumDataBefore to spectrumDataAfter, it's the same before changes
//     7) set spectrumDataBefore for both widgets

    qtauAudioSource *audio = loadAudio(fileName);

    if (audio)
    {
        ui->actionPlay->setEnabled(true);
        needsSynthesis = true;
        setWindowTitle(fileName + " :: " + CONST_ROCATOOL_NAME);

        player->stop(); // it may be playing audio that's gonna be deleted

        if (wavBefore)
            delete wavBefore;

        if (wavAfter)
            delete wavAfter;

        wavBefore = transformWaveToFloats(*audio);
        wavAfter  = new qtauAudioSource(*wavBefore, wavBefore->getAudioFormat());
        delete audio; // transformed to floats, not needed anymore

        QAudioFormat fmt = wavBefore->getAudioFormat();
        long totalSamples = wavBefore->size() * 8 / fmt.sampleSize();
        SetSampleRate(fmt.sampleRate());
        LoadWav((float*)wavBefore->buffer().data(), fmt.channelCount(), fmt.sampleRate(), totalSamples);

        // 10 seconds of floats with current sample rate (+1 for safety)
        spectrumDataBefore.resize(SPECTRUM_FLOATS * 4);

        FECSOLAState Ret = UpdateSpectrum1((float*)spectrumDataBefore.data(), (float*)wavBefore -> buffer().data());

        spectrumDataAfter = spectrumDataBefore;

        bF1 -> setValue(Ret.F1);
        bF2 -> setValue(Ret.F2);
        bF3 -> setValue(Ret.F3);
        bS1 -> setValue(Ret.S1);
        bS2 -> setValue(Ret.S2);
        bS3 -> setValue(Ret.S3);

        if(aS1 -> value() == 10 && aS2 -> value() == 10 && aS3 -> value() == 10)
        {
            aF1 -> setValue(Ret.F1);
            aF2 -> setValue(Ret.F2);
            aF3 -> setValue(Ret.F3);
            aS1 -> setValue(Ret.S1);
            aS2 -> setValue(Ret.S2);
            aS3 -> setValue(Ret.S3);
        }

        spectrumBefore->setSpectrumData((float*)spectrumDataBefore.data(), SPECTRUM_FLOATS);
        spectrumAfter ->setSpectrumData((float*)spectrumDataBefore.data(), SPECTRUM_FLOATS);
    }
}


//----- ui callbacks ------------
// before-synth Formants
void RocaTool::onbF1(int val) { bF1val->setText(QString("%1").arg(val)); updateSpectrum2(); }
void RocaTool::onbF2(int val) { bF2val->setText(QString("%1").arg(val)); updateSpectrum2(); }
void RocaTool::onbF3(int val) { bF3val->setText(QString("%1").arg(val)); updateSpectrum2(); }

// after-synth Formants
void RocaTool::onaF1(int val) { aF1val->setText(QString("%1").arg(val)); updateSpectrum2(); }
void RocaTool::onaF2(int val) { aF2val->setText(QString("%1").arg(val)); updateSpectrum2(); }
void RocaTool::onaF3(int val) { aF3val->setText(QString("%1").arg(val)); updateSpectrum2(); }

// before-synth Strength
void RocaTool::onbS1(int val) { bS1val->setText(QString("%1").arg((float)val / 10.f)); updateSpectrum2(); }
void RocaTool::onbS2(int val) { bS2val->setText(QString("%1").arg((float)val / 10.f)); updateSpectrum2(); }
void RocaTool::onbS3(int val) { bS3val->setText(QString("%1").arg((float)val / 10.f)); updateSpectrum2(); }

// after-synth Strength
void RocaTool::onaS1(int val) { aS1val->setText(QString("%1").arg((float)val / 10.f)); updateSpectrum2(); }
void RocaTool::onaS2(int val) { aS2val->setText(QString("%1").arg((float)val / 10.f)); updateSpectrum2(); }
void RocaTool::onaS3(int val) { aS3val->setText(QString("%1").arg((float)val / 10.f)); updateSpectrum2(); }

//----------- playback controls ---------------------
void RocaTool::onPlay()
{
    if (wavBefore)
    {
        if (playing)
            player->stop();

        if (needsSynthesis)
        {
            FECSOLAState stB;
            stB.F1 = bF1->value();
            stB.F2 = bF2->value();
            stB.F3 = bF3->value();

            stB.S1 = bS1->value();
            stB.S2 = bS2->value();
            stB.S3 = bS3->value();

            FECSOLAState stA;
            stA.F1 = aF1->value();
            stA.F2 = aF2->value();
            stA.F3 = aF3->value();

            stA.S1 = aS1->value();
            stA.S2 = aS2->value();
            stA.S3 = aS3->value();
            Synthesis((float*)wavAfter->buffer().data(), wavAfter->getAudioFormat().sampleRate(), stB, stA);
        }

        if (!wavAfter->isOpen())
            wavAfter->open(QIODevice::ReadOnly);

        wavAfter->reset();
        player->play(wavAfter);

        ui->actionPlay->setIcon(QIcon(":/images/b_play_prev.png"));
        ui->actionPlay->setText(tr("Replay"));
        playing = true;
    }
}

void RocaTool::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasFormat("text/uri-list"))
        e->acceptProposedAction();
}

void RocaTool::dragMoveEvent(QDragMoveEvent *e)
{
    if (e->mimeData()->hasFormat("text/uri-list"))
        e->acceptProposedAction();
}

void RocaTool::dropEvent(QDropEvent *e)
{
    QList<QUrl> uris;

    foreach (const QByteArray &uriData, e->mimeData()->data("text/uri-list").split('\n'))
        if (!uriData.isEmpty())
            uris << QUrl::fromEncoded(uriData).toLocalFile().remove('\r');

    qDebug() << uris;

    QFileInfo fi(uris.first().toString());

    if (fi.exists() && !fi.isDir() && fi.suffix() == "wav") // accepting only first one, if it's a ".wav"
        onLoadWav(fi.absoluteFilePath());
}

void RocaTool::updateSpectrum1()
{
    if (wavBefore) // check because its data is passed to UpdateSpectrum1
    {
        UpdateSpectrum1((float*)spectrumDataBefore.data(), (float*)wavBefore->buffer().data());
        spectrumBefore->setSpectrumData((float*)spectrumDataBefore.data(), SPECTRUM_FLOATS);
    }
}

void RocaTool::updateSpectrum2()
{
    FECSOLAState stA;
    stA.F1 = aF1->value();
    stA.F2 = aF2->value();
    stA.F3 = aF3->value();

    stA.S1 = aS1->value();
    stA.S2 = aS2->value();
    stA.S3 = aS3->value();

    FECSOLAState stB;
    stB.F1 = bF1->value();
    stB.F2 = bF2->value();
    stB.F3 = bF3->value();

    stB.S1 = bS1->value();
    stB.S2 = bS2->value();
    stB.S3 = bS3->value();

    UpdateSpectrum2((float*)spectrumDataAfter.data(), stB, stA);
    spectrumAfter->setSpectrumData((float*)spectrumDataAfter.data(), SPECTRUM_FLOATS);
}

void RocaTool::onVolumeSet(int level)
{
    player->setVolume(level);
}

void RocaTool::onPlaybackEnded()
{
    ui->actionPlay->setIcon(QIcon(":/images/b_play.png"));
    ui->actionPlay->setText(tr("Play"));
    playing = false;
}
