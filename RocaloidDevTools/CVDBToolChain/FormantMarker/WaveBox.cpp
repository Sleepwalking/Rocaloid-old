#include "WaveBox.h"
#include <malloc.h>
#include <QPainter>

_Constructor_ (WaveSet)
{
    WaveSet_CtorSize(Dest, 512);
}

_Destructor_ (WaveSet)
{
    int i;
    for(i = 0; i <= Dest -> SubWave_Index; i ++)
        free(Dest -> SubWave[i]);
    ArrayType_Dtor(float*, Dest -> SubWave);
}

void WaveSet_CtorSize(WaveSet *Dest, int Size)
{
    ArrayType_Init(float*, Dest -> SubWave);
    Dest -> Size = Size;
}

void WaveSet_SetWaveNum(WaveSet *Dest, int Num)
{
    int i;
    for(i = 0; i <= Dest -> SubWave_Index; i ++)
        free(Dest -> SubWave[i]);
    ArrayType_Resize(float*, Dest -> SubWave, Num);
    Dest -> SubWave_Index = Num - 1;
    for(i = 0; i <= Dest -> SubWave_Index; i ++)
        Dest -> SubWave[i] = (float*)malloc(sizeof(float) * Dest -> Size);
}

WaveBox::WaveBox(QWidget *parent) :
    QWidget(parent)
{
    WaveSet_Ctor(& this -> WaveList);
}

WaveBox::~WaveBox()
{
    WaveSet_Dtor(& this -> WaveList);
}

void WaveBox::SetWaveSize(int Size)
{
    WaveSet_Dtor(& this -> WaveList);
    WaveSet_CtorSize(& this -> WaveList, Size);
}

void WaveBox::SetWaveNum(int Num)
{
    WaveSet_SetWaveNum(& this -> WaveList, Num);
}

void WaveBox::LoadWave(float *Src, int Index)
{
    int i;
    for(i = 0; i < this -> WaveList.Size; i ++)
        this -> WaveList.SubWave[Index][i] = Src[i];
}

void WaveBox::Redraw()
{
    update();
}

#define IndexToPos
void WaveBox::paintEvent(QPaintEvent*)
{
    int i, j;
    int Width = this -> width();
    int Height = this -> height();
    QPainter Canvas(this);
    Canvas.fillRect(0, 0, Width, Height, QColor(255, 255, 255));
    for(i = 0; i <= this -> WaveList.SubWave_Index; i ++)
    {
        switch(i)
        {
        case 0:
            Canvas.setPen(QColor(0, 0, 0));
            break;
        case 1:
            Canvas.setPen(QColor(255, 0, 0));
            break;
        case 2:
            Canvas.setPen(QColor(0, 255, 0));
            break;
        case 3:
            Canvas.setPen(QColor(0, 0, 255));
            break;
        }

        for(j = 0; j < this -> WaveList.Size - 1; j ++)
        {
            int x1 = j * Width / this -> WaveList.Size;
            int x2 = (j + 1) * Width / this -> WaveList.Size;
            float y1 = this -> WaveList.SubWave[i][j];
            float y2 = this -> WaveList.SubWave[i][j + 1];
            Canvas.drawLine(x1, (1.0f - y1) * Height,
                            x2, (1.0f - y2) * Height);
        }
    }
}
