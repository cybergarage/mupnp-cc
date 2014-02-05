/******************************************************************
*
*  CyberLink for Java
*
*  Copyright (C) Satoshi Konno 2002-2004
*
*  File: AllowedValueList.java
*
*  Revision:
*
*  03/29/04
*    - first revision.
*  
******************************************************************/

#ifndef _CLINK_ALLOWEDVALUELIST_H_
#define _CLINK_ALLOWEDVALUELIST_H_

#include <string>
#include <uhttp/util/Vector.h>
#include <cybergarage/upnp/AllowedValue.h>

namespace CyberLink {
class AllowedValueList : public uHTTP::Vector  {
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////
  
 public:
  static const char *ELEM_NAME;


  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

 public:
  AllowedValueList() 
  {
  }

  ~AllowedValueList() 
  {
    clear();
  }

  ////////////////////////////////////////////////
  //  clear
  ////////////////////////////////////////////////

 public:
  void clear();
  
  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////
  
 public:
  AllowedValue *getAllowedValue(int n) {
    return (AllowedValue *)get(n);
  }

};

}

#endif

