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

BOOST_AUTO_TEST_CASE(SSDPRequestTests)
{
	// SSDPRequest::setLeaseTime
	SSDPRequest *ssdpReq = new SSDPRequest();
	ssdpReq->setLeaseTime(300);
	BOOST_CHECK(ssdpReq->getLeaseTime() == 300);
	delete ssdpReq;
}

BOOST_AUTO_TEST_CASE(STTests)
{
	BOOST_CHECK(ST::IsAllDevice("ssdp:all") == true);
	BOOST_CHECK(ST::IsRootDevice("upnp:rootdevice") == true);
	BOOST_CHECK(ST::IsUUIDDevice("uuid:fdfasdfaf") == true);
	BOOST_CHECK(ST::IsURNDevice("urn:schemas-upnp-org:device:clock:1") == true);
	BOOST_CHECK(ST::IsURNService("urn:schemas-upnp-org:service:timer:1") == true);
}

BOOST_AUTO_TEST_CASE(SSDPTests)
{
    const char *UPNP_TEST_MAXAGE_STR = "max-age=60";
    const int UPNP_TEST_MAXAGE = 60;
    
	int mx = SSDP::GetLeaseTime(UPNP_TEST_MAXAGE_STR);
	BOOST_CHECK_EQUAL(UPNP_TEST_MAXAGE, mx);
}
