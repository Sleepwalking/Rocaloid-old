## Process this file with automake to produce Makefile.in

## Created by Anjuta

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = spkit

spkit_SOURCES = \
	main.cc \
	structure/array.h \
	defs.h \
	misc/listopr.h \
	io/fileStream.h \
	io/fileStream.cc \
	structure/string.cc \
	structure/string.h \
	misc/converter.cc \
	misc/converter.h \
	misc/memopr.h \
	io/memoryStream.h \
	io/stringStream.h \
	io/terminal.h \
	structure/array.cc \
	io/stringStream.cc \
	io/memoryStream.cc \
	io/terminal.cc

spkit_LDFLAGS = 

spkit_LDADD = 


SUBDIRS = \
	structure \
	misc \
	io
