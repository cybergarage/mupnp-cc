############################################################
#
# mUPnP for C++
#
# Copyright (C) Satoshi Konno 2003
#
############################################################

TESTS = mupnptest
check_PROGRAMS = mupnptest

AM_CPPFLAGS = -I$(top_srcdir)/include -I../

noinst_HEADERS = \
	../TestDevice.h \
	../TestCtrlPoint.h \
	../TestHTTPServer.h

mupnptest_SOURCES = \
	../TestCtrlPoint.cpp \
	../TestDevice.cpp \
	../UPnPDeviceParseTests.cpp \
	../UPnPMiscTests.cpp \
	../NotifSocketTests.cpp \
	../UPnPDeviceTests.cpp \
	../XMLParserTests.cpp \
	../TestMain.cpp \
	../TestHTTPServer.cpp

mupnptest_LDADD = ../../lib/unix/libmupnp++.a -ldl @XML_LIBS@
