/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_LOGGER_H_
#define _UHTTP_LOGGER_H_

#include <stdio.h>

#include <string>
#include <vector>

#include <mupnp/util/LoggerTarget.h>
#include <mupnp/util/Mutex.h>

namespace uHTTP {

class Logger {
  public:
  static const int MAX_LINE_STRING;
  static const char* SEPARATOR;

  public:
  static void SetSharedInstance(Logger* logger);
  static Logger* GetSharedInstance();
  static bool HasSharedInstance();
  static const char* GetMaskString(int outputType);

  public:
  Logger();
  ~Logger();

  void setLevel(int value)
  {
    this->level = value;
  }

  int getLevel()
  {
    return this->level;
  }

  bool addTarget(LoggerTarget* target);
  bool clearAllTargets();

  int output(int outputType, const char* outputMessage);

  int trace(const char* outputMessage)
  {
    return output(LoggerTarget::TRACE, outputMessage);
  }

  int message(const char* outputMessage)
  {
    return output(LoggerTarget::INFO, outputMessage);
  }

  int warning(const char* outputMessage)
  {
    return output(LoggerTarget::WARN, outputMessage);
  }

  int error(const char* outputMessage)
  {
    return output(LoggerTarget::ERR, outputMessage);
  }

  int fatal(const char* outputMessage)
  {
    return output(LoggerTarget::FATAL, outputMessage);
  }

  int debug(const char* outputMessage)
  {
#if defined(DEBUG)
    return output(LoggerTarget::DBG, outputMessage);
#else
    return 0;
#endif
  }

  private:
  LoggerTargetList targetList;
  Mutex outputMutex;
  int level;
};

}

#endif
