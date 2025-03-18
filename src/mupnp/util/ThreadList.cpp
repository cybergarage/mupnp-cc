/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <mupnp/util/Thread.h>

uHTTP::ThreadList::ThreadList()
{
}

uHTTP::ThreadList::~ThreadList()
{
}

bool uHTTP::ThreadList::start()
{
  bool allThreadsStarted = true;
  for (ThreadList::iterator thread = begin(); thread != end(); thread++) {
    if ((*thread)->start() == false)
      allThreadsStarted = false;
  }
  return allThreadsStarted;
}

bool uHTTP::ThreadList::stop()
{
  bool allThreadsStopped = true;
  for (ThreadList::iterator thread = begin(); thread != end(); thread++) {
    if ((*thread)->stop() == false)
      allThreadsStopped = false;
  }
  return allThreadsStopped;
}
