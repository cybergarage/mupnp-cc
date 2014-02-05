/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: QueryResponse.cpp
*
*  Revision;
*
*  08/15/03
*    - first revision
*  05/19/04
*    - Changed the header include order for Cygwin.
*
******************************************************************/

#include <cybergarage/upnp/control/QueryResponse.h>
#include <cybergarage/upnp/StateVariable.h>

using namespace CyberLink;
using namespace CyberXML;

////////////////////////////////////////////////
//  setRequest
////////////////////////////////////////////////

void QueryResponse::setResponse(StateVariable *stateVar) {
  setStatusCode(uHTTP::HTTP::OK_REQUEST);
    
  const char *value = stateVar->getValue();
  CyberXML::Node *bodyNode = getBodyNode();
  CyberXML::Node *resNode = createResponseNode(value);
  bodyNode->addNode(resNode);
    
  CyberXML::Node *envNodee = getEnvelopeNode();
  setContent(envNodee);
}

////////////////////////////////////////////////
//  getReturn
////////////////////////////////////////////////

CyberXML::Node *QueryResponse::getReturnNode() {
  CyberXML::Node *bodyNode = getBodyNode();
  if (bodyNode == NULL)
    return NULL;
  if (bodyNode->hasNodes() == false)
    return NULL;
  CyberXML::Node *queryResNode = bodyNode->getNode(0);
  if (queryResNode == NULL)
    return NULL;
  if (queryResNode->hasNodes() == false)
    return NULL;
  return queryResNode->getNode(0);
}
  
const char *QueryResponse::getReturnValue() {
  CyberXML::Node *node = getReturnNode();
  if (node == NULL)
    return "";
  return node->getValue();
}

////////////////////////////////////////////////
//  setRequest
////////////////////////////////////////////////

Node *QueryResponse::createResponseNode(const std::string &value) {
  CyberXML::Node *queryResNode = new CyberXML::Node();
  queryResNode->setName(Control::NS, Control::QUERY_STATE_VARIABLE_RESPONSE);
  queryResNode->setNameSpace(Control::NS, Control::XMLNS);
    
  CyberXML::Node *returnNode = new CyberXML::Node();
  returnNode->setName(Control::RETURN);
  returnNode->setValue(value);
  queryResNode->addNode(returnNode);
    
  return queryResNode;
}
