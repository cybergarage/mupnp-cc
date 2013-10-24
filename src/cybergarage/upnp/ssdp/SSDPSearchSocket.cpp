<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPSearchSocket.cpp
*
*	Revision;
*
*	08/14/03
*		- first revision
*	04/20/05
*		- Mikael Hakman <mhakman@dkab.net>
*		- Added close() in stop().
*		- Added test for null return from receive() in run().
*
******************************************************************/

#include <cybergarage/upnp/ControlPoint.h>
#include <cybergarage/upnp/ssdp/SSDPSearchSocket.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

SSDPSearchSocket::SSDPSearchSocket()
{
}

SSDPSearchSocket::SSDPSearchSocket(const std::string &bindAddr)
{
	open(bindAddr);
}

SSDPSearchSocket::~SSDPSearchSocket()
{
	stop();
	close();
}

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

bool SSDPSearchSocket::open(const std::string &bindAddr)
{
	const char *addr = SSDP::ADDRESS;
	useIPv6Address = false;
	if (uHTTP::IsIPv6Address(bindAddr) == true) {
		addr = SSDP::GetIPv6Address();
		useIPv6Address = true;
	}
	return HTTPMUSocket::open(addr, SSDP::PORT, bindAddr);
}

////////////////////////////////////////////////
//	run	
////////////////////////////////////////////////

void SSDPSearchSocket::run()
{
	while (isRunnable() == true) {
		//Thread.yield();
		SSDPPacket *packet = receive();
		if (packet == NULL)
			continue;
		if (packet->isDiscover() == true)
			performSearchListener(packet);
	}
}
=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPSearchSocket.cpp
*
*	Revision;
*
*	08/14/03
*		- first revision
*	04/20/05
*		- Mikael Hakman <mhakman@dkab.net>
*		- Added close() in stop().
*		- Added test for null return from receive() in run().
*
******************************************************************/

#include <cybergarage/upnp/ControlPoint.h>
#include <cybergarage/upnp/ssdp/SSDPSearchSocket.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

SSDPSearchSocket::SSDPSearchSocket()
{
}

SSDPSearchSocket::SSDPSearchSocket(const char *bindAddr)
{
	open(bindAddr);
}

SSDPSearchSocket::~SSDPSearchSocket()
{
	stop();
	close();
}

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

bool SSDPSearchSocket::open(const char *bindAddr)
{
	const char *addr = SSDP::ADDRESS;
	useIPv6Address = false;
	if (CyberNet::IsIPv6Address(bindAddr) == true) {
		addr = SSDP::GetIPv6Address();
		useIPv6Address = true;
	}
	return HTTPMUSocket::open(addr, SSDP::PORT, bindAddr);
}

////////////////////////////////////////////////
//	run	
////////////////////////////////////////////////

void SSDPSearchSocket::run()
{
	while (isRunnable() == true) {
		//Thread.yield();
		SSDPPacket *packet = receive();
		if (packet == NULL)
			continue;
		if (packet->isDiscover() == true)
			performSearchListener(packet);
	}
}
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
