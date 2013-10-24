<<<<<<< HEAD
if UNITTESTS
SUBDIRS = include lib unittest examples
else
SUBDIRS = include lib examples
endif
=======
SUBDIRS = include lib sample
#SUBDIRS = include lib sample testunit

devdocsdir = $(datadir)/doc/clinkcc-dev

nobase_devdocs_DATA = \
	doxygen/html/*

doxygen/html/*:
	cd $(srcdir) && doxygen Doxyfile
# scp -r doxygen skonno,clinkcc@frs.sourceforge.net:/home/groups/c/cl/clinkcc/htdocs
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
