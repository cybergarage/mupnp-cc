/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_HTTPWORKERTHREAD_H_
#define _UHTTP_HTTPWORKERTHREAD_H_

#include <mupnp/http/HTTPServer.h>
#include <mupnp/util/Thread.h>

namespace uHTTP {

class HTTPWorkerThread : public uHTTP::Thread {
  uHTTP::HTTPServer* httpServer;

  public:
  HTTPWorkerThread(uHTTP::HTTPServer* server);
  ~HTTPWorkerThread();

  ////////////////////////////////////////////////
  //  run
  ////////////////////////////////////////////////

  void run();
};

}

#endif
