/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ServiceStateTable.h
*
*  Revision;
*
*  07/21/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_SERVICESTATETABLE_H_
#define _CLINK_SERVICESTATETABLE_H_

#include <uhttp/util/Vector.h>

namespace CyberLink {
class StateVariable;

class ServiceStateTable : public uHTTP::Vector  {
public:
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  ServiceStateTable() 
  {
  }

  ~ServiceStateTable() 
  {
    clear();
  }
  
  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////
  
  StateVariable *getStateVariable(int n) {
    return (StateVariable *)get(n);
  }

  void clear();
};

}

#endif


