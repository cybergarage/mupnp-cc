/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_IO_FILEINPUTSTREAM_H_
#define _UHTTP_IO_FILEINPUTSTREAM_H_

#include <stdio.h>
#include <string>
#include <mupnp/io/File.h>
#include <mupnp/io/InputStream.h>

namespace uHTTP {
const long FILE_INBUF_SIZE = 512 * 1024;

class FileInputStream : public InputStream {
  FILE* fp;
  char* inBuf;

  public:
  FileInputStream(File* file, const std::string& mode);
  ~FileInputStream();

  ssize_t read(std::string& b, size_t len);
  ssize_t read(char* b, size_t len);

  void unread(std::string& b, size_t off, size_t len); // Not Implemented

  long skip(long n);

  void close();
};

}

#endif
