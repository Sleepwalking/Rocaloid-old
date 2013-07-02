

rsctool_CXXFLAGS = -O2 \
	-Wall \
	-g  \
	-I@top_srcdir@/LibCVSCommon/ \
	 -I@top_srcdir@/LibCyberBase/ \
	 -I@top_srcdir@/SPKit/ \
	 -DCVSCOMMON_DEBUG \
	 -DMEMCHECK
## Process this file with automake to produce Makefile.in

.AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g


bin_PROGRAMS =  \
	rsctool

rsctool_SOURCES =  \
	main.cc \
	CVSCommon.cc \
	CVSCommon.h \
	CVSReader.cc \
	CVSReader.h \
	CVSWriter.cc \
	CVSWriter.h \
	../LibCyberBase/Overall.cc \
	../LibCyberBase/Overall.h \
	../LibCyberBase/RDLIO.cc \
	../LibCyberBase/RDLIO.h \
	../SPKit/structure/string.cc \
	../SPKit/structure/string.h \
	../SPKit/misc/converter.cc \
	../SPKit/misc/converter.h \
	../SPKit/misc/listopr.h \
	../SPKit/misc/memopr.h \
	../SPKit/io/fileStream.cc \
	../SPKit/io/fileStream.h \
	../SPKit/io/memoryStream.cc \
	../SPKit/io/memoryStream.h \
	../SPKit/io/stringStream.cc \
	../SPKit/io/stringStream.h \
	../SPKit/io/terminal.cc \
	../SPKit/io/terminal.h \
	../SPKit/defs.h

rsctool_LDFLAGS = -L../LibCyberBase/.libs/ \
	-L../LibCVSCommon/.libs/ 

SUBDIRS = \
	../LibCyberBase/ \
	../LibCVSCommon/
