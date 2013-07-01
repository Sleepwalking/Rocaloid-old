

rsctool_CXXFLAGS = -O2 \
	-Wall \
	-g  \
	-I@top_srcdir@/LibCVSCommon/ \
	 -I@top_srcdir@/LibCyberBase/ \
	 -I@top_srcdir@/SPKit/
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
	main.cc

rsctool_LDFLAGS = -lCyberBase \
	-L../LibCyberBase/.libs/ \
	-L../LibCVSCommon/.libs/ \
	-lCVSCommon 

SUBDIRS = \
	../LibCyberBase/ \
	../LibCVSCommon/
