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

libRSCCommon_la_CXXFLAGS = -I@top_srcdir@/src/LibCyberBase/ \
	-O2 \
	-Wall \
	-g \
	-I@top_srcdir@/src/ 

libRSCCommon_la_LDFLAGS = -lCyberBase \
	-L../LibCyberBase/.libs/ 
