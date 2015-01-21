/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/soap/SOAPResponse.h>

using namespace mUPnP;
using namespace std;

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
  
SOAPResponse::SOAPResponse() {
  rootNode = NULL;
  setRootNode(SOAP::CreateEnvelopeBodyNode());
  setContentType(uXML::XML::CONTENT_TYPE);
}

/*
SOAPResponse(uHTTP::HTTPResponse *httpRes)  : HTTPResponse(httpRes) {
  rootNode = NULL;
  setRootNode(SOAP::CreateEnvelopeBodyNode());
  setContentType(XML::CONTENT_TYPE);
}

SOAPResponse(SOAPResponse *soapRes) : HTTPResponse(soapRes) {
  rootNode = NULL;
  setEnvelopeNode(soapRes->getEnvelopeNode());
  setContentType(XML::CONTENT_TYPE);
}
*/

SOAPResponse::~SOAPResponse() {
  if (rootNode != NULL)
    delete rootNode;
}

////////////////////////////////////////////////
// setContent
////////////////////////////////////////////////
  
void SOAPResponse::setContent(uXML::Node *node) {
  string nodeBuf;
  node->toString(nodeBuf);
  std::string buf;
  buf.append(SOAP::VERSION_HEADER);
  buf.append("\n");
  buf.append(nodeBuf);
  HTTPResponse::setContent(buf.c_str());
}
