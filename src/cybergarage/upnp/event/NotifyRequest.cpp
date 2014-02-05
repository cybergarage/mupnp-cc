/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: NotifyRequest.cpp
*
*  Revision;
*
*  08/10/03
*    - first revision
*  09/08/03
*    - Giordano Sassaroli <sassarol@cefriel.it>
*    - Problem : when an event notification message is received and the message
*          contains updates on more than one variable, only the first variable update
*          is notified.
*    - Error :  the other xml nodes of the message are ignored
*    - Fix : add two methods to the NotifyRequest for extracting the property array
*        and modify the httpRequestRecieved method in ControlPoint
*  05/19/04
*    - Changed the header include order for Cygwin.
*  08/21/05
*    - Changed createPropertySetNode() using string instead of ostringstream.
*
******************************************************************/

#include <cybergarage/upnp/event/NotifyRequest.h>

#include <time.h>
#include <stdlib.h>
#include <string>

using namespace std;
using namespace CyberLink;
using namespace CyberXML;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const char *NotifyRequest::XMLNS = "e";
const char *NotifyRequest::PROPERTY = "property";
const char *NotifyRequest::PROPERTYSET = "propertyset";

////////////////////////////////////////////////
//  PropetySet
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

  setContentType(CyberXML::XML::CONTENT_TYPE);
  CyberXML::Node *propSetNode = createPropertySetNode(varName, value);

  setContent(propSetNode);
  return true;
}


CyberXML::Node *NotifyRequest::createPropertySetNode(const std::string &varName, const std::string &value) {
  string propSetXmlNs;
  //propSetXmlNs.append(XMLNS)
  //propSetXmlNs.append(CyberSOAP::SOAP::DELIM)
  propSetXmlNs.append(PROPERTYSET);
  Node *propSetNode = new CyberXML::Node(propSetXmlNs.c_str());
  propSetNode->setNameSpace(XMLNS, Subscription::XMLNS);

  string propXmlNs;
  //propXmlNs.append(XMLNS)
  //propXmlNs.append(CyberSOAP::SOAP::DELIM)
  propXmlNs.append(PROPERTY);
  Node *propNode = new CyberXML::Node(propXmlNs.c_str());
  propSetNode->addNode(propNode);

  Node *varNameNode = new CyberXML::Node(varName);
  varNameNode->setValue(value);
  propNode->addNode(varNameNode);

  return propSetNode;
}

CyberXML::Node *NotifyRequest::getVariableNode() {
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
//  PropetySet
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
  
