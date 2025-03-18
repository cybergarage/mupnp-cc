/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_IO_READER_H_
#define _UHTTP_IO_READER_H_

#include <stdio.h>

namespace uHTTP {
class Reader {
  public:
  Reader()
  {
  }

  virtual ~Reader()
  {
  }

  virtual ssize_t read(std::string& b, size_t len) = 0;

  virtual long skip(long n) = 0;

  virtual void unread(std::string& b, size_t off, size_t len) = 0;

  void unread(std::string& b, size_t len)
  {
    unread(b, 0, len);
  }

  void unread(char c)
  {
    std::string b;
    b.append(&c, 0, 1);
    unread(b, 0, 1);
  }

  virtual void close() = 0;
};

}

#endif
