/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/util/Logger.h>

uHTTP::LoggerTarget::LoggerTarget()
{
  setFD(NULL);
}

uHTTP::LoggerTarget::~LoggerTarget()
{
}

bool uHTTP::LoggerTarget::outputMessage(const char* lineMessage)
{
  int ouputLen = fputs(lineMessage, getFD());
  if (ouputLen < 0)
    return false;
  fputs("\n", getFD());
  return true;
}
