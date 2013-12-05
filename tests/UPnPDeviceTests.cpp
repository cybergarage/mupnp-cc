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

	/////////////////////////////
	// Search Device
	/////////////////////////////
    
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
