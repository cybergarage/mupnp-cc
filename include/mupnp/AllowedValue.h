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
  mupnp_shared_ptr<uXML::Node> allowedValueNode;
  
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;

  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

 public:
  void setAllowedValueNode(mupnp_shared_ptr<uXML::Node> node) {
    allowedValueNode = node;
  }

  mupnp_shared_ptr<uXML::Node> getAllowedValueNode() {
    return allowedValueNode;
  }

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

public:
  
  AllowedValue() {
    setAllowedValueNode(mupnp_shared_ptr<uXML::Node>((uXML::Node *)nullptr));
  }

  AllowedValue(mupnp_shared_ptr<uXML::Node> node) {
    setAllowedValueNode(node);
  }

  ////////////////////////////////////////////////
  // isAllowedValueNode
  ////////////////////////////////////////////////

 public:
  static bool isAllowedValueNode(mupnp_shared_ptr<uXML::Node> node) {
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

