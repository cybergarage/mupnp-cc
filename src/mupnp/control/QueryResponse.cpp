/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
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

#include <mupnp/control/QueryResponse.h>
#include <mupnp/StateVariable.h>

using namespace mUPnP;
using namespace mUPnP;

////////////////////////////////////////////////
// setRequest
////////////////////////////////////////////////

void QueryResponse::setResponse(StateVariable *stateVar) {
  setStatusCode(uHTTP::HTTP::OK_REQUEST);
    
  const char *value = stateVar->getValue();
  uXML::Node *bodyNode = getBodyNode();
  uXML::Node *resNode = createResponseNode(value);
  bodyNode->addNode(resNode);
    
  uXML::Node *envNodee = getEnvelopeNode();
  setContent(envNodee);
}

////////////////////////////////////////////////
// getReturn
////////////////////////////////////////////////

uXML::Node *QueryResponse::getReturnNode() {
  uXML::Node *bodyNode = getBodyNode();
  if (bodyNode == NULL)
    return NULL;
  if (bodyNode->hasNodes() == false)
    return NULL;
  uXML::Node *queryResNode = bodyNode->getNode(0);
  if (queryResNode == NULL)
    return NULL;
  if (queryResNode->hasNodes() == false)
    return NULL;
  return queryResNode->getNode(0);
}
  
const char *QueryResponse::getReturnValue() {
  uXML::Node *node = getReturnNode();
  if (node == NULL)
    return "";
  return node->getValue();
}

////////////////////////////////////////////////
// setRequest
////////////////////////////////////////////////

uXML::Node *QueryResponse::createResponseNode(const std::string &value) {
  uXML::Node *queryResNode = new uXML::Node();
  queryResNode->setName(Control::NS, Control::QUERY_STATE_VARIABLE_RESPONSE);
  queryResNode->setNameSpace(Control::NS, Control::XMLNS);
    
  uXML::Node *returnNode = new uXML::Node();
  returnNode->setName(Control::RETURN);
  returnNode->setValue(value);
  queryResNode->addNode(returnNode);
    
  return queryResNode;
}