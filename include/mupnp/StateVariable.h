/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: Icon.h
*
*  Revision;
*
*  07/20/03
*    - first revision
*
******************************************************************/

#ifndef _MUPMPCC_STATEVARIABLE_H_
#define _MUPMPCC_STATEVARIABLE_H_

#include <uhttp/net/HostInterface.h>
#include <uhttp/util/StringUtil.h>
#include <cybergarage/xml/Node.h>
#include <mupnp/UPnPStatus.h>
#include <mupnp/AllowedValueList.h>
#include <mupnp/AllowedValueRange.h>
#include <mupnp/xml/ServiceData.h>
#include <mupnp/xml/StateVariableData.h>
#include <mupnp/control/QueryResponse.h>
#include <mupnp/control/QueryRequest.h>

#include <sstream>

namespace mUPnP {
class Service;

class StateVariable {
  CyberXML::Node *stateVariableNode;
  CyberXML::Node *serviceNode;
  
  CyberXML::Node stateVarNode;
  UPnPStatus upnpStatus;
  
  AllowedValueList allowedValueList;
  AllowedValueRange allowedValueRange;

  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////
  
 public:
  static const char *ELEM_NAME;
  static const char *NAME;
  static const char *DATATYPE;
  static const char *SENDEVENTS;
  static const char *SENDEVENTS_YES;
  static const char *SENDEVENTS_NO;

  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

 public:
  CyberXML::Node *getServiceNode() {
    return serviceNode;
  }

  Service *getService() {
    CyberXML::Node *node = getServiceNode();
    if (node == NULL)
      return NULL;
    ServiceData *data = dynamic_cast<ServiceData *>(node->getUserData());
    if (data == NULL)
      return NULL;
    return data->getService();
  }

  CyberXML::Node *getStateVariableNode() {
    return stateVariableNode;
  }
  
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  StateVariable();
  StateVariable(CyberXML::Node *serviceNode, CyberXML::Node *stateVarNode);

  ~StateVariable();

  ////////////////////////////////////////////////
  // isStateVariableNode
  ////////////////////////////////////////////////

 public:
  static bool isStateVariableNode(CyberXML::Node *node) {
    return node->isName(ELEM_NAME);
  }

  ////////////////////////////////////////////////
  // AllowedValueList
  ////////////////////////////////////////////////

private:

  void initAllowedValueList();

 public:
  AllowedValueList *getAllowedValueList() {
    return &allowedValueList;
  }

  bool hasAllowedValueList() {
    return (0 < allowedValueList.size()) ? true : false;
  }

  ////////////////////////////////////////////////
  // AllowedValueRange
  ////////////////////////////////////////////////

private:

  void initAllowedValueRange();

 public:
  AllowedValueRange *getAllowedValueRange() {
    if (allowedValueRange.getAllowedValueRangeNode() == NULL)
        return NULL;
    return &allowedValueRange;
  }

  bool hasAllowedValueRange() {
    return (getAllowedValueRange() != NULL) ? true : false;
  }

  ////////////////////////////////////////////////
  // name
  ////////////////////////////////////////////////

 public:
  void setName(const std::string &value) {
    getStateVariableNode()->setNode(NAME, value);
  }

  const char *getName() {
    return getStateVariableNode()->getNodeValue(NAME);
  }

  ////////////////////////////////////////////////
  // dataType
  ////////////////////////////////////////////////

 public:
  void setDataType(const std::string &value) {
    getStateVariableNode()->setNode(DATATYPE, value);
  }

  const char *getDataType() {
    return getStateVariableNode()->getNodeValue(DATATYPE);
  }

  ////////////////////////////////////////////////
  // dataType
  ////////////////////////////////////////////////

 public:
  void setSendEvents(bool state) {
    getStateVariableNode()->setAttribute(SENDEVENTS, (state == true) ? SENDEVENTS_YES : SENDEVENTS_NO);
  }
  
  bool isSendEvents() {
    const char *state = getStateVariableNode()->getAttributeValue(SENDEVENTS);
    if (state == NULL)
      return false;
    uHTTP::String stateStr(state);
    if (stateStr.equalsIgnoreCase(SENDEVENTS_YES) == true)
      return true;
    return false;
  }
  
  ////////////////////////////////////////////////
  // UserData
  ////////////////////////////////////////////////

 public:
  StateVariableData *getStateVariableData () {
    CyberXML::Node *node = getStateVariableNode();
    StateVariableData *userData = dynamic_cast<StateVariableData *>(node->getUserData());
    if (userData == NULL) {
      userData = new StateVariableData();
      node->setUserData(userData);
    }
    return userData;
  }

  ////////////////////////////////////////////////
  // Value
  ////////////////////////////////////////////////

 public:
  void setValue(const std::string &value);
  void setValue(int value);
  void setValue(long value);

  const char *getValue() 
  {
    return getStateVariableData()->getValue();
  }

  ////////////////////////////////////////////////
  // set
  ////////////////////////////////////////////////

 public:
  void set(StateVariable *stateVar);

  ////////////////////////////////////////////////
  // queryAction
  ////////////////////////////////////////////////

 public:
  QueryListener *getQueryListener() 
  {
    return getStateVariableData()->getQueryListener();
  }

  void setQueryListener(QueryListener *listener) 
  {
    getStateVariableData()->setQueryListener(listener);
  }

  bool performQueryListener(QueryRequest *queryReq);

  ////////////////////////////////////////////////
  // ActionControl
  ////////////////////////////////////////////////

 public:
  QueryResponse *getQueryResponse() 
  {
    return getStateVariableData()->getQueryResponse();
  }

  void setQueryResponse(QueryResponse *res) 
  {
    getStateVariableData()->setQueryResponse(res);
  }

  UPnPStatus *getQueryStatus() {
    return getQueryResponse()->getUPnPError();
  }
  
  ////////////////////////////////////////////////
  // ActionControl
  ////////////////////////////////////////////////

 public:
  bool postQuerylAction();

  ////////////////////////////////////////////////
  // UPnPStatus
  ////////////////////////////////////////////////

 public:
  void setStatus(int code, const std::string &descr) {
    upnpStatus.setCode(code);
    upnpStatus.setDescription(descr);
  }

  void setStatus(int code) {
    setStatus(code, UPnP::StatusCodeToString(code));
  }
  
  UPnPStatus *getStatus() {
    return &upnpStatus;
  }

};

}

#endif
