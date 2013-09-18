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
    CVDB3/CVDB3IO.c \
    CDT3/Demapper.c \
    CDT3/CDT3Reader.c \
    CDT3/CDT3.c \
    CVS3/CVSRDLWriter.c \
    CVS3/CVSRDLReader.c \
    CVS3/CVS3.c \
    RDL.c

HEADERS += \
    RUtil/Memory.h \
    RUtil/IO/Wave.h \
    RUtil/IO/StringStream.h \
    RUtil/IO/FileUtil.h \
    RUtil/IO/FileStream.h \
    RUtil/Misc/Converter.h \
    RUtil/Structure/String.h \
    RUtil/Structure/Array.h \
    CVDB3/CVDB3IO.h \
    CDT3/Demapper.h \
    CDT3/CDT3Reader.h \
    CDT3/CDT3.h \
    RDL.h \
    RUtil/RUtil.h \
    CVS3/CVSRDLWriter.h \
    CVS3/CVSRDLReader.h \
    CVS3/CVS3.h

