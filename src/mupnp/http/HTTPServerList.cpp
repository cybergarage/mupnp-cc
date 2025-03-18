/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/http/HTTPServerList.h>
#include <mupnp/util/Debug.h>
#include <mupnp/util/StringUtil.h>

#include <sstream>

using namespace std;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

HTTPServerList::HTTPServerList()
{
}

HTTPServerList::~HTTPServerList()
{
  stop();
}

////////////////////////////////////////////////
//  addRequestListener
////////////////////////////////////////////////

void HTTPServerList::addRequestListener(HTTPRequestListener* listener)
{
  size_t nServers = size();
  for (size_t n = 0; n < nServers; n++) {
    HTTPServer* server = getHTTPServer(n);
    server->addRequestListener(listener);
  }
}

////////////////////////////////////////////////
//  addRequestListener
////////////////////////////////////////////////

void HTTPServerList::removeRequestListener(HTTPRequestListener* listener)
{
  size_t nServers = size();
  for (size_t n = 0; n < nServers; n++) {
    HTTPServer* server = getHTTPServer(n);
    server->removeRequestListener(listener);
  }
}

////////////////////////////////////////////////
//  addRequestListener
////////////////////////////////////////////////

void HTTPServerList::setWorkerCount(size_t count)
{
  size_t nServers = size();
  for (size_t n = 0; n < nServers; n++) {
    HTTPServer* server = getHTTPServer(n);
    server->setWorkerCount(count);
  }
}

////////////////////////////////////////////////
//  open/close
////////////////////////////////////////////////

bool HTTPServerList::close()
{
  bool areAllSocketsClosed = true;
  size_t nServers = size();
  for (size_t n = 0; n < nServers; n++) {
    HTTPServer* server = getHTTPServer(n);
    if (server->close() == false) {
      areAllSocketsClosed = false;
    }
  }
  clear();
  return areAllSocketsClosed;
}

bool HTTPServerList::open(int port)
{
  bool ret = true;
  size_t nHostAddrs = GetNHostAddresses();
  if (nHostAddrs == 0)
    return false;
  for (int n = 0; n < nHostAddrs; n++) {
    string buf;
    const char* bindAddr = GetHostAddress(n, buf);
    HTTPServer* httpServer = new HTTPServer();
    // Thanks for Ilkka Poutanen and Stefano Lenzi (07/16/04)
    if (httpServer->open(port, bindAddr) == false) {
      string msg;
      string ibuf;
      msg += "Couldn't bind to ";
      msg += bindAddr;
      msg += ":";
      msg += Integer2String(port, ibuf);
      ;
      Debug::warning(msg.c_str());
      ret = false;
      continue;
    }
    add(httpServer);
  }
  return ret;
}

////////////////////////////////////////////////
//  start/stop
////////////////////////////////////////////////

bool HTTPServerList::start()
{
  bool areAllSocketsStarted = true;
  size_t nServers = size();
  for (size_t n = 0; n < nServers; n++) {
    HTTPServer* server = getHTTPServer(n);
    if (server->start() == false) {
      areAllSocketsStarted = false;
    }
  }
  return areAllSocketsStarted;
}

bool HTTPServerList::stop()
{
  bool areAllSocketsStopped = true;
  size_t nServers = size();
  for (size_t n = 0; n < nServers; n++) {
    HTTPServer* server = getHTTPServer(n);
    if (server->stop() == false) {
      areAllSocketsStopped = false;
    }
  }
  close();
  return areAllSocketsStopped;
}
