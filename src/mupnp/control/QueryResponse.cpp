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
  mUPnP::Node *bodyNode = getBodyNode();
  mUPnP::Node *resNode = createResponseNode(value);
  bodyNode->addNode(resNode);
    
  mUPnP::Node *envNodee = getEnvelopeNode();
  setContent(envNodee);
}

////////////////////////////////////////////////
// getReturn
////////////////////////////////////////////////

mUPnP::Node *QueryResponse::getReturnNode() {
  mUPnP::Node *bodyNode = getBodyNode();
  if (bodyNode == NULL)
    return NULL;
  if (bodyNode->hasNodes() == false)
    return NULL;
  mUPnP::Node *queryResNode = bodyNode->getNode(0);
  if (queryResNode == NULL)
    return NULL;
  if (queryResNode->hasNodes() == false)
    return NULL;
  return queryResNode->getNode(0);
}
  
const char *QueryResponse::getReturnValue() {
  mUPnP::Node *node = getReturnNode();
  if (node == NULL)
    return "";
  return node->getValue();
}

////////////////////////////////////////////////
// setRequest
////////////////////////////////////////////////

Node *QueryResponse::createResponseNode(const std::string &value) {
  mUPnP::Node *queryResNode = new mUPnP::Node();
  queryResNode->setName(Control::NS, Control::QUERY_STATE_VARIABLE_RESPONSE);
  queryResNode->setNameSpace(Control::NS, Control::XMLNS);
    
  mUPnP::Node *returnNode = new mUPnP::Node();
  returnNode->setName(Control::RETURN);
  returnNode->setValue(value);
  queryResNode->addNode(returnNode);
    
  return queryResNode;
}
