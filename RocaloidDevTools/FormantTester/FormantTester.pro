QT += core widgets network multimedia

TARGET = FormantTester
TEMPLATE = app

INCLUDEPATH = ../..

HEADERS = \
    FormantTester.h \
    spectrum.h \
    QTau/qtau/editor/audio/Source.h \
    QTau/qtau/editor/audio/Player.h \
    QTau/qtau/editor/audio/CodecBase.h \
    QTau/qtau/editor/audio/Codec.h \
    QTau/qtau/editor/Utils.h \
    Interface.h \
    QTau/qtau/tools/ffft/OscSinCos.hpp \
    QTau/qtau/tools/ffft/OscSinCos.h \
    QTau/qtau/tools/ffft/FFTRealUseTrigo.hpp \
    QTau/qtau/tools/ffft/FFTRealUseTrigo.h \
    QTau/qtau/tools/ffft/FFTRealSelect.hpp \
    QTau/qtau/tools/ffft/FFTRealSelect.h \
    QTau/qtau/tools/ffft/FFTRealPassInverse.hpp \
    QTau/qtau/tools/ffft/FFTRealPassInverse.h \
    QTau/qtau/tools/ffft/FFTRealPassDirect.hpp \
    QTau/qtau/tools/ffft/FFTRealPassDirect.h \
    QTau/qtau/tools/ffft/FFTRealFixLenParam.h \
    QTau/qtau/tools/ffft/FFTRealFixLen.hpp \
    QTau/qtau/tools/ffft/FFTRealFixLen.h \
    QTau/qtau/tools/ffft/FFTReal.hpp \
    QTau/qtau/tools/ffft/FFTReal.h \
    QTau/qtau/tools/ffft/DynArray.hpp \
    QTau/qtau/tools/ffft/DynArray.h \
    QTau/qtau/tools/ffft/def.h \
    QTau/qtau/tools/ffft/Array.hpp \
    QTau/qtau/tools/ffft/Array.h \
    CVEDSP/Tester.h \
    CVEDSP/Plot.h \
    CVEDSP/Interpolation.h \
    CVEDSP/FrameProcessor.h \
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
    CVEDSP/DFT/FFTBlock.h \
    CVEDSP/DFT/FFTCommon.h \
    CVEDSP/DFT/FFT.h \
    CVEDSP/DFT/DFT.h \
    RUtil/IO/Wave.h \
    RUtil/IO/StringStream.h \
    RUtil/IO/FileUtil.h \
    RUtil/IO/FileStream.h \
    RUtil/Misc/Converter.h \
    RUtil/Structure/Array.h \
    RUtil/Structure/String.h \
    RUtil/RUtil.h \
    RUtil/Memory.h \
    CVEDSP/Algorithm/PSOLA.h \
    CVEDSP/Algorithm/Formant.h \
    CVEDSP/Algorithm/FECSOLA.h \
    CVEDSP/Algorithm/BaseFreq.h \
    CVEDSP/DSPBase/LPC.h \
    CVEDSP/DSPBase/Window.h \
    CVEDSP/DSPBase/TDEffects.h \
    CVEDSP/DSPBase/TDAnalysis.h \
    CVEDSP/DSPBase/Spectrum.h \
    CVEDSP/DSPBase/LPC.h \
    CVEDSP/DSPBase/LinearWarping.h \
    CVEDSP/DSPBase/Filter.h \
    CVEDSP/DSPBase/ControlPointFilter.h

SOURCES = \
    main.cpp \
    FormantTester.cpp \
    spectrum.cpp \
    QTau/qtau/editor/audio/Source.cpp \
    QTau/qtau/editor/audio/Player.cpp \
    QTau/qtau/editor/audio/CodecBase.cpp \
    QTau/qtau/editor/audio/Codec.cpp \
    QTau/qtau/editor/Utils.cpp \
    Interface.cpp \
    RUtil/IO/Wave.c \
    RUtil/IO/StringStream.c \
    RUtil/IO/FileUtil.c \
    RUtil/IO/FileStream.c \
    RUtil/Misc/Converter.c \
    RUtil/Structure/String.c \
    RUtil/Memory.c \

QMAKE_CXXFLAGS += -Wunused-parameter

FORMS += \
    FormantTester_window.ui

RESOURCES += \
    res.qrc

LIBS += -L$$PWD/CVEDSP/ -lCVEDSP

INCLUDEPATH += $$PWD/CVEDSP
DEPENDPATH += $$PWD/CVEDSP

OTHER_FILES +=
