/******************************************************************
*
*	CyberUPnP for Java
*
*	Copyright (C) Satoshi Konno 2002
*
*	File : TestDevice.h
*
******************************************************************/

#ifndef _CLINK_TESTDEVICE_H_
#define _CLINK_TESTDEVICE_H_

#include <cybergarage/upnp/CyberLink.h>

using namespace CyberLink;
using namespace uHTTP;

const char PRESENTATION_URI[] = "/presentation";

class TestDevice : public Device, public ActionListener, public QueryListener
{
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////

private:

	static const char *DEVICE_DESCRIPTION;
	static const char *SERVICE_DESCRIPTION;

	////////////////////////////////////////////////
	// Member
	////////////////////////////////////////////////

	int count;
	
public:

	TestDevice();

	////////////////////////////////////////////////
	// ActionListener
	////////////////////////////////////////////////

	bool actionControlReceived(Action *action);

	////////////////////////////////////////////////
	// QueryListener
	////////////////////////////////////////////////

	bool queryControlReceived(StateVariable *stateVar);

	////////////////////////////////////////////////
	// HttpRequestListner
	////////////////////////////////////////////////

	uHTTP::HTTP::StatusCode httpRequestRecieved(HTTPRequest *httpReq);

	////////////////////////////////////////////////
	// update
	////////////////////////////////////////////////

	void update();
};

#endif

