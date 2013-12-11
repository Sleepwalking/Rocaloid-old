#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSlider>
#include <QLabel>
#include <QListView>
#include <QStandardItem>
#include "WaveBox.h"

class MainWindow : public QWidget
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SetFormant(float F1, float F2, float F3, float S1, float S2, float S3, float Mul);

protected:
    void resizeEvent(QResizeEvent * event);
    void dropEvent(QDropEvent * event);
    void dragEnterEvent(QDragEnterEvent *);

private slots:
    void UpdateFilter(int);
    void CONFSelect(QModelIndex);
    void WCONFSave();
    void ScaleIn();
    void ScaleOut();

private:
    QStandardItemModel* CONFModel;
    QListView* CONFList;
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
