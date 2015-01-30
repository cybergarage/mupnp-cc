/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <string>
#include <sstream>
#include <string.h>
#include <mupnp/soap/SOAP.h>
#include <uhttp/util/StringUtil.h>

////////////////////////////////////////////////
// CreateEnvelopeBodyNode
////////////////////////////////////////////////

mupnp_shared_ptr<uXML::Node> uSOAP::SOAP::CreateEnvelopeBodyNode() {
  // <Envelope>
  std::string envNodeName;
  envNodeName += XMLNS;
  envNodeName += DELIM;
  envNodeName += ENVELOPE;
  uXML::Node *envNode = new uXML::Node(envNodeName.c_str());

  std::string xmlNs;
  xmlNs += "xmlns";
  xmlNs += DELIM;
  xmlNs += XMLNS;
  envNode->setAttribute(xmlNs.c_str(), XMLNS_URL);
  std::string encStyle;
  encStyle += XMLNS;
  encStyle += DELIM;
  encStyle += "encodingStyle";
  envNode->setAttribute(encStyle.c_str(), ENCSTYLE_URL);

  // <Body>
  std::string bodyNodeName;
  bodyNodeName += XMLNS;
  bodyNodeName += DELIM;
  bodyNodeName += BODY;
  uXML::Node *bodyNode = new uXML::Node(bodyNodeName.c_str());
  envNode->addNode(bodyNode);

  return mupnp_shared_ptr<uXML::Node>(envNode);
}

////////////////////////////////////////////////
// Header
////////////////////////////////////////////////

const char *uSOAP::SOAP::GetHeader(const std::string &content, std::string &header) {
  header = "";
  if (content.length() <= 0)
    return header.c_str();
  std::string::size_type gtIdx = content.find(">");
  if (gtIdx == std::string::npos)
    return header.c_str();
  header = content.substr(0, gtIdx+1);
  return header.c_str();
}

////////////////////////////////////////////////
// Encoding
////////////////////////////////////////////////

const char *uSOAP::SOAP::GetEncording(const std::string &content, std::string &encording) {
  encording = "";
  std::string header;
  SOAP::GetHeader(content, header);
  if (header.size() <= 0)
    return encording.c_str();
  std::string::size_type encIdx = header.find(uSOAP::SOAP::ENCORDING);
  if (encIdx == std::string::npos)
    return encording.c_str();
  std::string::size_type startIdx = header.find('\"', encIdx+strlen(uSOAP::SOAP::ENCORDING)+1);
  if (startIdx == std::string::npos)
    return encording.c_str();
  std::string::size_type endIdx = header.find('\"', startIdx+1);
  encording = header.substr(startIdx+1, (endIdx-startIdx-1));
  return encording.c_str();
}

bool uSOAP::SOAP::IsEncording(const std::string &content, const std::string &encType) {
  std::string enc;
  SOAP::GetEncording(content, enc);
  uHTTP::String encStr(enc);
  return encStr.equalsIgnoreCase(encType);
}
