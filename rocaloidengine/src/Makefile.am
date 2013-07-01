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

rsctool_CFLAGS = -O2 \
	-Wall \
	-g 

rsctool_LDFLAGS = -lCyberBase \
	-L../LibCyberBase/.libs/ 

SUBDIRS = \
	../LibCyberBase/
