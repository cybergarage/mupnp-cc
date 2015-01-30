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
  
  mupnp_shared_ptr<uXML::Node> bodyNode = getBodyNode();
  uXML::Node *faultNode = createFaultResponseNode(errCode, errDescr);
  bodyNode->addNode(faultNode);

  mupnp_shared_ptr<uXML::Node> envNode = getEnvelopeNode();
  setContent(envNode.get());
}

uXML::Node *ControlResponse::createFaultResponseNode(int errCode, const std::string &errDescr) {
  // <s:Fault>
  string faultNodeName;
  faultNodeName = uSOAP::SOAP::XMLNS;
  faultNodeName += uSOAP::SOAP::DELIM;
  faultNodeName += uSOAP::SOAP::FAULT;
  uXML::Node *faultNode = new uXML::Node(faultNodeName.c_str());

  // <faultcode>s:Client</faultcode>
  uXML::Node *faultCodeNode = new uXML::Node(uSOAP::SOAP::FAULT_CODE);
  string faultCodeNodeValue;
  faultCodeNodeValue = uSOAP::SOAP::XMLNS;
  faultCodeNodeValue += uSOAP::SOAP::DELIM;
  faultCodeNodeValue += FAULT_CODE;
  faultCodeNode->setValue(faultCodeNodeValue.c_str());
  faultNode->addNode(faultCodeNode);
    
  // <faultstring>UPnPError</faultstring>
  uXML::Node *faultStringNode = new uXML::Node(uSOAP::SOAP::FAULT_STRING);
  faultStringNode->setValue(FAULT_STRING);
  faultNode->addNode(faultStringNode);

  // <detail>
  uXML::Node *detailNode = new uXML::Node(uSOAP::SOAP::DETAIL);
  faultNode->addNode(detailNode);

  // <UPnPError xmlns="urn:schemas-upnp-org:control-1-0">
  uXML::Node *upnpErrorNode = new uXML::Node(FAULT_STRING);
  upnpErrorNode->setAttribute("xmlns", Control::XMLNS);
  detailNode->addNode(upnpErrorNode);

  // <errorCode>error code</errorCode>
  uXML::Node *errorCodeNode = new uXML::Node(uSOAP::SOAP::ERROR_CODE);
  errorCodeNode->setValue(errCode);
  upnpErrorNode->addNode(errorCodeNode);

  // <errorDescription>error string</errorDescription>
  uXML::Node *errorDesctiprionNode = new uXML::Node(uSOAP::SOAP::ERROR_DESCRIPTION);
  errorDesctiprionNode->setValue(errDescr);
  upnpErrorNode->addNode(errorDesctiprionNode);
    
  return faultNode;
}

