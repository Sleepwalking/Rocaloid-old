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
    ../../../RocaloidEngine/RFILE3/RDL.h

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
    ../../../RocaloidEngine/RFILE3/RDL.c
