/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2004
*
*  File: AllowedValueRange.h
*
*  Revision:
*
*  03/29/04
*    - first revision.
*  
******************************************************************/

#ifndef _CLINK_ALLOWEDVALUERANGE_H_
#define _CLINK_ALLOWEDVALUERANGE_H_

#include <cybergarage/xml/Node.h>

namespace CyberLink{
class AllowedValueRange {
  CyberXML::Node *allowedValueRangeNode;

  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////

public:
  
  static const char *ELEM_NAME;

  static const char *MAXIMUM;
  static const char *MINIMUM;
  static const char *STEP;

  
  ////////////////////////////////////////////////
  //  Member
  ////////////////////////////////////////////////

 public:
  void setAllowedValueRangeNode(CyberXML::Node *node) {
    allowedValueRangeNode = node;
  }

  CyberXML::Node *getAllowedValueRangeNode() {
    return allowedValueRangeNode;
  }

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

public:
  
  AllowedValueRange() {
    setAllowedValueRangeNode(NULL);
  }

  AllowedValueRange(CyberXML::Node *node) {
    setAllowedValueRangeNode(node);
  }

  ////////////////////////////////////////////////
  //  isIconNode
  ////////////////////////////////////////////////

 public:
  static bool isAllowedValueRangeNode(CyberXML::Node *node) {
    return node->isName(AllowedValueRange::ELEM_NAME);
  }

  ////////////////////////////////////////////////
  //  minimum
  ////////////////////////////////////////////////

 public:
  void setMinimum(const std::string &value) {
    getAllowedValueRangeNode()->setNode(MINIMUM, value);
  }

  const char *getMinimum() {
    return getAllowedValueRangeNode()->getNodeValue(MINIMUM);
  }

  ////////////////////////////////////////////////
  //  maximum
  ////////////////////////////////////////////////

 public:
  void setMaximum(const std::string &value) {
    getAllowedValueRangeNode()->setNode(MAXIMUM, value);
  }

  const char *getMaximum() {
    return getAllowedValueRangeNode()->getNodeValue(MAXIMUM);
  }

  ////////////////////////////////////////////////
  //  width
  ////////////////////////////////////////////////

 public:
  void setStep(const std::string &value) {
    getAllowedValueRangeNode()->setNode(STEP, value);
  }

  const char *getStep() {
    return getAllowedValueRangeNode()->getNodeValue(STEP);
  }
};

}

#endif

