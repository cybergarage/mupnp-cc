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
	../../src/mupnp/ActionList.cpp \
	../../src/mupnp/xml/NodeList.cpp \
	../../src/mupnp/xml/StateVariableData.cpp \
	../../src/mupnp/xml/XML.cpp \
	../../src/mupnp/xml/xerces/XercesParser.cpp \
	../../src/mupnp/xml/ServiceData.cpp \
	../../src/mupnp/xml/libxml2/Libxml2Parser.cpp \
	../../src/mupnp/xml/Node.cpp \
	../../src/mupnp/xml/DeviceData.cpp \
	../../src/mupnp/xml/Parser.cpp \
	../../src/mupnp/xml/AttributeList.cpp \
	../../src/mupnp/xml/expat/ExpatParser.cpp \
	../../src/mupnp/xml/ActionData.cpp \
	../../src/mupnp/AllowedValue.cpp \
	../../src/mupnp/AllowedValueList.cpp \
	../../src/mupnp/IconList.cpp \
	../../src/mupnp/control/QueryRequest.cpp \
	../../src/mupnp/control/ActionResponse.cpp \
	../../src/mupnp/control/RenewSubscriber.cpp \
	../../src/mupnp/control/ControlRequest.cpp \
	../../src/mupnp/control/ControlResponse.cpp \
	../../src/mupnp/control/QueryResponse.cpp \
	../../src/mupnp/control/ActionRequest.cpp \
	../../src/mupnp/ServiceStateTable.cpp \
	../../src/mupnp/ssdp/SSDPSearchResponseSocketList.cpp \
	../../src/mupnp/ssdp/SSDPResponse.cpp \
	../../src/mupnp/ssdp/HTTPUSocket.cpp \
	../../src/mupnp/ssdp/SSDPNotifySocketList.cpp \
	../../src/mupnp/ssdp/SSDPNotifySocket.cpp \
	../../src/mupnp/ssdp/SSDPSearchSocketList.cpp \
	../../src/mupnp/ssdp/SSDPSearchSocket.cpp \
	../../src/mupnp/ssdp/HTTPMUSocket.cpp \
	../../src/mupnp/ssdp/SSDPPacket.cpp \
	../../src/mupnp/ssdp/SSDPSearchResponseSocket.cpp \
	../../src/mupnp/ssdp/SSDP.cpp \
	../../src/mupnp/DeviceList.cpp \
	../../src/mupnp/Device.cpp \
	../../src/mupnp/device/NTS.cpp \
	../../src/mupnp/device/NT.cpp \
	../../src/mupnp/device/ST.cpp \
	../../src/mupnp/device/Advertiser.cpp \
	../../src/mupnp/device/USN.cpp \
	../../src/mupnp/device/MAN.cpp \
	../../src/mupnp/device/Disposer.cpp \
	../../src/mupnp/ControlPoint.cpp \
	../../src/mupnp/soap/SOAP.cpp \
	../../src/mupnp/soap/SOAPRequest.cpp \
	../../src/mupnp/soap/SOAPResponse.cpp \
	../../src/mupnp/Service.cpp \
	../../src/mupnp/net/SocketInputStream.cpp \
	../../src/mupnp/net/DatagramSocket.cpp \
	../../src/mupnp/net/SocketUtil.cpp \
	../../src/mupnp/net/URI.cpp \
	../../src/mupnp/net/Socket.cpp \
	../../src/mupnp/net/URL.cpp \
	../../src/mupnp/net/SocketCore.cpp \
	../../src/mupnp/net/HostInterface.cpp \
	../../src/mupnp/net/ServerSocket.cpp \
	../../src/mupnp/net/MulticastSocket.cpp \
	../../src/mupnp/event/Subscriber.cpp \
	../../src/mupnp/event/SubscriptionRequest.cpp \
	../../src/mupnp/event/PropertyList.cpp \
	../../src/mupnp/event/NotifyRequest.cpp \
	../../src/mupnp/event/Subscription.cpp \
	../../src/mupnp/UPnP.cpp \
	../../src/mupnp/http/HTTPDate.cpp \
	../../src/mupnp/http/HTTPWorkerThread.cpp \
	../../src/mupnp/http/HTTPRequest.cpp \
	../../src/mupnp/http/HTTPSocket.cpp \
	../../src/mupnp/http/HTTP.cpp \
	../../src/mupnp/http/HTTPMessageQueue.cpp \
	../../src/mupnp/http/HTTPHeader.cpp \
	../../src/mupnp/http/HTTPResponse.cpp \
	../../src/mupnp/http/HTTPPacket.cpp \
	../../src/mupnp/http/HTTPStatus.cpp \
	../../src/mupnp/http/HTTPServerList.cpp \
	../../src/mupnp/http/HTTPServer.cpp \
	../../src/mupnp/util/Mutex.cpp \
	../../src/mupnp/util/Semaphore.cpp \
	../../src/mupnp/util/Logger.cpp \
	../../src/mupnp/util/StringTokenizer.cpp \
	../../src/mupnp/util/Log.cpp \
	../../src/mupnp/util/Date.cpp \
	../../src/mupnp/util/TimeUtil.cpp \
	../../src/mupnp/util/LoggerTargetList.cpp \
	../../src/mupnp/util/Message.cpp \
	../../src/mupnp/util/StringUtil.cpp \
	../../src/mupnp/util/MessageQueue.cpp \
	../../src/mupnp/util/ThreadList.cpp \
	../../src/mupnp/util/Thread.cpp \
	../../src/mupnp/util/LoggerTarget.cpp \
	../../src/mupnp/util/LoggerFileTarget.cpp \
	../../src/mupnp/util/Random.cpp \
	../../src/mupnp/util/Debug.cpp \
	../../src/mupnp/ArgumentList.cpp \
	../../src/mupnp/AllowedValueRange.cpp \
	../../src/mupnp/Argument.cpp \
	../../src/mupnp/Icon.cpp \
	../../src/mupnp/io/File.cpp \
	../../src/mupnp/io/FileInputStream.cpp \
	../../src/mupnp/io/StringBufferInputStream.cpp \
	../../src/mupnp/io/BufferedReader.cpp \
	../../src/mupnp/io/StringReader.cpp \
	../../src/mupnp/StateVariable.cpp \
	../../src/mupnp/ServiceList.cpp \
	../../src/mupnp/Action.cpp \
	../../src/mupnp/UPnPStatus.cpp

libmupnp___a_SOURCES = \
        $(mupnpcc_sources)
