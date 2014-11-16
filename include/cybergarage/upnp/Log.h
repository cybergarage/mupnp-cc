/******************************************************************
*
* CyberLink for C++
*
* Copyright (C) Satoshi Konno 2002
*
* This is licensed under BSD-style license, see file COPYING.
*
******************************************************************/

#ifndef _CLINKCC_LOG_H_
#define _CLINKCC_LOG_H_

#include <uhttp/util/Log.h>

namespace CyberLink {
  
#if defined(DEBUG)
#define LogTrace(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::TRACE,   __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogInfo(format, ...)      uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::INFO,    __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogWarn(format, ...)      uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::WARN,    __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogError(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::ERR,     __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogFatal(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::FATAL,   __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#define LogDebug(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::DBG,     __FILE__,  __LINE__, __PRETTY_FUNCTION__, format, ##__VA_ARGS__)
#else
#define LogTrace(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::TRACE,   format, ##__VA_ARGS__)
#define LogInfo(format, ...)      uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::INFO,    format, ##__VA_ARGS__)
#define LogWarn(format, ...)      uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::WARN,    format, ##__VA_ARGS__)
#define LogError(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::ERR,     format, ##__VA_ARGS__)
#define LogFatal(format, ...)     uHTTP::Log(uHTTP::Logger::GetSharedInstance(), uHTTP::LoggerTarget::FATAL,   format, ##__VA_ARGS__)
#define LogDebug(format, ...)
#endif

}

#endif
