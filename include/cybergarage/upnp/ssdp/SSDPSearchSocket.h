/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPSearchSocket.h
*
*	Revision;
*
*	07/05/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SSDPSEARCHSOCKET_H_
#define _CLINK_SSDPSEARCHSOCKET_H_

#include <string>

#include <cybergarage/util/ListenerList.h>
#include <cybergarage/util/Thread.h>
#include <cybergarage/net/HostInterface.h>
#include <cybergarage/upnp/ssdp/SSDP.h>
#include <cybergarage/upnp/ssdp/HTTPMUSocket.h>
#include <cybergarage/upnp/device/SearchListener.h>

namespace CyberLink {

class SSDPSearchSocket : public HTTPMUSocket, public CyberUtil::Thread
{
	bool useIPv6Address;
	CyberUtil::ListenerList deviceSearchListenerList;

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	SSDPSearchSocket();
	SSDPSearchSocket(const char *bindAddr);
	~SSDPSearchSocket();

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	bool open(const char *bindAddr);

	////////////////////////////////////////////////
	//	deviceSearch
	////////////////////////////////////////////////

public:

	void addSearchListener(SearchListener *listener)
	{
		deviceSearchListenerList.add(listener);
	}		

	void removeSearchListener(SearchListener *listener)
	{
		deviceSearchListenerList.remove(listener);
	}		

	void performSearchListener(SSDPPacket *ssdpPacket)
	{
		int listenerSize = deviceSearchListenerList.size();
		for (int n=0; n<listenerSize; n++) {
			SearchListener *listener = (SearchListener *)deviceSearchListenerList.get(n);
			listener->deviceSearchReceived(ssdpPacket);
		}
	}		

	////////////////////////////////////////////////
	//	run	
	////////////////////////////////////////////////

public:

	void run();

};

}

#endif



