/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ActionResponse.cpp
*
*  Revision;
*
*  08/18/03
*    - first revision
*  09/02/03
*    - Giordano Sassaroli <sassarol@cefriel.it>
*    - Problem : Action Responses do not contain the mandatory header field EXT
*    - Error : ActionResponse class does not set the EXT header
*  05/19/04
*    - Changed the header include order for Cygwin.
*
******************************************************************/

#include <mupnp/control/ActionResponse.h>
#include <mupnp/Device.h>
#include <mupnp/Service.h>
#include <mupnp/Action.h>

#include <sstream>

using namespace std;
using namespace uHTTP;
using namespace mUPnP;
using namespace mUPnP;
using namespace mUPnP;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////

ActionResponse::ActionResponse() {
  setHeader(HTTP::EXT, "");
}

ActionResponse::ActionResponse(SOAPResponse *soapRes) {
  set(soapRes);
  setHeader(HTTP::EXT, "");
}

////////////////////////////////////////////////
// Response
////////////////////////////////////////////////

void ActionResponse::setResponse(Action *action) {
  setStatusCode(uHTTP::HTTP::OK_REQUEST);
  
  uXML::Node *bodyNode = getBodyNode();
  uXML::Node *resNode = createResponseNode(action);
  bodyNode->addNode(resNode);

  uXML::Node *envNode = getEnvelopeNode();
  setContent(envNode);
}

uXML::Node *ActionResponse::createResponseNode(Action *action) {
  string nodeName;
  nodeName = uSOAP::SOAP::METHODNS;
  nodeName += uSOAP::SOAP::DELIM;
  nodeName += action->getName();
  nodeName += uSOAP::SOAP::RESPONSE;
  uXML::Node *actionNameResNode = new uXML::Node(nodeName.c_str());
    
  Service *service = action->getService();    
  if (service != NULL) {
    string attrName;
    attrName ="xmlns:";
    attrName += uSOAP::SOAP::METHODNS;
    actionNameResNode->setAttribute(
      attrName.c_str(),
      service->getServiceType());
  }
    
  ArgumentList *argList = action->getArgumentList();
  size_t nArgs = argList->size();
  for (size_t n = 0; n < nArgs; n++) {
    Argument *arg = argList->getArgument(n);
    if (arg->isOutDirection() == false)
      continue;
    uXML::Node *argNode = new uXML::Node();
    argNode->setName(arg->getName());
    argNode->setValue(arg->getValue());
    actionNameResNode->addNode(argNode);
  }
    
  return actionNameResNode;
}

 ////////////////////////////////////////////////
// getResponse
////////////////////////////////////////////////

uXML::Node *ActionResponse::getActionResponseNode() {
  uXML::Node *bodyNode = getBodyNode();
  if (bodyNode == NULL || bodyNode->hasNodes() == false)
    return NULL;
  return bodyNode->getNode(0);
}

ArgumentList *ActionResponse::getResponse() {
  argList.clear();
    
  uXML::Node *resNode = getActionResponseNode();
  if (resNode == NULL)
    return &argList;
      
  size_t nArgs = resNode->getNNodes();
  for (size_t n = 0; n < nArgs; n++) {
    uXML::Node *node = resNode->getNode(n);
    const char *name = node->getName();
    const char *value = node->getValue();
    Argument *arg = new Argument(name, value);
    argList.add(arg);
  }
    
  return &argList;
}

