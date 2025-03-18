/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/http/HTTPMessageQueue.h>
#include <mupnp/net/Socket.h>

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

uHTTP::HTTPMessageQueue::HTTPMessageQueue()
{
}

uHTTP::HTTPMessageQueue::~HTTPMessageQueue()
{
}

////////////////////////////////////////////////
//  pushMessage
////////////////////////////////////////////////

bool uHTTP::HTTPMessageQueue::pushMessage(HTTPMessage* httpMsg)
{
  return MessageQueue::pushMessage(httpMsg);
}

////////////////////////////////////////////////
//  waitMessage
////////////////////////////////////////////////

bool uHTTP::HTTPMessageQueue::waitMessage(HTTPMessage** httpMsg, time_t timeoutSec)
{
  Message* msg;
  if (!MessageQueue::waitMessage(&msg, timeoutSec))
    return false;
  *httpMsg = dynamic_cast<HTTPMessage*>(msg);
  return (*httpMsg) ? true : false;
}

////////////////////////////////////////////////
//  reset
////////////////////////////////////////////////

bool uHTTP::HTTPMessageQueue::reset()
{
  return MessageQueue::reset();
}

////////////////////////////////////////////////
//  clear
////////////////////////////////////////////////

bool uHTTP::HTTPMessageQueue::clear()
{
  return MessageQueue::clear();
}
