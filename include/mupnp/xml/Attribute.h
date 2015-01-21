/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ATTRIBUTE_H_
#define _MUPMPCC_ATTRIBUTE_H_

#include <string>

namespace uXML {

class Attribute  {
  std::string name; 
  std::string value; 

 public:
  Attribute() 
  {
  }

  Attribute(const std::string &name, const std::string &value) 
  {
    setName(name);
    setValue(value);
  }

  ////////////////////////////////////////////////
  // name
  ////////////////////////////////////////////////

  void setName(const std::string &val) 
  {
    name = val;
  }

  const char *getName() 
  {
    return name.c_str();
  }

  ////////////////////////////////////////////////
  // value
  ////////////////////////////////////////////////

  void setValue(const std::string &val) 
  {
    value = val;
  }

  const char *getValue() 
  {
    return value.c_str();
  }
};

}

#endif
