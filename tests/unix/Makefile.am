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
	../TestCtrlPoint.h \
	../TestDevice.h

mupnpcctestunit_SOURCES = \
	../TestDevice.cpp \
	../TestHTTPServer.cpp \
	../XMLParserTests.cpp \
	../TestCtrlPoint.cpp \
	../TestMain.cpp \
	../UPnPMiscTests.cpp \
	../UPnPDeviceParseTests.cpp \
	../UPnPDeviceTests.cpp \
	../NotifSocketTests.cpp

mupnpcctestunit_LDADD = ../../lib/unix/libclink++.a -ldl @XML_LIBS@
