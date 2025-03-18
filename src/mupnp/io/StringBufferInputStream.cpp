/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string.h>
#include <mupnp/io/StringBufferInputStream.h>

using namespace uHTTP;

StringBufferInputStream::StringBufferInputStream(const std::string& str)
{
  buf = str;
  pos = 0;
}

ssize_t StringBufferInputStream::read(std::string& b, size_t len)
{
  size_t bufLen = buf.length() - pos;
  if (bufLen <= 0)
    return 0;
  size_t copyLen = (len < bufLen) ? len : bufLen;
  b.append(buf, pos, copyLen);
  pos += copyLen;
  return copyLen;
}

ssize_t StringBufferInputStream::read(char* b, size_t len)
{
  size_t bufLen = buf.length() - pos;
  if (bufLen <= 0)
    return 0;
  size_t copyLen = (len < bufLen) ? len : bufLen;
  strncpy(b, (buf.c_str() + pos), copyLen);
  pos += copyLen;
  return copyLen;
}

long StringBufferInputStream::skip(long n)
{
  pos += n;
  return n;
}
