/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SUBSCRIPTION_H_
#define _MUPMPCC_SUBSCRIPTION_H_

#include <string>

namespace mUPnP {
namespace Subscription {
  const char XMLNS[] = "urn:schemas-upnp-org:event-1-0";
  const char TIMEOUT_HEADER[] = "Second-";
  const char INFINITE_STRING[] = "infinite";
  const int INFINITE_VALUE = -1;
  const char UUID[] = "uuid:";
  const char SUBSCRIBE_METHOD[] = "SUBSCRIBE";
  const char UNSUBSCRIBE_METHOD[] = "UNSUBSCRIBE";

  ////////////////////////////////////////////////
  // Timeout
  ////////////////////////////////////////////////

  const char* toTimeoutHeaderString(long time, std::string& buf);
  long GetTimeout(const std::string& headerValue);

  ////////////////////////////////////////////////
  // SID
  ////////////////////////////////////////////////

  const char* CreateSID(std::string& buf);
  const char* toSIDHeaderString(const std::string& sid, std::string& buf);
  const char* GetSID(const std::string& headerValue, std::string& buf);

}

}

#endif
