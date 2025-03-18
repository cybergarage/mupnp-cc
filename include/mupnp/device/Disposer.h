/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_DISPOSER_H_
#define _MUPMPCC_DISPOSER_H_

#include <mupnp/util/Thread.h>

namespace mUPnP {
class ControlPoint;

class Disposer : public uHTTP::Thread {
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  Disposer(ControlPoint *ctrlp) {
    setControlPoint(ctrlp);
  }
  
  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

private:
  
  ControlPoint *controlPoint;

 public:
  void setControlPoint(ControlPoint *ctrlp) {
    controlPoint = ctrlp;
  }
  
  ControlPoint *getControlPoint() {
    return controlPoint;
  }

  ////////////////////////////////////////////////
  // Thread
  ////////////////////////////////////////////////
  
 public:
  void run();

};

}

#endif

