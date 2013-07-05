## Process this file with automake to produce Makefile.in
## Created by Anjuta

SUBDIRS =  src

rocaloidenginedocdir = ${prefix}/doc/rocaloidengine
rocaloidenginedoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS


EXTRA_DIST = $(rocaloidenginedoc_DATA) 


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(rocaloidenginedocdir)
