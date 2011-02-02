 ##################################################
#
#	CyberLink for C
#
#	Copyright (C) Satoshi Konno 2005
#
#	File: Makefile.inc
#
#	Revision:
#
#	07/28/05
#		- first revision
#
##################################################

CLINKHEADERROOT = $(CLINKROOT)/include
CLINKSRCROOT = $(CLINKROOT)/src/cybergarage

CLINKUTILSRC = \
	$(CLINKSRCROOT)/util/Date.cpp \
	$(CLINKSRCROOT)/util/Debug.cpp \
	$(CLINKSRCROOT)/util/Mutex.cpp \
	$(CLINKSRCROOT)/util/StringTokenizer.cpp \
	$(CLINKSRCROOT)/util/StringUtil.cpp \
	$(CLINKSRCROOT)/util/Thread.cpp \
	$(CLINKSRCROOT)/util/TimeUtil.cpp

CLINKNETSRC = \
	$(CLINKSRCROOT)/net/DatagramSocket.cpp \
	$(CLINKSRCROOT)/net/HostInterface.cpp \
	$(CLINKSRCROOT)/net/MulticastSocket.cpp \
	$(CLINKSRCROOT)/net/ServerSocket.cpp \
	$(CLINKSRCROOT)/net/Socket.cpp \
	$(CLINKSRCROOT)/net/SocketImp.cpp \
	$(CLINKSRCROOT)/net/SocketInputStream.cpp \
	$(CLINKSRCROOT)/net/SocketUtil.cpp \
	$(CLINKSRCROOT)/net/URI.cpp \
	$(CLINKSRCROOT)/net/URL.cpp

CLINKIOSRC = \
	$(CLINKSRCROOT)/io/BufferedReader.cpp \
	$(CLINKSRCROOT)/io/File.cpp \
	$(CLINKSRCROOT)/io/FileInputStream.cpp \
	$(CLINKSRCROOT)/io/FileList.cpp \
	$(CLINKSRCROOT)/io/StringBufferInputStream.cpp \
	$(CLINKSRCROOT)/io/StringReader.cpp

CLINKXMLSRC = \
	$(CLINKSRCROOT)/xml/AttributeList.cpp \
	$(CLINKSRCROOT)/xml/Node.cpp \
	$(CLINKSRCROOT)/xml/NodeList.cpp \
	$(CLINKSRCROOT)/xml/Parser.cpp \
	$(CLINKSRCROOT)/xml/XML.cpp \
	$(CLINKSRCROOT)/xml/expat/ExpatParser.cpp

CLINKHTTPSRC = \
	$(CLINKSRCROOT)/http/HTTP.cpp \
	$(CLINKSRCROOT)/http/HTTPDate.cpp \
	$(CLINKSRCROOT)/http/HTTPHeader.cpp \
	$(CLINKSRCROOT)/http/HTTPPacket.cpp \
	$(CLINKSRCROOT)/http/HTTPRequest.cpp \
	$(CLINKSRCROOT)/http/HTTPResponse.cpp \
	$(CLINKSRCROOT)/http/HTTPServer.cpp \
	$(CLINKSRCROOT)/http/HTTPServerList.cpp \
	$(CLINKSRCROOT)/http/HTTPServerThread.cpp \
	$(CLINKSRCROOT)/http/HTTPResponse.cpp \
	$(CLINKSRCROOT)/http/HTTPSocket.cpp \
	$(CLINKSRCROOT)/http/HTTPStatus.cpp

CLINKSOAPSRC = \
	$(CLINKSRCROOT)/soap/SOAP.cpp \
	$(CLINKSRCROOT)/soap/SOAPRequest.cpp \
	$(CLINKSRCROOT)/soap/SOAPResponse.cpp

