lib_LIBRARIES = libclink++.a

INCLUDES = -I$(top_srcdir)/include @XML_CFLAGS@

########################################
# CyberLink
########################################

clink_source = \
	../../src/cybergarage/xml/AttributeList.cpp \
	../../src/cybergarage/xml/Node.cpp \
	../../src/cybergarage/xml/NodeList.cpp \
	../../src/cybergarage/xml/Parser.cpp \
	../../src/cybergarage/xml/XML.cpp \
	../../src/cybergarage/xml/xerces/XercesParser.cpp \
	../../src/cybergarage/xml/expat/ExpatParser.cpp \
	../../src/cybergarage/xml/libxml2/Libxml2Parser.cpp \
	../../src/cybergarage/soap/SOAP.cpp \
	../../src/cybergarage/soap/SOAPRequest.cpp \
	../../src/cybergarage/soap/SOAPResponse.cpp \
	../../src/cybergarage/upnp/Action.cpp \
	../../src/cybergarage/upnp/ActionList.cpp \
	../../src/cybergarage/upnp/AllowedValue.cpp \
	../../src/cybergarage/upnp/AllowedValueList.cpp \
	../../src/cybergarage/upnp/AllowedValueRange.cpp \
	../../src/cybergarage/upnp/Argument.cpp \
	../../src/cybergarage/upnp/ArgumentList.cpp \
	../../src/cybergarage/upnp/ControlPoint.cpp \
	../../src/cybergarage/upnp/Device.cpp \
	../../src/cybergarage/upnp/DeviceList.cpp \
	../../src/cybergarage/upnp/Icon.cpp \
	../../src/cybergarage/upnp/IconList.cpp \
	../../src/cybergarage/upnp/Service.cpp \
	../../src/cybergarage/upnp/ServiceList.cpp \
	../../src/cybergarage/upnp/ServiceStateTable.cpp \
	../../src/cybergarage/upnp/StateVariable.cpp \
	../../src/cybergarage/upnp/UPnP.cpp \
	../../src/cybergarage/upnp/UPnPStatus.cpp \
	../../src/cybergarage/upnp/control/ActionRequest.cpp \
	../../src/cybergarage/upnp/control/ActionResponse.cpp \
	../../src/cybergarage/upnp/control/ControlRequest.cpp \
	../../src/cybergarage/upnp/control/ControlResponse.cpp \
	../../src/cybergarage/upnp/control/QueryRequest.cpp \
	../../src/cybergarage/upnp/control/QueryResponse.cpp \
	../../src/cybergarage/upnp/control/RenewSubscriber.cpp \
	../../src/cybergarage/upnp/device/Advertiser.cpp \
	../../src/cybergarage/upnp/device/Disposer.cpp \
	../../src/cybergarage/upnp/device/MAN.cpp \
	../../src/cybergarage/upnp/device/NT.cpp \
	../../src/cybergarage/upnp/device/NTS.cpp \
	../../src/cybergarage/upnp/device/ST.cpp \
	../../src/cybergarage/upnp/device/USN.cpp \
	../../src/cybergarage/upnp/event/NotifyRequest.cpp \
	../../src/cybergarage/upnp/event/PropertyList.cpp \
	../../src/cybergarage/upnp/event/Subscriber.cpp \
	../../src/cybergarage/upnp/event/Subscription.cpp \
	../../src/cybergarage/upnp/event/SubscriptionRequest.cpp \
	../../src/cybergarage/upnp/ssdp/HTTPMUSocket.cpp \
	../../src/cybergarage/upnp/ssdp/HTTPUSocket.cpp \
	../../src/cybergarage/upnp/ssdp/SSDP.cpp \
	../../src/cybergarage/upnp/ssdp/SSDPNotifySocket.cpp \
	../../src/cybergarage/upnp/ssdp/SSDPNotifySocketList.cpp \
	../../src/cybergarage/upnp/ssdp/SSDPPacket.cpp \
	../../src/cybergarage/upnp/ssdp/SSDPResponse.cpp \
	../../src/cybergarage/upnp/ssdp/SSDPSearchResponseSocket.cpp \
	../../src/cybergarage/upnp/ssdp/SSDPSearchResponseSocketList.cpp \
	../../src/cybergarage/upnp/ssdp/SSDPSearchSocket.cpp \
	../../src/cybergarage/upnp/ssdp/SSDPSearchSocketList.cpp \
	../../src/cybergarage/upnp/xml/ActionData.cpp \
	../../src/cybergarage/upnp/xml/DeviceData.cpp \
	../../src/cybergarage/upnp/xml/ServiceData.cpp \
	../../src/cybergarage/upnp/xml/StateVariableData.cpp

########################################
# Library
########################################

libclink___a_SOURCES = \
	$(clink_source)

