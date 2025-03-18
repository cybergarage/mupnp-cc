/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/http/HTTPResponse.h>
#include <mupnp/http/HTTPSocket.h>
#include <mupnp/util/StringUtil.h>

using namespace std;
using namespace uHTTP;
using namespace uHTTP;
using namespace uHTTP;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

HTTPSocket::HTTPSocket(uHTTP::Socket* socket)
{
  setSocket(socket);
  open();
}

HTTPSocket::HTTPSocket(HTTPSocket* socket)
{
  setSocket((socket) ? socket->getSocket() : NULL);
}

HTTPSocket::~HTTPSocket()
{
  close();
}

////////////////////////////////////////////////
//  open/close
////////////////////////////////////////////////

bool HTTPSocket::open()
{
  return true;
}

bool HTTPSocket::close()
{
  if (socket) {
    delete socket;
    setSocket(NULL);
  }
  return true;
}

////////////////////////////////////////////////
//  post
////////////////////////////////////////////////

bool HTTPSocket::post(HTTPResponse* httpRes)
{
  HTTPDate now;
  httpRes->setDate(&now);

  Socket* sock = getSocket();
  string header;
  sock->send(httpRes->getHeader(header));
  return sock->send(HTTP::CRLF);
}

bool HTTPSocket::post(HTTPResponse* httpRes, const std::string& content, size_t contentOffset, size_t contentLength, bool isOnlyHeader, bool isChunked)
{
  httpRes->setContentLength(contentLength);
  post(httpRes);

  Socket* sock = getSocket();

  if (isOnlyHeader == true)
    return true;

  if (isChunked == true) {
    string chunSizeBuf;
    Sizet2HexString(contentLength, chunSizeBuf);
    sock->send(chunSizeBuf.c_str());
    sock->send(HTTP::CRLF);
  }

  sock->send((content.c_str() + contentOffset), contentLength);

  if (isChunked == true) {
    sock->send(HTTP::CRLF);
    sock->send("0");
    sock->send(HTTP::CRLF);
  }

  return true;
}

bool HTTPSocket::post(HTTPResponse* httpRes, InputStream* in, size_t contentOffset, size_t contentLength, bool isOnlyHeader, bool isChunked)
{
  HTTPDate now;
  httpRes->setDate(&now);

  Socket* sock = getSocket();

  httpRes->setContentLength(contentLength);

  string header;
  sock->send(httpRes->getHeader(header));
  sock->send(HTTP::CRLF);

  if (isOnlyHeader == true)
    return true;

  if (0 < contentOffset)
    in->skip(contentOffset);

  int chunkSize = HTTP::GetChunkSize();
  char* chunkBuf = new char[chunkSize + 1];

  string readBuf;
  string chunSizeBuf;
  long readCnt = 0;
  long readSize = (chunkSize < contentLength) ? chunkSize : contentLength;
  ssize_t readLen = in->read(chunkBuf, (int)readSize);
  while (0 < readLen && readCnt < contentLength) {
    if (isChunked == true) {
      Sizet2HexString(readLen, chunSizeBuf);
      sock->send(chunSizeBuf.c_str());
      sock->send(HTTP::CRLF);
    }
    if (sock->send(chunkBuf, readLen) <= 0)
      break;
    if (isChunked == true)
      sock->send(HTTP::CRLF);
    readCnt += readLen;
    readBuf = "";
    readSize = (chunkSize < (contentLength - readCnt)) ? chunkSize : (contentLength - readCnt);
    readLen = in->read(chunkBuf, (int)readSize);
  }

  if (isChunked == true) {
    sock->send("0");
    sock->send(HTTP::CRLF);
  }

  delete[] chunkBuf;

  return true;
}

bool HTTPSocket::post(HTTPResponse* httpRes, size_t contentOffset, size_t contentLength, bool isOnlyHeader, bool isChunked)
{
  if (httpRes->hasContentInputStream() == true)
    return post(httpRes, httpRes->getContentInputStream(), contentOffset, contentLength, isOnlyHeader, isChunked);
  return post(httpRes, httpRes->getContent(), contentOffset, contentLength, isOnlyHeader, isChunked);
}

bool HTTPSocket::post(const std::string& content)
{
  Socket* sock = getSocket();
  return sock->send(content);
}

bool HTTPSocket::post(const char c)
{
  Socket* sock = getSocket();
  return sock->send(c);
}
