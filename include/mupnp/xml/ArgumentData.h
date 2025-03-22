/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ARGUMENTDATA_H_
#define _MUPMPCC_ARGUMENTDATA_H_

#include <mupnp/xml/NodeData.h>
#include <string>

namespace mUPnP {

class ArgumentData : public uXML::NodeData {
  std::string value;

  public:
  ArgumentData()
  {
  }

  ////////////////////////////////////////////////
  // value
  ////////////////////////////////////////////////

  const char* getValue()
  {
    return value.c_str();
  }

  void setValue(const std::string& val)
  {
    value = val;
  }
};

}

#endif
