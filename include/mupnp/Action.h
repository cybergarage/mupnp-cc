/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ACTION_H_
#define _MUPMPCC_ACTION_H_

#include <mupnp/control/ActionRequest.h>
#include <mupnp/control/ActionResponse.h>
#include <mupnp/xml/Node.h>
#include <mupnp/UPnPStatus.h>
#include <mupnp/xml/ServiceData.h>
#include <mupnp/xml/ActionData.h>
#include <mupnp/ArgumentList.h>
#include <mupnp/control/ActionListener.h>
#include <uhttp/util/Mutex.h>

#include <sstream>

namespace mUPnP {
class Service;

class Action {
  mupnp_shared_ptr<uXML::Node> serviceNode;
  mupnp_shared_ptr<uXML::Node> actionNode;
  
  ArgumentList *argumentList;
  ArgumentList *argumentInList;
  ArgumentList *argumentOutList;

  UPnPStatus upnpStatus;

  uHTTP::Mutex mutex;

  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

 public:
  static const char *ELEM_NAME;
  static const char *NAME;

  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

private:

  mupnp_shared_ptr<uXML::Node> getServiceNode() {
    return serviceNode;
  }

public:
  
  Service *getService();
  
  mupnp_shared_ptr<uXML::Node> getActionNode() {
    return actionNode;
  }
  
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  Action(mupnp_shared_ptr<uXML::Node> serviceNode, mupnp_shared_ptr<uXML::Node> actionNode);
  Action(Action *action);

  ~Action();

  ////////////////////////////////////////////////
  // Mutex
  ////////////////////////////////////////////////
  
 public:
  void lock() {
    mutex.lock();
  }
  
  void unlock() {
    mutex.unlock();
  }

  ////////////////////////////////////////////////
  // isActionNode
  ////////////////////////////////////////////////

  static bool isActionNode(mupnp_shared_ptr<uXML::Node> node) {
    std::string nodeName = node->getName();
    if (nodeName.compare(Action::ELEM_NAME) == 0)
      return true;
    return false;
  }

  ////////////////////////////////////////////////
  // name
  ////////////////////////////////////////////////

  void setName(const std::string &value) {
    getActionNode()->setNode(Action::NAME, value);
  }

  const char *getName() {
    return getActionNode()->getNodeValue(Action::NAME);
  }

  ////////////////////////////////////////////////
  // argumentList
  ////////////////////////////////////////////////

private:

  void initArgumentList();
  void clearOutputAgumentValues();

 public:
  ArgumentList *getArgumentList() {
    return argumentList;
  }

  ArgumentList *getInputArgumentList() {
    return argumentInList;
  }

  ArgumentList *getOutputArgumentList() {
    return argumentOutList;
  }

  Argument *getArgument(const std::string &name);

  void setArgumentValues(ArgumentList *argList) {
    getArgumentList()->set(argList);
  }
  
  void setArgumentValue(const std::string &name, const std::string &value) {
    Argument *arg = getArgument(name);
    if (arg == NULL)
      return;
    arg->setValue(value);
  }

  void setArgumentValue(const std::string &name, int value) {
    Argument *arg = getArgument(name);
    if (arg == NULL)
      return;
    arg->setValue(value);
  }

  const char *getArgumentValue(const std::string &name) {
    Argument *arg = getArgument(name);
    if (arg == NULL)
      return "";
    return arg->getValue();
  }

  int getArgumentIntegerValue(const std::string &name) {
    Argument *arg = getArgument(name);
    if (arg == NULL)
      return 0;
    return arg->getIntegerValue();
  }
  
  ////////////////////////////////////////////////
  // UserData
  ////////////////////////////////////////////////

  ActionData *getActionData() {
    mupnp_shared_ptr<uXML::Node> node = getActionNode();
    ActionData *userData = dynamic_cast<ActionData *>(node->getUserData());
    if (userData == NULL) {
      userData = new ActionData();
      node->setUserData(userData);
    }
    return userData;
  }
  
  ////////////////////////////////////////////////
  // controlAction
  ////////////////////////////////////////////////

  ActionListener *getActionListener() 
  {
    return getActionData()->getActionListener();
  }

  void setActionListener(ActionListener *listener) 
  {
    getActionData()->setActionListener(listener);
  }

  bool performActionListener(ActionRequest *actionReq);

  ////////////////////////////////////////////////
  // ActionControl
  ////////////////////////////////////////////////

  ControlResponse *getControlResponse() 
  {
    return getActionData()->getControlResponse();
  }

  void setControlResponse(ControlResponse *res) 
  {
    getActionData()->setControlResponse(res);
  }
  
  UPnPStatus *getControlStatus() {
    return getControlResponse()->getUPnPError();
  }

  ////////////////////////////////////////////////
  // postControlAction
  ////////////////////////////////////////////////

 public:
  bool postControlAction();

  ////////////////////////////////////////////////
  // UPnPStatus
  ////////////////////////////////////////////////

 public:
  void setStatus(int code, const std::string &descr) {
    upnpStatus.setCode(code);
    upnpStatus.setDescription(descr);
  }

  void setStatus(int code) {
    setStatus(code, UPnP::StatusCodeToString(code));
  }
  
  UPnPStatus *getStatus() {
    return &upnpStatus;
  }

};

}

#endif

