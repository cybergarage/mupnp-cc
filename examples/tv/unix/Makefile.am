noinst_PROGRAMS = upnptv

INCLUDES = -I$(top_srcdir)/include -I../ -I../../common @XML_CFLAGS@ @GTK_CFLAGS@ @GDK_IMLIB_CFLAGS@

noinst_HEADERS = \
	../../common/InputUtil.h

upnptv_SOURCES = \
	TvMain.cpp \
	../TvDevice.cpp \
	../../common/InputUtil.cpp

upnptv_LDADD = ../../../lib/unix/libclink++.a @XML_LIBS@ @GTK_LIBS@ @GDK_IMLIB_LIBS@

