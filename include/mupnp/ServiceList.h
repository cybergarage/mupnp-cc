/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ServiceList.h
*
*  Revision;
*
*  07/22/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SERVICELIST_H_
#define _CLINK_SERVICELIST_H_

#include <uhttp/util/Vector.h>

namespace CyberLink {
class Service;

class ServiceList : public uHTTP::Vector<Service> {
public:
    
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  ServiceList() 
  {
  }

  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  Service *getService(size_t n) {
    return get(n);
  }
};

}

#endif


