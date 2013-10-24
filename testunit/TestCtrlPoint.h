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

#ifndef _TESTCTRLPOINT_H_
#define _TESTCTRLPOINT_H_

#include <cybergarage/upnp/CyberLink.h>

using namespace CyberLink;

class TestCtrlPoint : public ControlPoint , public NotifyListener, public EventListener, public SearchResponseListener
{

public:

	TestCtrlPoint();
	
	////////////////////////////////////////////////
	//	Listener
	////////////////////////////////////////////////
	
public:

	void deviceNotifyReceived(SSDPPacket *packet);
	void deviceSearchResponseReceived(SSDPPacket *packet);
	void eventNotifyReceived(const char *uuid, long seq, const char *name, const char *value);

	void print();

};

#endif

