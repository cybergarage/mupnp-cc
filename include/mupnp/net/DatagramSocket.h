/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_NET_DATAGRAMSOCKET_H_
#define _UHTTP_NET_DATAGRAMSOCKET_H_

#include <mupnp/net/DatagramPacket.h>
#include <mupnp/net/SocketCore.h>

namespace uHTTP {
class DatagramSocket : public SocketCore {
  public:
  DatagramSocket();
  DatagramSocket(int port, const std::string& bindAddr, bool bindAddrFlag = true, bool reuseAddrFlag = false);
  ~DatagramSocket();

  bool bind(int port, const std::string& addr, bool bindAddrFlag = true, bool reuseAddrFlag = false);

  ssize_t send(const std::string& addr, int port, const std::string& data, size_t dataLen = 0);

  ssize_t send(DatagramPacket* dataPack);

  ssize_t receive(DatagramPacket& dataPack);
};

}

#endif
