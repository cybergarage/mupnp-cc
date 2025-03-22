/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string.h>
#include <sys/msg.h>
#include <unistd.h>

#include <mupnp/util/MessageQueue.h>

uHTTP::MessageQueue::MessageQueue()
{
  this->sem = new Semaphore(0);
  this->mutex = new Mutex();
}

uHTTP::MessageQueue::~MessageQueue()
{
  clear();
  delete this->sem;
  delete this->mutex;
}

bool uHTTP::MessageQueue::pushMessage(Message* message)
{
  this->mutex->lock();

  push(message);
  this->sem->post();

  this->mutex->unlock();

  return true;
}

bool uHTTP::MessageQueue::popMessage(Message** message)
{
  *message = NULL;

  if (empty())
    return false;

  *message = front();
  pop();

  return true;
}

bool uHTTP::MessageQueue::waitMessage(Message** message, time_t timeoutSec)
{
  if (!this->sem)
    return false;

  if (!this->sem->wait(timeoutSec))
    return false;

  if (this->mutex) {
    this->mutex->lock();
  }

  bool popSucces = popMessage(message);

  if (this->mutex) {
    this->mutex->unlock();
  }

  return popSucces;
}

bool uHTTP::MessageQueue::reset()
{

  bool areAllOperationSuccess = true;
  if (clear() == false) {
    areAllOperationSuccess = false;
  }

  if (this->sem->reset() == false) {
    areAllOperationSuccess = false;
  }

  return areAllOperationSuccess;
}

bool uHTTP::MessageQueue::clear()
{

  if (this->sem) {
    this->sem->cancel();
  }

  Message* message;
  while (popMessage(&message)) {
    delete message;
  }

  return true;
}
