lib_LIBRARIES = libclink++.a

INCLUDES = -I$(top_srcdir)/include @XML_CFLAGS@

########################################
# CyberLink
########################################

clink_source = \
	../../src/cybergarage/util/Date.cpp \
	../../src/cybergarage/util/Debug.cpp \
	../../src/cybergarage/util/Mutex.cpp \
	../../src/cybergarage/util/StringTokenizer.cpp \
	../../src/cybergarage/util/StringUtil.cpp \
	../../src/cybergarage/util/Thread.cpp \
	../../src/cybergarage/util/TimeUtil.cpp \
	../../src/cybergarage/io/BufferedReader.cpp \
	../../src/cybergarage/io/File.cpp \
	../../src/cybergarage/io/FileList.cpp \
	../../src/cybergarage/io/FileInputStream.cpp \
	../../src/cybergarage/io/FileInputStream.cpp \
	../../src/cybergarage/io/StringBufferInputStream.cpp \
	../../src/cybergarage/io/StringReader.cpp \
	../../src/cybergarage/net/DatagramSocket.cpp \
	../../src/cybergarage/net/HostInterface.cpp \
	../../src/cybergarage/net/MulticastSocket.cpp \
	../../src/cybergarage/net/ServerSocket.cpp \
	../../src/cybergarage/net/Socket.cpp \
	../../src/cybergarage/net/SocketImp.cpp \
	../../src/cybergarage/net/SocketInputStream.cpp \
	../../src/cybergarage/net/SocketUtil.cpp \
	../../src/cybergarage/net/URI.cpp \
	../../src/cybergarage/net/URL.cpp \
	../../src/cybergarage/http/HTTP.cpp \
	../../src/cybergarage/http/HTTPDate.cpp \
	../../src/cybergarage/http/HTTPHeader.cpp \
	../../src/cybergarage/http/HTTPPacket.cpp \
	../../src/cybergarage/http/HTTPRequest.cpp \
	../../src/cybergarage/http/HTTPResponse.cpp \
	../../src/cybergarage/http/HTTPServer.cpp \
	../../src/cybergarage/http/HTTPServerList.cpp \
	../../src/cybergarage/http/HTTPServerThread.cpp \
	../../src/cybergarage/http/HTTPSocket.cpp \
	../../src/cybergarage/http/HTTPStatus.cpp \
	../../src/cybergarage/sql/UniDatabase.cpp \
	../../src/cybergarage/sql/UniMySQL.cpp \
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
# CyberLink (Media)
########################################

clink_media_header = \
	../../include/cybergarage/upnp/media/server/ConnectionInfo.h \
	../../include/cybergarage/upnp/media/server/ConnectionInfoList.h \
	../../include/cybergarage/upnp/media/server/ConnectionManager.h \
	../../include/cybergarage/upnp/media/server/ContentDirectory.h \
	../../include/cybergarage/upnp/media/server/DC.h \
	../../include/cybergarage/upnp/media/server/Directory.h \
	../../include/cybergarage/upnp/media/server/DirectoryList.h \
	../../include/cybergarage/upnp/media/server/MediaServer.h \
	../../include/cybergarage/upnp/media/server/UPnP.h \
	../../include/cybergarage/upnp/media/server/action/BrowseAction.h \
	../../include/cybergarage/upnp/media/server/action/SearchAction.h \
	../../include/cybergarage/upnp/media/server/directory/file/FileDirectory.h \
	../../include/cybergarage/upnp/media/server/directory/mythtv/MythDatabase.h \
	../../include/cybergarage/upnp/media/server/directory/mythtv/MythDirectory.h \
	../../include/cybergarage/upnp/media/server/directory/mythtv/MythRecordedInfo.h \
	../../include/cybergarage/upnp/media/server/directory/mythtv/MythRecordedInfoList.h \
	../../include/cybergarage/upnp/media/server/object/ContentNode.h \
	../../include/cybergarage/upnp/media/server/object/ContentNodeList.h \
	../../include/cybergarage/upnp/media/server/object/ContentProperty.h \
	../../include/cybergarage/upnp/media/server/object/ContentPropertyList.h \
	../../include/cybergarage/upnp/media/server/object/DIDLLite.h \
	../../include/cybergarage/upnp/media/server/object/DIDLLiteNode.h \
	../../include/cybergarage/upnp/media/server/object/Format.h \
	../../include/cybergarage/upnp/media/server/object/FormatList.h \
	../../include/cybergarage/upnp/media/server/object/FormatObject.h \
	../../include/cybergarage/upnp/media/server/object/SearchCapList.h \
	../../include/cybergarage/upnp/media/server/object/SearchCriteriaList.h \
	../../include/cybergarage/upnp/media/server/object/SearchCriteria.h \
	../../include/cybergarage/upnp/media/server/object/SearchCriteriaList.h \
	../../include/cybergarage/upnp/media/server/object/SortCap.h \
	../../include/cybergarage/upnp/media/server/object/SortCapList.h \
	../../include/cybergarage/upnp/media/server/object/SortCriteriaList.h \
	../../include/cybergarage/upnp/media/server/object/container/ContainerNode.h \
	../../include/cybergarage/upnp/media/server/object/container/RootNode.h \
	../../include/cybergarage/upnp/media/server/object/format/AudioFormat.h \
	../../include/cybergarage/upnp/media/server/object/format/DefaultFormat.h \
	../../include/cybergarage/upnp/media/server/object/format/ID3Format.h \
	../../include/cybergarage/upnp/media/server/object/format/ID3Frame.h \
	../../include/cybergarage/upnp/media/server/object/format/ID3FrameList.h \
	../../include/cybergarage/upnp/media/server/object/format/GIFFormat.h \
	../../include/cybergarage/upnp/media/server/object/format/ImageFormat.h \
	../../include/cybergarage/upnp/media/server/object/format/JPEGFormat.h \
	../../include/cybergarage/upnp/media/server/object/format/MovieFormat.h \
	../../include/cybergarage/upnp/media/server/object/format/MPEGFormat.h \
	../../include/cybergarage/upnp/media/server/object/format/PNGFormat.h \
	../../include/cybergarage/upnp/media/server/object/item/ItemNode.h \
	../../include/cybergarage/upnp/media/server/object/item/ItemNodeList.h \
	../../include/cybergarage/upnp/media/server/object/item/file/FileItemNode.h \
	../../include/cybergarage/upnp/media/server/object/item/file/FileItemNodeList.h \
	../../include/cybergarage/upnp/media/server/object/item/mythtv/MythRecordedItemNode.h \
	../../include/cybergarage/upnp/media/server/object/item/mythtv/MythRecordedItemNodeList.h \
	../../include/cybergarage/upnp/media/server/object/search/IdSearchCap.h \
	../../include/cybergarage/upnp/media/server/object/search/TitleSearchCap.h \
	../../include/cybergarage/upnp/media/server/object/sort/DCDateSortCap.h \
	../../include/cybergarage/upnp/media/server/object/sort/DCTitleSortCap.h \
	../../include/cybergarage/upnp/media/server/object/sort/UPnPClassSortCap.h \
	../../include/cybergarage/upnp/media/player/MediaPlayer.h \
	../../include/cybergarage/upnp/media/player/action/BrowseResult.h \
	../../include/cybergarage/upnp/media/player/action/BrowseResultNode.h

