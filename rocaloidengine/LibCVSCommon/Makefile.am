## Process this file with automake to produce Makefile.in


lib_LTLIBRARIES =  \
	libCVSCommon.la

#libCVSCommon_la_CXXFLAGS = 

libCVSCommon_la_SOURCES =  \
	CVSCommon.cc \
	CVSCommon.h \
	CVSReader.cc \
	CVSReader.h \
	CVSWriter.cc \
	CVSWriter.h

libCVSCommon_la_CXXFLAGS = -I@top_srcdir@/LibCyberBase/ \
	-I@top_srcdir@/SPKit/ \
	-O2 \
	-Wall \
	-g 
