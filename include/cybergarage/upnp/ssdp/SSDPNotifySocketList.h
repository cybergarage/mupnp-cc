/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SSDPNotifySocketList.h
*
*	Revision;
*
*	07/11/03
*		- first revision
*
******************************************************************/

#ifndef _CLINK_SSDPNOTIFYSOCKETLIST_H_
#define _CLINK_SSDPNOTIFYSOCKETLIST_H_

#include <cybergarage/net/HostInterface.h>
#include <cybergarage/util/Vector.h>
#include <cybergarage/upnp/ssdp/SSDPNotifySocket.h>

namespace CyberLink {

class ControlPoint;

class SSDPNotifySocketList : public CyberUtil::Vector 
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
public:

	SSDPNotifySocketList();

	~SSDPNotifySocketList();

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////
	
public:

	SSDPNotifySocket *getSSDPNotifySocket(int n)
	{
		return (SSDPNotifySocket *)get(n);
	}

	////////////////////////////////////////////////
	//	ControlPoint
	////////////////////////////////////////////////

public:

	void setControlPoint(ControlPoint *ctrlPoint);

	////////////////////////////////////////////////
	//	open/close
	////////////////////////////////////////////////
	
public:

	bool open();
	void close();
	
	////////////////////////////////////////////////
	//	start/stop
	////////////////////////////////////////////////
	
public:

	void start();
	void stop();
	
	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif


