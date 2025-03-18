/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdarg.h>

#include <mupnp/util/Log.h>

int uHTTP::Log(
    Logger* logger,
    int logType,
#if defined(DEBUG)
    const char* fileName,
    int lineNo,
    const char* functionName,
#endif
    const char* format,
    ...)
{
  char outputMessage[uHTTP::Logger::MAX_LINE_STRING];

  va_list vaList;
  va_start(vaList, format);
  int outputMessageLength = vsnprintf(outputMessage, uHTTP::Logger::MAX_LINE_STRING, format, vaList);
  va_end(vaList);

#if defined(DEBUG)
  snprintf(outputMessage + outputMessageLength,
      (uHTTP::Logger::MAX_LINE_STRING - outputMessageLength),
      " - %s%s%d%s%s",
      fileName,
      uHTTP::Logger::SEPARATOR,
      lineNo,
      uHTTP::Logger::SEPARATOR,
      functionName);
#endif

  return logger->output(logType, outputMessage);
}
