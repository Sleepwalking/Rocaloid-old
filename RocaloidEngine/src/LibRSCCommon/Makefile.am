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
	RSCWriter.cc \
	RSCWriter.h \
	RSCReader.cc \
	RSCReader.h \
	VSQXCommon/VSQ3Reader.cc \
	VSQXCommon/VSQ3Reader.h \
	VSQXCommon/VSQXReader.h \
	VSQXCommon/VSQXReader.cc \
	CVSGenerator/EffectGen.h \
	CVSGenerator/EffectGen.cc \
	CVSGenerator/Generator.cc \
	CVSGenerator/Generator.h \
	CVSGenerator/Rearrager.cc \
	CVSGenerator/Rearrager.h \
	CVSGenerator/TransitionGen.cc \
	CVSGenerator/TransitionGen.h

libRSCCommon_la_CXXFLAGS = -I@top_srcdir@/src/ \
	-I@top_srcdir@/src/LibCyberBase/SPKit/ \
	-O2 \
	-g 

libRSCCommon_la_LDFLAGS = -lCyberBase \
	-L../LibCyberBase/.libs/ 
