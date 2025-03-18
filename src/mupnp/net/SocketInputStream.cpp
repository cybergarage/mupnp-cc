/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/net/SocketInputStream.h>
#include <mupnp/util/TimeUtil.h>

using namespace uHTTP;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

SocketInputStream::SocketInputStream(Socket* sock)
{
  this->sock = sock;
  this->inBuf = new char[SOCKET_INBUF_SIZE];
}

////////////////////////////////////////////////
//  Destructor
////////////////////////////////////////////////

SocketInputStream::~SocketInputStream()
{
  delete[] this->inBuf;
}

////////////////////////////////////////////////
//  read
////////////////////////////////////////////////

ssize_t SocketInputStream::read(std::string& b, size_t len)
{
  if (!this->inBuf)
    return 0;

  size_t readCnt = 0;
  int retryCnt = 0;

  size_t unputBufLen = unputBuf.length();
  if (0 < unputBufLen) {
    size_t cpyCnt = (len < unputBufLen) ? len : unputBufLen;
    readCnt = cpyCnt;
    b.append(unputBuf, 0, cpyCnt);
    unputBuf = unputBuf.substr(cpyCnt, unputBufLen - cpyCnt);
  }

  while (readCnt < len) {
    size_t readSize = len - readCnt;
    if (SOCKET_INBUF_SIZE < readSize)
      readSize = SOCKET_INBUF_SIZE;
    ssize_t readLen = sock->recv(this->inBuf, readSize);
    if (readLen <= 0) {
      Wait(SOCKET_RECV_WAIT_TIME);
      retryCnt++;
      if (SOCKET_RECV_RETRY_CNT < retryCnt)
        break;
    }
    else {
      b.append(this->inBuf, 0, readLen);
      readCnt += readLen;
    }
  }
  return readCnt;
}

////////////////////////////////////////////////
//  read
////////////////////////////////////////////////

ssize_t SocketInputStream::read(char* b, size_t len)
{
  if (!this->inBuf)
    return 0;

  size_t readCnt = 0;
  int retryCnt = 0;

  while (readCnt < len) {
    size_t readSize = len - readCnt;
    ssize_t readLen = sock->recv(b + readCnt, readSize);
    if (readLen <= 0) {
      Wait(SOCKET_RECV_WAIT_TIME);
      retryCnt++;
      if (SOCKET_RECV_RETRY_CNT < retryCnt)
        break;
    }
    readCnt += readLen;
  }
  return readCnt;
}

////////////////////////////////////////////////
//  unread
////////////////////////////////////////////////

void SocketInputStream::unread(std::string& b, size_t off, size_t len)
{
  unputBuf.append(b.substr(off, len));
}

////////////////////////////////////////////////
//  skip
////////////////////////////////////////////////

long SocketInputStream::skip(long n)
{
  if (!this->inBuf)
    return 0;

  long skippedByte = 0;
  int retryCnt = 0;
  while (n < skippedByte) {
    long readByte = n - skippedByte;
    if (SOCKET_INBUF_SIZE < readByte)
      readByte = SOCKET_INBUF_SIZE;
    ssize_t readLen = sock->recv(this->inBuf, (int)readByte);
    if (readLen <= 0) {
      Wait(SOCKET_RECV_WAIT_TIME);
      retryCnt++;
      if (SOCKET_RECV_RETRY_CNT < retryCnt)
        break;
    }
    else
      skippedByte += readLen;
  }
  return skippedByte;
}

////////////////////////////////////////////////
//  close
////////////////////////////////////////////////

void SocketInputStream::close()
{
  sock->close();
}
