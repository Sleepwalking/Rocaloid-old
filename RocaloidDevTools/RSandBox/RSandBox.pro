TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -O3 -msse -ffast-math -lm

SOURCES += main.c \
    RUtil/Memory.c \
    RUtil/IO/Wave.c \
    RUtil/IO/StringStream.c \
    RUtil/IO/FileUtil.c \
    RUtil/IO/FileStream.c \
    RUtil/Misc/Converter.c \
    RUtil/Structure/String.c \
    RFILE3/RDL.c \
    RFILE3/CDT3/Demapper.c \
    RFILE3/CDT3/CDT3Reader.c \
    RFILE3/CDT3/CDT3.c \
    RFILE3/CVDB3/CVDB3IO.c \
    RFILE3/CVS3/CVSRDLWriter.c \
    RFILE3/CVS3/CVSRDLReader.c \
    RFILE3/CVS3/CVS3.c \
    CVEANN/Rand.c \
    CVEANN/Activator.c \
    CVEANN/Network/SOFM.c \
    CVEANN/Network/LVQ.c \
    CVEANN/Network/FeedForwardMomentum.c \
    CVEANN/Network/FeedForward.c \
    CVEANN/Trainer/Trainer_SOFM.c \
    CVEANN/Trainer/Trainer_LVQ.c \
    CVEANN/Trainer/Trainer_FeedForward.c \
    CVEANN/Trainer/Trainer_BPMomentum.c

HEADERS += \
    RUtil/RUtil.h \
    RUtil/Memory.h \
    RUtil/IO/Wave.h \
    RUtil/IO/StringStream.h \
    RUtil/IO/FileUtil.h \
    RUtil/IO/FileStream.h \
    RUtil/Misc/Converter.h \
    RUtil/Structure/String.h \
    RUtil/Structure/Array.h \
    RFILE3/RDL.h \
    RFILE3/CDT3/Demapper.h \
    RFILE3/CDT3/CDT3Reader.h \
    RFILE3/CDT3/CDT3.h \
    RFILE3/CVDB3/CVDB3IO.h \
    RFILE3/CVS3/CVSRDLWriter.h \
    RFILE3/CVS3/CVSRDLReader.h \
    RFILE3/CVS3/CVS3.h \
    CVEANN/Rand.h \
    CVEANN/Activator.h \
    CVEANN/Network/SOFM.h \
    CVEANN/Network/LVQ.h \
    CVEANN/Network/FeedForwardMomentum.h \
    CVEANN/Network/FeedForward.h \
    CVEANN/Trainer/Trainer_SOFM.h \
    CVEANN/Trainer/Trainer_LVQ.h \
    CVEANN/Trainer/Trainer_FeedForward.h \
    CVEANN/Trainer/Trainer_BPMomentum.h \
    CVEDSP/Interpolation.h \
    CVEDSP/FrameProcessor.h \
    CVEDSP/Plot.h \
    CVEDSP/Tester.h \
    CVEDSP/DFT/StaticRev.h \
    CVEDSP/DFT/StaticFFT_Small.h \
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
    CVEDSP/Algorithm/PSOLA.h \
    CVEDSP/Algorithm/Formant.h \
    CVEDSP/Algorithm/FECSOLA.h \
    CVEDSP/Algorithm/BaseFreq.h \
    CVEDSP/DSPBase/Window.h \
    CVEDSP/DSPBase/TDEffects.h \
    CVEDSP/DSPBase/TDAnalysis.h \
    CVEDSP/DSPBase/Spectrum.h \
    CVEDSP/DSPBase/LPC.h \
    CVEDSP/DSPBase/LinearWarping.h \
    CVEDSP/DSPBase/Filter.h \
    CVEDSP/DSPBase/ControlPointFilter.h \


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/CVEDSP/release/ -lCVEDSP
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/CVEDSP/debug/ -lCVEDSP
else:unix: LIBS += -L$$PWD/CVEDSP/ -lCVEDSP

INCLUDEPATH += $$PWD/CVEDSP
DEPENDPATH += $$PWD/CVEDSP

win32:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/CVEDSP/release/CVEDSP.lib
else:win32:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/CVEDSP/debug/CVEDSP.lib
else:unix: PRE_TARGETDEPS += $$PWD/CVEDSP/libCVEDSP.a
