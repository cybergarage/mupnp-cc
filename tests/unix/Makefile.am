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
	../TestMain.cpp \
	../XMLParserTests.cpp \
	../UPnPDeviceTests.cpp \
	../TestHTTPServer.cpp \
	../UPnPMiscTests.cpp \
	../NotifSocketTests.cpp \
	../TestCtrlPoint.cpp \
	../UPnPDeviceParseTests.cpp

mupnpcctestunit_LDADD = ../../lib/unix/libmupnp++.a -ldl @XML_LIBS@
