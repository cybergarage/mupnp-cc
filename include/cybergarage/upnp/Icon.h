/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: Icon.h
*
*  Revision;
*
*  07/20/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_ICON_H_
#define _CLINK_ICON_H_

#include <sstream>
#include <cybergarage/xml/Node.h>

namespace CyberLink {
class Icon {
  CyberXML::Node *iconNode;

 public:
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////
  
  static const char *ELEM_NAME;
  static const char *MIME_TYPE;
  static const char *WIDTH;
  static const char *HEIGHT;
  static const char *DEPTH;
  static const char *URL;
  
  ////////////////////////////////////////////////
  //  Member
  ////////////////////////////////////////////////

  CyberXML::Node *getIconNode() {
    return iconNode;
  }
  
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

  Icon(CyberXML::Node *node) {
    iconNode = node;
  }

  ////////////////////////////////////////////////
  //  isIconNode
  ////////////////////////////////////////////////

  static bool isIconNode(CyberXML::Node *node) {
    return node->isName(ELEM_NAME);
  }

  ////////////////////////////////////////////////
  //  mimeType
  ////////////////////////////////////////////////

  void setMimeType(const std::string &value) {
    getIconNode()->setNode(MIME_TYPE, value);
  }

  const char *getMimeType() {
    return getIconNode()->getNodeValue(MIME_TYPE);
  }

  ////////////////////////////////////////////////
  //  width
  ////////////////////////////////////////////////

  void setWidth(const std::string &value) {
    getIconNode()->setNode(WIDTH, value);
  }

  const char *getWidth() {
    return getIconNode()->getNodeValue(WIDTH);
  }

  ////////////////////////////////////////////////
  //  height
  ////////////////////////////////////////////////

  void setHeight(const std::string &value) {
    getIconNode()->setNode(HEIGHT, value);
  }

  const char *getHeight() {
    return getIconNode()->getNodeValue(HEIGHT);
  }

  ////////////////////////////////////////////////
  //  depth
  ////////////////////////////////////////////////

  void setDepth(const std::string &value) {
    getIconNode()->setNode(DEPTH, value);
  }

  const char *getDepth() {
    return getIconNode()->getNodeValue(DEPTH);
  }

  ////////////////////////////////////////////////
  //  URL
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
