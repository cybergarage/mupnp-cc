/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ArgumentData.h
*
*  Revision;
*
*  07/14/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_ARGUMENTDATA_H_
#define _CLINK_ARGUMENTDATA_H_

#include <string>
#include <cybergarage/xml/NodeData.h>

namespace CyberLink {
class ArgumentData : public CyberXML::NodeData {
  std::string value;
  
 public:
  ArgumentData() 
  {
  }

  ////////////////////////////////////////////////
  // value
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
