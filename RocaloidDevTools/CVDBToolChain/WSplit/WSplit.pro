TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

HEADERS += \
    ../../../RUtil/IO/Wave.h \
    ../../../RUtil/IO/StringStream.h \
    ../../../RUtil/IO/FileUtil.h \
    ../../../RUtil/IO/FileStream.h \
    ../../../RUtil/Misc/Converter.h \
    ../../../RUtil/Structure/String.h \
    ../../../RUtil/Structure/Array.h \
    ../../../RUtil/RUtil.h \
    ../TCFILE/WCONF.h \
    ../TCFILE/SCONF.h \
    ../TCFILE/CDS.h \
    ../../../RocaloidEngine/RFILE3/RDL.h \
    ../../../CVEDSP/Tester.h \
    ../../../CVEDSP/Plot.h \
    ../../../CVEDSP/Interpolation.h \
    ../../../CVEDSP/FrameProcessor.h \
    ../../../CVEDSP/Algorithm/SpeechDetector.h \
    ../../../CVEDSP/Algorithm/PSOLA.h \
    ../../../CVEDSP/Algorithm/Formant.h \
    ../../../CVEDSP/Algorithm/FECSOLA.h \
    ../../../CVEDSP/Algorithm/BaseFreq.h \
    ../../../CVEDSP/DFT/StaticFFT_9.h \
    ../../../CVEDSP/DFT/StaticFFT_Small.h \
    ../../../CVEDSP/DFT/StaticRadix.h \
    ../../../CVEDSP/DFT/StaticRev.h \
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
    ../../../CVEDSP/DSPBase/Window.h \
    ../../../CVEDSP/DSPBase/TDAnalysis.h \
    ../../../CVEDSP/DSPBase/TDEffects.h \
    ../../../CVEDSP/DSPBase/Spectrum.h \
    ../../../CVEDSP/DSPBase/LPC.h \
    ../../../CVEDSP/DSPBase/LinearWarping.h \
    ../../../CVEDSP/DSPBase/Filter.h \
    ../../../CVEDSP/DSPBase/ControlPointFilter.h \
    ../../../CVEDSP/IntrinUtil/Memory.h \
    ../../../CVEDSP/IntrinUtil/LogicArray.h \
    ../../../CVEDSP/IntrinUtil/IntArray.h \
    ../../../CVEDSP/IntrinUtil/FloatArray.h \
    ../../../CVEDSP/IntrinUtil/Calculation.h \
    Spliter.h \
    Scanner.h

SOURCES += \
    ../../../RUtil/IO/Wave.c \
    ../../../RUtil/IO/StringStream.c \
    ../../../RUtil/IO/FileUtil.c \
    ../../../RUtil/IO/FileStream.c \
    ../../../RUtil/Misc/Converter.c \
    ../../../RUtil/Structure/String.c \
    main.c \
    ../TCFILE/WCONF.c \
    ../TCFILE/SCONF.c \
    ../TCFILE/CDS.c \
    ../../../RocaloidEngine/RFILE3/RDL.c \
    Spliter.c \
    Scanner.c



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../CVEDSP/release/ -lCVEDSP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../CVEDSP/debug/ -lCVEDSP
else:unix: LIBS += -L$$PWD/../../../CVEDSP/ -lCVEDSP

INCLUDEPATH += $$PWD/../../../CVEDSP
DEPENDPATH += $$PWD/../../../CVEDSP

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../../../CVEDSP/release/CVEDSP.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../../../CVEDSP/debug/CVEDSP.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../CVEDSP/libCVEDSP.a
