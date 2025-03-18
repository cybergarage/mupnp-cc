/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_LOGGERTARGET_H_
#define _UHTTP_LOGGERTARGET_H_

#include <stdio.h>

#include <string>
#include <vector>

#include <mupnp/util/Mutex.h>

namespace uHTTP {
class LoggerLevel {
  public:
  enum {
    NONE = 0x00,
    TRACE = 0x01,
    DBG = 0x02,
    INFO = 0x04,
    WARN = 0x08,
    ERR = 0x10,
    FATAL = 0x20,
  };
};

class LoggerTarget {
  public:
  enum {
    NONE = LoggerLevel::NONE,
    TRACE = LoggerLevel::TRACE,
    DBG = LoggerLevel::DBG,
    INFO = LoggerLevel::INFO,
    WARN = LoggerLevel::WARN,
    ERR = LoggerLevel::ERR,
    FATAL = LoggerLevel::FATAL,
  };

  public:
  LoggerTarget();
  virtual ~LoggerTarget();

  void setMask(int mask)
  {
    this->outputMask = mask;
  }

  int getMask()
  {
    return this->outputMask;
  }

  FILE* getFD() const
  {
    return this->fd;
  }

  bool hasFD()
  {
    return (this->fd ? true : false);
  }

  virtual bool outputMessage(const char* lineMessage);

  protected:
  void setFD(FILE* fd)
  {
    this->fd = fd;
  }

  private:
  FILE* fd;
  int outputMask;
};

class LoggerTargetList : public std::vector<LoggerTarget*> {

  public:
  LoggerTargetList();
  virtual ~LoggerTargetList();

  bool addTarget(LoggerTarget* target)
  {
    push_back(target);
    return true;
  }

  LoggerTarget* getTarget(int index) const
  {
    return at(index);
  }
};

}

#endif
