/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/event/Subscriber.h>
#include <mupnp/event/Subscription.h>

using namespace mUPnP;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Subscriber::Subscriber()
{
  renew();
}

Subscriber::~Subscriber()
{
  renew();
}

////////////////////////////////////////////////
// SEQ
////////////////////////////////////////////////

void Subscriber::incrementNotifyCount()
{
  if (notifyCount == LONG_MAX) {
    notifyCount = 1;
    return;
  }
  notifyCount++;
}

////////////////////////////////////////////////
// Timeout
////////////////////////////////////////////////

bool Subscriber::isExpired()
{
  long currTime = time(NULL);

  // Thanks for Oliver Newell (10/26/04)
  if (timeOut == Subscription::INFINITE_VALUE)
    return false;

  // Thanks for Oliver Newell (10/26/04)
  long expiredTime = getSubscriptionTime() + getTimeOut() * 1000;
  if (expiredTime < currTime)
    return true;

  return false;
}

////////////////////////////////////////////////
// renew
////////////////////////////////////////////////

void Subscriber::renew()
{
  setSubscriptionTime(time(NULL));
  setNotifyCount(0);
}
