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
	../TestDevice.h \
	../TestCtrlPoint.h \
	../TestHTTPServer.h

clinkcctestunit_SOURCES = \
	../XMLParserTests.cpp \
	../UPnPDeviceParseTests.cpp \
	../TestDevice.cpp \
	../UPnPDeviceTests.cpp \
	../UPnPMiscTests.cpp \
	../TestCtrlPoint.cpp \
	../TestHTTPServer.cpp \
	../TestMain.cpp

clinkcctestunit_LDADD = ../../lib/unix/libclink++.a -ldl @XML_LIBS@
