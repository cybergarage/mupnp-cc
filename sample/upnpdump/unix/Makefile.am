noinst_PROGRAMS = upnpdump

INCLUDES = -I$(top_srcdir)/include -I../../common @XML_CFLAGS@

noinst_HEADERS = \
	../../common/InputUtil.h

upnpdump_SOURCES = \
	../upnpdump.cpp \
	../CtrlPoint.cpp \
	../../common/InputUtil.cpp

upnpdump_LDADD = ../../../lib/unix/libclink++.a @XML_LIBS@

