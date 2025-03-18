/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_UTIL_SEMAPHORE_H_
#define _UHTTP_UTIL_SEMAPHORE_H_

#include <time.h>

#if defined(__APPLE__)
#include <mach/mach.h>
#include <mach/semaphore.h>
#else
#include <pthread.h>
#include <semaphore.h>
#endif

namespace uHTTP {

#if defined(__APPLE__)
typedef semaphore_t SemaphoreId;
#else
typedef sem_t SemaphoreId;
#endif

class Semaphore {
  public:
  Semaphore(size_t maxCount);
  ~Semaphore();

  bool post();
  bool wait(time_t timeoutSec = 0);

  bool reset();
  bool cancel();

  private:
  bool init(size_t maxCount);
  bool destory();

  SemaphoreId semId;
  bool isInitialized;
  size_t maxCount;
};

}

#endif
