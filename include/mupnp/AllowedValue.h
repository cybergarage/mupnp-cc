/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ALLOWEDVALUE_H_
#define _MUPMPCC_ALLOWEDVALUE_H_

#include <mupnp/xml/Node.h>

namespace mUPnP{
class AllowedValue {
  mUPnP::Node *allowedValueNode;
  
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

 public:
  void setAllowedValueNode(Node *node) {
    allowedValueNode = node;
  }

  mUPnP::Node *getAllowedValueNode() {
    return allowedValueNode;
  }

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

public:
  
  AllowedValue() {
    setAllowedValueNode(NULL);
  }

  AllowedValue(Node *node) {
    setAllowedValueNode(node);
  }

  ////////////////////////////////////////////////
  // isAllowedValueNode
  ////////////////////////////////////////////////

 public:
  static bool isAllowedValueNode(Node *node) {
    return node->isName(AllowedValue::ELEM_NAME);
  }

  ////////////////////////////////////////////////
  // minimum
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

