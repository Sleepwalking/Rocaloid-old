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
    Routines.h \
    ../TCFILE/WCONF.h \
    ../TCFILE/SCONF.h \
    ../TCFILE/CDS.h \
    ../../../RocaloidEngine/RFILE3/RDL.h \
    GenCDT.h \
    ../../../RocaloidEngine/RFILE3/CDT3/CDT3Writer.h \
    ../../../RocaloidEngine/RFILE3/CDT3/CDT3.h \
    ../../../RocaloidEngine/RFILE3/CVDB3/CVDB3IO.h \
    ../../../RUtil/IO/FilePath.h

SOURCES += \
    ../../../RUtil/IO/Wave.c \
    ../../../RUtil/IO/StringStream.c \
    ../../../RUtil/IO/FileUtil.c \
    ../../../RUtil/IO/FileStream.c \
    ../../../RUtil/Misc/Converter.c \
    ../../../RUtil/Structure/String.c \
    main.c \
    Routines.c \
    ../TCFILE/WCONF.c \
    ../TCFILE/SCONF.c \
    ../TCFILE/CDS.c \
    ../../../RocaloidEngine/RFILE3/RDL.c \
    ../../../RocaloidEngine/RFILE3/CDT3/CDT3Writer.c \
    ../../../RocaloidEngine/RFILE3/CDT3/CDT3.c \
    ../../../RocaloidEngine/RFILE3/CVDB3/CVDB3IO.c \
    ../../../RUtil/IO/FilePath.c
