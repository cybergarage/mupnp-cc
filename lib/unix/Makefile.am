############################################################
#
# mUPnP for C++
#
# Copyright (C) Satoshi Konno 2003
#
############################################################

lib_LIBRARIES = libmupnp++.a

AM_CPPFLAGS = -I$(top_srcdir)/include @XML_CFLAGS@

mupnpcc_sources = \
	../../src/mupnp/Action.cpp \
	../../src/mupnp/ActionList.cpp \
	../../src/mupnp/AllowedValue.cpp \
	../../src/mupnp/AllowedValueList.cpp \
	../../src/mupnp/AllowedValueRange.cpp \
	../../src/mupnp/Argument.cpp \
	../../src/mupnp/ArgumentList.cpp \
	../../src/mupnp/control/ActionRequest.cpp \
	../../src/mupnp/control/ActionResponse.cpp \
	../../src/mupnp/control/ControlRequest.cpp \
	../../src/mupnp/control/ControlResponse.cpp \
	../../src/mupnp/control/QueryRequest.cpp \
	../../src/mupnp/control/QueryResponse.cpp \
	../../src/mupnp/control/RenewSubscriber.cpp \
	../../src/mupnp/ControlPoint.cpp \
	../../src/mupnp/device/Advertiser.cpp \
	../../src/mupnp/device/Disposer.cpp \
	../../src/mupnp/device/MAN.cpp \
	../../src/mupnp/device/NT.cpp \
	../../src/mupnp/device/NTS.cpp \
	../../src/mupnp/device/ST.cpp \
	../../src/mupnp/device/USN.cpp \
	../../src/mupnp/Device.cpp \
	../../src/mupnp/DeviceList.cpp \
	../../src/mupnp/event/NotifyRequest.cpp \
	../../src/mupnp/event/PropertyList.cpp \
	../../src/mupnp/event/Subscriber.cpp \
	../../src/mupnp/event/Subscription.cpp \
	../../src/mupnp/event/SubscriptionRequest.cpp \
	../../src/mupnp/Icon.cpp \
	../../src/mupnp/IconList.cpp \
	../../src/mupnp/Service.cpp \
	../../src/mupnp/ServiceList.cpp \
	../../src/mupnp/ServiceStateTable.cpp \
	../../src/mupnp/soap/SOAP.cpp \
	../../src/mupnp/soap/SOAPRequest.cpp \
	../../src/mupnp/soap/SOAPResponse.cpp \
	../../src/mupnp/ssdp/HTTPMUSocket.cpp \
	../../src/mupnp/ssdp/HTTPUSocket.cpp \
	../../src/mupnp/ssdp/SSDP.cpp \
	../../src/mupnp/ssdp/SSDPNotifySocket.cpp \
	../../src/mupnp/ssdp/SSDPNotifySocketList.cpp \
	../../src/mupnp/ssdp/SSDPPacket.cpp \
	../../src/mupnp/ssdp/SSDPResponse.cpp \
	../../src/mupnp/ssdp/SSDPSearchResponseSocket.cpp \
	../../src/mupnp/ssdp/SSDPSearchResponseSocketList.cpp \
	../../src/mupnp/ssdp/SSDPSearchSocket.cpp \
	../../src/mupnp/ssdp/SSDPSearchSocketList.cpp \
	../../src/mupnp/StateVariable.cpp \
	../../src/mupnp/UPnP.cpp \
	../../src/mupnp/UPnPStatus.cpp \
	../../src/mupnp/xml/ActionData.cpp \
	../../src/mupnp/xml/AttributeList.cpp \
	../../src/mupnp/xml/DeviceData.cpp \
	../../src/mupnp/xml/expat/ExpatParser.cpp \
	../../src/mupnp/xml/libxml2/Libxml2Parser.cpp \
	../../src/mupnp/xml/Node.cpp \
	../../src/mupnp/xml/NodeList.cpp \
	../../src/mupnp/xml/Parser.cpp \
	../../src/mupnp/xml/ServiceData.cpp \
	../../src/mupnp/xml/StateVariableData.cpp \
	../../src/mupnp/xml/xerces/XercesParser.cpp \
	../../src/mupnp/xml/XML.cpp

libmupnp___a_SOURCES = \
        $(mupnpcc_sources)
