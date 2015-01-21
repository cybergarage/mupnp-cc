/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/Action.h>
#include <uhttp/util/Debug.h>
#include <mupnp/Service.h>

#include <string>

using namespace std;
using namespace uHTTP;
using namespace mUPnP;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *Action::ELEM_NAME = "action";
const char *Action::NAME = "name";

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

Action::Action(Node *serviceNode, mUPnP::Node *actionNode) {
  this->serviceNode = serviceNode;
  this->actionNode = actionNode;

  initArgumentList();
}

Action::Action(Action *action) {
  this->serviceNode = action->getServiceNode();
  this->actionNode = action->getActionNode();

  initArgumentList();
}

Action::~Action() {
  delete argumentList;
  delete argumentInList;
  delete argumentOutList;
}

////////////////////////////////////////////////
// getService
////////////////////////////////////////////////

Service *Action::getService() {
  mUPnP::Node *node = getServiceNode();
  ServiceData *data = dynamic_cast<ServiceData *>(node->getUserData());
  if (data == NULL)
    return NULL;
  return data->getService();
}

////////////////////////////////////////////////
// argumentList
////////////////////////////////////////////////

void Action::initArgumentList() {
  argumentList = new ArgumentList(true);
  argumentInList = new ArgumentList(false);
  argumentOutList = new ArgumentList(false);

  mUPnP::Node *serviceNode = getServiceNode();
  mUPnP::Node *argumentListNode = getActionNode()->getNode(ArgumentList::ELEM_NAME);
  if (serviceNode == NULL || argumentListNode == NULL)
    return;

  size_t nodeCnt = argumentListNode->getNNodes();
  for (size_t n = 0; n < nodeCnt; n++) {
    mUPnP::Node *argNode = argumentListNode->getNode(n);
    if (Argument::isArgumentNode(argNode) == false)
      continue;
    Argument *arg = new Argument(serviceNode, argNode);
    argumentList->add(arg);
    if (arg->isInDirection() == true) 
      argumentInList->add(arg);
    if (arg->isOutDirection() == true)
      argumentOutList->add(arg);
  } 
}

Argument *Action::getArgument(const std::string &name) {
  ArgumentList *argList = getArgumentList();
  size_t nArgs = argList->size();
  for (size_t n = 0; n < nArgs; n++) {
    Argument *arg = argList->getArgument(n);
    const char *argName = arg->getName();
    if (argName == NULL)
      continue;
    string argNameStr = argName;
    if (argNameStr.compare(name) == 0)
      return arg;
  }
  return NULL;
}

void Action::clearOutputAgumentValues() {
  ArgumentList *outArgList = getOutputArgumentList();
  size_t nArgs = outArgList->size();
  for (size_t n = 0; n < nArgs; n++) {
    Argument *arg = outArgList->getArgument(n);
    arg->setValue("");
  }
}

////////////////////////////////////////////////
// controlAction
////////////////////////////////////////////////

bool Action::performActionListener(ActionRequest *actionReq) {
  ActionListener *listener = (ActionListener *)getActionListener();
  if (listener == NULL)
    return false;
  ActionResponse actionRes;
  setStatus(UPnP::INVALID_ACTION);
  clearOutputAgumentValues();
  if (listener->actionControlReceived(this) == true) {
    actionRes.setResponse(this);
  }
  else {
    UPnPStatus *upnpStatus = getStatus();
    actionRes.setFaultResponse(upnpStatus->getCode(), upnpStatus->getDescription());
  }
  if (Debug::isOn() == true)
    actionRes.print();
  ControlRequest *ctrlReq = actionReq;
  ctrlReq->post(&actionRes);
  return true;
}

////////////////////////////////////////////////
// postControlAction
////////////////////////////////////////////////

bool Action::postControlAction() {
  ArgumentList *actionArgList = getArgumentList();
  ArgumentList *actionInputArgList = getInputArgumentList();
  ActionRequest ctrlReq;
  ctrlReq.setRequest(this, actionInputArgList);
  if (Debug::isOn() == true)
    ctrlReq.print();
  ActionResponse *ctrlRes = new ActionResponse();
  ctrlReq.post(ctrlRes);
  if (Debug::isOn() == true)
    ctrlRes->print();
  setControlResponse(ctrlRes);
  // Thanks for Dimas <cyberrate@users.sourceforge.net> and Stefano Lenzi <kismet-sl@users.sourceforge.net> (07/09/04)
  int statCode = ctrlRes->getStatusCode();
  setStatus(statCode);
  if (ctrlRes->isSuccessful() == false)
    return false;
  ArgumentList *outArgList = ctrlRes->getResponse();
  actionArgList->set(outArgList);
  return true;
}
