/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_EVENTLISTENER_H_
#define _MUPMPCC_EVENTLISTENER_H_

#include <uhttp/util/Listener.h>

namespace mUPnP {

class EventListener : public uHTTP::Listener {
public:
  virtual bool eventNotifyReceived(const std::string &uuid, long seq, const std::string &varName, const std::string &value) = 0;
};

}

#endif

