/******************************************************************
*
*  mUPnP for Java
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

#ifndef _MUPMPCC_ALLOWEDVALUELIST_H_
#define _MUPMPCC_ALLOWEDVALUELIST_H_

#include <string>
#include <uhttp/util/Vector.h>
#include <mupnp/AllowedValue.h>

namespace mUPnP {
    
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

