/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ACTIONLIST_H_
#define _MUPMPCC_ACTIONLIST_H_

#include <mupnp/Action.h>
#include <mupnp/util/Vector.h>

namespace mUPnP {

class ActionList : public Vector<Action> {

  public:
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

  static const char* ELEM_NAME;

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

  Action* getAction(size_t n)
  {
    return get(n);
  }
};

}

#endif
