/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#if !defined(__MINGW32__)
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#endif

#if defined(__CYGWIN__) && !defined(FIONREAD)
#include <windows.h>
#include <winsock2.h>
#endif

#if !defined(__MINGW32__)
static struct termios orgTermAttr;
#endif

void kbinit()
{
#if !defined(__MINGW32__)
  struct termios termAttr;
  tcgetattr(0, &orgTermAttr);
  termAttr = orgTermAttr;
  termAttr.c_lflag &= ~(ICANON | ECHO);
  termAttr.c_cc[VTIME] = 0;
  termAttr.c_cc[VMIN] = 1;
  tcsetattr(0, TCSANOW, &termAttr);
#endif
}

int kbhit()
{
#if !defined(__MINGW32__)
  int ret, n;
  ret = ioctl(0, FIONREAD, &n);
  if (ret != -1)
    return n;
#endif
  return 0;
}

int kbkey()
{
  return 0;
}

void kbexit()
{
#if !defined(__MINGW32__)
  tcsetattr(0, TCSANOW, &orgTermAttr);
#endif
}
