/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SUBSCRIBER_H_
#define _MUPMPCC_SUBSCRIBER_H_

#include <limits.h>
#include <mupnp/net/URL.h>
#include <string>
#include <time.h>

namespace mUPnP {
class Subscriber {
  std::string SID;
  std::string ifAddr;

  uHTTP::URL deliveryURL;

  long timeOut;
  long notifyCount;
  long subscriptionTime;

  public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  Subscriber();
  ~Subscriber();

  ////////////////////////////////////////////////
  // SID
  ////////////////////////////////////////////////

  const char* getSID()
  {
    return SID.c_str();
  }

  void setSID(const std::string& sid)
  {
    SID = sid;
  }

  ////////////////////////////////////////////////
  // deliveryURL
  ////////////////////////////////////////////////

  void setInterfaceAddress(const std::string& addr)
  {
    ifAddr = addr;
  }

  const char* getInterfaceAddress()
  {
    return ifAddr.c_str();
  }

  ////////////////////////////////////////////////
  // deliveryURL
  ////////////////////////////////////////////////

  const char* getDeliveryURL()
  {
    return deliveryURL.getSting();
  }

  void setDeliveryURL(const std::string& url)
  {
    deliveryURL.setString(url);
  }

  const char* getDeliveryHost()
  {
    return deliveryURL.getHost();
  }

  const char* getDeliveryPath()
  {
    return deliveryURL.getPath();
  }

  int getDeliveryPort()
  {
    return deliveryURL.getPort();
  }

  ////////////////////////////////////////////////
  // Timeout
  ////////////////////////////////////////////////

  long getTimeOut()
  {
    return timeOut;
  }

  void setTimeOut(long value)
  {
    timeOut = value;
  }

  bool isExpired();

  ////////////////////////////////////////////////
  // SubscriptionTIme
  ////////////////////////////////////////////////

  long getSubscriptionTime()
  {
    return subscriptionTime;
  }

  void setSubscriptionTime(long time)
  {
    subscriptionTime = time;
  }

  ////////////////////////////////////////////////
  // SEQ
  ////////////////////////////////////////////////

  long getNotifyCount()
  {
    return notifyCount;
  }

  void setNotifyCount(int cnt)
  {
    notifyCount = cnt;
  }

  void incrementNotifyCount();

  ////////////////////////////////////////////////
  // renew
  ////////////////////////////////////////////////

  void renew();
};

}

#endif
