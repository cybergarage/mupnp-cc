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

#include <cybergarage/upnp/CyberLink.h>

using namespace CyberLink;
using namespace std;

//////////////////////////////////////////////////////////////////////
// testDevice
//////////////////////////////////////////////////////////////////////

static const char *UPNP_TEST_DEVICE_DESCR = 
"<?xml version=\"1.0\" ?>\n" 
"<root xmlns=\"urn:schemas-upnp-org:device-1-0\">"
"	<specVersion>"
"		<major>1</major> "
"		<minor>0</minor> "
"	</specVersion>"
"	<device>"
"		<deviceType>urn:schemas-upnp-org:device:clock:1</deviceType> "
"		<friendlyName>CyberGarage Clock Device</friendlyName> "
"		<manufacture>CyberGarage</manufacture> "
"		<manufactureURL>http://www.cybergarage.org</manufactureURL> "
"		<modelDescription>CyberUPnP Clock Device</modelDescription> "
"		<modelName>Clock</modelName> "
"		<modelNumber>1.0</modelNumber> "
"		<modelURL>http://www.cybergarage.org</modelURL> "
"		<serialNumber>1234567890</serialNumber> "
"		<UDN>uuid:cybergarageClockDevice</UDN> "
"		<UPC>123456789012</UPC> "
"		<iconList>"
"			<icon>"
"				<mimetype>image/gif</mimetype> "
"				<width>48</width> "
"				<height>32</height>" 
"				<depth>8</depth> "
"				<url>icon.gif</url> "
"			</icon>"
"		</iconList>"
"		<serviceList>"
"			<service>"
"				<serviceType>urn:schemas-upnp-org:service:timer:1</serviceType> "
"				<serviceId>urn:schemas-upnp-org:serviceId:timer:1</serviceId> "
"				<SCPDURL>/service/timer/description.xml</SCPDURL> "
"				<controlURL>/service/timer/control</controlURL> "
"				<eventSubURL>/service/timer/eventSub</eventSubURL> "
"			</service>"
"		</serviceList>"
"		<presentationURL>http://www.cybergarage.org</presentationURL> "
"	</device>"
"</root>";

char *UPNP_TEST_SERVICE_DESCR = 
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

char *UPNP_TEST_DEVICE_TYPE = "urn:schemas-upnp-org:device:test:1";

