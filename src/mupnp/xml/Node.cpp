/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <mupnp/xml/XML.h>
#include <mupnp/xml/Node.h>

using namespace std;
using namespace uXML;

////////////////////////////////////////////////
// Node
////////////////////////////////////////////////

Node::Node() {
  userData = NULL;
  setParentNode(NULL);
}

Node::Node(const std::string &name)  {
  userData = NULL;
  setParentNode(NULL);
  setName(name);
}

Node::Node(const std::string &ns, const std::string &name)  {
  userData = NULL;
  setParentNode(NULL);
  setName(ns, name);
}

Node::~Node() {
  removeAllNodes();
  if (userData)
    delete userData;
}

////////////////////////////////////////////////
// userData
////////////////////////////////////////////////

void Node::setUserData(NodeData *data) {
  if (userData)
    delete userData;
  userData = data;
  if (userData)
    userData->setNode(this);
}

////////////////////////////////////////////////
// value
////////////////////////////////////////////////

void Node::setValue(int val) {
#ifndef NO_USE_OSTRINGSTREAM
  std::ostringstream valStr;
  valStr << val;
  setValue(valStr.str().c_str());
#else
  //UINT_MAX : 4294967295U
  char strBuf[16];
#ifdef HAVE_SNPRINTF
  snprintf(strBuf, sizeof(strBuf), "%d", val);
#else
  sprintf(strBuf, "%d", val);
#endif
  setValue(strBuf);
#endif
}

////////////////////////////////////////////////
// Attribute (Extention)
////////////////////////////////////////////////

void Node::setAttribute(const std::string & name, const std::string &value) {
  Attribute *attr = getAttribute(name);
  if (!attr) {
    attr = new Attribute(name, value);
    addAttribute(attr);
  }
  attr->setValue(value);
}

void Node::setAttribute(const std::string &name, int value) {
#ifndef NO_USE_OSTRINGSTREAM
  std::ostringstream os;
  os << value;
  std::string valStr = os.str();
  setAttribute(name, valStr.c_str());
#else
  //UINT_MAX : 4294967295U
  char valStr[16];
#ifdef HAVE_SNPRINTF
  snprintf(strBuf, sizeof(strBuf), "%d", value);
#else
  sprintf(valStr, "%d", value);
#endif
  setAttribute(name, valStr);
#endif
}

const char *Node::getAttributeValue(const std::string & name) {
  Attribute *attr = getAttribute(name);
  if (attr)
    return attr->getValue();
  return "";
}

int Node::getAttributeIntegerValue(const std::string &name) {
  std::string val = getAttributeValue(name);
  return atoi(val.c_str());
}

////////////////////////////////////////////////
// outputAttribures
////////////////////////////////////////////////

#ifndef NO_USE_OSTRINGSTREAM
void Node::outputAttributes(std::ostream& ps) {
#else
void Node::outputAttributes(std::string& ps) {
#endif
  std::string valBuf;
  int nAttributes = getNAttributes();
  for (int n = 0; n < nAttributes; n++) {
#ifndef NO_USE_OSTRINGSTREAM
    Attribute *attr = getAttribute(n);
    ps << " " << attr->getName() << "=\"" << XML::EscapeXMLChars(attr->getValue(), valBuf) << "\"";
#else
    Attribute *attr = getAttribute(n);
    ps += " ";
    ps += attr->getName();
    ps += "=\"";
    ps += XML::EscapeXMLChars(attr->getValue(), valBuf);
    ps += "\"";
#endif
  }
}


////////////////////////////////////////////////
// output
////////////////////////////////////////////////

#ifndef NO_USE_OSTRINGSTREAM
void Node::output(std::ostream& ps, int indentLevel, bool hasChildNode) {
#else
void Node::output(std::string& ps, int indentLevel, bool hasChildNode) {
#endif
  std::string identStringBuf;
  const char *indentString = getIndentLevelString(indentLevel, identStringBuf);

  const char *name = getName();
  const char *value = getValue();

  if (hasNodes() == false || hasChildNode == false) {
#ifndef NO_USE_OSTRINGSTREAM
    ps << indentString << "<" << name;
#else
    ps += indentString;
    ps += "<";
    ps += name;
#endif
    outputAttributes(ps);
    // Thnaks for Tho Beisch (11/09/04)
    if (!value || strlen(value) == 0) {
      // No value, so use short notation <node />
#ifndef NO_USE_OSTRINGSTREAM
      ps << " />";
#else
      ps += " />";
#endif
    }
    else {
      std::string valBuf;
#ifndef NO_USE_OSTRINGSTREAM
      ps << ">" << XML::EscapeXMLChars(value, valBuf) << "</" << name << ">" << std::endl;
#else
      ps += ">";
      ps += XML::EscapeXMLChars(value, valBuf);
      ps += "</";
      ps += name;
      ps += ">";
      ps += "\n";
#endif
    }
    return;
  }

#ifndef NO_USE_OSTRINGSTREAM
  ps << indentString << "<" << name;
#else
  ps += indentString;
  ps += "<";
  ps += name;
#endif
  outputAttributes(ps);

#ifndef NO_USE_OSTRINGSTREAM
  ps << ">" << std::endl;
#else
  ps += ">";
  ps += "\n";
#endif

  size_t nChildNodes = getNNodes();
  for (size_t n = 0; n < nChildNodes; n++) {
    mupnp_shared_ptr<uXML::Node> cnode = getNode(n);
    cnode->output(ps, indentLevel+1, true);
  }

#ifndef NO_USE_OSTRINGSTREAM
  ps << indentString << "</" << name << ">" << std::endl;
#else
  ps += indentString;
  ps += "</";
  ps += name;
  ps += ">";
  ps += "\n";
#endif
}

////////////////////////////////////////////////
// toString
////////////////////////////////////////////////

const char *Node::toString(std::string &buf, bool hasChildNode) {
#ifndef NO_USE_OSTRINGSTREAM
  ostringstream strBuf;
  output(strBuf, 0, hasChildNode);
  buf = strBuf.str();
#else
  output(buf, 0, hasChildNode);
#endif
  return buf.c_str();
}

////////////////////////////////////////////////
// print
////////////////////////////////////////////////

void Node::print(bool hasChildNode) {
#ifndef NO_USE_OSTRINGSTREAM
  output(std::cout, 0, hasChildNode);
#else
  string buf;
  output(buf, 0, hasChildNode);
  printf("%s", buf.c_str());
#endif
}
