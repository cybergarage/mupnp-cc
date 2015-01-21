/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ACTIONLISTENER_H_
#define _MUPMPCC_ACTIONLISTENER_H_

//#include <mupnp/Action.h>

namespace mUPnP {
class Action;

class ActionListener {
public:
  virtual bool actionControlReceived(Action *action) = 0;
};

}

#endif

