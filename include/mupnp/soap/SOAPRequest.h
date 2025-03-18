/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPNP_SOAPREQUEST_H_
#define _MUPNP_SOAPREQUEST_H_

#include <mupnp/http/HTTPRequest.h>
#include <mupnp/http/HTTPResponse.h>
#include <mupnp/http/HTTP.h>
#include <mupnp/soap/SOAP.h>
#include <mupnp/soap/SOAPResponse.h>
#include <mupnp/xml/Node.h>

namespace uSOAP {
const char SOAPACTION[] = "SOAPACTION";

class SOAPRequest : public uHTTP::HTTPRequest {
  mupnp_shared_ptr<uXML::Node> rootNode;
  SOAPResponse soapRes;
    
  ////////////////////////////////////////////////
  // Constructor
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
  // post
  ////////////////////////////////////////////////

private:

  mupnp_shared_ptr<uXML::Node> parseMessage(const std::string &content, size_t contentLen);

 public:
  SOAPResponse *postMessage(const std::string &host, int port, SOAPResponse *soapRes);

  SOAPResponse *postMessage(const std::string &host, int port) {
    return postMessage(host, port, &soapRes);
  }

  ////////////////////////////////////////////////
  // Node
  ////////////////////////////////////////////////

private:

  void setRootNode(mupnp_shared_ptr<uXML::Node> node) {
    rootNode = node;
  }

  mupnp_shared_ptr<uXML::Node> getRootNode();
  
  ////////////////////////////////////////////////
  // XML
  ////////////////////////////////////////////////

 public:
  void setEnvelopeNode(mupnp_shared_ptr<uXML::Node> node) {
    setRootNode(node);
  }
  
  mupnp_shared_ptr<uXML::Node> getEnvelopeNode() {
    return getRootNode();
  }
    
  mupnp_shared_ptr<uXML::Node> getBodyNode() {
    mupnp_shared_ptr<uXML::Node> envNode = getEnvelopeNode();
    if (!envNode)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    if (envNode->hasNodes() == false)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return envNode->getNode(0);
  }

  ////////////////////////////////////////////////
  // SOAP UPnP
  ////////////////////////////////////////////////
  
 public:
  void setContent(uXML::Node *node);
};

}

#endif
