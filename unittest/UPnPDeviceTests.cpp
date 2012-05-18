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
#include <cybergarage/util/TimeUtil.h>

#include "TestDevice.h"
#include "TestCtrlPoint.h"

using namespace CyberLink;
using namespace std;

//////////////////////////////////////////////////////////////////////
// testDevice
//////////////////////////////////////////////////////////////////////

const std::string UPNP_TEST_DEVICE_DESCR = 
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

const std::string UPNP_TEST_SERVICE_DESCR = 
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

BOOST_AUTO_TEST_CASE(DeveiceDescriptionParceTest)
{
	Device *dev = new Device();
	BOOST_CHECK(dev->loadDescription(UPNP_TEST_DEVICE_DESCR));
	BOOST_CHECK(strcmp(dev->getDeviceType(), "urn:schemas-upnp-org:device:clock:1") == 0);
	delete dev;
}

//////////////////////////////////////////////////////////////////////
// testDevice
//////////////////////////////////////////////////////////////////////

BOOST_AUTO_TEST_CASE(TestDeviceTests)
{
	/////////////////////////////
	// Init Device
	/////////////////////////////

	TestDevice *testDev = new TestDevice();
	BOOST_CHECK(testDev);
	testDev->start();

	/////////////////////////////
	// VariableTest
	/////////////////////////////
		
	StateVariable *statVal = testDev->getStateVariable("Count");
	BOOST_CHECK(statVal != NULL);
	statVal->setValue(10);
	BOOST_CHECK(atoi(statVal->getValue()) == 10);
	statVal->setValue("");
	statVal->setValue(10);
	BOOST_CHECK(atoi(statVal->getValue()) == 10);

	/////////////////////////////
	// Init ControlPoint
	/////////////////////////////

	TestCtrlPoint *ctrlp = new TestCtrlPoint();
	ctrlp->start();

    Wait((5 * 1000));
    
	Device *ctrlpDev = ctrlp->getDevice("CyberGarageCountDevice");
	BOOST_CHECK(ctrlpDev != NULL);

	/////////////////////////////
	// Action Test
	/////////////////////////////
		
	Action *ctrlpSetCountAction = ctrlpDev->getAction("SetCount");
	BOOST_CHECK(ctrlpSetCountAction != NULL);
	ctrlpSetCountAction->setArgumentValue("NewCount", 12);
	BOOST_CHECK(ctrlpSetCountAction->postControlAction() == true);
		
	Action *ctrlpGetCountAction = ctrlpDev->getAction("GetCount");
	BOOST_CHECK(ctrlpGetCountAction != NULL);
	BOOST_CHECK(ctrlpGetCountAction->postControlAction() == true);
	BOOST_CHECK(ctrlpGetCountAction->getArgumentIntegerValue("CurrentCount") == 12);

	/////////////////////////////
	// Event Test
	/////////////////////////////

	Service *ctrlpCountService = ctrlpDev->getService("urn:schemas-upnp-org:service:count:1");
	BOOST_CHECK(ctrlpCountService != NULL);
	BOOST_CHECK(ctrlp->subscribe(ctrlpCountService) == true);
	BOOST_CHECK(ctrlp->unsubscribe(ctrlpCountService) == true);

	/////////////////////////////
	// Exit
	/////////////////////////////

	ctrlp->stop();
	delete ctrlp;
    
	testDev->stop();
	delete testDev;
}
