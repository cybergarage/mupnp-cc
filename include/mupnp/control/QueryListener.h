/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_QUERYLISTENER_H_
#define _MUPMPCC_QUERYLISTENER_H_

#include <string>

namespace mUPnP {
class StateVariable;

class QueryListener {
public:
  virtual bool queryControlReceived(StateVariable *stateVar) = 0;
};

}

#endif
