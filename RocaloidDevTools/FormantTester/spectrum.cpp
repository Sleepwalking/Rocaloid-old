#include "spectrum.h"
#include "QTau/qtau/editor/audio/Source.h"
#include "QTau/qtau/editor/Utils.h"

#include <QUrl>
#include <QFileInfo>
#include <QFile>
#include <qevent.h>

#include <QPainter>
#include <QPixmap>
#include <QMimeData>


Spectrum::Spectrum(QWidget *parent) :
    QWidget(parent), audio(0), spectrumCache(0)
{
    setAcceptDrops(false); // disabled for now - whole window will handle a single dropped item
    spectrumData.resize(0);
}

void Spectrum::cacheSpectrum()
{
    // cache audio pcm data to pixmap for fast rendering here
    if (spectrumCache && spectrumCache->size() != this->size())
    {
        delete spectrumCache;
        spectrumCache = 0;
    }

    if (!spectrumCache)
        spectrumCache = new QPixmap(this->size());

    spectrumCache->fill(Qt::white);

    if (!spectrumData.isEmpty())
    {
        QVector<QLineF> lines;
        QPointF prev, next;
        float hOff = 0;
        float hDelta = (float)width() / spectrumData.size();

        for (int i = 0; i < spectrumData.size(); ++i)
        {
            next.setX(hOff);
            next.setY((spectrumData[i] + 1.f) * (float)height() / 2.f);

            lines.append(QLineF(prev, next));

            hOff += hDelta;
            prev = next;
        }

        QPainter p(spectrumCache);
        p.drawLines(lines);
    }

    update();
}

void Spectrum::paintEvent(QPaintEvent *e)
{
    QPainter p(this);

    if (spectrumCache)
        p.drawPixmap(0, 0, *spectrumCache);
    else
    {
        QBrush brush(p.brush());
        brush.setStyle(Qt::Dense5Pattern);
        brush.setColor(QColor(0xffffeab2));

        p.setBrush(brush);
        p.drawRect(e->rect());

        p.drawText(e->rect(), "Here be spectrum!", QTextOption(Qt::AlignCenter));
    }
}

void Spectrum::resizeEvent(QResizeEvent *)
{
    cacheSpectrum();
}

void Spectrum::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasFormat("text/uri-list"))
        e->acceptProposedAction();
}

void Spectrum::dragMoveEvent(QDragMoveEvent *e)
{
    if (e->mimeData()->hasFormat("text/uri-list"))
        e->acceptProposedAction();
}

void Spectrum::dropEvent(QDropEvent *e)
{
    QList<QUrl> uris;

    foreach (const QByteArray &uriData, e->mimeData()->data("text/uri-list").split('\n'))
        if (!uriData.isEmpty())
            uris << QUrl::fromEncoded(uriData).toLocalFile().remove('\r');

    qDebug() << uris;

    QFileInfo fi(uris.first().toString());

    if (fi.exists() && !fi.isDir() && fi.suffix() == "wav") // accepting only first one, if it's a ".wav"
        emit audioDropped(fi.absoluteFilePath());
}

void Spectrum::loadWav(qtauAudioSource &a)
{
    if (audio)
        delete audio;

    audio = &a;
    cacheSpectrum();
}

void Spectrum::setSpectrumData(float *data, int len)
{
    if (data && len > 0)
    {
        spectrumData.clear();

        for (int i = 0; i < len; ++i)
            spectrumData.append(data[i]); // NOTE: this is very dangerous. Let's hope that len is correct

        cacheSpectrum();
    }
    else
        vsLog::e("Wrong spectrum data input! Ignoring...");
}
