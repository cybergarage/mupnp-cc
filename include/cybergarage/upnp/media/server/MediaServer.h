/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : MediaServer.h
*
*	04/03/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_MEDIASERVER_H_
#define _CLINK_MEDIA_MEDIASERVER_H_

#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/media/server/ContentDirectory.h>
#include <cybergarage/upnp/media/server/ConnectionManager.h>
#include <uhttp/net/HostInterface.h>

namespace CyberLink {

class MediaServer : public Device
{
	ContentDirectory *conDir;
	ConnectionManager *conMan;

	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////
	
public:

	static const char *DEVICE_TYPE;

	static const int DEFAULT_HTTP_PORT;
	
	static const char *DESCRIPTION;

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:
	
	MediaServer();

	~MediaServer();
	
	////////////////////////////////////////////////
	//	setName
	////////////////////////////////////////////////
	
public:

	void setName(const std::string &name)
	{
		setFriendlyName(name);
	}
	
	const char *getName()
	{
		getFriendlyName();
	}

	////////////////////////////////////////////////
	// Memeber
	////////////////////////////////////////////////
	
public:

	ConnectionManager *getConnectionManager()
	{
		return conMan;
	}

	ContentDirectory *getContentDirectory()
	{
		return conDir;
	}	
	
	////////////////////////////////////////////////
	//	ContentDirectory	
	////////////////////////////////////////////////

public:

	void addContentDirectory(Directory *dir)
	{
		getContentDirectory()->addDirectory(dir);
	}
	
	void removeContentDirectory(const std::string &name)
	{
		getContentDirectory()->removeDirectory(name);
	}

	void removeContentDirectory(int n)
	{
		getContentDirectory()->removeDirectory(n);
	}

	int getNContentDirectories()
	{
		return getContentDirectory()->getNDirectories();
	}
	
	Directory *getContentDirectory(int n)
	{
		return getContentDirectory()->getDirectory(n);
	}

	////////////////////////////////////////////////
	// PulgIn
	////////////////////////////////////////////////

public:

	bool addPlugIn(Format *format)
	{
		return getContentDirectory()->addPlugIn(format);
	}

	////////////////////////////////////////////////
	// HostAddress
	////////////////////////////////////////////////

public:

	void setInterfaceAddress(const std::string &ifaddr)
	{
		uHTTP::SetHostInterface(ifaddr);
	}

	const char *getInterfaceAddress()
	{
		return uHTTP::GetHostInterface();
	}			

	////////////////////////////////////////////////
	// HttpRequestListner (Overridded)
	////////////////////////////////////////////////

public:

	void httpRequestRecieved(uHTTP::HTTPRequest *httpReq);

	////////////////////////////////////////////////
	// start/stop (Overided)
	////////////////////////////////////////////////
	
public:

	bool start()
	{
		getContentDirectory()->start();
		Device::start();
		return true;
	}
	
	bool stop()
	{
		getContentDirectory()->stop();
		Device::stop();
		return true;
	}
	
	////////////////////////////////////////////////
	// update
	////////////////////////////////////////////////

public:

	void update()
	{
	}			

};

}

#endif


