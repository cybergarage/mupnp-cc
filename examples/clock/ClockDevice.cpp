/******************************************************************
*
*	CyberUPnP for Java
*
*	Copyright (C) Satoshi Konno 2002-2004
*
*	File : ClockDevice.java
*
******************************************************************/

#include <string.h>
#include <iostream>
#include <sstream>

#include "ClockDevice.h"
#include "Clock.h"

using namespace std;
using namespace CyberLink;

//#define USE_CLOCK_DESCRIPTION_FILE

#if defined(USE_CLOCK_DESCRIPTION_FILE)
ClockDevice::ClockDevice() : Device(CLOCK_DESCRIPTION_FILE_NAME)
#else
ClockDevice::ClockDevice() : Device()
#endif
{
#if !defined(USE_CLOCK_DESCRIPTION_FILE)
	loadDescription(CLOCK_DEVICE_DESCRIPTION);
	Service *timeService = getService("urn:schemas-upnp-org:service:timer:1");
	timeService->loadSCPD(CLOCK_SERVICE_DESCRIPTION);
#endif

	Action *getTimeAction = getAction("GetTime");
	getTimeAction->setActionListener(this);
		
	Action *setTimeAction = getAction("SetTime");
	setTimeAction->setActionListener(this);
		
	ServiceList *serviceList = getServiceList();
	Service *service = serviceList->getService(0);
	service->setQueryListener(this);

	timeVar = getStateVariable("Time");

	setLeaseTime(60);
}

////////////////////////////////////////////////
// ActionListener
////////////////////////////////////////////////

bool ClockDevice::actionControlReceived(Action *action)
{
	const char *actionName = action->getName();
	if (strcmp("GetTime", actionName) == 0) {
		std::string dateStr;
		Clock clock;
		clock.toString(dateStr);
		Argument *timeArg = action->getArgument("CurrentTime");
		timeArg->setValue(dateStr.c_str());
		return true;
	}
	if (strcmp(actionName, "SetTime") == 0) {
		Argument *timeArg = action->getArgument("NewTime");
		const char *newTime = timeArg->getValue();
		Argument *resultArg = action->getArgument("Result");
		std::ostringstream valbuf;
		valbuf << "Not implemented (" << newTime << ")";
		resultArg->setValue(valbuf.str().c_str());
		return true;
	}
	return false;
}

////////////////////////////////////////////////
// QueryListener
////////////////////////////////////////////////

bool ClockDevice::queryControlReceived(StateVariable *stateVar)
{
	const char *varName = stateVar->getName();
	Clock clock;
	string clockVal;
	stateVar->setValue(clock.toString(clockVal));
	return true;
}

////////////////////////////////////////////////
// HttpRequestListner
////////////////////////////////////////////////
	
uHTTP::HTTP::StatusCode ClockDevice::httpRequestRecieved(HTTPRequest *httpReq)
{
	ParameterList paramList;
	httpReq->getParameterList(paramList);
	for (int n=0; n<paramList.size(); n++) {
		Parameter *param = paramList.getParameter(n);
		cout << "[" << n << "] : " << param->getName() << " = " << param->getValue() << endl;
	}

	string uri;
	httpReq->getURI(uri);
	if (uri.find(CLOCK_PRESENTATION_URI) == string::npos)  {
		return Device::httpRequestRecieved(httpReq);
	}
			 
	string clockStr;
	Clock clock;
	clock.toString(clockStr);
	string contents;
	contents = "<HTML><BODY><H1>";
	contents += clockStr;
	contents += "</H1></BODY></HTML>";
		
	HTTPResponse httpRes;
	httpRes.setStatusCode(HTTP::OK_REQUEST);
	httpRes.setContent(contents);
	return httpReq->post(&httpRes);
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////

void ClockDevice::update()
{
	Clock clock;
	std::string timeStr;
	clock.toString(timeStr);
	timeVar->setValue(timeStr.c_str());
	//scout << "time = " << timeStr << endl;
}			

