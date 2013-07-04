## Process this file with automake to produce Makefile.in


lib_LTLIBRARIES =  \
	libRSCCommon.la
libRSCCommon_la_SOURCES =  \
	CDTCommon/CDTCommon.cc \
	CDTCommon/CDTCommon.h \
	RSCCommon.cc \
	RSCCommon.h \
	CDTCommon/CDTReader.h \
	CDTCommon/CDTReader.cc \
	RSCReader.cc \
	RSCReader.h

libRSCCommon_la_CXXFLAGS = -I@top_srcdir@/LibCyberBase/\
	-I@top_srcdir@/LibCVSCommon/ \
	-I@top_srcdir@/SPKit/ \
	-O2 \
	-Wall \
	-g 

libRSCCommon_la_LDFLAGS = -lCyberBase \
	-L../LibCyberBase/.libs/ 
