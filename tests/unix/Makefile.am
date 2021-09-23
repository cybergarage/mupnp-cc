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
	..//TestHTTPServer.h \
	..//TestCtrlPoint.h \
	..//TestDevice.h

mupnpcctestunit_SOURCES = \
	..//UPnPMiscTests.cpp \
	..//TestDevice.cpp \
	..//TestMain.cpp \
	..//TestCtrlPoint.cpp \
	..//UPnPDeviceParseTests.cpp \
	..//NotifSocketTests.cpp \
	..//XMLParserTests.cpp \
	..//TestHTTPServer.cpp \
	..//UPnPDeviceTests.cpp

mupnpcctestunit_LDADD = ../../lib/unix/libmupnp++.a -ldl @XML_LIBS@
