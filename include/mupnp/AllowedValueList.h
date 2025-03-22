/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ALLOWEDVALUELIST_H_
#define _MUPMPCC_ALLOWEDVALUELIST_H_

#include <mupnp/AllowedValue.h>
#include <mupnp/util/Vector.h>
#include <string>

namespace mUPnP {

class AllowedValueList : public Vector<AllowedValue> {
  public:
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

  static const char* ELEM_NAME;

  public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  AllowedValueList()
  {
  }

  AllowedValue* getAllowedValue(size_t n)
  {
    return get(n);
  }
};

}

#endif
