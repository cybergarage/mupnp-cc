/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_IO_BUFFEREDREADER_H_
#define _UHTTP_IO_BUFFEREDREADER_H_

#include <string>
#include <mupnp/io/Reader.h>

namespace uHTTP {
class BufferedReader {
  Reader* reader;
  std::string lineStr;

  public:
  BufferedReader(Reader* reader)
  {
    this->reader = reader;
  }

  ssize_t read(std::string& b, size_t len)
  {
    return reader->read(b, len);
  }

  long skip(long n)
  {
    return reader->skip(n);
  }

  void unread(std::string& b, size_t off, size_t len)
  {
    reader->unread(b, off, len);
  }

  void unread(std::string& b, size_t len)
  {
    reader->unread(b, len);
  }

  void unread(char b)
  {
    reader->unread(b);
  }

  void close()
  {
    reader->close();
  }

  const char* readLine();
};

}

#endif
