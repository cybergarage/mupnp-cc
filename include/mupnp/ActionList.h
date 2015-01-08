/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ActionList.h
*
*  Revision;
*
*  07/05/03
*    - first revision
*
******************************************************************/

#ifndef _MUPMPCC_ACTIONLIST_H_
#define _MUPMPCC_ACTIONLIST_H_

#include <uhttp/util/Vector.h>
#include <mupnp/Action.h>

namespace mUPnP {

class ActionList : public uHTTP::Vector<Action>  {

public:
    
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

public:
    
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  ActionList() 
  {
  }

  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////
  
  Action *getAction(size_t n) {
    return get(n);
  }
};

}

#endif
