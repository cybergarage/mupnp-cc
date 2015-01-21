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
  uXML::Node *rootNode;
  
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

  void setRootNode(uXML::Node *node) {
    if (rootNode != NULL)
      delete rootNode;
    rootNode = node;
  }
  
  uXML::Node *getRootNode() {
    return rootNode;
  }
  
  ////////////////////////////////////////////////
  // SOAP Basic
  ////////////////////////////////////////////////

 public:
  void setEnvelopeNode(uXML::Node *node) {
    setRootNode(node);
  }

  uXML::Node *getEnvelopeNode() {
    return getRootNode();
  }
  
  uXML::Node *getBodyNode() {
    uXML::Node *envNode = getEnvelopeNode();
    if (envNode == NULL)
      return NULL;
    return envNode->getNodeEndsWith(SOAP::BODY);
  }

  uXML::Node *getMethodResponseNode(const std::string & name) {
    uXML::Node *bodyNode = getBodyNode();
    if (bodyNode == NULL)
      return NULL;
    std::string methodResName;
    methodResName = name;
    methodResName += SOAP::RESPONSE;
    return bodyNode->getNodeEndsWith(methodResName.c_str());
  }

  uXML::Node *getFaultNode() {
    uXML::Node *bodyNode = getBodyNode();
    if (bodyNode == NULL)
      return NULL;
    return bodyNode->getNodeEndsWith(SOAP::FAULT);
  }

  uXML::Node *getFaultCodeNode() {
    uXML::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::FAULT_CODE);
  }

  uXML::Node *getFaultStringNode() {
    uXML::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::FAULT_STRING);
  }

  uXML::Node *getFaultActorNode() {
    uXML::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::FAULTACTOR);
  }

  uXML::Node *getFaultDetailNode() {
    uXML::Node *faultNode = getFaultNode();
    if (faultNode == NULL)
      return NULL;
    return faultNode->getNodeEndsWith(SOAP::DETAIL);
  }

  const char *getFaultCode() {
    uXML::Node *node = getFaultCodeNode();
    if (node == NULL)
      return "";
    return node->getValue();
  }
  
  const char *getFaultString() {
    uXML::Node *node = getFaultStringNode();
    if (node == NULL)
      return "";
    return node->getValue();
  }
  
  const char *getFaultActor() {
    uXML::Node *node = getFaultActorNode();
    if (node == NULL)
      return "";
    return node->getValue();
  }

  ////////////////////////////////////////////////
  // setContent
  ////////////////////////////////////////////////
  
 public:
  void setContent(uXML::Node *node);

};

}

#endif
