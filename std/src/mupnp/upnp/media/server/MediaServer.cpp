/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : MediaServer.cpp
*
*	04/03/04
*		- first revision.
*	05/19/04
*		- Changed the header include order for Cygwin.
*	02/24/06
*		- Added setName() and getName().
*
******************************************************************/

#include <mupnp/upnp/media/server/MediaServer.h>

#include <string>

using namespace std;
using namespace CyberLink;
using namespace CyberNet;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const char *MediaServer::DEVICE_TYPE = "urn:schemas-upnp-org:device:MediaServer:1";

const int MediaServer::DEFAULT_HTTP_PORT = 38520;

const char *MediaServer::DESCRIPTION = 
"<?xml version=\"1.0\" encoding=\"utf-8\"?> \n"
"<root xmlns=\"urn:schemas-upnp-org:device-1-0\"> \n"
"   <specVersion> \n"
"      <major>1</major> \n"
"      <minor>0</minor> \n"
"   </specVersion> \n"
"   <device> \n"
"      <deviceType>urn:schemas-upnp-org:device:MediaServer:1</deviceType> \n"
"      <friendlyName>Cyber Garage Media Server</friendlyName> \n"
"      <manufacturer>Cyber Garage</manufacturer> \n"
"      <manufacturerURL>http://www.cybergarage.org</manufacturerURL> \n"
"      <modelDescription>CyberGarage</modelDescription> \n"
"      <modelName>Cyber Garage Media Server</modelName> \n"
"      <modelNumber>1.0</modelNumber> \n"
"      <modelURL>http://www.cybergarage.org</modelURL> \n"
"      <serviceList> \n"
"         <service> \n"
"            <serviceType>urn:schemas-upnp-org:service:ContentDirectory:1</serviceType> \n"
"            <serviceId>urn:upnp-org:serviceId:urn:schemas-upnp-org:service:ContentDirectory</serviceId> \n"
"            <SCPDURL>/service/ContentDirectory1.xml</SCPDURL> \n"
"            <controlURL>/service/ContentDirectory_control</controlURL> \n"
"            <eventSubURL>/service/ContentDirectory_event</eventSubURL> \n"
"         </service> \n"
"         <service> \n"
"            <serviceType>urn:schemas-upnp-org:service:ConnectionManager:1</serviceType> \n"
"            <serviceId>urn:upnp-org:serviceId:urn:schemas-upnp-org:service:ConnectionManager</serviceId> \n"
"            <SCPDURL>/service/ConnectionManager1.xml</SCPDURL> \n"
"            <controlURL>/service/ConnectionManager_control</controlURL> \n"
"            <eventSubURL>/service/ConnectionManager_event</eventSubURL> \n"
"         </service> \n"
"      </serviceList> \n"
"   </device> \n"
"</root> \n";
	
////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
	
	
MediaServer::MediaServer() : Device()
{
	// Device Configuration
	loadDescription(MediaServer::DESCRIPTION);

	// Netwroking initialization		
	UPnP::SetEnable(UPnP::USE_ONLY_IPV4_ADDR);
	string firstIf;
	GetHostAddress(0, firstIf);
	setInterfaceAddress(firstIf.c_str());
	setHTTPPort(DEFAULT_HTTP_PORT);

	// Servce Configuration
	conMan = new ConnectionManager(this);
	conDir = new ContentDirectory(this);
		
	Service *servConMan = getService(ConnectionManager::SERVICE_TYPE);
	servConMan->loadSCPD(ConnectionManager::DESCRIPTION);
	servConMan->setActionListener(getConnectionManager());
	servConMan->setQueryListener(getConnectionManager());

	Service *servConDir = getService(ContentDirectory::SERVICE_TYPE);
	servConDir->loadSCPD(ContentDirectory::DESCRIPTION);
	servConDir->setActionListener(getContentDirectory());
	servConDir->setQueryListener(getContentDirectory());
}

MediaServer::~MediaServer()
{
	delete conMan;
	delete conDir;
	stop();		
}

////////////////////////////////////////////////
// HttpRequestListner (Overridded)
////////////////////////////////////////////////
	
void MediaServer::httpRequestRecieved(CyberHTTP::HTTPRequest *httpReq)
{
	string uri;
	httpReq->getURI(uri);
	
	if (uri.find(ContentDirectory::CONTENT_EXPORT_URI) != string::npos) {
		getContentDirectory()->contentExportRequestRecieved(httpReq);
		return;
	}
			 
	Device::httpRequestRecieved(httpReq);
}
