/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPSearchResponseSocket.cpp
*
*	Revision;
*
*	08/14/03
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/ControlPoint.h>
#include <cybergarage/upnp/ssdp/SSDPSearchResponseSocket.h>

using namespace CyberLink;
<<<<<<< HEAD

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

SSDPSearchResponseSocket::SSDPSearchResponseSocket()
{
	setControlPoint(NULL);
}
	
SSDPSearchResponseSocket::SSDPSearchResponseSocket(const std::string &bindAddr, int port) : HTTPUSocket(bindAddr, port)
{
	setControlPoint(NULL);
}

SSDPSearchResponseSocket::~SSDPSearchResponseSocket()
{
	stop();
	close();
}
=======

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

SSDPSearchResponseSocket::SSDPSearchResponseSocket()
{
	setControlPoint(NULL);
}
	
SSDPSearchResponseSocket::SSDPSearchResponseSocket(const char *bindAddr, int port) : HTTPUSocket(bindAddr, port)
{
	setControlPoint(NULL);
}

SSDPSearchResponseSocket::~SSDPSearchResponseSocket()
{
	stop();
	close();
}
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2

////////////////////////////////////////////////
//	run	
////////////////////////////////////////////////

void SSDPSearchResponseSocket::run()
{
	ControlPoint *ctrlPoint = getControlPoint();
	while (isRunnable() == true) {
		//Thread.yield();
		SSDPPacket *packet = receive();
		if (packet == NULL)
			continue;
		if (ctrlPoint != NULL)
			ctrlPoint->searchResponseReceived(packet); 
	}
}
