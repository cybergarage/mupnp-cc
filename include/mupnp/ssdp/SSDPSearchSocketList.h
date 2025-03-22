/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_SSDPSEARCHSOCKETLIST_H_
#define _MUPMPCC_SSDPSEARCHSOCKETLIST_H_

#include <mupnp/common/Vector.h>
#include <mupnp/device/SearchListener.h>
#include <mupnp/ssdp/SSDPSearchSocket.h>

namespace mUPnP {

class SSDPSearchSocketList : public Vector<SSDPSearchSocket> {
  public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  SSDPSearchSocketList();
  ~SSDPSearchSocketList();

  ////////////////////////////////////////////////
  // Methods
  ////////////////////////////////////////////////

  SSDPSearchSocket* getSSDPSearchSocket(size_t n)
  {
    return get(n);
  }

  void addSearchListener(SearchListener* listener);
  void removeSearchListener(SearchListener* listener);

  bool open();
  bool close();

  bool start();
  bool stop();
};

}

#endif
