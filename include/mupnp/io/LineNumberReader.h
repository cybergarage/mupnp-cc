/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_IO_LINENUMBERREADER_H_
#define _UHTTP_IO_LINENUMBERREADER_H_

#include <string>

#include <mupnp/io/BufferedReader.h>

namespace uHTTP {
class LineNumberReader : public BufferedReader {
  int lineNum;

  public:
  LineNumberReader(Reader* reader)
      : BufferedReader(reader)
  {
    lineNum = -1;
  }

  int getLineNumber()
  {
    return lineNum;
  }

  const char* readLine()
  {
    lineNum++;
    return BufferedReader::readLine();
  }
};

}

#endif
