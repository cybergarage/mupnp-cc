/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_IO_STRINGREADER_H_
#define _UHTTP_IO_STRINGREADER_H_

#include <string>

#include <mupnp/io/InputStream.h>
#include <mupnp/io/Reader.h>

namespace uHTTP {
class StringReader : public Reader {
  std::string buf;
  int pos;

  public:
  StringReader(const std::string& str);

  ssize_t read(std::string& b, size_t len);

  long skip(long n);

  void unread(std::string& b, size_t off, size_t len)
  {
    // Not Implemented yet.
  }

  void close()
  {
  }
};

}

#endif
