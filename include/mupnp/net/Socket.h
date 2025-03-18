/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_NET_SOCKET_H_
#define _UHTTP_NET_SOCKET_H_

#include <mupnp/net/SocketCore.h>

namespace uHTTP {

class SocketList;

class Socket : public SocketCore {

  public:
  Socket();
  ~Socket();

  bool listen();

  bool bind(int port, const std::string& addr);

  bool accept(Socket* socket);

  bool connect(const std::string& addr, int port);

  ssize_t send(const char* cmd, size_t cmdLen);
  ssize_t send(const std::string& cmd);
  ssize_t send(const char c);

  ssize_t recv(char* buffer, size_t bufferLen);

  private:
#if defined(ITRON)
  static const int WINDOW_BUF_SIZE;
  UH* sendWinBuf;
  UH* recvWinBuf;
#endif

#if defined(ITRON)
  void initWindowBuffer();
#endif
};

}

#endif
