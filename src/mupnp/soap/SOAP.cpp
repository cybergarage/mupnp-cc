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

using namespace std;
using namespace mUPnP;
using namespace mUPnP;
using namespace uHTTP;

////////////////////////////////////////////////
// CreateEnvelopeBodyNode
////////////////////////////////////////////////

mUPnP::Node *mUPnP::SOAP::CreateEnvelopeBodyNode() {
  // <Envelope>
  string envNodeName;
  envNodeName += XMLNS;
  envNodeName += DELIM;
  envNodeName += ENVELOPE;
  Node *envNode = new mUPnP::Node(envNodeName.c_str());

  string xmlNs;
  xmlNs += "xmlns";
  xmlNs += DELIM;
  xmlNs += XMLNS;
  envNode->setAttribute(xmlNs.c_str(), XMLNS_URL);
  string encStyle;
  encStyle += XMLNS;
  encStyle += DELIM;
  encStyle += "encodingStyle";
  envNode->setAttribute(encStyle.c_str(), ENCSTYLE_URL);

  // <Body>
  string bodyNodeName;
  bodyNodeName += XMLNS;
  bodyNodeName += DELIM;
  bodyNodeName += BODY;
  Node *bodyNode = new mUPnP::Node(bodyNodeName.c_str());
  envNode->addNode(bodyNode);

  return envNode;
}

////////////////////////////////////////////////
// Header
////////////////////////////////////////////////

const char *mUPnP::SOAP::GetHeader(const std::string &content, std::string &header) {
  header = "";
  if (content.length() <= 0)
    return header.c_str();
  string::size_type gtIdx = content.find(">");
  if (gtIdx == string::npos)
    return header.c_str();
  header = content.substr(0, gtIdx+1);
  return header.c_str();
}

////////////////////////////////////////////////
// Encoding
////////////////////////////////////////////////

const char *mUPnP::SOAP::GetEncording(const std::string &content, std::string &encording) {
  encording = "";
  string header;
  SOAP::GetHeader(content, header);
  if (header.size() <= 0)
    return encording.c_str();
  string::size_type encIdx = header.find(SOAP::ENCORDING);
  if (encIdx == string::npos)
    return encording.c_str();
  string::size_type startIdx = header.find('\"', encIdx+strlen(SOAP::ENCORDING)+1);
  if (startIdx == string::npos)
    return encording.c_str();
  string::size_type endIdx = header.find('\"', startIdx+1);
  encording = header.substr(startIdx+1, (endIdx-startIdx-1));
  return encording.c_str();
}

bool mUPnP::SOAP::IsEncording(const std::string &content, const std::string &encType) {
  string enc;
  SOAP::GetEncording(content, enc);
  String encStr(enc);
  return encStr.equalsIgnoreCase(encType);
}
