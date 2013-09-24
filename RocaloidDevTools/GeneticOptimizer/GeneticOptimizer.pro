TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    RUtil/Memory.c \
    RUtil/IO/Wave.c \
    RUtil/IO/StringStream.c \
    RUtil/IO/FileUtil.c \
    RUtil/IO/FileStream.c \
    RUtil/Misc/Converter.c \
    RUtil/Structure/String.c \
    GeneticSimulator.c \
    GFormant/GFormant.c \
    GPitch/GPitch.c

HEADERS += \
    CVEDSP/Interpolation.h \
    CVEDSP/FrameProcessor.h \
    CVEDSP/Plot.h \
    CVEDSP/Tester.h \
    CVEDSP/DFT/StaticRev.h \
    CVEDSP/DFT/StaticFFT_Small.h \
    CVEDSP/DFT/StaticFFT_11.h \
    CVEDSP/DFT/StaticFFT_10.h \
    CVEDSP/DFT/StaticFFT_9.h \
    CVEDSP/DFT/StaticFFT_8.h \
    CVEDSP/DFT/StaticFFT_7.h \
    CVEDSP/DFT/StaticFFT_6.h \
    CVEDSP/DFT/StaticFFT_5.h \
    CVEDSP/DFT/SplitRadixGen.h \
    CVEDSP/DFT/SplitRadix.h \
    CVEDSP/DFT/Radix2Gen.h \
    CVEDSP/DFT/Radix2.h \
    CVEDSP/DFT/FFTCommon.h \
    CVEDSP/DFT/FFTBlock.h \
    CVEDSP/DFT/FFT.h \
    CVEDSP/DFT/DFT.h \
    CVEDSP/FreqDomain/Spectrum.h \
    CVEDSP/FreqDomain/LPC.h \
    CVEDSP/FreqDomain/LinearWarping.h \
    CVEDSP/FreqDomain/Formant.h \
    CVEDSP/FreqDomain/Filter.h \
    CVEDSP/FreqDomain/FECSOLA.h \
    CVEDSP/FreqDomain/FDAnalysis.h \
    CVEDSP/FreqDomain/ControlPointFilter.h \
    CVEDSP/IntrinUtil/Memory.h \
    CVEDSP/IntrinUtil/LogicArray.h \
    CVEDSP/IntrinUtil/IntArray.h \
    CVEDSP/IntrinUtil/FloatArray.h \
    CVEDSP/IntrinUtil/Calculation.h \
    CVEDSP/TimeDomain/Window.h \
    CVEDSP/TimeDomain/TDEffects.h \
    CVEDSP/TimeDomain/TDAnalysis.h \
    CVEDSP/TimeDomain/PSOLA.h \
    RUtil/RUtil.h \
    RUtil/Memory.h \
    RUtil/IO/Wave.h \
    RUtil/IO/StringStream.h \
    RUtil/IO/FileUtil.h \
    RUtil/IO/FileStream.h \
    RUtil/Misc/Converter.h \
    RUtil/Structure/String.h \
    RUtil/Structure/Array.h \
    GeneticSimulator.h \
    GFormant/GFormant.h \
    GPitch/GPitch.h


unix:!macx: LIBS += -L$$PWD/CVEDSP/ -lCVEDSP

INCLUDEPATH += $$PWD/CVEDSP
DEPENDPATH += $$PWD/CVEDSP

unix:!macx: PRE_TARGETDEPS += $$PWD/CVEDSP/libCVEDSP.a
