#-------------------------------------------------
#
# Project created by QtCreator 2013-11-18T19:52:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FormantMarker
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
    WaveBox.cpp \
    ../../../RUtil/IO/Wave.c \
    ../../../RUtil/IO/StringStream.c \
    ../../../RUtil/IO/FileUtil.c \
    ../../../RUtil/IO/FileStream.c \
    ../../../RUtil/Misc/Converter.c \
    ../../../RUtil/Structure/String.c \
    ../../../RocaloidEngine/CVE3/DSPEx/LCFECSOLA.c \
    ../TCFILE/WCONF.c \
    ../../../RocaloidEngine/RFILE3/RDL.c

HEADERS  += MainWindow.h \
    WaveBox.h \
    ../../../RUtil/RUtil.h \
    ../../../RUtil/IO/Wave.h \
    ../../../RUtil/IO/StringStream.h \
    ../../../RUtil/IO/FileUtil.h \
    ../../../RUtil/IO/FileStream.h \
    ../../../RUtil/Misc/Converter.h \
    ../../../RUtil/Structure/String.h \
    ../../../RUtil/Structure/Array.h \
    ../../../CVEDSP/Interpolation.h \
    ../../../CVEDSP/FrameProcessor.h \
    ../../../CVEDSP/Plot.h \
    ../../../CVEDSP/Tester.h \
    ../../../CVEDSP/DFT/StaticRev.h \
    ../../../CVEDSP/DFT/StaticFFT_Small.h \
    ../../../CVEDSP/DFT/StaticFFT_9.h \
    ../../../CVEDSP/DFT/StaticFFT_8.h \
    ../../../CVEDSP/DFT/StaticFFT_7.h \
    ../../../CVEDSP/DFT/StaticFFT_6.h \
    ../../../CVEDSP/DFT/StaticFFT_5.h \
    ../../../CVEDSP/DFT/SplitRadixGen.h \
    ../../../CVEDSP/DFT/SplitRadix.h \
    ../../../CVEDSP/DFT/Radix2Gen.h \
    ../../../CVEDSP/DFT/Radix2.h \
    ../../../CVEDSP/DFT/FFTCommon.h \
    ../../../CVEDSP/DFT/FFTBlock.h \
    ../../../CVEDSP/DFT/FFT.h \
    ../../../CVEDSP/DFT/DFT.h \
    ../../../CVEDSP/Algorithm/PSOLA.h \
    ../../../CVEDSP/Algorithm/Formant.h \
    ../../../CVEDSP/Algorithm/FECSOLA.h \
    ../../../CVEDSP/Algorithm/BaseFreq.h \
    ../../../CVEDSP/DSPBase/Window.h \
    ../../../CVEDSP/DSPBase/TDEffects.h \
    ../../../CVEDSP/DSPBase/TDAnalysis.h \
    ../../../CVEDSP/DSPBase/Spectrum.h \
    ../../../CVEDSP/DSPBase/LPC.h \
    ../../../CVEDSP/DSPBase/LinearWarping.h \
    ../../../CVEDSP/DSPBase/Filter.h \
    ../../../CVEDSP/DSPBase/ControlPointFilter.h \
    DSP.h \
    ../../../RocaloidEngine/CVE3/DSPEx/LCFECSOLA.h \
    CONFIO.h \
    ../TCFILE/WCONF.h \
    ../../../RocaloidEngine/RFILE3/RDL.h

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../CVEDSP/release/ -lCVEDSP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../CVEDSP/debug/ -lCVEDSP
else:unix: LIBS += -L$$PWD/../../../CVEDSP/ -lCVEDSP

INCLUDEPATH += $$PWD/../../../CVEDSP
DEPENDPATH += $$PWD/../../../CVEDSP

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../CVEDSP/release/CVEDSP.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../CVEDSP/debug/CVEDSP.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../CVEDSP/libCVEDSP.a
