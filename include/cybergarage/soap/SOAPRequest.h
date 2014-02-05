/******************************************************************
*
*  CyberSOAP for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SOAPRequest.h
*
*  Revision;
*
*  05/21/03
*    - first revision
*
******************************************************************/

#ifndef _CSOAP_SOAPREQUEST_H_
#define _CSOAP_SOAPREQUEST_H_

#include <uhttp/http/HTTPRequest.h>
#include <uhttp/http/HTTPResponse.h>
#include <uhttp/http/HTTP.h>
#include <cybergarage/soap/SOAP.h>
#include <cybergarage/soap/SOAPResponse.h>
#include <cybergarage/xml/Node.h>

namespace CyberSOAP {
const char SOAPACTION[] = "SOAPACTION";

class SOAPRequest : public uHTTP::HTTPRequest {
  CyberXML::Node *rootNode;
  SOAPResponse soapRes;
    
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
 public:
  SOAPRequest();
  SOAPRequest(uHTTP::HTTPRequest *httpReq);

  ~SOAPRequest();

  ////////////////////////////////////////////////
  // SOAPACTION
  ////////////////////////////////////////////////

 public:
  void setSOAPAction(const std::string &action) {
    setStringHeader(SOAPACTION, action);
  }
  
  const char *getSOAPAction(std::string &buf) {
    return getStringHeaderValue(SOAPACTION, buf);
  }

  bool isSOAPAction(const std::string &value);
 
  ////////////////////////////////////////////////
  //  Header
  ////////////////////////////////////////////////

 public:
  const char *getHeader(std::string &buf) {
    return SOAP::GetHeader(getContent(), buf);
  }

  ////////////////////////////////////////////////
  //  Encoding
  ////////////////////////////////////////////////

 public:
  const char *getEncording(std::string &buf) {
    return SOAP::GetEncording(getContent(), buf);
  }

  bool isEncording(const std::string &encType) {
    return SOAP::IsEncording(getContent(), encType);
  }

  ////////////////////////////////////////////////
  //  post
  ////////////////////////////////////////////////

private:

  CyberXML::Node *parseMessage(const std::string &content, size_t contentLen);

 public:
  SOAPResponse *postMessage(const std::string &host, int port, SOAPResponse *soapRes);

  SOAPResponse *postMessage(const std::string &host, int port) {
    return postMessage(host, port, &soapRes);
  }

  ////////////////////////////////////////////////
  //  Node
  ////////////////////////////////////////////////

private:

  void setRootNode(CyberXML::Node *node) {
    rootNode = node;
  }

  CyberXML::Node *getRootNode();
  
  ////////////////////////////////////////////////
  //  XML
  ////////////////////////////////////////////////

 public:
  void setEnvelopeNode(CyberXML::Node *node) {
    setRootNode(node);
  }
  
  CyberXML::Node *getEnvelopeNode() {
    return getRootNode();
  }
    
  CyberXML::Node *getBodyNode() {
    CyberXML::Node *envNode = getEnvelopeNode();
    if (envNode == NULL)
      return NULL;
    if (envNode->hasNodes() == false)
      return NULL;
    return envNode->getNode(0);
  }

  ////////////////////////////////////////////////
  //  SOAP UPnP
  ////////////////////////////////////////////////
  
 public:
  void setContent(CyberXML::Node *node);

  ////////////////////////////////////////////////
  //  print
  ////////////////////////////////////////////////
/*  
  public void print() {
    System.out.println(toString());
    if (hasContent() == true)
      return;
    Node rootElem = getRootNode();
    if (rootElem == null)
      return;
    System.out.println(rootElem.toString());
  }
*/
};

}

#endif
