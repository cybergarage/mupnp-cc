/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_HTTPSERVER_H_
#define _UHTTP_HTTPSERVER_H_

#include <mupnp/http/HTTPMessageQueue.h>
#include <mupnp/http/HTTPRequest.h>
#include <mupnp/http/HTTPRequestListener.h>
#include <mupnp/net/ServerSocket.h>
#include <mupnp/util/Listener.h>
#include <mupnp/util/Thread.h>

#include <string>

namespace uHTTP {

class HTTPServer : public uHTTP::Thread {

  public:
  static const long DEFAULT_SERVER_THREAD_WAIT_TIME;
  static const size_t DEFAULT_SERVER_WORKER_THREAD_NUM;

  public:
  HTTPServer();
  ~HTTPServer();

  ////////////////////////////////////////////////
  // open/close
  ////////////////////////////////////////////////

  bool open(int port, const std::string& addr = "");
  bool close();

  ////////////////////////////////////////////////
  // binding address and port
  ////////////////////////////////////////////////

  const char* getAddress()
  {
    if (!serverSock)
      return "";
    return serverSock->getLocalAddress();
  }

  int getPort()
  {
    if (!serverSock)
      return 0;
    return serverSock->getLocalPort();
  }

  ////////////////////////////////////////////////
  //  httpRequest
  ////////////////////////////////////////////////

  void addRequestListener(HTTPRequestListener* listener)
  {
    httpRequestListenerList.add(listener);
  }

  void removeRequestListener(HTTPRequestListener* listener)
  {
    httpRequestListenerList.remove(listener);
  }

  HTTP::StatusCode performRequestListener(HTTPRequest* httpReq)
  {
    HTTP::StatusCode lastStatusCode = HTTP::INTERNAL_SERVER_ERROR;
    size_t listenerSize = httpRequestListenerList.size();
    for (size_t n = 0; n < listenerSize; n++) {
      HTTPRequestListener* listener = httpRequestListenerList.get(n);
      lastStatusCode = listener->httpRequestRecieved(httpReq);
      if (lastStatusCode == HTTP::OK_REQUEST)
        break;
    }
    return lastStatusCode;
  }

  ////////////////////////////////////////////////
  //  run
  ////////////////////////////////////////////////

  bool start();
  void run();
  bool stop();

  ////////////////////////////////////////////////
  //  Worker Threads
  ////////////////////////////////////////////////

  void setWorkerCount(size_t count)
  {
    this->workerThreadMax = count;
  }

  size_t getWorkerCount()
  {
    return this->workerThreadMax;
  }

  bool waitMessage(HTTPMessage** httpMsg, time_t timeoutSec = 0)
  {
    return messageQueue.waitMessage(httpMsg, timeoutSec);
  }

  private:
  ServerSocket* serverSock;
  ListenerList<HTTPRequestListener> httpRequestListenerList;

  HTTPMessageQueue messageQueue;

  size_t workerThreadMax;
  ThreadList workerThreadList;

  bool bind(int port, const std::string& addr = "");
  bool accept(uHTTP::Socket* socket);
  bool isOpened();

  uHTTP::ServerSocket* getServerSock()
  {
    return serverSock;
  }
};

const char* GetServerName(std::string& buf);

}

#endif
