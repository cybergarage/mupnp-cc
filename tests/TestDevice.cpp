/******************************************************************
*
*	CyberUPnP for Java
*
*	Copyright (C) Satoshi Konno 2002-2004
*
*	File : TestDevice.cpp
*
******************************************************************/

#include "TestDevice.h"

#include <iostream>
#include <sstream>

using namespace std;
using namespace CyberLink;

TestDevice::TestDevice()
{
    loadDescription(DEVICE_DESCRIPTION);
    
	Service *counterService = getService("urn:schemas-upnp-org:service:count:1");
	counterService->loadSCPD(SERVICE_DESCRIPTION);
    
	Action *getCountAction = getAction("GetCount");
	getCountAction->setActionListener(this);
		
	Action *setCountAction = getAction("SetCount");
	setCountAction->setActionListener(this);
		
	ServiceList *serviceList = getServiceList();
	Service *service = serviceList->getService(0);
	service->setQueryListener(this);
}

////////////////////////////////////////////////
// ActionListener
////////////////////////////////////////////////

bool TestDevice::actionControlReceived(Action *action)
{
	const char *actionName = action->getName();
	if (strcmp("GetCount", actionName) == 0) {
		Argument *countArg = action->getArgument("CurrentCount");
		countArg->setValue(count);
		return true;
	}
	if (strcmp(actionName, "SetCount") == 0) {
		Argument *countArg = action->getArgument("NewCount");
		int newCount = countArg->getIntegerValue();
		count = newCount;
		return true;
	}
	return false;
}

////////////////////////////////////////////////
// QueryListener
////////////////////////////////////////////////

bool TestDevice::queryControlReceived(StateVariable *stateVar)
{
	string clockVal;
	stateVar->setValue(count);
	return true;
}

////////////////////////////////////////////////
// HttpRequestListner
////////////////////////////////////////////////
	
uHTTP::HTTP::StatusCode TestDevice::httpRequestRecieved(HTTPRequest *httpReq)
{
	ParameterList paramList;
	httpReq->getParameterList(paramList);
	for (int n=0; n<paramList.size(); n++) {
		Parameter *param = paramList.getParameter(n);
		cout << "["<< n << "] : "<< param->getName() << "= "<< param->getValue() << endl;
	}

	string uri;
	httpReq->getURI(uri);
	if (uri.find(PRESENTATION_URI) == string::npos)  {
		return Device::httpRequestRecieved(httpReq);
	}
			 
	string contents;
	contents = "<HTML><BODY><H1>";
	contents += "";
	contents += "</H1></BODY></HTML>";
		
	HTTPResponse httpRes;
	httpRes.setStatusCode(HTTP::OK_REQUEST);
	httpRes.setContent(contents);
	return httpReq->post(&httpRes);
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////

void TestDevice::update()
{
}			

////////////////////////////////////////////////
// Device Description
////////////////////////////////////////////////

const char *TestDevice::DEVICE_DESCRIPTION =
"<?xml version=\"1.0\"?>\n"
"<root xmlns=\"urn:schemas-upnp-org:device-1-0\">\n"
"	<specVersion>\n"
"		<major>1</major>\n"
"		<minor>0</minor>\n"
"	</specVersion>\n"
"	<device>\n"
"		<deviceType>urn:schemas-upnp-org:device:count:1</deviceType>\n"
"		<friendlyName>CyberGarageCountDevice</friendlyName>\n"
"		<manufacturer>CyberGarage</manufacturer>\n"
"		<manufacturerURL>http://www.cybergarage.org</manufacturerURL>\n"
"		<modelDescription>CyberLink Count Device</modelDescription>\n"
"		<modelName>Count</modelName>\n"
"		<modelNumber>1.0</modelNumber>\n"
"		<modelURL>http://www.cybergarage.org</modelURL>\n"
"		<serialNumber>1234567890</serialNumber>\n"
"		<UPC>123456789012</UPC>\n"
"		<iconList>\n"
"			<icon>\n"
"				<mimetype>image/gif</mimetype>\n"
"				<width>48</width>\n"
"				<height>32</height>\n"
"				<depth>8</depth>\n"
"				<url>icon.gif</url>\n"
"			</icon>\n"
"		</iconList>\n"
"		<serviceList>\n"
"			<service>\n"
"				<serviceType>urn:schemas-upnp-org:service:count:1</serviceType>\n"
"				<serviceId>urn:schemas-upnp-org:serviceId:count:1</serviceId>\n"
"				<SCPDURL>/service/count/description.xml</SCPDURL>\n"
"				<controlURL>/service/count/control</controlURL>\n"
"				<eventSubURL>/service/count/eventSub</eventSubURL>\n"
"			</service>\n"
"		</serviceList>\n"
"		<presentationURL>/presentation</presentationURL>\n"
"	</device>\n"
"</root>\n";

////////////////////////////////////////////////
// Service Description
////////////////////////////////////////////////

const char *TestDevice::SERVICE_DESCRIPTION = 
"<?xml version=\"1.0\"?>\n"
"<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\">\n"
"	<specVersion>\n"
"		<major>1</major>\n"
"		<minor>0</minor>\n"
"	</specVersion>\n"
"	<actionList>\n"
"		<action>\n"
"			<name>SetCount</name>\n"
"			<argumentList>\n"
"				<argument>\n"
"					<name>NewCount</name>\n"
"					<relatedStateVariable>Count</relatedStateVariable>\n"
"					<direction>in</direction>\n"
"				</argument>\n"
"				<argument>\n"
"					<name>Result</name>\n"
"					<relatedStateVariable>Result</relatedStateVariable>\n"
"					<direction>out</direction>\n"
"				</argument>\n"
"			</argumentList>\n"
"		</action>\n"
"		<action>\n"
"			<name>GetCount</name>\n"
"			<argumentList>\n"
"				<argument>\n"
"					<name>CurrentCount</name>\n"
"					<relatedStateVariable>Count</relatedStateVariable>\n"
"					<direction>out</direction>\n"
"				</argument>\n"
"			</argumentList>\n"
"		</action>\n"
"	</actionList>\n"
"	<serviceStateTable>\n"
"		<stateVariable sendEvents=\"yes\">\n"
"			<name>Count</name>\n"
"			<dataType>string</dataType>\n"
"		</stateVariable>\n"
"		<stateVariable sendEvents=\"no\">\n"
"			<name>Result</name>\n"
"			<dataType>string</dataType>\n"
"		</stateVariable>\n"
"	</serviceStateTable>\n"
"</scpd>\n";
