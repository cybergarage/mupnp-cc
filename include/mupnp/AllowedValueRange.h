/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ALLOWEDVALUERANGE_H_
#define _MUPMPCC_ALLOWEDVALUERANGE_H_

#include <mupnp/xml/Node.h>

namespace mUPnP {
class AllowedValueRange {
  mupnp_shared_ptr<uXML::Node> allowedValueRangeNode;

  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

  public:
  static const char* ELEM_NAME;

  static const char* MAXIMUM;
  static const char* MINIMUM;
  static const char* STEP;

  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

  public:
  void setAllowedValueRangeNode(mupnp_shared_ptr<uXML::Node> node)
  {
    allowedValueRangeNode = node;
  }

  mupnp_shared_ptr<uXML::Node> getAllowedValueRangeNode()
  {
    return allowedValueRangeNode;
  }

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  public:
  AllowedValueRange()
  {
    setAllowedValueRangeNode(mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr));
  }

  AllowedValueRange(mupnp_shared_ptr<uXML::Node> node)
  {
    setAllowedValueRangeNode(node);
  }

  ////////////////////////////////////////////////
  // isIconNode
  ////////////////////////////////////////////////

  public:
  static bool isAllowedValueRangeNode(uXML::Node* node)
  {
    return node->isName(AllowedValueRange::ELEM_NAME);
  }

  ////////////////////////////////////////////////
  // minimum
  ////////////////////////////////////////////////

  public:
  void setMinimum(const std::string& value)
  {
    getAllowedValueRangeNode()->setNode(MINIMUM, value);
  }

  const char* getMinimum()
  {
    return getAllowedValueRangeNode()->getNodeValue(MINIMUM);
  }

  ////////////////////////////////////////////////
  // maximum
  ////////////////////////////////////////////////

  public:
  void setMaximum(const std::string& value)
  {
    getAllowedValueRangeNode()->setNode(MAXIMUM, value);
  }

  const char* getMaximum()
  {
    return getAllowedValueRangeNode()->getNodeValue(MAXIMUM);
  }

  ////////////////////////////////////////////////
  // width
  ////////////////////////////////////////////////

  public:
  void setStep(const std::string& value)
  {
    getAllowedValueRangeNode()->setNode(STEP, value);
  }

  const char* getStep()
  {
    return getAllowedValueRangeNode()->getNodeValue(STEP);
  }
};

}

#endif
