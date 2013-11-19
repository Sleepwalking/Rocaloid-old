#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QLabel>
#include "WaveBox.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void resizeEvent(QResizeEvent * event);
    void dropEvent(QDropEvent * event);
    void dragEnterEvent(QDragEnterEvent *);

private slots:
    void UpdateFilter(int);

private:
    WaveBox* InnerWaveBox;
    QSlider* F1Slider;
    QSlider* F2Slider;
    QSlider* F3Slider;
    QSlider* S1Slider;
    QSlider* S2Slider;
    QSlider* S3Slider;
    QSlider* SSlider;
    QLabel* StatusLabel;
};

#endif // MAINWINDOW_H
