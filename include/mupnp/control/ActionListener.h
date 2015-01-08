/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ActionListener.h
*
*  Revision;
*
*  07/11/03
*    - first revision
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

