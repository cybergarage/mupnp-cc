/******************************************************************
*
*	CyberUPnP for Java
*
*	Copyright (C) Satoshi Konno 2002
*
*	File : ClockDevice.java
*
******************************************************************/

#ifndef _CLINK_CLOCKDEVICE_H_
#define _CLINK_CLOCKDEVICE_H_

#include <cybergarage/upnp/CyberLink.h>
#include "Clock.h"

using namespace CyberLink;
using namespace uHTTP;

const char CLOCK_DESCRIPTION_FILE_NAME[] = "description/description.xml";
const char CLOCK_PRESENTATION_URI[] = "/presentation";

const char CLOCK_DEVICE_DESCRIPTION[] =
"<?xml version=\"1.0\" ?>\n"
"<root xmlns=\"urn:schemas-upnp-org:device-1-0\">\n"
" 	<specVersion>\n"
" 		<major>1</major>\n"
" 		<minor>0</minor>\n"
" 	</specVersion>\n"
" 	<device>\n"
" 		<deviceType>urn:schemas-upnp-org:device:clock:1</deviceType>\n"
" 		<friendlyName>CyberGarage Clock Device</friendlyName>\n"
" 		<manufacturer>CyberGarage</manufacturer>\n"
" 		<manufacturerURL>http://www.cybergarage.org</manufacturerURL>\n"
" 		<modelDescription>CyberUPnP Clock Device</modelDescription>\n"
" 		<modelName>Clock</modelName>\n"
" 		<modelNumber>1.0</modelNumber>\n"
" 		<modelURL>http://www.cybergarage.org</modelURL>\n"
" 		<serialNumber>1234567890</serialNumber>\n"
" 		<UDN>uuid:cybergarageClockDevice</UDN>\n"
" 		<UPC>123456789012</UPC>\n"
" 		<iconList>\n"
" 			<icon>\n"
" 				<mimetype>image/gif</mimetype>\n"
" 				<width>48</width>\n"
" 				<height>32</height>\n"
" 				<depth>8</depth>\n"
" 				<url>icon.gif</url>\n"
" 			</icon>\n"
" 		</iconList>\n"
" 		<serviceList>\n"
" 			<service>\n"
" 				<serviceType>urn:schemas-upnp-org:service:timer:1</serviceType>\n"
" 				<serviceId>urn:schemas-upnp-org:serviceId:timer:1</serviceId>\n"
" 				<SCPDURL>/service/timer/description.xml</SCPDURL>\n"
" 				<controlURL>/service/timer/control</controlURL>\n"
" 				<eventSubURL>/service/timer/eventSub</eventSubURL>\n"
" 			</service>\n"
" 		</serviceList>\n"
" 		<presentationURL>/presentation</presentationURL>\n"
"	</device>\n"
"</root>\n";

const char CLOCK_SERVICE_DESCRIPTION[] =
"<?xml version=\"1.0\"?>\n"
"<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\" >\n"
" 	<specVersion>\n"
" 		<major>1</major>\n"
" 		<minor>0</minor>\n"
" 	</specVersion>\n"
" 	<actionList>\n"
" 		<action>\n"
" 			<name>SetTime</name>\n"
" 			<argumentList>\n"
" 				<argument>\n"
" 					<name>NewTime</name>\n"
" 					<relatedStateVariable>Time</relatedStateVariable>\n"
" 					<direction>in</direction>\n"
" 				</argument>\n"
" 				<argument>\n"
" 					<name>Result</name>\n"
" 					<relatedStateVariable>Result</relatedStateVariable>\n"
" 					<direction>out</direction>\n"
" 				</argument>\n"
" 			</argumentList>\n"
" 		</action>\n"
" 		<action>\n"
" 			<name>GetTime</name>\n"
" 			<argumentList>\n"
" 				<argument>\n"
" 					<name>CurrentTime</name>\n"
" 					<relatedStateVariable>Time</relatedStateVariable>\n"
" 					<direction>out</direction>\n"
" 				</argument>\n"
" 			</argumentList>\n"
" 		</action>\n"
" 	</actionList>\n"
" 	<serviceStateTable>\n"
" 		<stateVariable sendEvents=\"yes\">\n"
" 			<name>Time</name>\n"
" 			<dataType>string</dataType>\n"
" 		</stateVariable>\n"
" 		<stateVariable sendEvents=\"no\">\n"
" 			<name>Result</name>\n"
" 			<dataType>string</dataType>\n"
" 		</stateVariable>\n"
" 	</serviceStateTable>\n"
"</scpd>\n";

class ClockDevice : public Device, public ActionListener, public QueryListener
{
	StateVariable *timeVar;
	
public:

	ClockDevice();

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

