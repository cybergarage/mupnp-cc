/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: Property.h
*
*  Revision;
*
*  08/02/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_PROPERTY_H_
#define _CLINK_PROPERTY_H_

#include <string>

namespace CyberLink {
class Property {
  std::string name;
  std::string value;

 public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  Property() {
  }

  ////////////////////////////////////////////////
  //  name
  ////////////////////////////////////////////////

  const char *getName() {
    return name.c_str();
  }

  void setName(const std::string &val) {
    name = val;
  }

  ////////////////////////////////////////////////
  //  value
  ////////////////////////////////////////////////

  const char *getValue() {
    return value.c_str();
  }

  void setValue(const std::string &val) {
    value = val;
  }
};

}

#endif

