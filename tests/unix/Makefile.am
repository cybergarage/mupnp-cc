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
	..//TestCtrlPoint.h \
	..//TestDevice.h \
	..//TestHTTPServer.h

mupnpcctestunit_SOURCES = \
	..//NotifSocketTests.cpp \
	..//TestCtrlPoint.cpp \
	..//TestDevice.cpp \
	..//TestHTTPServer.cpp \
	..//TestMain.cpp \
	..//UPnPDeviceParseTests.cpp \
	..//UPnPDeviceTests.cpp \
	..//UPnPMiscTests.cpp \
	..//XMLParserTests.cpp

mupnpcctestunit_LDADD = ../../lib/unix/libmupnp++.a -ldl @XML_LIBS@
