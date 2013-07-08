
SUBDIRS = LibCyberBase LibCVSCommon LibRSCCommon LibCVE

rsctool_CXXFLAGS = -I@top_srcdir@/src/ \
	 -I@top_srcdir@/src/LibCyberBase/SPKit/ \
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
	rsctool

rsctool_SOURCES =  \
	main.cc

rsctool_LDFLAGS = -lCyberBase \
	-LLibCyberBase/.libs/ \
	-LLibCVSCommon/.libs/ \
	-lCVSCommon \
	-LLibRSCCommon/.libs/ \
	-lRSCCommon \
	-LLibCVE/.libs/ \
	-lCVE 

