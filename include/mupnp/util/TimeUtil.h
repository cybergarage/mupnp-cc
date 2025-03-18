/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_UTIL_TIMERUTIL_H_
#define _UHTTP_UTIL_TIMERUTIL_H_

namespace uHTTP {

void Wait(long mtime);
void WaitRandom(long mtime);
long GetCurrentSystemTime();
float Random();

}

#endif
