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

#include <mupnp/http/HTTPResponse.h>
#include <mupnp/soap/SOAP.h>
#include <mupnp/xml/XML.h>

namespace uSOAP {
class SOAPResponse : public uHTTP::HTTPResponse {
  mupnp_shared_ptr<uXML::Node> rootNode;

  public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  SOAPResponse();
  ~SOAPResponse();

  ////////////////////////////////////////////////
  // Header
  ////////////////////////////////////////////////

  public:
  const char* getHeader(std::string& buf)
  {
    return SOAP::GetHeader(getContent(), buf);
  }

  ////////////////////////////////////////////////
  // Encoding
  ////////////////////////////////////////////////

  public:
  const char* getEncording(std::string& buf)
  {
    return SOAP::GetEncording(getContent(), buf);
  }

  bool isEncording(const std::string& encType)
  {
    return SOAP::IsEncording(getContent(), encType);
  }

  ////////////////////////////////////////////////
  // Node
  ////////////////////////////////////////////////

  private:
  void setRootNode(mupnp_shared_ptr<uXML::Node> node)
  {
    rootNode = node;
  }

  mupnp_shared_ptr<uXML::Node> getRootNode()
  {
    return rootNode;
  }

  ////////////////////////////////////////////////
  // SOAP Basic
  ////////////////////////////////////////////////

  public:
  void setEnvelopeNode(mupnp_shared_ptr<uXML::Node> node)
  {
    setRootNode(node);
  }

  mupnp_shared_ptr<uXML::Node> getEnvelopeNode()
  {
    return getRootNode();
  }

  mupnp_shared_ptr<uXML::Node> getBodyNode()
  {
    mupnp_shared_ptr<uXML::Node> envNode = getEnvelopeNode();
    if (!envNode)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
    return envNode->getNodeEndsWith(uSOAP::SOAP::BODY);
  }

  mupnp_shared_ptr<uXML::Node> getMethodResponseNode(const std::string& name)
  {
    mupnp_shared_ptr<uXML::Node> bodyNode = getBodyNode();
    if (!bodyNode)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
    std::string methodResName;
    methodResName = name;
    methodResName += SOAP::RESPONSE;
    return bodyNode->getNodeEndsWith(methodResName.c_str());
  }

  mupnp_shared_ptr<uXML::Node> getFaultNode()
  {
    mupnp_shared_ptr<uXML::Node> bodyNode = getBodyNode();
    if (!bodyNode)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
    return bodyNode->getNodeEndsWith(uSOAP::SOAP::FAULT);
  }

  mupnp_shared_ptr<uXML::Node> getFaultCodeNode()
  {
    mupnp_shared_ptr<uXML::Node> faultNode = getFaultNode();
    if (!faultNode)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
    return faultNode->getNodeEndsWith(uSOAP::SOAP::FAULT_CODE);
  }

  mupnp_shared_ptr<uXML::Node> getFaultStringNode()
  {
    mupnp_shared_ptr<uXML::Node> faultNode = getFaultNode();
    if (!faultNode)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
    return faultNode->getNodeEndsWith(uSOAP::SOAP::FAULT_STRING);
  }

  mupnp_shared_ptr<uXML::Node> getFaultActorNode()
  {
    mupnp_shared_ptr<uXML::Node> faultNode = getFaultNode();
    if (!faultNode)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
    return faultNode->getNodeEndsWith(uSOAP::SOAP::FAULTACTOR);
  }

  mupnp_shared_ptr<uXML::Node> getFaultDetailNode()
  {
    mupnp_shared_ptr<uXML::Node> faultNode = getFaultNode();
    if (!faultNode)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node*)nullptr);
    return faultNode->getNodeEndsWith(uSOAP::SOAP::DETAIL);
  }

  const char* getFaultCode()
  {
    mupnp_shared_ptr<uXML::Node> node = getFaultCodeNode();
    if (!node)
      return "";
    return node->getValue();
  }

  const char* getFaultString()
  {
    mupnp_shared_ptr<uXML::Node> node = getFaultStringNode();
    if (!node)
      return "";
    return node->getValue();
  }

  const char* getFaultActor()
  {
    mupnp_shared_ptr<uXML::Node> node = getFaultActorNode();
    if (!node)
      return "";
    return node->getValue();
  }

  ////////////////////////////////////////////////
  // setContent
  ////////////////////////////////////////////////

  public:
  void setContent(uXML::Node* node);
};

}

#endif
