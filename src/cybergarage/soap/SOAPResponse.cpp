/******************************************************************
*
*  CyberSOAP for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SOAPResponse.cpp
*
*  Revision;
*
*  05/21/03
*    - first revision
*  02/13/04
*    - Ralf G. R. Bergs <Ralf@Ber.gs>, Inma Marin Lopez <inma@dif.um.es>.
*    - Added XML header, <?xml version=\"1.0\"?> to setContent().
*  05/31/04
*    - Added XML header of setContent() to <?xml version=\"1.0\"? encording="utf-8">.
*  06/01/04
*    - Added getHeader().
*    - Added getEncording() and isEncording().
*
******************************************************************/

#include <cybergarage/soap/SOAPResponse.h>

using namespace CyberSOAP;
using namespace std;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////
  
SOAPResponse::SOAPResponse() {
  rootNode = NULL;
  setRootNode(SOAP::CreateEnvelopeBodyNode());
  setContentType(CyberXML::XML::CONTENT_TYPE);
}

/*
SOAPResponse(uHTTP::HTTPResponse *httpRes)  : HTTPResponse(httpRes) {
  rootNode = NULL;
  setRootNode(SOAP::CreateEnvelopeBodyNode());
  setContentType(CyberXML::XML::CONTENT_TYPE);
}

SOAPResponse(SOAPResponse *soapRes) : HTTPResponse(soapRes) {
  rootNode = NULL;
  setEnvelopeNode(soapRes->getEnvelopeNode());
  setContentType(CyberXML::XML::CONTENT_TYPE);
}
*/

SOAPResponse::~SOAPResponse() {
  if (rootNode != NULL)
    delete rootNode;
}

////////////////////////////////////////////////
//  setContent
////////////////////////////////////////////////
  
void SOAPResponse::setContent(CyberXML::Node *node) {
  string nodeBuf;
  node->toString(nodeBuf);
  std::string buf;
  buf.append(SOAP::VERSION_HEADER);
  buf.append("\n");
  buf.append(nodeBuf);
  HTTPResponse::setContent(buf.c_str());
}
