/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
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

#include <cybergarage/upnp/control/ActionResponse.h>
#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/Service.h>
#include <cybergarage/upnp/Action.h>

#include <sstream>

using namespace std;
using namespace uHTTP;
using namespace CyberLink;
using namespace CyberXML;
using namespace CyberSOAP;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

ActionResponse::ActionResponse() {
  setHeader(HTTP::EXT, "");
}

ActionResponse::ActionResponse(CyberSOAP::SOAPResponse *soapRes) {
  set(soapRes);
  setHeader(HTTP::EXT, "");
}

////////////////////////////////////////////////
//  Response
////////////////////////////////////////////////

void ActionResponse::setResponse(CyberLink::Action *action) {
  setStatusCode(uHTTP::HTTP::OK_REQUEST);
  
  CyberXML::Node *bodyNode = getBodyNode();
  CyberXML::Node *resNode = createResponseNode(action);
  bodyNode->addNode(resNode);

  CyberXML::Node *envNode = getEnvelopeNode();
  setContent(envNode);
}

CyberXML::Node *ActionResponse::createResponseNode(CyberLink::Action *action) {
  string nodeName;
  nodeName = CyberSOAP::SOAP::METHODNS;
  nodeName += CyberSOAP::SOAP::DELIM;
  nodeName += action->getName();
  nodeName += CyberSOAP::SOAP::RESPONSE;
  Node *actionNameResNode = new CyberXML::Node(nodeName.c_str());
    
  Service *service = action->getService();    
  if (service != NULL) {
    string attrName;
    attrName ="xmlns:";
    attrName += CyberSOAP::SOAP::METHODNS;
    actionNameResNode->setAttribute(
      attrName.c_str(),
      service->getServiceType());
  }
    
  ArgumentList *argList = action->getArgumentList();
  int nArgs = argList->size();
  for (int n = 0; n < nArgs; n++) {
    Argument *arg = argList->getArgument(n);
    if (arg->isOutDirection() == false)
      continue;
    CyberXML::Node *argNode = new CyberXML::Node();
    argNode->setName(arg->getName());
    argNode->setValue(arg->getValue());
    actionNameResNode->addNode(argNode);
  }
    
  return actionNameResNode;
}

 ////////////////////////////////////////////////
//  getResponse
////////////////////////////////////////////////

Node *ActionResponse::getActionResponseNode() {
  Node *bodyNode = getBodyNode();
  if (bodyNode == NULL || bodyNode->hasNodes() == false)
    return NULL;
  return bodyNode->getNode(0);
}

ArgumentList *ActionResponse::getResponse() {
  argList.clear();
    
  Node *resNode = getActionResponseNode();
  if (resNode == NULL)
    return &argList;
      
  int nArgs = resNode->getNNodes();
  for (int n = 0; n < nArgs; n++) {
    Node *node = resNode->getNode(n);
    const char *name = node->getName();
    const char *value = node->getValue();
    Argument *arg = new Argument(name, value);
    argList.add(arg);
  }
    
  return &argList;
}

