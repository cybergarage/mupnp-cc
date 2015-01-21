/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ICON_H_
#define _MUPMPCC_ICON_H_

#include <sstream>
#include <mupnp/xml/Node.h>

namespace mUPnP {
class Icon {
  uXML::Node *iconNode;

 public:
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;
  static const char *MIME_TYPE;
  static const char *WIDTH;
  static const char *HEIGHT;
  static const char *DEPTH;
  static const char *URL;
  
  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

  uXML::Node *getIconNode() {
    return iconNode;
  }
  
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  Icon(uXML::Node *node) {
    iconNode = node;
  }

  ////////////////////////////////////////////////
  // isIconNode
  ////////////////////////////////////////////////

  static bool isIconNode(uXML::Node *node) {
    return node->isName(ELEM_NAME);
  }

  ////////////////////////////////////////////////
  // mimeType
  ////////////////////////////////////////////////

  void setMimeType(const std::string &value) {
    getIconNode()->setNode(MIME_TYPE, value);
  }

  const char *getMimeType() {
    return getIconNode()->getNodeValue(MIME_TYPE);
  }

  ////////////////////////////////////////////////
  // width
  ////////////////////////////////////////////////

  void setWidth(const std::string &value) {
    getIconNode()->setNode(WIDTH, value);
  }

  const char *getWidth() {
    return getIconNode()->getNodeValue(WIDTH);
  }

  ////////////////////////////////////////////////
  // height
  ////////////////////////////////////////////////

  void setHeight(const std::string &value) {
    getIconNode()->setNode(HEIGHT, value);
  }

  const char *getHeight() {
    return getIconNode()->getNodeValue(HEIGHT);
  }

  ////////////////////////////////////////////////
  // depth
  ////////////////////////////////////////////////

  void setDepth(const std::string &value) {
    getIconNode()->setNode(DEPTH, value);
  }

  const char *getDepth() {
    return getIconNode()->getNodeValue(DEPTH);
  }

  ////////////////////////////////////////////////
  // URL
  ////////////////////////////////////////////////

  void setURL(const std::string &value) {
    getIconNode()->setNode(URL, value);
  }

  const char *getURL() {
    return getIconNode()->getNodeValue(URL);
  }
};

}

#endif
