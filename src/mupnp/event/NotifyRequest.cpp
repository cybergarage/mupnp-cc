/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/event/NotifyRequest.h>

#include <time.h>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace mUPnP;
using namespace mUPnP;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char *NotifyRequest::XMLNS = "e";
const char *NotifyRequest::PROPERTY = "property";
const char *NotifyRequest::PROPERTYSET = "propertyset";

////////////////////////////////////////////////
// PropetySet
////////////////////////////////////////////////

bool NotifyRequest::setRequest(Subscriber *sub, const std::string &varName, const std::string &value) {
  //const char *callback = sub->getDeliveryURL();
  const char *sid = sub->getSID();
  long notifyCnt = sub->getNotifyCount();
  const char *host = sub->getDeliveryHost();
  const char *path = sub->getDeliveryPath();
  int port = sub->getDeliveryPort();

  setMethod(uHTTP::HTTP::NOTIFY);
  setURI(path);
  setHost(host, port);
  setNT(NT::EVENT);
  setNTS(NTS::PROPCHANGE);
  setSID(sid);
  setSEQ(notifyCnt);

  setContentType(XML::CONTENT_TYPE);
  mUPnP::Node *propSetNode = createPropertySetNode(varName, value);

  setContent(propSetNode);
  return true;
}


mUPnP::Node *NotifyRequest::createPropertySetNode(const std::string &varName, const std::string &value) {
  string propSetXmlNs;
  //propSetXmlNs.append(XMLNS)
  //propSetXmlNs.append(SOAP::DELIM)
  propSetXmlNs.append(PROPERTYSET);
  Node *propSetNode = new mUPnP::Node(propSetXmlNs.c_str());
  propSetNode->setNameSpace(XMLNS, Subscription::XMLNS);

  string propXmlNs;
  //propXmlNs.append(XMLNS)
  //propXmlNs.append(SOAP::DELIM)
  propXmlNs.append(PROPERTY);
  Node *propNode = new mUPnP::Node(propXmlNs.c_str());
  propSetNode->addNode(propNode);

  Node *varNameNode = new mUPnP::Node(varName);
  varNameNode->setValue(value);
  propNode->addNode(varNameNode);

  return propSetNode;
}

mUPnP::Node *NotifyRequest::getVariableNode() {
  Node *rootNode = getEnvelopeNode();
  if (rootNode == NULL)
    return NULL;
  if (rootNode->hasNodes() == false)
    return NULL;
  Node *propNode = rootNode->getNode(0);
  if (propNode->hasNodes() == false)
    return NULL;
  return propNode->getNode(0);
}

////////////////////////////////////////////////
// PropetySet
////////////////////////////////////////////////

// Thanks for Giordano Sassaroli <sassarol@cefriel.it> (09/08/03)
Property *NotifyRequest::getProperty(Node *varNode) {
  Property *prop = new Property();
  if (varNode == NULL) {
    prop->setName("");
    prop->setValue("");
    return prop;
  }
  // remove the event namespace
  std::string variableName = varNode->getName();
  size_t index = variableName.rfind(':');
  if (index != (int)std::string::npos)
    variableName = variableName.substr(index + 1);
  prop->setName(variableName.c_str());
  prop->setValue(varNode->getValue());
  return prop;
}

// Thanks for Giordano Sassaroli <sassarol@cefriel.it> (09/08/03)
PropertyList *NotifyRequest::getPropertyList()  {
  propList.clear();
  Node *propSetNode = getEnvelopeNode();
  for (int i = 0; i<propSetNode->getNNodes(); i++){
    Node *propNode = propSetNode->getNode(i);
    if (propNode == NULL)
      continue;
    Property *prop = getProperty(propNode->getNode(0));
    propList.add(prop);
  }
  return &propList;
}
  
