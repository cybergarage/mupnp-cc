SUBDIRS = include lib sample
#SUBDIRS = include lib sample testunit

devdocsdir = $(datadir)/doc/clinkcc-dev

nobase_devdocs_DATA = \
	doxygen/html/*

doxygen/html/*:
	cd $(srcdir) && doxygen Doxyfile
# scp -r doxygen skonno,clinkcc@frs.sourceforge.net:/home/groups/c/cl/clinkcc/htdocs