BOOST_AUTO_TEST_CASE(SimpleDeviceTests)
{
	Device *dev = new Device();
	
	//// parse device description ////

	BOOST_CHECK(dev->loadDescription(UPNP_TEST_DEVICE_DESCR));

	//BOOST_CHECK(strcmp(dev->getDeviceType(), "urn:schemas-upnp-org:device:clock:1") == 0);
	//cg_upnp_device_setdevicetype(dev, UPNP_TEST_DEVICE_TYPE);
	//BOOST_CHECK(strcmp(dev->getDeviceType(), UPNP_TEST_DEVICE_TYPE) == 0);
/*
	BOOST_CHECK(cg_upnp_device_isdevicetype(dev, UPNP_TEST_DEVICE_TYPE) == TRUE);
	
	BOOST_CHECK(strcmp(cg_upnp_device_getfriendlyname(dev), "CyberGarage Clock Device") == 0);
	BOOST_CHECK(strcmp(cg_upnp_device_getmanufacture(dev), "CyberGarage") == 0);
	BOOST_CHECK(strcmp(cg_upnp_device_getmanufactureurl(dev), "http://www.cybergarage.org") == 0);
	BOOST_CHECK(strcmp(cg_upnp_device_getmodeldescription(dev), "CyberUPnP Clock Device") == 0);
	BOOST_CHECK(strcmp(cg_upnp_device_getmodelname(dev), "Clock") == 0);
	BOOST_CHECK(strcmp(cg_upnp_device_getmodelnumber(dev), "1.0") == 0);
	BOOST_CHECK(strcmp(cg_upnp_device_getmodelurl(dev), "http://www.cybergarage.org") == 0);
	BOOST_CHECK(strcmp(cg_upnp_device_getserialnumber(dev), "1234567890") == 0);
	BOOST_CHECK(strcmp(cg_upnp_device_getudn(dev), "uuid:cybergarageClockDevice") == 0);
	BOOST_CHECK(strcmp(cg_upnp_device_getupc(dev), "123456789012") == 0);
	BOOST_CHECK(strcmp(cg_upnp_device_getpresentationurl(dev), "http://www.cybergarage.org") == 0);

	CgUpnpService *service = cg_upnp_device_getservicebyname(dev, "urn:schemas-upnp-org:serviceId:timer:1");
	BOOST_CHECK(service != NULL);
	BOOST_CHECK(cg_strcmp(cg_upnp_service_getservicetype(service), "urn:schemas-upnp-org:service:timer:1") == 0);
	BOOST_CHECK(cg_strcmp(cg_upnp_service_getserviceid(service), "urn:schemas-upnp-org:serviceId:timer:1") == 0);
	BOOST_CHECK(cg_strcmp(cg_upnp_service_getscpdurl(service), "/service/timer/description.xml") == 0);
	BOOST_CHECK(cg_strcmp(cg_upnp_service_getcontrolurl(service), "/service/timer/control") == 0);
	BOOST_CHECK(cg_strcmp(cg_upnp_service_geteventsuburl(service), "/service/timer/eventSub") == 0);
	
	CgUpnpIcon *icon = cg_upnp_device_geticon(dev, 0);
	BOOST_CHECK(icon != NULL);
	BOOST_CHECK(cg_strcmp(cg_upnp_icon_getmimetype(icon), "image/gif") == 0);
	BOOST_CHECK(cg_strcmp(cg_upnp_icon_getwidth(icon), "48") == 0);
	BOOST_CHECK(cg_strcmp(cg_upnp_icon_getheight(icon), "32") == 0);
	BOOST_CHECK(cg_strcmp(cg_upnp_icon_getdepth(icon), "8") == 0);
	BOOST_CHECK(cg_strcmp(cg_upnp_icon_geturl(icon), "icon.gif") == 0);
	
	//// parse service description ////
	CgUpnpService *timeService = cg_upnp_device_getservicebyname(dev, "urn:schemas-upnp-org:serviceId:timer:1");
	BOOST_CHECK(timeService != NULL);
	BOOST_CHECK(cg_upnp_service_getdevice(timeService) == dev);
	BOOST_CHECK(cg_upnp_service_getrootdevice(timeService) == dev);
	CgXmlNode *timeServiceNode = cg_upnp_service_getservicenode(timeService);
	BOOST_CHECK(timeServiceNode != NULL);
	BOOST_CHECK(cg_upnp_service_parsedescription(timeService, UPNP_TEST_SERVICE_DESCR, strlen(UPNP_TEST_SERVICE_DESCR)) == TRUE);
	
	CgUpnpAction *setAction = cg_upnp_service_getactionbyname(service, "SetTime");
	BOOST_CHECK(setAction != NULL);
	CgUpnpArgument *newArg = cg_upnp_action_getargumentbyname(setAction, "NewTime");
	BOOST_CHECK(cg_upnp_argument_isindirection(newArg) == TRUE);
	cg_upnp_argument_setvalue(newArg, "123456");
	BOOST_CHECK(cg_streq(cg_upnp_argument_getvalue(newArg), "123456") == TRUE);
	
	CgUpnpStateVariable *timeVar = cg_upnp_service_getstatevariablebyname(service, "Time");
	BOOST_CHECK(timeVar != NULL);
	BOOST_CHECK(strcmp(cg_upnp_statevariable_getdatatype(timeVar), "string") == 0);
	BOOST_CHECK(strcmp(cg_upnp_statevariable_getsendevents(timeVar), "yes") == 0);
	BOOST_CHECK(cg_upnp_statevariable_issendevents(timeVar) == TRUE);

	//// start ////
	
	cg_upnp_device_start(dev);
	
	//// stop ////
	
	cg_upnp_device_stop(dev);
	
	//// exit ////
	
	cg_upnp_device_delete(dev);
*/

	delete dev;
}

//////////////////////////////////////////////////////////////////////
// testDevice
//////////////////////////////////////////////////////////////////////

/*
BOOST_AUTO_TEST_CASE(TestDeviceTests)
{
	/////////////////////////////
	// Init Device
	/////////////////////////////

	TestDevice *testDev = NULL;
	testDev = new TestDevice();
	BOOST_CHECK(testDev != NULL);
	testDev->start();

	/////////////////////////////
	// VariableTest
	/////////////////////////////
		
	StateVariable *statVal = testDev->getStateVariable("Count");
	BOOST_CHECK(statVal != NULL);
	statVal->setValue(10);
	BOOST_CHECK(atoi(statVal->getValue()) == 10);
	statVal->setValue((const char *)NULL);
	statVal->setValue(10);
	BOOST_CHECK(atoi(statVal->getValue()) == 10);

	/////////////////////////////
	// Init ControlPoint
	/////////////////////////////

	TestCtrlPoint *ctrlp = new TestCtrlPoint();
	ctrlp->start();

	Wait(20 * 1000);

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

*/