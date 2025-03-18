/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2012
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_LOG_H_
#define _UHTTP_LOG_H_

#include <mupnp/util/Logger.h>
#include <mupnp/util/LoggerFileTarget.h>
#include <mupnp/util/LoggerStdTarget.h>

namespace uHTTP {
int Log(
    Logger* logger,
    int logType,
#if defined(DEBUG)
    const char* fileName,
    int lineNo,
    const char* functionName,
#endif
    const char* format,
    ...);

#if defined(DEBUG)
#define LogTrace(format, ...) uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::TRACE, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogInfo(format, ...) uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::INFO, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogWarn(format, ...) uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::WARN, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogError(format, ...) uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::ERR, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogFatal(format, ...) uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::FATAL, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogDebug(format, ...) uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::DBG, __FILE__, __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#else
#define LogTrace(format, ...) uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::TRACE, format, ##__VA_ARGS__)
#define LogInfo(format, ...) uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::INFO, format, ##__VA_ARGS__)
#define LogWarn(format, ...) uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::WARN, format, ##__VA_ARGS__)
#define LogError(format, ...) uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::ERR, format, ##__VA_ARGS__)
#define LogFatal(format, ...) uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::FATAL, format, ##__VA_ARGS__)
#define LogDebug(format, ...)
#endif

}

#endif
