/******************************************************************
*
*  CyberSOAP for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: SOAPResponse.h
*
*  Revision;
*
*  05/21/03
*    - first revision
*
******************************************************************/

#ifndef _CSOAP_SOAPRESPONSE_H_
#define _CSOAP_SOAPRESPONSE_H_

#include <uhttp/http/HTTPResponse.h>
#include <cybergarage/xml/XML.h>
#include <cybergarage/soap/SOAP.h>

namespace CyberSOAP {
class SOAPResponse : public uHTTP::HTTPResponse {
  CyberXML::Node *rootNode;
  
 public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  SOAPResponse();

  /*
  SOAPResponse(uHTTP::HTTPResponse *httpRes)  : HTTPResponse(httpRes)
  SOAPResponse(SOAPResponse *soapRes) : HTTPResponse(soapRes)
  */

  ~SOAPResponse();

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
  //  Node
  ////////////////////////////////////////////////

private:

  void setRootNode(CyberXML::Node *node) {
    if (rootNode != NULL)
      delete rootNode;
    rootNode = node;
  }
  
  CyberXML::Node *getRootNode() {
    return rootNode;
  }
  
  ////////////////////////////////////////////////
  //  SOAP Basic
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
    return envNode->getNodeEndsWith(SOAP::BODY);
  }

  CyberXML::Node *getMethodResponseNode(const std::string & name) {
    CyberXML::Node *bodyNode = getBodyNode();
    if (bodyNode == NULL)
      return NULL;
    std::string methodResName;
    methodResName = name;
    methodResName += SOAP::RESPONSE;
    return bodyNode->getNodeEndsWith(methodResName.c_str());
  }

  CyberXML::Node *getFaultNode() {
    CyberXML::Node *bodyNode = getBodyNode();
    if (bodyNode == NULL)
      return NULL;
    return bodyNode->getNodeEndsWith(SOAP::FAULT);
  }

  CyberXML::Node *getFaultCodeNode() {
    CyberXML::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::FAULT_CODE);
  }

  CyberXML::Node *getFaultStringNode() {
    CyberXML::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::FAULT_STRING);
  }

  CyberXML::Node *getFaultActorNode() {
    CyberXML::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::FAULTACTOR);
  }

  CyberXML::Node *getFaultDetailNode() {
    CyberXML::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::DETAIL);
  }

  const char *getFaultCode() {
    CyberXML::Node *node = getFaultCodeNode();
    if (node == NULL)
      return "";
    return node->getValue();
  }
  
  const char *getFaultString() {
    CyberXML::Node *node = getFaultStringNode();
    if (node == NULL)
      return "";
    return node->getValue();
  }
  
  const char *getFaultActor() {
    CyberXML::Node *node = getFaultActorNode();
    if (node == NULL)
      return "";
    return node->getValue();
  }

  ////////////////////////////////////////////////
  //  setContent
  ////////////////////////////////////////////////
  
 public:
  void setContent(CyberXML::Node *node);

  ////////////////////////////////////////////////
  //  print
  ////////////////////////////////////////////////
/*  
  public void print() {
    System.out.println(toconst char *());
    if (hasContent() == true)
      return;
    Node rootElem = getRootNode();
    if (rootElem == NULL)
      return;
    System.out.println(rootElem.toconst char *());
  }
*/
};

}

#endif
