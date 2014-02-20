/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: Action.cpp
*
*  Revision;
*
*  07/15/03
*    - first revision
*  01/05/04
*    - Added UPnP status methods.
*    - Changed about new ActionListener interface.
*  01/05/04
*    - Added clearOutputAgumentValues() to initialize the output values before calling performActionListener().
*  04/23/04
*    - Fixed initArgumentList() to share a argument node in three Argument when the argument lists are initialized.
*    - Fixed getArgument(name) to return the valid pointer. 
*  04/26/04
*    - Changed postControlAction() to get the return value using the ActionResponse.
*  05/19/04
*    - Changed the header include order for Cygwin.
*  07/09/04
*    - Thanks for Dimas <cyberrate@users.sourceforge.net> and Stefano Lenzi <kismet-sl@users.sourceforge.net>
*    - Changed postControlAction() to set the status code to the UPnPStatus.
*
******************************************************************/

#include <cybergarage/upnp/Action.h>
#include <uhttp/util/Debug.h>
#include <cybergarage/upnp/Service.h>

#include <string>

using namespace std;
using namespace uHTTP;
using namespace CyberLink;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const char *Action::ELEM_NAME = "action";
const char *Action::NAME = "name";

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

Action::Action(CyberXML::Node *serviceNode, CyberXML::Node *actionNode) {
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
//  getService
////////////////////////////////////////////////

Service *Action::getService() {
  CyberXML::Node *node = getServiceNode();
  ServiceData *data = (ServiceData *)node->getUserData();
  if (data == NULL)
    return NULL;
  return data->getService();
}

////////////////////////////////////////////////
//  argumentList
////////////////////////////////////////////////

void Action::initArgumentList() {
  argumentList = new ArgumentList(true);
  argumentInList = new ArgumentList(false);
  argumentOutList = new ArgumentList(false);

  CyberXML::Node *serviceNode = getServiceNode();
  CyberXML::Node *argumentListNode = getActionNode()->getNode(ArgumentList::ELEM_NAME);
  if (serviceNode == NULL || argumentListNode == NULL)
    return;

  int nodeCnt = argumentListNode->getNNodes();
  for (int n = 0; n < nodeCnt; n++) {
    CyberXML::Node *argNode = argumentListNode->getNode(n);
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
  int nArgs = argList->size();
  for (int n = 0; n < nArgs; n++) {
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
  int nArgs = outArgList->size();
  for (int n = 0; n < nArgs; n++) {
    Argument *arg = outArgList->getArgument(n);
    arg->setValue("");
  }
}

////////////////////////////////////////////////
//  controlAction
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
//  postControlAction
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
