/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <boost/test/unit_test.hpp>
#include <boost/thread.hpp>

#include <mupnp/UPnP.h>
#include <uhttp/util/TimeUtil.h>

#include "TestDevice.h"
#include "TestCtrlPoint.h"

using namespace mUPnP;
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
  BOOST_CHECK(testDev->start());

  /////////////////////////////
  // VariableTest
  /////////////////////////////
    
  StateVariable *statVal = testDev->getStateVariable("Count");
  BOOST_CHECK(statVal);
  statVal->setValue(10);
  BOOST_CHECK(atoi(statVal->getValue()) == 10);
  statVal->setValue("");
  statVal->setValue(10);
  BOOST_CHECK(atoi(statVal->getValue()) == 10);

  /////////////////////////////
  // Init ControlPoint
  /////////////////////////////

  TestCtrlPoint *ctrlp = new TestCtrlPoint();
  BOOST_CHECK(ctrlp->start());
  BOOST_CHECK(ctrlp->search());

  /////////////////////////////
  // Search Device
  /////////////////////////////
  
  mupnp_shared_ptr<Device> ctrlpDev;
  
  while (!ctrlpDev) {
    BOOST_CHECK(ctrlp->search());
    Wait((SSDP::DEFAULT_MSEARCH_MX * 1000));
    BOOST_CHECK(testDev->announce());
    Wait((SSDP::DEFAULT_MSEARCH_MX * 1000));
    ctrlpDev = ctrlp->getDevice("CyberGarageCountDevice");
  }
  
  BOOST_CHECK(ctrlpDev);
    
  /////////////////////////////
  // Action Test
  /////////////////////////////
    
  Action *ctrlpSetCountAction = ctrlpDev->getAction("SetCount");
  BOOST_CHECK(ctrlpSetCountAction);
  ctrlpSetCountAction->setArgumentValue("NewCount", 12);
  BOOST_CHECK(ctrlpSetCountAction->postControlAction() == true);
    
  Action *ctrlpGetCountAction = ctrlpDev->getAction("GetCount");
  BOOST_CHECK(ctrlpGetCountAction);
  BOOST_CHECK(ctrlpGetCountAction->postControlAction() == true);
  BOOST_CHECK(ctrlpGetCountAction->getArgumentIntegerValue("CurrentCount") == 12);

  /////////////////////////////
  // Event Test
  /////////////////////////////

  Service *ctrlpCountService = ctrlpDev->getService("urn:schemas-upnp-org:service:count:1");
  BOOST_CHECK(ctrlpCountService);
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
