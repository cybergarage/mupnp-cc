/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: upnpdump.cpp
*
*	Revision;
*
*	08/22/03
*		- first revision
*
******************************************************************/

#ifndef _UPNPDUMP_CTRLPOINT_H_
#define _UPNPDUMP_CTRLPOINT_H_

#include <cybergarage/upnp/CyberLink.h>

using namespace CyberLink;

class CtrlPoint : public ControlPoint , public NotifyListener, public EventListener, public SearchResponseListener
{

public:

	CtrlPoint();
	
	////////////////////////////////////////////////
	//	Listener
	////////////////////////////////////////////////
	
public:

	void deviceNotifyReceived(SSDPPacket *packet);
	void deviceSearchResponseReceived(SSDPPacket *packet);
	void eventNotifyReceived(const std::string &uuid, long seq, const std::string &name, const std::string &value);

	void print();

};

#endif

