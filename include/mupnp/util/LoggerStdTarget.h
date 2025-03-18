/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_LOGGERSTDTARGET_H_
#define _UHTTP_LOGGERSTDTARGET_H_

#include <mupnp/util/LoggerTarget.h>

namespace uHTTP {
class LoggerStdoutTarget : public LoggerTarget {
  public:
  LoggerStdoutTarget()
  {
    setFD(stdout);
    setMask(
        LoggerTarget::TRACE | LoggerTarget::DBG | LoggerTarget::INFO);
  }
};

class LoggerStderrTarget : public LoggerTarget {
  public:
  LoggerStderrTarget()
  {
    setFD(stderr);
    setMask(
        LoggerTarget::WARN | LoggerTarget::ERR | LoggerTarget::FATAL);
  }
};

class LoggerNullTarget : public LoggerTarget {
  public:
  LoggerNullTarget()
  {
    setMask(
        LoggerTarget::TRACE | LoggerTarget::DBG | LoggerTarget::INFO | LoggerTarget::WARN | LoggerTarget::ERR | LoggerTarget::FATAL);
  }

  bool outputMessage(const char* lineMessage)
  {
    return true;
  }
};

}

#endif
