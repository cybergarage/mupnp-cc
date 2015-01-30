############################################################
#
# mUPnP for C++
#
# Copyright (C) Satoshi Konno 2003
#
############################################################

noinst_PROGRAMS = mupnpcctestunit

AM_CPPFLAGS = -I$(top_srcdir)/include -I../

noinst_HEADERS = \
	../TestHTTPServer.h \
	../TestDevice.h \
	../TestCtrlPoint.h

mupnpcctestunit_SOURCES = \
	../TestDevice.cpp \
	../TestHTTPServer.cpp \
	../XMLParserTests.cpp \
	../TestCtrlPoint.cpp \
	../TestMain.cpp \
	../UPnPDeviceTests.cpp \
	../UPnPMiscTests.cpp \
	../UPnPDeviceParseTests.cpp \
	../NotifSocketTests.cpp

mupnpcctestunit_LDADD = ../../lib/unix/libmupnp++.a -ldl @XML_LIBS@
