# Microsoft Developer Studio Project File - Name="CyberLink" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** 編集しないでください **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=CyberLink - Win32 Debug
!MESSAGE これは有効なﾒｲｸﾌｧｲﾙではありません。 このﾌﾟﾛｼﾞｪｸﾄをﾋﾞﾙﾄﾞするためには NMAKE を使用してください。
!MESSAGE [ﾒｲｸﾌｧｲﾙのｴｸｽﾎﾟｰﾄ] ｺﾏﾝﾄﾞを使用して実行してください
!MESSAGE 
!MESSAGE NMAKE /f "CyberLink.mak".
!MESSAGE 
!MESSAGE NMAKE の実行時に構成を指定できます
!MESSAGE ｺﾏﾝﾄﾞ ﾗｲﾝ上でﾏｸﾛの設定を定義します。例:
!MESSAGE 
!MESSAGE NMAKE /f "CyberLink.mak" CFG="CyberLink - Win32 Debug"
!MESSAGE 
!MESSAGE 選択可能なﾋﾞﾙﾄﾞ ﾓｰﾄﾞ:
!MESSAGE 
!MESSAGE "CyberLink - Win32 Release" ("Win32 (x86) Static Library" 用)
!MESSAGE "CyberLink - Win32 Debug" ("Win32 (x86) Static Library" 用)
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "CyberLink - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../../../include" /D "NDEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "USE_XMLPARSER_EXPAT" /YX /FD /c
# ADD BASE RSC /l 0x411 /d "NDEBUG"
# ADD RSC /l 0x411 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"CyberLink.lib"

!ELSEIF  "$(CFG)" == "CyberLink - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "../../../include" /D "_DEBUG" /D "WIN32" /D "_MBCS" /D "_LIB" /D "USE_XMLPARSER_EXPAT" /YX /FD /GZ /c
# ADD BASE RSC /l 0x411 /d "_DEBUG"
# ADD RSC /l 0x411 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"CyberLink.lib"

!ENDIF 

# Begin Target

# Name "CyberLink - Win32 Release"
# Name "CyberLink - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\Action.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\xml\ActionData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ActionList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\control\ActionRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\control\ActionResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\device\Advertiser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\AllowedValue.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\AllowedValueList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\AllowedValueRange.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\Argument.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ArgumentList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\xml\AttributeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\io\BufferedReader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ControlPoint.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\control\ControlRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\control\ControlResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\net\DatagramSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\util\Date.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\util\Debug.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\Device.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\xml\DeviceData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\DeviceList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\device\Disposer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\xml\expat\ExpatParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\io\File.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\io\FileInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\io\FileList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\net\HostInterface.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\http\HTTP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\http\HTTPDate.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\http\HTTPHeader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ssdp\HTTPMUSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\http\HTTPPacket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\http\HTTPRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\http\HTTPResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\http\HTTPServer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\http\HTTPServerList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\http\HTTPServerThread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\http\HTTPSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\http\HTTPStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ssdp\HTTPUSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\Icon.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\IconList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\device\MAN.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\net\MulticastSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\util\Mutex.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\xml\Node.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\xml\NodeList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\event\NotifyRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\device\NT.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\device\NTS.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\xml\Parser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\event\PropertyList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\control\QueryRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\control\QueryResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\control\RenewSubscriber.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\net\ServerSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\Service.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\xml\ServiceData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ServiceList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ServiceStateTable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\soap\SOAP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\soap\SOAPRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\soap\SOAPResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\net\Socket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\net\SocketImp.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\net\SocketInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\net\SocketUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ssdp\SSDP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ssdp\SSDPNotifySocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ssdp\SSDPNotifySocketList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ssdp\SSDPPacket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ssdp\SSDPResponse.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ssdp\SSDPSearchResponseSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ssdp\SSDPSearchResponseSocketList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ssdp\SSDPSearchSocket.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\ssdp\SSDPSearchSocketList.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\device\ST.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\StateVariable.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\xml\StateVariableData.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\io\StringBufferInputStream.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\io\StringReader.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\util\StringTokenizer.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\util\StringUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\event\Subscriber.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\event\Subscription.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\event\SubscriptionRequest.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\util\Thread.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\util\TimeUtil.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\sql\UniDatabase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\sql\UniMySQL.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\UPnP.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\UPnPStatus.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\net\URI.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\net\URL.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\upnp\device\USN.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\xml\xerces\XercesParser.cpp
# End Source File
# Begin Source File

SOURCE=..\..\..\src\cybergarage\xml\XML.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\Action.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\xml\ActionData.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ActionList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\control\ActionListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\control\ActionRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\control\ActionResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\Advertiser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\AllowedValue.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\AllowedValueList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\AllowedValueRange.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\Argument.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\xml\ArgumentData.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ArgumentList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\xml\Attribute.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\xml\AttributeList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\io\BufferedReader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\control\Control.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ControlPoint.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\control\ControlRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\control\ControlResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\CyberLink.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\DatagramPacket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\DatagramSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\util\Date.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\util\Debug.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\Description.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\Device.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\DeviceChangeListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\xml\DeviceData.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\DeviceList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\Disposer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\event\EventListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\util\Exception.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\io\File.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\io\FileInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\io\FileList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\HostInterface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTML.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTPDate.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTPHeader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\HTTPMUSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTPPacket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTPRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTPRequestListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTPResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTPServer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTPServerList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTPServerThread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTPSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\HTTPStatus.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\HTTPUSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\Icon.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\IconList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\InetSocketAddress.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\io\InputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\io\InputStreamReader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\InvalidDescriptionException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\io\LineNumberReader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\util\ListenerList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\MAN.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\MulticastSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\util\Mutex.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\NetworkInterface.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\NetworkInterfaceList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\xml\Node.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\xml\NodeData.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\xml\NodeList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\NotifyListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\event\NotifyRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\NT.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\NTS.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\Parameter.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\http\ParameterList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\xml\Parser.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\xml\ParserException.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\event\Property.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\event\PropertyList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\control\QueryListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\control\QueryRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\control\QueryResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\io\Reader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\control\RenewSubscriber.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\SearchListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\SearchResponseListener.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\ServerSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\Service.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\xml\ServiceData.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ServiceList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ServiceStateTable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\soap\SOAP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\soap\SOAPRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\soap\SOAPResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\Socket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\SocketImp.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\SocketInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\SocketUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPNotifyRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPNotifySocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPNotifySocketList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPPacket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPSearchRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPSearchResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPSearchResponseSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPSearchResponseSocketList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPSearchSocket.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\ssdp\SSDPSearchSocketList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\ST.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\StateVariable.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\xml\StateVariableData.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\io\StringBufferInputStream.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\io\StringReader.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\util\StringTokenizer.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\util\StringUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\event\Subscriber.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\event\SubscriberList.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\event\Subscription.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\event\SubscriptionRequest.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\event\SubscriptionResponse.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\util\Thread.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\util\TimeUtil.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\sql\UniDatabase.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\sql\UniMySQL.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\UPnP.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\UPnPStatus.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\URI.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\net\URL.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\upnp\device\USN.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\util\Vector.h
# End Source File
# Begin Source File

SOURCE=..\..\..\include\cybergarage\xml\XML.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\CyberLink.lib
# End Source File
# End Target
# End Project
