/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
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

#include <cybergarage/upnp/control/QueryRequest.h>
#include <cybergarage/upnp/Device.h>
#include <cybergarage/upnp/Service.h>
#include <cybergarage/upnp/StateVariable.h>

using namespace CyberLink;
using namespace CyberXML;

////////////////////////////////////////////////
//  setRequest
////////////////////////////////////////////////
  
void QueryRequest::setRequest(StateVariable *stateVar) {
  Service *service = stateVar->getService();    
    
  setRequestHost(service);

  setEnvelopeNode(CyberSOAP::SOAP::CreateEnvelopeBodyNode());
  CyberXML::Node *envNode = getEnvelopeNode();
  CyberXML::Node *bodyNode = getBodyNode();
  CyberXML::Node *qeuryNode = createContentNode(stateVar);
  bodyNode->addNode(qeuryNode);
  setContent(envNode);

  setSOAPAction(Control::QUERY_SOAPACTION);
}

////////////////////////////////////////////////
//  Contents
////////////////////////////////////////////////

CyberXML::Node *QueryRequest::createContentNode(StateVariable *stateVar) {
  CyberXML::Node *queryVarNode = new CyberXML::Node();
  queryVarNode->setName(Control::NS, Control::QUERY_STATE_VARIABLE);
  queryVarNode->setNameSpace(Control::NS, Control::XMLNS);

  CyberXML::Node *varNode = new CyberXML::Node();
  varNode->setName(Control::NS, Control::VAR_NAME);
  varNode->setValue(stateVar->getName());
  queryVarNode->addNode(varNode);
    
  return queryVarNode;
}

////////////////////////////////////////////////
//  getVarName
////////////////////////////////////////////////

CyberXML::Node *QueryRequest::getVarNameNode() {
  CyberXML::Node *bodyNode = getBodyNode();
  if (bodyNode == NULL)
    return NULL;
  if (bodyNode->hasNodes() == false)
    return NULL;
  CyberXML::Node *queryStateVarNode = bodyNode->getNode(0);
  if (queryStateVarNode == NULL)
    return NULL;
  if (queryStateVarNode->hasNodes() == false)
    return NULL;
  return queryStateVarNode->getNode(0);
}
  
const char *QueryRequest::getVarName() {
  CyberXML::Node *node = getVarNameNode();
  if (node == NULL)
    return "";
  return node->getValue();
}

////////////////////////////////////////////////
//  post
////////////////////////////////////////////////

QueryResponse *QueryRequest::post(QueryResponse *queryRes) {
  postMessage(getRequestHost(), getRequestPort(), queryRes);
  return queryRes;
}
