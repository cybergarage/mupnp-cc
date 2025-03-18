/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_UTIL_MUTEX_H_
#define _UHTTP_UTIL_MUTEX_H_

#if defined(WIN32) && defined(ITRON) && defined(_AFXDLL)
#include <afxwin.h>
#endif

#if defined(WIN32) && !defined(ITRON)
#include <winsock2.h>
#elif defined(BTRON)
#include <btron/taskcomm.h>
#elif defined(ITRON)
#include <kernel.h>
#elif defined(TENGINE) && !defined(PROCESS_BASE)
#include <tk/tkernel.h>
#elif defined(TENGINE) && defined(PROCESS_BASE)
#include <btron/taskcomm.h>
#else
#include <pthread.h>
#endif

namespace uHTTP {
class Mutex {
#if defined(WIN32) && !defined(ITRON)
  HANDLE mutexID;
#elif defined(BTRON)
  WERR mutexID;
#elif defined(ITRON)
  ER_ID mutexID;
#elif defined(TENGINE) && !defined(PROCESS_BASE)
  ID mutexID;
#elif defined(TENGINE) && defined(PROCESS_BASE)
  WERR mutexID;
#else
  pthread_mutex_t mutexID;
#endif

  public:
  Mutex();
  ~Mutex();

  bool lock();
  bool unlock();
};

}

#endif