clink_media_source = \
	../../src/cybergarage/upnp/media/server/ConnectionInfo.cpp \
	../../src/cybergarage/upnp/media/server/ConnectionInfoList.cpp \
	../../src/cybergarage/upnp/media/server/ConnectionManager.cpp \
	../../src/cybergarage/upnp/media/server/ContentDirectory.cpp \
	../../src/cybergarage/upnp/media/server/DirectoryList.cpp \
	../../src/cybergarage/upnp/media/server/MediaServer.cpp \
	../../src/cybergarage/upnp/media/server/action/BrowseAction.cpp \
	../../src/cybergarage/upnp/media/server/action/SearchAction.cpp \
	../../src/cybergarage/upnp/media/server/directory/file/FileDirectory.cpp \
	../../src/cybergarage/upnp/media/server/directory/mythtv/MythDatabase.cpp \
	../../src/cybergarage/upnp/media/server/directory/mythtv/MythDirectory.cpp \
	../../src/cybergarage/upnp/media/server/directory/mythtv/MythRecordedInfo.cpp \
	../../src/cybergarage/upnp/media/server/directory/mythtv/MythRecordedInfoList.cpp \
	../../src/cybergarage/upnp/media/server/object/ContentNode.cpp \
	../../src/cybergarage/upnp/media/server/object/ContentNodeList.cpp \
	../../src/cybergarage/upnp/media/server/object/ContentPropertyList.cpp \
	../../src/cybergarage/upnp/media/server/object/DIDLLite.cpp \
	../../src/cybergarage/upnp/media/server/object/FormatList.cpp \
	../../src/cybergarage/upnp/media/server/object/SearchCapList.cpp \
	../../src/cybergarage/upnp/media/server/object/SearchCriteria.cpp \
	../../src/cybergarage/upnp/media/server/object/SearchCriteriaList.cpp \
	../../src/cybergarage/upnp/media/server/object/SortCapList.cpp \
	../../src/cybergarage/upnp/media/server/object/SortCriteriaList.cpp \
	../../src/cybergarage/upnp/media/server/object/container/ContainerNode.cpp \
	../../src/cybergarage/upnp/media/server/object/format/DefaultFormat.cpp \
	../../src/cybergarage/upnp/media/server/object/format/ID3Format.cpp \
	../../src/cybergarage/upnp/media/server/object/format/ID3Frame.cpp \
	../../src/cybergarage/upnp/media/server/object/format/ID3FrameList.cpp \
	../../src/cybergarage/upnp/media/server/object/format/GIFFormat.cpp \
	../../src/cybergarage/upnp/media/server/object/format/JPEGFormat.cpp \
	../../src/cybergarage/upnp/media/server/object/format/MPEGFormat.cpp \
	../../src/cybergarage/upnp/media/server/object/format/PNGFormat.cpp \
	../../src/cybergarage/upnp/media/server/object/item/ItemNode.cpp \
	../../src/cybergarage/upnp/media/server/object/item/ItemNodeList.cpp \
	../../src/cybergarage/upnp/media/server/object/item/file/FileItemNode.cpp \
	../../src/cybergarage/upnp/media/server/object/item/file/FileItemNodeList.cpp \
	../../src/cybergarage/upnp/media/server/object/item/mythtv/MythRecordedItemNode.cpp \
	../../src/cybergarage/upnp/media/server/object/item/mythtv/MythRecordedItemNodeList.cpp \
	../../src/cybergarage/upnp/media/server/object/search/IdSearchCap.cpp \
	../../src/cybergarage/upnp/media/server/object/search/TitleSearchCap.cpp \
	../../src/cybergarage/upnp/media/server/object/sort/DCDateSortCap.cpp \
	../../src/cybergarage/upnp/media/server/object/sort/DCTitleSortCap.cpp \
	../../src/cybergarage/upnp/media/server/object/sort/UPnPClassSortCap.cpp \
	../../src/cybergarage/upnp/media/player/MediaPlayer.cpp

########################################
# Library
########################################

libclink___a_SOURCES = \
	$(clink_source) \
	$(clink_media_source)

