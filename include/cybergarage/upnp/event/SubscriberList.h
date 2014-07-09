/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: SubscriberList.h
*
*  Revision;
*
*  07/05/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SUBSCRIBERLIST_H_
#define _CLINK_SUBSCRIBERLIST_H_

#include <uhttp/util/Vector.h>
#include <cybergarage/upnp/event/Subscriber.h>

namespace CyberLink {
    
class SubscriberList : public uHTTP::Vector<Subscriber>  {
public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  SubscriberList()
  {
  }
  
  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  Subscriber *getSubscriber(size_t n) {
    return get(n);
  }
};

}

#endif


