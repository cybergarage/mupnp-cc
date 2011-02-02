noinst_PROGRAMS = upnpclock

INCLUDES = -I$(top_srcdir)/include -I../ -I../../common @XML_CFLAGS@ @GTK_CFLAGS@ @GDK_IMLIB_CFLAGS@

noinst_HEADERS = \
	../../common/InputUtil.h

upnpclock_SOURCES = \
	ClockMain.cpp \
	../Clock.cpp \
	../ClockDevice.cpp \
	../../common/InputUtil.cpp

upnpclock_LDADD = ../../../lib/unix/libclink.a @XML_LIBS@ @GTK_LIBS@ @GDK_IMLIB_LIBS@

