/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_NET_SOCKETINPUTSTREAM_H_
#define _UHTTP_NET_SOCKETINPUTSTREAM_H_

#include <mupnp/io/InputStream.h>
#include <mupnp/net/Socket.h>
#include <string>

namespace uHTTP {
const long SOCKET_RECV_WAIT_TIME = 100;
const long SOCKET_RECV_RETRY_CNT = 10;
const long SOCKET_INBUF_SIZE = 512 * 1024;

class SocketInputStream : public uHTTP::InputStream {
  Socket* sock;
  std::string unputBuf;
  char* inBuf;

  public:
  SocketInputStream(Socket* sock);

  virtual ~SocketInputStream();

  ssize_t read(std::string& b, size_t len);
  ssize_t read(char* b, size_t len); // Not support the unput buffer;

  void unread(std::string& b, size_t off, size_t len);

  long skip(long n);

  void close();
};

}

#endif
