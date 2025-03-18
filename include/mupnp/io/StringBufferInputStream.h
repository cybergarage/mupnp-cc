/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_IO_STRINGBUFFERINPUTSTREAM_H_
#define _UHTTP_IO_STRINGBUFFERINPUTSTREAM_H_

#include <stdio.h>
#include <string>
#include <mupnp/io/File.h>
#include <mupnp/io/InputStream.h>

namespace uHTTP {
class StringBufferInputStream : public InputStream {
  std::string buf;
  long pos;

  public:
  StringBufferInputStream(const std::string& str);

  ssize_t read(std::string& b, size_t len);
  ssize_t read(char* b, size_t len);

  void unread(std::string& b, size_t off, size_t len)
  {
    // Not Implemented yet
  }

  long skip(long n);

  void close()
  {
  }
};

}

#endif
