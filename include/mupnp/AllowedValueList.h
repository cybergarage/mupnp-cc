/******************************************************************
*
*  CyberLink for Java
*
*  Copyright (C) Satoshi Konno 2002
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
    
class AllowedValueList : public uHTTP::Vector<AllowedValue>  {
public:
    
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  AllowedValueList()
  {
  }

  AllowedValue *getAllowedValue(size_t n) {
    return get(n);
  }

};

}

#endif

