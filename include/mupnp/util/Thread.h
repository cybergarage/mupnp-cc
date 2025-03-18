/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_THREAD_H_
#define _UHTTP_THREAD_H_

#if defined(WIN32) && !defined(ITRON)
#include <windows.h>
#elif defined(BTRON)
#include <btron/proctask.h>
#elif defined(ITRON)
#if defined(WIN32) && defined(ITRON) && defined(_AFXDLL)
#include <afxwin.h>
#endif
#include <kernel.h>
#elif defined(TENGINE) && !defined(PROCESS_BASE)
#include <tk/tkernel.h>
#elif defined(TENGINE) && defined(PROCESS_BASE)
#include <btron/proctask.h>
#else
#include <pthread.h>
#include <signal.h>
#endif

#include <mupnp/util/Mutex.h>
#include <mupnp/util/Vector.h>

namespace uHTTP {

class Thread {
  public:
  Thread();
  virtual ~Thread();

  virtual bool start();
  virtual void run() = 0;
  bool isRunnable();
  virtual bool stop();

  void setObject(void* object)
  {
    this->runObject = object;
  }

  void* getObject()
  {
    return this->runObject;
  }

  bool restart()
  {
    stop();
    start();
    return true;
  }

  private:
  void setRunnableFlag(bool flag);

  private:
#if defined(WIN32) && !defined(ITRON)
  HANDLE hThread;
  DWORD threadID;
#elif defined(BTRON)
  W taskID;
#elif defined(ITRON)
  ER_ID taskID;
#elif defined(TENGINE) && !defined(PROCESS_BASE)
  ID taskID;
#elif defined(TENGINE) && defined(PROCESS_BASE)
  WERR taskID;
#else
  pthread_t thread;
#endif

  Mutex mutex;
  bool runnableFlag;
  void* runObject;
};

class ThreadList : public ::uHTTP::SharedVector<Thread> {

  public:
  ThreadList();
  virtual ~ThreadList();

  bool start();
  bool stop();
};

}

#endif
