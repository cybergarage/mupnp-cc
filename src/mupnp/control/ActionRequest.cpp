/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
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

#include <mupnp/control/ActionRequest.h>
#include <mupnp/Device.h>
#include <mupnp/Service.h>
#include <mupnp/Action.h>

#include <string>

using namespace std;
using namespace mUPnP;

////////////////////////////////////////////////
// initArgumentList
////////////////////////////////////////////////

void ActionRequest::initArgumentList() {
  mupnp_shared_ptr<uXML::Node> actNode = getActionNode();
  if (!actNode)
    return;
  size_t nArgNodes = actNode->getNNodes();
  argumentList.clear();
  for (size_t n = 0; n < nArgNodes; n++) {
    Argument *arg = new Argument();
    mupnp_shared_ptr<uXML::Node> argNode = actNode->getNode(n);
    arg->setName(argNode->getName());
    arg->setValue(argNode->getValue());
    argumentList.add(arg);
  }
}

////////////////////////////////////////////////
// getActionNode
////////////////////////////////////////////////

mupnp_shared_ptr<uXML::Node> ActionRequest::getActionNode() {
  mupnp_shared_ptr<uXML::Node> bodyNode = getBodyNode();
  if (!bodyNode)
    return nullptr;
  if (bodyNode->hasNodes() == false)
    return nullptr;
  return bodyNode->getNode(0);
}

////////////////////////////////////////////////
// getActionName
////////////////////////////////////////////////

const char *ActionRequest::getActionName(std::string &buf) {
  mupnp_shared_ptr<uXML::Node> node = getActionNode();
  if (!node)
    return "";
  const char *name = node->getName();
  if (!name)
    return "";
  uHTTP::String nameStr(name);
  int idx = nameStr.indexOf(uSOAP::SOAP::DELIM)+1;
  if (idx < 0)
    return "";
  uHTTP::String actName;
  buf = nameStr.substring(idx, nameStr.length(), actName);
  return buf.c_str();
}

////////////////////////////////////////////////
// setRequest
////////////////////////////////////////////////

void ActionRequest::setRequest(Action *action, ArgumentList *argList) {
  Service *service = action->getService();

  setRequestHost(service);

  setEnvelopeNode(uSOAP::SOAP::CreateEnvelopeBodyNode());
  mupnp_shared_ptr<uXML::Node> envNode = getEnvelopeNode();
  mupnp_shared_ptr<uXML::Node> bodyNode = getBodyNode();
  uXML::Node *argNode = createContentNode(service, action, argList);
  bodyNode->addNode(argNode);
  setContent(envNode.get());

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
// Contents
////////////////////////////////////////////////

uXML::Node *ActionRequest::createContentNode(Service *service, mUPnP::Action *action, ArgumentList *argList) {
  const char *actionName = action->getName();
  const char *serviceType = service->getServiceType();

  uXML::Node *actionNode = new uXML::Node();
  actionNode->setName(Control::NS, actionName);
  actionNode->setNameSpace(Control::NS, serviceType);
  size_t argListCnt = argList->size();
  for (size_t n = 0; n < argListCnt; n++) {
    Argument *arg = argList->getArgument(n);
    uXML::Node *argNode = new uXML::Node();
    string name = arg->getName();
    string value = arg->getValue();
    argNode->setName(name.c_str());
    argNode->setValue(value.c_str());
    actionNode->addNode(argNode);
  }
    
  return actionNode;
}

////////////////////////////////////////////////
// post
////////////////////////////////////////////////

ActionResponse *ActionRequest::post(ActionResponse *actionRes) {
  postMessage(getRequestHost(), getRequestPort(), actionRes);
  return actionRes;
}
