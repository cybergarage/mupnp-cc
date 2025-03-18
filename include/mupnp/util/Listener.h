/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_UTIL_LISTENERLIST_H_
#define _UHTTP_UTIL_LISTENERLIST_H_

#include <mupnp/util/Vector.h>

namespace uHTTP {

class Listener {
  public:
  Listener()
  {
  }
  virtual ~Listener()
  {
  }
};

template <typename T>
class ListenerList : public ::uHTTP::WeakVector<T> {

  public:
  ListenerList()
  {
  }
};

}

#endif
