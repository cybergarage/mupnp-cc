/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ControlResponse.cpp
*
*  Revision;
*
*  08/13/03
*    - first revision
*
******************************************************************/

#include <mupnp/control/ControlResponse.h>
#include <mupnp/Device.h>

#include <string>

using namespace std;
using namespace mUPnP;
using namespace uHTTP;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *ControlResponse::FAULT_CODE = "Client";
const char *ControlResponse::FAULT_STRING = "UPnPError";

////////////////////////////////////////////////
// FaultResponse
////////////////////////////////////////////////

void ControlResponse::setFaultResponse(int errCode, const std::string &errDescr) {
  setStatusCode(HTTP::INTERNAL_SERVER_ERROR);
  
  uXML::Node *bodyNode = getBodyNode();
  uXML::Node *faultNode = createFaultResponseNode(errCode, errDescr);
  bodyNode->addNode(faultNode);

  uXML::Node *envNode = getEnvelopeNode();
  setContent(envNode);
}

uXML::Node *ControlResponse::createFaultResponseNode(int errCode, const std::string &errDescr) {
  // <s:Fault>
  string faultNodeName;
  faultNodeName = SOAP::XMLNS;
  faultNodeName += SOAP::DELIM;
  faultNodeName += SOAP::FAULT;
  uXML::Node *faultNode = new uXML::Node(faultNodeName.c_str());

  // <faultcode>s:Client</faultcode>
  uXML::Node *faultCodeNode = new uXML::Node(SOAP::FAULT_CODE);
  string faultCodeNodeValue;
  faultCodeNodeValue = SOAP::XMLNS;
  faultCodeNodeValue += SOAP::DELIM;
  faultCodeNodeValue += FAULT_CODE;
  faultCodeNode->setValue(faultCodeNodeValue.c_str());
  faultNode->addNode(faultCodeNode);
    
  // <faultstring>UPnPError</faultstring>
  uXML::Node *faultStringNode = new uXML::Node(SOAP::FAULT_STRING);
  faultStringNode->setValue(FAULT_STRING);
  faultNode->addNode(faultStringNode);

  // <detail>
  uXML::Node *detailNode = new uXML::Node(SOAP::DETAIL);
  faultNode->addNode(detailNode);

  // <UPnPError xmlns="urn:schemas-upnp-org:control-1-0">
  uXML::Node *upnpErrorNode = new uXML::Node(FAULT_STRING);
  upnpErrorNode->setAttribute("xmlns", Control::XMLNS);
  detailNode->addNode(upnpErrorNode);

  // <errorCode>error code</errorCode>
  uXML::Node *errorCodeNode = new uXML::Node(SOAP::ERROR_CODE);
  errorCodeNode->setValue(errCode);
  upnpErrorNode->addNode(errorCodeNode);

  // <errorDescription>error string</errorDescription>
  uXML::Node *errorDesctiprionNode = new uXML::Node(SOAP::ERROR_DESCRIPTION);
  errorDesctiprionNode->setValue(errDescr);
  upnpErrorNode->addNode(errorDesctiprionNode);
    
  return faultNode;
}

