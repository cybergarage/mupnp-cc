/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2004
*
*  File: AllowedValue.h
*
*  Revision:
*
*  03/27/04
*    - first revision.
*  
******************************************************************/

#ifndef _CLINK_ALLOWEDVALUE_H_
#define _CLINK_ALLOWEDVALUE_H_

#include <cybergarage/xml/Node.h>

namespace CyberLink{
class AllowedValue {
  CyberXML::Node *allowedValueNode;
  
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

  ////////////////////////////////////////////////
  //  Member
  ////////////////////////////////////////////////

 public:
  void setAllowedValueNode(CyberXML::Node *node) {
    allowedValueNode = node;
  }

  CyberXML::Node *getAllowedValueNode() {
    return allowedValueNode;
  }

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

public:
  
  AllowedValue() {
    setAllowedValueNode(NULL);
  }

  AllowedValue(CyberXML::Node *node) {
    setAllowedValueNode(node);
  }

  ////////////////////////////////////////////////
  //  isAllowedValueNode
  ////////////////////////////////////////////////

 public:
  static bool isAllowedValueNode(CyberXML::Node *node) {
    return node->isName(AllowedValue::ELEM_NAME);
  }

  ////////////////////////////////////////////////
  //  minimum
  ////////////////////////////////////////////////

 public:
  void setValue(const std::string &value) {
    getAllowedValueNode()->setValue(value);
  }

  const char *getValue() {
    return getAllowedValueNode()->getValue();
  }
  
};

}

#endif

