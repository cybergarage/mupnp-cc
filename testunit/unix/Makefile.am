noinst_PROGRAMS = clinktestunit

INCLUDES = -I$(top_srcdir)/include -I../ @XML_CFLAGS@

noinst_HEADERS = \
	../TestCtrlPoint.h \
	../TestDevice.h \
	../TestHTTPServer.h \
	../TestMediaServer.h \
	../UPnPTestCase.h

clinktestunit_SOURCES = \
	../clinktestunit.cpp \
	../TestCtrlPoint.cpp \
	../TestDevice.cpp \
	../TestHTTPServer.cpp \
	../TestMediaServer.cpp \
	../UPnPTestCase.cpp 

clinktestunit_LDADD = ../../lib/unix/libclink++.a -lcppunit -ldl @XML_LIBS@
