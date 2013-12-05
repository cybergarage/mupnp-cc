noinst_PROGRAMS = clinktestunit

INCLUDES = -I$(top_srcdir)/include -I../ @XML_CFLAGS@

clinktestunit_SOURCES = \
	../TestCtrlPoint.cpp \
	../TestDevice.cpp \
	../TestHTTPServer.cpp \
	../TestMain.cpp \
	../UPnPDeviceParseTests.cpp \
	../UPnPDeviceTests.cpp \
	../UPnPMiscTests.cpp \
	../XMLParserTests.cpp

clinktestunit_LDADD = ../../lib/unix/libclink++.a -ldl @XML_LIBS@
