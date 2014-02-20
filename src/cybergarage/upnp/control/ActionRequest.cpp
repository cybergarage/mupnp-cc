/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ControlRequest.cpp
*
*  Revision;
*
*  08/13/03
*    - first revision
*  04/25/04
*    - Added post(ActionResponse *actionRes);
*  05/19/04
*    - Changed the header include order for Cygwin.
*  05/09/05
*    - Changed getActionName() to return when the delimiter is not found.
*  08/21/05
*    - Changed setRequest() using string instead of ostringstream.
*
******************************************************************/

#include <cybergarage/upnp/control/ActionRequest.h>
#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/Service.h>
#include <cybergarage/upnp/Action.h>

#include <string>

using namespace std;
using namespace CyberLink;
using namespace CyberXML;
using namespace CyberSOAP;

////////////////////////////////////////////////
//  initArgumentList
////////////////////////////////////////////////

void ActionRequest::initArgumentList() {
  Node *actNode = getActionNode();
  if (actNode == NULL)
    return;
  int nArgNodes = actNode->getNNodes();
  argumentList.clear();
  for (int n = 0; n < nArgNodes; n++) {
    Argument *arg = new Argument();
    Node *argNode = actNode->getNode(n);
    arg->setName(argNode->getName());
    arg->setValue(argNode->getValue());
    argumentList.add(arg);
  }
}

////////////////////////////////////////////////
//  getActionNode
////////////////////////////////////////////////

CyberXML::Node *ActionRequest::getActionNode() {
  CyberXML::Node *bodyNode = getBodyNode();
  if (bodyNode == NULL)
    return NULL;
  if (bodyNode->hasNodes() == false)
    return NULL;
  return bodyNode->getNode(0);
}

////////////////////////////////////////////////
//  getActionName
////////////////////////////////////////////////

const char *ActionRequest::getActionName(std::string &buf) {
  CyberXML::Node *node = getActionNode();
  if (node == NULL)
    return "";
  const char *name = node->getName();
  if (name == NULL)
    return "";
  uHTTP::String nameStr(name);
  int idx = nameStr.indexOf(CyberSOAP::SOAP::DELIM)+1;
  if (idx < 0)
    return "";
  uHTTP::String actName;
  buf = nameStr.substring(idx, nameStr.length(), actName);
  return buf.c_str();
}

////////////////////////////////////////////////
//  setRequest
////////////////////////////////////////////////

void ActionRequest::setRequest(CyberLink::Action *action, ArgumentList *argList) {
  Service *service = action->getService();

  setRequestHost(service);

  setEnvelopeNode(SOAP::CreateEnvelopeBodyNode());
  Node *envNode = getEnvelopeNode();
  Node *bodyNode = getBodyNode();
  Node *argNode = createContentNode(service, action, argList);
  bodyNode->addNode(argNode);
  setContent(envNode);

  const char *serviceType = service->getServiceType();
  const char *actionName = action->getName();
  string soapAction;
  soapAction.append("\"");
  soapAction.append(serviceType);
  soapAction.append("#");
  soapAction.append(actionName);
  soapAction.append("\"");
  setSOAPAction(soapAction.c_str());
}

////////////////////////////////////////////////
//  Contents
////////////////////////////////////////////////

Node *ActionRequest::createContentNode(Service *service, CyberLink::Action *action, ArgumentList *argList) {
  const char *actionName = action->getName();
  const char *serviceType = service->getServiceType();

  Node *actionNode = new Node();
  actionNode->setName(Control::NS, actionName);
  actionNode->setNameSpace(Control::NS, serviceType);
  int argListCnt = argList->size();
  for (int n = 0; n < argListCnt; n++) {
    Argument *arg = argList->getArgument(n);
    Node *argNode = new Node();
    string name = arg->getName();
    string value = arg->getValue();
    argNode->setName(name.c_str());
    argNode->setValue(value.c_str());
    actionNode->addNode(argNode);
  }
    
  return actionNode;
}

////////////////////////////////////////////////
//  post
////////////////////////////////////////////////

ActionResponse *ActionRequest::post(ActionResponse *actionRes) {
  postMessage(getRequestHost(), getRequestPort(), actionRes);
  return actionRes;
}
