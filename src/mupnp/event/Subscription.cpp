/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/UPnP.h>
#include <mupnp/event/Subscription.h>
#include <mupnp/util/StringUtil.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace uHTTP;
using namespace mUPnP;

////////////////////////////////////////////////
// Timeout
////////////////////////////////////////////////

const char *mUPnP::Subscription::toTimeoutHeaderString(long time, std::string &buf) {
  if (time != Subscription::INFINITE_VALUE) {
    string timeBuf;
    buf = Subscription::TIMEOUT_HEADER;
    buf.append(Long2String(time, timeBuf));
  }
  else
    buf = Subscription::INFINITE_STRING;
  return buf.c_str();
}

long mUPnP::Subscription::GetTimeout(const std::string &headerValue) {
  string headerValueStr = headerValue;
  string::size_type minusIdx = headerValueStr.find('-');
  if (minusIdx == std::string::npos)
    return Subscription::INFINITE_VALUE;
  string timeoutStr = headerValueStr.substr(minusIdx+1, headerValueStr.length());
  long timeout = atol(timeoutStr.c_str());
  if (timeout == 0L)
    timeout = Subscription::INFINITE_VALUE;
  return timeout;
}

////////////////////////////////////////////////
// SID
////////////////////////////////////////////////

const char *mUPnP::Subscription::CreateSID(std::string &buf) {
  time_t time1 = time(NULL);
  time_t time2 = (time_t)((double)time(NULL) * ((double)rand() / (double)RAND_MAX));
  char sidBuf[((4+1)*4) + 1];
  sprintf(sidBuf, "%04x-%04x-%04x-%04x",
    (int)(time1 & 0xFFFF),
    (int)(((time1 >> 31) | 0xA000) & 0xFFFF),
    (int)(time2 & 0xFFFF),
    (int)(((time2 >> 31) | 0xE000) & 0xFFFF));
  buf = sidBuf;
  return buf.c_str();
}

const char *Subscription::toSIDHeaderString(const std::string &id, std::string &buf) {
  buf = Subscription::UUID;
  buf.append(id);
  return buf.c_str();
}

const char *mUPnP::Subscription::GetSID(const std::string &headerValue, std::string &buf) {
  std::string uuid = Subscription::UUID;
  std::string headerValueStr = headerValue;
  buf = headerValueStr.substr(uuid.length(), headerValueStr.length());
  return buf.c_str();
}
