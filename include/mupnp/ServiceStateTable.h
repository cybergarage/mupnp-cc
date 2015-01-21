/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SERVICESTATETABLE_H_
#define _MUPMPCC_SERVICESTATETABLE_H_

#include <uhttp/util/Vector.h>

namespace mUPnP {
class StateVariable;

class ServiceStateTable : public uHTTP::Vector<StateVariable>  {
public:
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  ServiceStateTable() 
  {
  }

  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  StateVariable *getStateVariable(size_t n) {
    return get(n);
  }
};

}

#endif


