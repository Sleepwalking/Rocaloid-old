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
#INTLTOOL_FILES = intltool-extract.in \
#	intltool-merge.in \
#	intltool-update.in

#EXTRA_DIST = $(rsccommondoc_DATA) \
#	$(INTLTOOL_FILES)

#DISTCLEANFILES = intltool-extract \
#	intltool-merge \
#	intltool-update \
#	po/.intltool-merge-cache


# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(rocaloidenginedocdir)
