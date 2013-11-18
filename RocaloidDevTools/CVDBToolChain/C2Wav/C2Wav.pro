TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    main.c \
    ../../../RUtil/Memory.c \
    ../../../RUtil/IO/Wave.c \
    ../../../RUtil/IO/StringStream.c \
    ../../../RUtil/IO/FileUtil.c \
    ../../../RUtil/IO/FileStream.c \
    ../../../RUtil/Misc/Converter.c \
    ../../../RUtil/Structure/String.c \
    ../../../RocaloidEngine/RFILE3/CVDB3/CVDB3IO.c

HEADERS += \
    ../../../RUtil/RUtil.h \
    ../../../RUtil/Memory.h \
    ../../../RUtil/IO/Wave.h \
    ../../../RUtil/IO/StringStream.h \
    ../../../RUtil/IO/FileUtil.h \
    ../../../RUtil/IO/FileStream.h \
    ../../../RUtil/Misc/Converter.h \
    ../../../RUtil/Structure/String.h \
    ../../../RUtil/Structure/Array.h \
    ../../../RocaloidEngine/RFILE3/CVDB3/CVDB3IO.h
