#ifndef WAVEBOX_H
#define WAVEBOX_H

#include <QWidget>
#include "../../../RUtil/RUtil.h"

AutoClass
{
    int Size;
    ArrayType_Define(float*, SubWave);
} EndClass(WaveSet);

extern void WaveSet_CtorSize(WaveSet* Dest, int Size);
extern void WaveSet_SetWaveNum(WaveSet* Dest, int Num);

class WaveBox : public QWidget
{
    Q_OBJECT
public:
    WaveBox(QWidget *parent = 0);
    ~WaveBox();
    void SetWaveSize(int Size);
    void SetWaveNum(int Num);
    void LoadWave(float* Src, int Index);
    void Redraw();

    
signals:
    
public slots:

protected:
    void paintEvent(QPaintEvent *event);
    
private:
    WaveSet WaveList;
    QPainter* Canvas;
};

#endif // WAVEBOX_H