CLINKUPNPSRC = \
	$(CLINKSRCROOT)/upnp/Action.cpp \
	$(CLINKSRCROOT)/upnp/ActionList.cpp \
	$(CLINKSRCROOT)/upnp/AllowedValue.cpp \
	$(CLINKSRCROOT)/upnp/AllowedValueList.cpp \
	$(CLINKSRCROOT)/upnp/AllowedValueRange.cpp \
	$(CLINKSRCROOT)/upnp/Argument.cpp \
	$(CLINKSRCROOT)/upnp/ArgumentList.cpp \
	$(CLINKSRCROOT)/upnp/ControlPoint.cpp \
	$(CLINKSRCROOT)/upnp/Device.cpp \
	$(CLINKSRCROOT)/upnp/DeviceList.cpp \
	$(CLINKSRCROOT)/upnp/Icon.cpp \
	$(CLINKSRCROOT)/upnp/IconList.cpp \
	$(CLINKSRCROOT)/upnp/Service.cpp \
	$(CLINKSRCROOT)/upnp/ServiceList.cpp \
	$(CLINKSRCROOT)/upnp/ServiceStateTable.cpp \
	$(CLINKSRCROOT)/upnp/StateVariable.cpp \
	$(CLINKSRCROOT)/upnp/UPnP.cpp \
	$(CLINKSRCROOT)/upnp/UPnPStatus.cpp \
	$(CLINKSRCROOT)/upnp/control/ActionRequest.cpp \
	$(CLINKSRCROOT)/upnp/control/ActionResponse.cpp \
	$(CLINKSRCROOT)/upnp/control/ControlRequest.cpp \
	$(CLINKSRCROOT)/upnp/control/ControlResponse.cpp \
	$(CLINKSRCROOT)/upnp/control/QueryRequest.cpp \
	$(CLINKSRCROOT)/upnp/control/QueryResponse.cpp \
	$(CLINKSRCROOT)/upnp/control/RenewSubscriber.cpp \
	$(CLINKSRCROOT)/upnp/device/Advertiser.cpp \
	$(CLINKSRCROOT)/upnp/device/Disposer.cpp \
	$(CLINKSRCROOT)/upnp/device/MAN.cpp \
	$(CLINKSRCROOT)/upnp/device/NT.cpp \
	$(CLINKSRCROOT)/upnp/device/NTS.cpp \
	$(CLINKSRCROOT)/upnp/device/ST.cpp \
	$(CLINKSRCROOT)/upnp/device/USN.cpp \
	$(CLINKSRCROOT)/upnp/event/NotifyRequest.cpp \
	$(CLINKSRCROOT)/upnp/event/PropertyList.cpp \
	$(CLINKSRCROOT)/upnp/event/Subscriber.cpp \
	$(CLINKSRCROOT)/upnp/event/Subscription.cpp \
	$(CLINKSRCROOT)/upnp/event/SubscriptionRequest.cpp \
	$(CLINKSRCROOT)/upnp/ssdp/HTTPMUSocket.cpp \
	$(CLINKSRCROOT)/upnp/ssdp/HTTPUSocket.cpp \
	$(CLINKSRCROOT)/upnp/ssdp/SSDP.cpp \
	$(CLINKSRCROOT)/upnp/ssdp/SSDPNotifySocket.cpp \
	$(CLINKSRCROOT)/upnp/ssdp/SSDPNotifySocketList.cpp \
	$(CLINKSRCROOT)/upnp/ssdp/SSDPPacket.cpp \
	$(CLINKSRCROOT)/upnp/ssdp/SSDPResponse.cpp \
	$(CLINKSRCROOT)/upnp/ssdp/SSDPSearchResponseSocket.cpp \
	$(CLINKSRCROOT)/upnp/ssdp/SSDPSearchResponseSocketList.cpp \
	$(CLINKSRCROOT)/upnp/ssdp/SSDPSearchSocket.cpp \
	$(CLINKSRCROOT)/upnp/ssdp/SSDPSearchSocketList.cpp \
	$(CLINKSRCROOT)/upnp/xml/ActionData.cpp \
	$(CLINKSRCROOT)/upnp/xml/DeviceData.cpp \
	$(CLINKSRCROOT)/upnp/xml/ServiceData.cpp \
	$(CLINKSRCROOT)/upnp/xml/StateVariableData.cpp

EXPATSRC = \
	$(EXPATROOT)/lib/xmlparse.c \
	$(EXPATROOT)/lib/xmlrole.c \
	$(EXPATROOT)/lib/xmltok.c
#	$(EXPATROOT)/lib/xmltok_ns.c
#	$(EXPATROOT)/lib/xmltok_impl.c \

unexport CLINKSRC =
CLINKSRC = \
	$(CLINKUTILSRC) \
	$(CLINKNETSRC) \
	$(CLINKIOSRC) \
	$(CLINKXMLSRC) \
	$(CLINKHTTPSRC) \
	$(CLINKSOAPSRC) \
	$(CLINKUPNPSRC) \
	$(EXPATSRC)
