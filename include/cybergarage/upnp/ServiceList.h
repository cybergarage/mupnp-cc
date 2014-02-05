/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
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

class ServiceList : public uHTTP::Vector {
public:
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  ServiceList() 
  {
  }

  ~ServiceList() 
  {
    clear();
  }
  
  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////
  
  Service *getService(int n) {
    return (Service *)get(n);
  }

  void clear();
};

}

#endif


