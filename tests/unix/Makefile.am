############################################################
#
# CyberGarage for C
#
# Copyright (C) Satoshi Konno 2005
#
############################################################

noinst_PROGRAMS = clinkcctestunit

AM_CPPFLAGS = -I$(top_srcdir)/include -I../

noinst_HEADERS = \
	..//TestCtrlPoint.h \
	..//TestDevice.h \
	..//TestHTTPServer.h

clinkcctestunit_SOURCES = \
	..//TestCtrlPoint.cpp \
	..//TestDevice.cpp \
	..//TestHTTPServer.cpp \
	..//TestMain.cpp \
	..//UPnPDeviceParseTests.cpp \
	..//UPnPDeviceTests.cpp \
	..//UPnPMiscTests.cpp \
	..//XMLParserTests.cpp

clinkcctestunit_LDADD = ../../lib/unix/libclink++.a -ldl @XML_LIBS@
