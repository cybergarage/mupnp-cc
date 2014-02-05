/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: Subscriber.cpp
*
*  Revision:
*
*  08/02/03
*    - first revision
*  07/31/04
*    - Added isExpired().
*  10/26/04
*    - Oliver Newell <newell@media-rush.com>
*    - Added support the intinite time and fixed a bug in isExpired().
*
******************************************************************/

#include <cybergarage/upnp/event/Subscriber.h>
#include <cybergarage/upnp/event/Subscription.h>

using namespace CyberLink;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////
  
Subscriber::Subscriber() {
  renew();
}

Subscriber::~Subscriber() {
  renew();
}

////////////////////////////////////////////////
//  SEQ
////////////////////////////////////////////////

void Subscriber::incrementNotifyCount()  {
  if (notifyCount == LONG_MAX) {
    notifyCount = 1;
    return;
  }
  notifyCount++;
}
  
////////////////////////////////////////////////
//  Timeout
////////////////////////////////////////////////

bool Subscriber::isExpired() {
  long currTime = time(NULL);
    
  // Thanks for Oliver Newell (10/26/04)
  if(timeOut == Subscription::INFINITE_VALUE) 
    return false; 
      
  // Thanks for Oliver Newell (10/26/04)
  long expiredTime = getSubscriptionTime() + getTimeOut()*1000;
  if (expiredTime < currTime)
    return true;
      
  return false;
}

////////////////////////////////////////////////
//  renew
////////////////////////////////////////////////
  
void Subscriber::renew() {
  setSubscriptionTime(time(NULL));
  setNotifyCount(0);
}
