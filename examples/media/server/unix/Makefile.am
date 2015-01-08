noinst_PROGRAMS = mediagate

INCLUDES = -I$(top_srcdir)/include -I../../../common -I../ @XML_CFLAGS@

noinst_HEADERS = \
	../MediaGate.h \
	../../../common/InputUtil.h

mediagate_SOURCES = \
	MediaGateMain.cpp \
	../MediaGate.cpp \
	../../../common/InputUtil.cpp

mediagate_LDADD = ../../../../lib/unix/libmupnp.a @XML_LIBS@
