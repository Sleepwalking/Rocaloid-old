TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    Structure/String.c \
    Misc/Converter.c \
    IO/FileStream.c \
    IO/StringStream.c \
    Memory.c \
    IO/FileUtil.c \
    IO/Wave.c

HEADERS += \
    Structure/Array.h \
    Structure/String.h \
    Misc/Converter.h \
    IO/FileStream.h \
    IO/StringStream.h \
    Memory.h \
    IO/FileUtil.h \
    IO/Wave.h

