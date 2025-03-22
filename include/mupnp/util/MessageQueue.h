/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_UTIL_MESSAGEQUEUE_H_
#define _UHTTP_UTIL_MESSAGEQUEUE_H_

#include <queue>

#include <mupnp/util/Mutex.h>
#include <mupnp/util/Semaphore.h>

namespace uHTTP {

class Message {

  public:
  Message();
  virtual ~Message();
};

class MessageQueue : private std::queue<Message*> {

  public:
  MessageQueue();
  virtual ~MessageQueue();

  bool pushMessage(Message* message);
  bool waitMessage(Message** message, time_t timeoutSec = 0);

  size_t size()
  {
    return std::queue<Message*>::size();
  }

  bool reset();
  bool clear();

  private:
  bool popMessage(Message** message);

  private:
  Semaphore* sem;
  Mutex* mutex;
};

}

#endif
