/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_LOGGERFILETARGET_H_
#define _UHTTP_LOGGERFILETARGET_H_

#include <mupnp/util/LoggerTarget.h>

namespace uHTTP {
class LoggerFileTarget : public LoggerTarget {
  public:
  LoggerFileTarget();
  ~LoggerFileTarget();

  bool open(const std::string& filename);
  bool close();
};

class LoggerStdFileTarget : public LoggerFileTarget {
  public:
  LoggerStdFileTarget()
  {
    setMask(
        LoggerTarget::TRACE | LoggerTarget::DBG | LoggerTarget::INFO);
  }
};

class LoggerErrorFileTarget : public LoggerFileTarget {
  public:
  LoggerErrorFileTarget()
  {
    setMask(
        LoggerTarget::WARN | LoggerTarget::ERR | LoggerTarget::FATAL);
  }
};

}

#endif
