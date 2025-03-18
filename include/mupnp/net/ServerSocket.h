/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_NET_SERVERSOCKET_H_
#define _UHTTP_NET_SERVERSOCKET_H_

#include <mupnp/net/Socket.h>

namespace uHTTP {
class ServerSocket : public ::uHTTP::Socket {
  public:
  ServerSocket();
  ~ServerSocket();
};

}

#endif
