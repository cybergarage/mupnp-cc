/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: Argument.h
*
*  Revision;
*
*  07/08/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_ARGUMENT_H_
#define _CLINK_ARGUMENT_H_

#include <stdlib.h>

#include <uhttp/util/StringUtil.h>
#include <cybergarage/xml/Node.h>
#include <cybergarage/upnp/xml/ArgumentData.h>

namespace CyberLink{
class Service;
class StateVariable;

class Argument {
  
  CyberXML::Node *serviceNode;
  CyberXML::Node *argumentNode;

  CyberXML::Node defaultArgumentNode;
  CyberXML::Node defaultServiceNode;
  
 public:
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////

  static const char *ELEM_NAME;
  static const char *IN_DIR;
  static const char *OUT_DIR;
  static const char *NAME;
  static const char *DIRECTION;
  static const char *RELATED_STATE_VARIABLE;

 public:
  ////////////////////////////////////////////////
  //  Member
  ////////////////////////////////////////////////

  CyberXML::Node *getServiceNode() {
    return serviceNode;
  }

  CyberXML::Node *getArgumentNode() {
    return argumentNode;
  }
  
  Service *getService();

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

  Argument();
  Argument(CyberXML::Node *servNode, CyberXML::Node *argNode);
  Argument(const std::string &name, const std::string &value);

  ~Argument();

  ////////////////////////////////////////////////
  //  isArgumentNode
  ////////////////////////////////////////////////

  static bool isArgumentNode(CyberXML::Node *node) {
    return node->isName(Argument::ELEM_NAME);
  }

  ////////////////////////////////////////////////
  //  name
  ////////////////////////////////////////////////

  void setName(const std::string &value) {
    getArgumentNode()->setNode(NAME, value);
  }

  const char *getName() {
    return getArgumentNode()->getNodeValue(NAME);
  }

  ////////////////////////////////////////////////
  //  direction
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
  //  relatedStateVariable
  ////////////////////////////////////////////////

  void setRelatedStateVariableName(const std::string &value) {
    getArgumentNode()->setNode(RELATED_STATE_VARIABLE, value);
  }

  const char *getRelatedStateVariableName() {
    return getArgumentNode()->getNodeValue(RELATED_STATE_VARIABLE);
  }

  StateVariable *getRelatedStateVariable();

  ////////////////////////////////////////////////
  //  UserData
  ////////////////////////////////////////////////

  ArgumentData *getArgumentData() {
    CyberXML::Node *node = getArgumentNode();
    ArgumentData *userData = (ArgumentData *)node->getUserData();
    if (userData == NULL) {
      userData = new ArgumentData();
      node->setUserData(userData);
    }
    return userData;
  }

  ////////////////////////////////////////////////
  //  value
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
