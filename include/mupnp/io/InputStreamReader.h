/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_IO_INPUTSTREAMREADER_H_
#define _UHTTP_IO_INPUTSTREAMREADER_H_

#include <mupnp/io/InputStream.h>
#include <mupnp/io/Reader.h>

namespace uHTTP {
class InputStreamReader : public Reader {
  InputStream* in;

  public:
  InputStreamReader(InputStream* in)
  {
    this->in = in;
  }

  virtual ~InputStreamReader()
  {
  }

  ssize_t read(std::string& b, size_t len)
  {
    return in->read(b, len);
  }

  long skip(long n)
  {
    return in->skip(n);
  }

  void unread(std::string& b, size_t off, size_t len)
  {
    in->unread(b, off, len);
  }

  void unread(std::string& b, size_t len)
  {
    in->unread(b, len);
  }

  void unread(std::string& b)
  {
    in->unread(b);
  }

  void unread(char c)
  {
    in->unread(c);
  }

  void close()
  {
    in->close();
  }
};

}

#endif
