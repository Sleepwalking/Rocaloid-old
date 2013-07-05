
SUBDIRS = LibCyberBase LibCVSCommon LibRSCCommon LibCVE

rsctool_CXXFLAGS = -I@top_srcdir@/src/ \
	 -I@top_srcdir@/src/LibCyberBase/SPKit/ \
	 -O2 \
	-Wall \
<<<<<<< HEAD
	-g
=======
	-g  \
	-I@top_srcdir@/src/LibCVSCommon/ \
	 -I@top_srcdir@/LibCyberBase/ \
	 -I@top_srcdir@/src/LibRSCCommon/ \
	 -I@top_srcdir@/SPKit/
>>>>>>> 3480c544d2030e3528e5b80dd3777bbc9e7fc38e
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
	-lRSCCommon 

