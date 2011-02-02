/******************************************************************
*
*	CyberUPnP for Java
*
*	Copyright (C) Satoshi Konno 2002
*
*	File : TestMediaServer.h
*
******************************************************************/

#ifndef _CLINK_TESTMEDIASERVER_H_
#define _CLINK_TESTMEDIASERVER_H_

#include <cybergarage/upnp/MediaServer.h>

using namespace CyberLink;
using namespace CyberHTTP;

const char MEDIA_SERVER_DESCRIPTION_FILE_NAME[] = "testMediaServer/description.xml";

class TestMediaServer : public MediaServer
{
	int count;
	
public:

	TestMediaServer();

};

#endif

