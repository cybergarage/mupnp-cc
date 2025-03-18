/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/util/LoggerFileTarget.h>

uHTTP::LoggerFileTarget::LoggerFileTarget()
{
}

uHTTP::LoggerFileTarget::~LoggerFileTarget()
{
  close();
}

bool uHTTP::LoggerFileTarget::open(const std::string& filename)
{
  FILE* fd = fopen(filename.c_str(), "a");
  if (!fd)
    return false;
  setFD(fd);
  return true;
}

bool uHTTP::LoggerFileTarget::close()
{
  bool isClosed = false;
  if (hasFD()) {
    isClosed = (fclose(getFD()) == 0) ? true : false;
    setFD(NULL);
  }
  return isClosed;
}
