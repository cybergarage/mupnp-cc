/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/io/StringReader.h>

using namespace uHTTP;

StringReader::StringReader(const std::string& str)
{
  buf = str;
  pos = 0;
}

ssize_t StringReader::read(std::string& b, size_t len)
{
  size_t bufLen = buf.length() - pos;
  if (bufLen <= 0)
    return 0;
  size_t copyLen = (len < bufLen) ? len : bufLen;
  b.append(buf, pos, copyLen);
  pos += copyLen;
  return copyLen;
}

long StringReader::skip(long skipLen)
{
  pos += skipLen;
  return skipLen;
}
