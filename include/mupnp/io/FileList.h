/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_IO_FILELIST_H_
#define _UHTTP_IO_FILELIST_H_

#include <mupnp/util/Vector.h>

namespace uHTTP {
class File;

class FileList : public ::uHTTP::SharedVector<File> {
  public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

  FileList()
  {
  }

  ////////////////////////////////////////////////
  //  Methods
  ////////////////////////////////////////////////

  public:
  File* getFile(size_t n)
  {
    return get(n).get();
  }
};

}

#endif
