/******************************************************************
 *
 * CyberLink for C++
 *
 * Copyright (C) Satoshi Konno 2002-2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>

#include <cybergarage/upnp/CyberLink.h>
#include <uhttp/util/TimeUtil.h>

#include "TestDevice.h"
#include "TestCtrlPoint.h"

using namespace CyberLink;
using namespace std;

//////////////////////////////////////////////////////////////////////
// Sample 01
//////////////////////////////////////////////////////////////////////

const std::string UPNP_TEST_DEVICE_DESCR_01 = 
"<?xml version=\"1.0\" ?>\n" 
"<root xmlns=\"urn:schemas-upnp-org:device-1-0\">"
"	<specVersion>"
"		<major>1</major>"
"		<minor>0</minor>"
"	</specVersion>"
"	<device>"
"		<deviceType>urn:schemas-upnp-org:device:clock:1</deviceType>"
"		<friendlyName>CyberGarage Clock Device</friendlyName>"
"		<manufacture>CyberGarage</manufacture>"
"		<manufactureURL>http://www.cybergarage.org</manufactureURL>"
"		<modelDescription>CyberUPnP Clock Device</modelDescription>"
"		<modelName>Clock</modelName>"
"		<modelNumber>1.0</modelNumber>"
"		<modelURL>http://www.cybergarage.org</modelURL>"
"		<serialNumber>1234567890</serialNumber>"
"		<UDN>uuid:cybergarageClockDevice</UDN>"
"		<UPC>123456789012</UPC>"
"		<iconList>"
"			<icon>"
"				<mimetype>image/gif</mimetype>"
"				<width>48</width>"
"				<height>32</height>" 
"				<depth>8</depth>"
"				<url>icon.gif</url>"
"			</icon>"
"		</iconList>"
"		<serviceList>"
"			<service>"
"				<serviceType>urn:schemas-upnp-org:service:timer:1</serviceType>"
"				<serviceId>urn:schemas-upnp-org:serviceId:timer:1</serviceId>"
"				<SCPDURL>/service/timer/description.xml</SCPDURL>"
"				<controlURL>/service/timer/control</controlURL>"
"				<eventSubURL>/service/timer/eventSub</eventSubURL>"
"			</service>"
"		</serviceList>"
"		<presentationURL>http://www.cybergarage.org</presentationURL>"
"	</device>"
"</root>";

const std::string UPNP_TEST_SERVICE_DESCR_01 = 
"<?xml version=\"1.0\"?>\n"
"<scpd xmlns=\"urn:schemas-upnp-org:service-1-0\" >"
"	<specVersion>"
"		<major>1</major>"
"		<minor>0</minor>"
"	</specVersion>"
"	<actionList>"
"		<action>"
"			<name>SetTime</name>"
"			<argumentList>"
"				<argument>"
"					<name>NewTime</name>"
"					<relatedStateVariable>Time</relatedStateVariable>"
"					<direction>in</direction>"
"				</argument>"
"				<argument>"
"					<name>Result</name>"
"					<relatedStateVariable>Result</relatedStateVariable>"
"					<direction>out</direction>"
"				</argument>"
"			</argumentList>"
"		</action>"
"		<action>"
"			<name>GetTime</name>"
"			<argumentList>"
"				<argument>"
"					<name>CurrentTime</name>"
"					<relatedStateVariable>Time</relatedStateVariable>"
"					<direction>out</direction>"
"				</argument>"
"			</argumentList>"
"		</action>"
"	</actionList>"
"	<serviceStateTable>"
"		<stateVariable sendEvents=\"yes\">"
"			<name>Time</name>"
"			<dataType>string</dataType>"
"		</stateVariable>"
"		<stateVariable sendEvents=\"no\">"
"			<name>Result</name>"
"			<dataType>string</dataType>"
"		</stateVariable>"
"	</serviceStateTable>"
"</scpd>";

const std::string UPNP_TEST_DEVICE_TYPE = "urn:schemas-upnp-org:device:test:1";

BOOST_AUTO_TEST_CASE(DeveiceDescriptionParceTest01)
{
	Device *dev = new Device();
	BOOST_CHECK(dev->loadDescription(UPNP_TEST_DEVICE_DESCR_01));
	BOOST_CHECK(strcmp(dev->getDeviceType(), "urn:schemas-upnp-org:device:clock:1") == 0);
	delete dev;
}

//////////////////////////////////////////////////////////////////////
// Sample 02
//////////////////////////////////////////////////////////////////////

static const std::string UPNP_TEST_DEVICE_DESCR_02 =
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

BOOST_AUTO_TEST_CASE(DeveiceDescriptionParceTest02)
{
	Device *dev = new Device();
	BOOST_CHECK(dev->loadDescription(UPNP_TEST_DEVICE_DESCR_02));
	BOOST_CHECK(strcmp(dev->getDeviceType(), "urn:schemas-upnp-org:device:clock:1") == 0);
	delete dev;
}

