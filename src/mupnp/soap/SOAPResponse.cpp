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

////////////////////////////////////////////////
// Constructor
////////////////////////////////////////////////
  
uSOAP::SOAPResponse::SOAPResponse() {
  setRootNode(uSOAP::SOAP::CreateEnvelopeBodyNode());
  setContentType(uXML::XML::CONTENT_TYPE);
}

uSOAP::SOAPResponse::~SOAPResponse() {
}

////////////////////////////////////////////////
// setContent
////////////////////////////////////////////////
  
void uSOAP::SOAPResponse::setContent(uXML::Node *node) {
  std::string nodeBuf;
  node->toString(nodeBuf);
  std::string buf;
  buf.append(uSOAP::SOAP::VERSION_HEADER);
  buf.append("\n");
  buf.append(nodeBuf);
  HTTPResponse::setContent(buf.c_str());
}
