/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ARGUMENT_H_
#define _MUPMPCC_ARGUMENT_H_

#include <stdlib.h>

#include <uhttp/util/StringUtil.h>
#include <mupnp/xml/Node.h>
#include <mupnp/xml/ArgumentData.h>

namespace mUPnP{
class Service;
class StateVariable;

class Argument {
  
  mUPnP::Node *serviceNode;
  mUPnP::Node *argumentNode;

  mUPnP::Node defaultArgumentNode;
  mUPnP::Node defaultServiceNode;
  
 public:
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

  static const char *ELEM_NAME;
  static const char *IN_DIR;
  static const char *OUT_DIR;
  static const char *NAME;
  static const char *DIRECTION;
  static const char *RELATED_STATE_VARIABLE;

 public:
  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

  mUPnP::Node *getServiceNode() {
    return serviceNode;
  }

  mUPnP::Node *getArgumentNode() {
    return argumentNode;
  }
  
  Service *getService();

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  Argument();
  Argument(Node *servNode, mUPnP::Node *argNode);
  Argument(const std::string &name, const std::string &value);

  ~Argument();

  ////////////////////////////////////////////////
  // isArgumentNode
  ////////////////////////////////////////////////

  static bool isArgumentNode(Node *node) {
    return node->isName(Argument::ELEM_NAME);
  }

  ////////////////////////////////////////////////
  // name
  ////////////////////////////////////////////////

  void setName(const std::string &value) {
    getArgumentNode()->setNode(NAME, value);
  }

  const char *getName() {
    return getArgumentNode()->getNodeValue(NAME);
  }

  ////////////////////////////////////////////////
  // direction
  ////////////////////////////////////////////////

  void setDirection(const std::string &value) {
    getArgumentNode()->setNode(DIRECTION, value);
  }

  const char *getDirection() {
    return getArgumentNode()->getNodeValue(DIRECTION);
  }

  bool isInDirection() {
    const char *dir = getDirection();
    if (dir == NULL)
      return false;
    uHTTP::String dirStr(dir);
    return dirStr.equalsIgnoreCase(IN_DIR);
  }

  bool isOutDirection() {
    return !isInDirection();
  }
  
  ////////////////////////////////////////////////
  // relatedStateVariable
  ////////////////////////////////////////////////

  void setRelatedStateVariableName(const std::string &value) {
    getArgumentNode()->setNode(RELATED_STATE_VARIABLE, value);
  }

  const char *getRelatedStateVariableName() {
    return getArgumentNode()->getNodeValue(RELATED_STATE_VARIABLE);
  }

  StateVariable *getRelatedStateVariable();

  ////////////////////////////////////////////////
  // UserData
  ////////////////////////////////////////////////

  ArgumentData *getArgumentData() {
    mUPnP::Node *node = getArgumentNode();
    ArgumentData *userData = dynamic_cast<ArgumentData *>(node->getUserData());
    if (userData == NULL) {
      userData = new ArgumentData();
      node->setUserData(userData);
    }
    return userData;
  }

  ////////////////////////////////////////////////
  // value
  ////////////////////////////////////////////////

  void setValue(const std::string &value) {
    getArgumentData()->setValue(value);
  }

  void setValue(int value);

  const char *getValue() {
    return getArgumentData()->getValue();
  }

  int getIntegerValue() {
    return atoi(getValue());
  }

};

}

#endif
