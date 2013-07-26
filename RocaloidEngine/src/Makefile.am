
SUBDIRS = LibCyberBase LibCVSCommon LibCVE

rsctool_CXXFLAGS = -I@top_srcdir@/src/ \
	 -I@top_srcdir@/src/LibCyberBase/ \
	 -O2 \
	 -Wall \
	 -g

## Process this file with automake to produce Makefile.in

.AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


bin_PROGRAMS =  \
	rsctool \
	cvecli

rsctool_SOURCES =  \
	main.cc \
	LibRSCCommon/RSCCommon.h \
	LibRSCCommon/RSCCommon.cc \
	LibRSCCommon/RSCWriter.h \
	LibRSCCommon/RSCWriter.cc \
	LibRSCCommon/RSCReader.h \
	LibRSCCommon/RSCReader.cc \
	LibCVSCommon/CVSWriter.h \
	LibCVSCommon/CVSWriter.cc \
	LibCVSCommon/CVSReader.cc \
	LibCVSCommon/CVSReader.h \
	LibCVSCommon/CVSCommon.cc \
	LibCVSCommon/CVSCommon.h \
	LibRSCCommon/CDTCommon/CDTCommon.h \
	LibRSCCommon/CDTCommon/CDTCommon.cc \
	LibRSCCommon/CDTCommon/CDTReader.cc \
	LibRSCCommon/CDTCommon/CDTReader.h \
	LibRSCCommon/VSQXCommon/VSQXReader.cc \
	LibRSCCommon/VSQXCommon/VSQ3Reader.cc \
	LibRSCCommon/VSQXCommon/VSQXReader.h \
	LibRSCCommon/VSQXCommon/VSQ3Reader.h \
	LibRSCCommon/CVSGenerator/Generator.cc \
	LibRSCCommon/CVSGenerator/Rearrager.cc \
	LibRSCCommon/CVSGenerator/Rearrager.h \
	LibRSCCommon/CVSGenerator/Generator.h \
	LibRSCCommon/CVSGenerator/TransitionGen.cc \
	LibRSCCommon/CVSGenerator/TransitionGen.h \
	LibRSCCommon/CVSGenerator/EffectGen.h \
	LibRSCCommon/CVSGenerator/EffectGen.cc

rsctool_LDFLAGS = -static \
	-lCyberBase \
	-LLibCyberBase/.libs/ \
	-LLibCVSCommon/.libs/ \
	-lCVSCommon \
	-LLibCVE/.libs/ \
	-lCVE# \
	-LLibRSCCommon/.libs/ \
	-lRSCCommon \
	-LLibCVE/.libs/ \
	-lCVE 

cvecli_SOURCES =  \
	cve_main.cc \
	cve_main.h

cvecli_CXXFLAGS = -I@top_srcdir@/src/ \
	-I@top_srcdir@/src/LibCyberBase/ \
	-O2 \
	-Wall \
	-g 

cvecli_LDFLAGS = -static \
	-lCyberBase \
	-LLibCyberBase/.libs/ \
	-LLibCVSCommon/.libs/ \
	-lCVSCommon \
	-LLibCVE/.libs/ \
	-lCVE 

