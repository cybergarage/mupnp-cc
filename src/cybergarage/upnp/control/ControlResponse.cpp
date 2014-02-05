/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ControlResponse.cpp
*
*  Revision;
*
*  08/13/03
*    - first revision
*
******************************************************************/

#include <cybergarage/upnp/control/ControlResponse.h>
#include <cybergarage/upnp/Device.h>

#include <string>

using namespace std;
using namespace CyberLink;
using namespace CyberXML;
using namespace uHTTP;
using namespace CyberSOAP;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const char *ControlResponse::FAULT_CODE = "Client";
const char *ControlResponse::FAULT_STRING = "UPnPError";

////////////////////////////////////////////////
//  FaultResponse
////////////////////////////////////////////////

void ControlResponse::setFaultResponse(int errCode, const std::string &errDescr) {
  setStatusCode(HTTP::INTERNAL_SERVER_ERROR);
  
  Node *bodyNode = getBodyNode();
  Node *faultNode = createFaultResponseNode(errCode, errDescr);
  bodyNode->addNode(faultNode);

  Node *envNode = getEnvelopeNode();
  setContent(envNode);
}

Node *ControlResponse::createFaultResponseNode(int errCode, const std::string &errDescr) {
  // <s:Fault>
  string faultNodeName;
  faultNodeName = SOAP::XMLNS;
  faultNodeName += SOAP::DELIM;
  faultNodeName += SOAP::FAULT;
  Node *faultNode = new Node(faultNodeName.c_str());

  // <faultcode>s:Client</faultcode>
  Node *faultCodeNode = new Node(SOAP::FAULT_CODE);
  string faultCodeNodeValue;
  faultCodeNodeValue = SOAP::XMLNS;
  faultCodeNodeValue += SOAP::DELIM;
  faultCodeNodeValue += FAULT_CODE;
  faultCodeNode->setValue(faultCodeNodeValue.c_str());
  faultNode->addNode(faultCodeNode);
    
  // <faultstring>UPnPError</faultstring>
  Node *faultStringNode = new Node(SOAP::FAULT_STRING);
  faultStringNode->setValue(FAULT_STRING);
  faultNode->addNode(faultStringNode);

  // <detail>
  Node *detailNode = new Node(SOAP::DETAIL);
  faultNode->addNode(detailNode);

  // <UPnPError xmlns="urn:schemas-upnp-org:control-1-0">
  Node *upnpErrorNode = new Node(FAULT_STRING);
  upnpErrorNode->setAttribute("xmlns", Control::XMLNS);
  detailNode->addNode(upnpErrorNode);

  // <errorCode>error code</errorCode>
  Node *errorCodeNode = new Node(SOAP::ERROR_CODE);
  errorCodeNode->setValue(errCode);
  upnpErrorNode->addNode(errorCodeNode);

  // <errorDescription>error string</errorDescription>
  Node *errorDesctiprionNode = new Node(SOAP::ERROR_DESCRIPTION);
  errorDesctiprionNode->setValue(errDescr);
  upnpErrorNode->addNode(errorDesctiprionNode);
    
  return faultNode;
}

