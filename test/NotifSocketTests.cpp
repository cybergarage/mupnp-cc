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

#include <mupnp/mUPnP.h>

using namespace uHTTP;
using namespace mUPnP;
using namespace std;

BOOST_AUTO_TEST_CASE(NotifySocketPost)
{
  NetworkInterfaceList netIfList;
  GetHostAddresses(netIfList);
  BOOST_CHECK(0 < netIfList.size());
  
  NetworkInterface *netIf = netIfList.getNetworkInterface(0);
  string ifAddr = netIf->getAddress();

  for (int n=0; n<10; n++) {
    SSDPNotifySocket ssdpSock;
    SSDPNotifyRequest ssdpReq;
    ssdpReq.setNTS(NTS::ALIVE);
    BOOST_CHECK(ssdpSock.post(&ssdpReq, ifAddr));
  }
}
