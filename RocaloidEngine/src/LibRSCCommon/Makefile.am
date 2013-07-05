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

<<<<<<< HEAD:RocaloidEngine/src/LibRSCCommon/Makefile.am
libRSCCommon_la_CXXFLAGS = -I@top_srcdir@/src/ \
	-I@top_srcdir@/src/LibCyberBase/SPKit/ \
	-O2 \
	-g 
=======
libRSCCommon_la_CXXFLAGS = -I@top_srcdir@/src/LibCyberBase/ \
	-O2 \
	-Wall \
	-g \
	-I@top_srcdir@/src/ 
>>>>>>> 3480c544d2030e3528e5b80dd3777bbc9e7fc38e:RocaloidEngine/src/LibRSCCommon/Makefile.am

libRSCCommon_la_LDFLAGS = -lCyberBase \
	-L../LibCyberBase/.libs/ 
