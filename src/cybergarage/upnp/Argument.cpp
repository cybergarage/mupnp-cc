/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: StateVariable.cpp
*
*  Revision;
*
*  08/10/03
*    - first revision
*  03/30/04
*    - Added getRelatedStateVariable().
*    - Changed setRelatedStateVariable() to setRelatedStateVariableName().
*    - Changed getRelatedStateVariable() to getRelatedStateVariableName().
*    - Added getActionNode() and getAction().
*    - Added getServiceNode() and getService().
*    - Added the parent service node to the constructor.
*  08/21/05
*    - Changed setValue(int) using Integer2String instead of ostringstream.
*
******************************************************************/

#include <cybergarage/upnp/Service.h>
#include <cybergarage/upnp/Argument.h>
#include <uhttp/util/StringUtil.h>

using namespace std;
using namespace CyberLink;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const char *Argument::ELEM_NAME = "argument";

const char *Argument::IN_DIR = "in";
const char *Argument::OUT_DIR = "out";
const char *Argument::NAME = "name";
const char *Argument::DIRECTION = "direction";
const char *Argument::RELATED_STATE_VARIABLE = "relatedStateVariable";

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

Argument::Argument() {
  argumentNode = &defaultArgumentNode;
  serviceNode = &defaultServiceNode;
}
  
Argument::Argument(CyberXML::Node *servNode, CyberXML::Node *argNode) {
  argumentNode = argNode;
  serviceNode = servNode;
}

Argument::Argument(const std::string &name, const std::string &value) {
  argumentNode = &defaultArgumentNode;
  serviceNode = &defaultServiceNode;
  setName(name);
  setValue(value);
}

Argument::~Argument() {
}

////////////////////////////////////////////////
//  setValue
////////////////////////////////////////////////

void Argument::setValue(int value) {
  string valueStr;
  Integer2String(value, valueStr);
  setValue(valueStr.c_str());
}

////////////////////////////////////////////////
//  getService
////////////////////////////////////////////////

Service *Argument::getService() {
  CyberXML::Node *node = getServiceNode();
  ServiceData *data = (ServiceData *)node->getUserData();
  if (data == NULL)
    return NULL;
  return data->getService();
}

////////////////////////////////////////////////
//  relatedStateVariable
////////////////////////////////////////////////

StateVariable *Argument::getRelatedStateVariable() {
  Service *service = getService();
  if (service == NULL)
    return NULL;
  const char *relatedStatVarName = getRelatedStateVariableName();
  return service->getStateVariable(relatedStatVarName);
}

