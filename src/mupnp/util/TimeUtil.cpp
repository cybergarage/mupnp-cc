/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#if defined(WIN32) && defined(ITRON) && defined(_AFXDLL)
#include <afxwin.h>
#endif

#if defined(WIN32)
#include <time.h>
#include <windows.h>
#if defined(ITRON)
#include <kernel.h>
#endif
#elif defined(BTRON)
#include <btron/clk.h>
#include <btron/proctask.h>
#include <time.h>
#elif defined(ITRON)
#include <kernel.h>
#elif defined(TENGINE) && !defined(PROCESS_BASE)
#include <time.h>
#include <tk/tkernel.h>
#elif defined(TENGINE) && defined(PROCESS_BASE)
#include <btron/proctask.h>
#include <time.h>
#include <tk/tkernel.h>
#else
#include <time.h>
#include <unistd.h>
#endif

#include <limits.h>
#include <stdlib.h>

#include <mupnp/util/TimeUtil.h>

using namespace uHTTP;

void uHTTP::Wait(long mtime)
{
#if defined(WIN32)
  Sleep(mtime);
#elif defined(BTRON)
  slp_tsk(mtime);
#elif defined(ITRON)
  tslp_tsk(mtime);
#elif defined(TENGINE) && !defined(PROCESS_BASE)
  tk_slp_tsk(mtime);
#elif defined(TENGINE) && defined(PROCESS_BASE)
  b_slp_tsk(mtime);
#else
  double utime = mtime * 1000.0;
  usleep((int)utime);
#endif
}

void uHTTP::WaitRandom(long mtime)
{
  double factor = (double)rand() / (double)RAND_MAX;
  long waitTime = (long)((double)mtime * factor);
  Wait(waitTime);
}

long uHTTP::GetCurrentSystemTime()
{
#if defined(BTRON)
  STIME systime;
  TIMEZONE tz;
  if (get_tim(&systime, &tz) != 0)
    return 0;
  STIME localtime = systime - tz.adjust + (tz.dst_flg ? (tz.dst_adj * 60) : 0);
  return localtime;
#elif defined(ITRON)
  static BOOL initialized = FALSE;
  SYSTIM sysTim;
  if (initialized == FALSE) {
    sysTim.utime = 0;
    sysTim.ltime = 0;
    set_tim(&sysTim);
  }
  get_tim(&sysTim);
  return ((sysTim.utime / 1000) << 32) + (sysTim.ltime / 1000);
#else
  return time(NULL);
#endif
}

float uHTTP::Random()
{
  static bool seedDone = false;
  if (seedDone == false) {
    srand((time(NULL) % UINT_MAX));
    seedDone = true;
  }
  return (float)rand() / (float)RAND_MAX;
}
