/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: QueryRequest.cpp
*
*  Revision;
*
*  08/15/03
*    - first revision
*  09/02/03
*    - Giordano Sassaroli <sassarol@cefriel.it>
*    - Error : redundant code, the setRequest method in QueryRequest invokes setURI even if after a couple of rows setRequestHost is invoked
*  04/26/04
*    - Added post(QueryResponse *queryRes);
*  05/19/04
*    - Changed the header include order for Cygwin.
*
******************************************************************/

#include <mupnp/control/QueryRequest.h>
#include <mupnp/Device.h>
#include <mupnp/Service.h>
#include <mupnp/StateVariable.h>

using namespace mUPnP;
using namespace mUPnP;

////////////////////////////////////////////////
// setRequest
////////////////////////////////////////////////
  
void QueryRequest::setRequest(StateVariable *stateVar) {
  Service *service = stateVar->getService();    
    
  setRequestHost(service);

  setEnvelopeNode(SOAP::CreateEnvelopeBodyNode());
  mUPnP::Node *envNode = getEnvelopeNode();
  mUPnP::Node *bodyNode = getBodyNode();
  mUPnP::Node *qeuryNode = createContentNode(stateVar);
  bodyNode->addNode(qeuryNode);
  setContent(envNode);

  setSOAPAction(Control::QUERY_SOAPACTION);
}

////////////////////////////////////////////////
// Contents
////////////////////////////////////////////////

mUPnP::Node *QueryRequest::createContentNode(StateVariable *stateVar) {
  mUPnP::Node *queryVarNode = new mUPnP::Node();
  queryVarNode->setName(Control::NS, Control::QUERY_STATE_VARIABLE);
  queryVarNode->setNameSpace(Control::NS, Control::XMLNS);

  mUPnP::Node *varNode = new mUPnP::Node();
  varNode->setName(Control::NS, Control::VAR_NAME);
  varNode->setValue(stateVar->getName());
  queryVarNode->addNode(varNode);
    
  return queryVarNode;
}

////////////////////////////////////////////////
// getVarName
////////////////////////////////////////////////

mUPnP::Node *QueryRequest::getVarNameNode() {
  mUPnP::Node *bodyNode = getBodyNode();
  if (bodyNode == NULL)
    return NULL;
  if (bodyNode->hasNodes() == false)
    return NULL;
  mUPnP::Node *queryStateVarNode = bodyNode->getNode(0);
  if (queryStateVarNode == NULL)
    return NULL;
  if (queryStateVarNode->hasNodes() == false)
    return NULL;
  return queryStateVarNode->getNode(0);
}
  
const char *QueryRequest::getVarName() {
  mUPnP::Node *node = getVarNameNode();
  if (node == NULL)
    return "";
  return node->getValue();
}

////////////////////////////////////////////////
// post
////////////////////////////////////////////////

QueryResponse *QueryRequest::post(QueryResponse *queryRes) {
  postMessage(getRequestHost(), getRequestPort(), queryRes);
  return queryRes;
}
