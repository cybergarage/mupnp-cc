noinst_PROGRAMS = serverdump

INCLUDES = -I$(top_srcdir)/include -I../../../common @XML_CFLAGS@

noinst_HEADERS = \
	../../../common/InputUtil.h

serverdump_SOURCES = \
	../serverdump.cpp \
	../../../common/InputUtil.cpp

serverdump_LDADD = ../../../../lib/unix/libclink.a @XML_LIBS@

