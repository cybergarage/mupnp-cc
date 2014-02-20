/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
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
class SubscriberList : public uHTTP::Vector  {
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
 public:
  SubscriberList() 
  {
  }
  
  ~SubscriberList() 
  {
    clear();
  }

  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////
  
 public:
  Subscriber *getSubscriber(int n) {
    return (Subscriber *)get(n);
  }

  void clear() 
  {
    int nSub = size();
    for (int n = 0; n < nSub; n++) {
      Subscriber *sub = getSubscriber(n);
      delete sub;
    }
    Vector::clear();
  }

  void remove(Subscriber *sub) {
    if (sub == NULL)
        return;
    Vector::remove(sub);
    delete sub;
  }
};

}

#endif


