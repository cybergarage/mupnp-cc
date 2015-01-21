/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPNP_SOAPRESPONSE_H_
#define _MUPNP_SOAPRESPONSE_H_

#include <uhttp/http/HTTPResponse.h>
#include <mupnp/xml/XML.h>
#include <mupnp/soap/SOAP.h>

namespace mUPnP {
class SOAPResponse : public uHTTP::HTTPResponse {
  mUPnP::Node *rootNode;
  
 public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  SOAPResponse();

  /*
  SOAPResponse(uHTTP::HTTPResponse *httpRes)  : HTTPResponse(httpRes)
  SOAPResponse(SOAPResponse *soapRes) : HTTPResponse(soapRes)
  */

  ~SOAPResponse();

  ////////////////////////////////////////////////
  // Header
  ////////////////////////////////////////////////

 public:
  const char *getHeader(std::string &buf) {
    return SOAP::GetHeader(getContent(), buf);
  }

  ////////////////////////////////////////////////
  // Encoding
  ////////////////////////////////////////////////

 public:
  const char *getEncording(std::string &buf) {
    return SOAP::GetEncording(getContent(), buf);
  }

  bool isEncording(const std::string &encType) {
    return SOAP::IsEncording(getContent(), encType);
  }

  ////////////////////////////////////////////////
  // Node
  ////////////////////////////////////////////////

private:

  void setRootNode(Node *node) {
    if (rootNode != NULL)
      delete rootNode;
    rootNode = node;
  }
  
  mUPnP::Node *getRootNode() {
    return rootNode;
  }
  
  ////////////////////////////////////////////////
  // SOAP Basic
  ////////////////////////////////////////////////

 public:
  void setEnvelopeNode(Node *node) {
    setRootNode(node);
  }

  mUPnP::Node *getEnvelopeNode() {
    return getRootNode();
  }
  
  mUPnP::Node *getBodyNode() {
    mUPnP::Node *envNode = getEnvelopeNode();
    if (envNode == NULL)
      return NULL;
    return envNode->getNodeEndsWith(SOAP::BODY);
  }

  mUPnP::Node *getMethodResponseNode(const std::string & name) {
    mUPnP::Node *bodyNode = getBodyNode();
    if (bodyNode == NULL)
      return NULL;
    std::string methodResName;
    methodResName = name;
    methodResName += SOAP::RESPONSE;
    return bodyNode->getNodeEndsWith(methodResName.c_str());
  }

  mUPnP::Node *getFaultNode() {
    mUPnP::Node *bodyNode = getBodyNode();
    if (bodyNode == NULL)
      return NULL;
    return bodyNode->getNodeEndsWith(SOAP::FAULT);
  }

  mUPnP::Node *getFaultCodeNode() {
    mUPnP::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::FAULT_CODE);
  }

  mUPnP::Node *getFaultStringNode() {
    mUPnP::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::FAULT_STRING);
  }

  mUPnP::Node *getFaultActorNode() {
    mUPnP::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::FAULTACTOR);
  }

  mUPnP::Node *getFaultDetailNode() {
    mUPnP::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::DETAIL);
  }

  const char *getFaultCode() {
    mUPnP::Node *node = getFaultCodeNode();
    if (node == NULL)
      return "";
    return node->getValue();
  }
  
  const char *getFaultString() {
    mUPnP::Node *node = getFaultStringNode();
    if (node == NULL)
      return "";
    return node->getValue();
  }
  
  const char *getFaultActor() {
    mUPnP::Node *node = getFaultActorNode();
    if (node == NULL)
      return "";
    return node->getValue();
  }

  ////////////////////////////////////////////////
  // setContent
  ////////////////////////////////////////////////
  
 public:
  void setContent(Node *node);

  ////////////////////////////////////////////////
  // print
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
