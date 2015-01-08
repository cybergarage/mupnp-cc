/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ServiceStateTable.h
*
*  Revision;
*
*  07/21/03
*    - first revision
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


