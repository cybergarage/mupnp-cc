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
*  01/05/04
*    - Added UPnP status methods.
*  01/06/04
*    - Added the following methods.
*      getQueryListener()
*      setQueryListener()
*      performQueryListener()
*  01/07/04
*    - Added StateVariable() and set();
*    - Changed performQueryListener() to use a copy of the StateVariable.
*  03/29/04
*    - Thanks for Adavy
*    - Added the following methods;
*      initAllowedValueList().
*      initAllowedValueRange().
*      getAllowedValueList().
*      getAllowedValueRange().
*  04/26/04
*    - Changed postQuerylAction() to get the return value using the QueryResponse.
*  05/11/04
*    - Added hasAllowedValueList() and hasAllowedValueRange().
*  05/19/04
*    - Changed the header include order for Cygwin.
*  07/09/04
*    - Thanks for Dimas <cyberrate@users.sourceforge.net> and Stefano Lenzi <kismet-sl@users.sourceforge.net>
*    - Changed postQuerylAction() to set the status code to the UPnPStatus.
*  11/09/04
*    - Theo Beisch <theo.beisch@gmx.de>
*    - Changed StateVariable::setValue() to update and send the event when the value is not equal to the current value.
*  11/19/04
*    - Rick Keiner <rick@emanciple.com>
*    - Fixed setValue() to compare only when the current value is not null.
*
******************************************************************/

#include <cybergarage/upnp/StateVariable.h>
#include <uhttp/util/Debug.h>
#include <cybergarage/upnp/Service.h>
#include <cybergarage/upnp/Service.h>
#include <cybergarage/upnp/AllowedValue.h>
#include <cybergarage/upnp/control/QueryListener.h>
#include <uhttp/util/StringUtil.h>

using namespace std;
using namespace uHTTP;
using namespace CyberLink;
using namespace uHTTP;
using namespace CyberXML;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const char *StateVariable::ELEM_NAME = "stateVariable";

const char *StateVariable::NAME = "name";
const char *StateVariable::DATATYPE = "dataType";
const char *StateVariable::SENDEVENTS = "sendEvents";
const char *StateVariable::SENDEVENTS_YES = "yes";
const char *StateVariable::SENDEVENTS_NO = "no";

////////////////////////////////////////////////
//  StateVariable::StateVariable
////////////////////////////////////////////////

StateVariable::StateVariable() {
  this->serviceNode = NULL;
  this->stateVariableNode = &stateVarNode;

  initAllowedValueList();
  initAllowedValueRange();
}

StateVariable::StateVariable(CyberXML::Node *serviceNode, CyberXML::Node *stateVarNode) {
  this->serviceNode = serviceNode;
  this->stateVariableNode = stateVarNode;

  initAllowedValueList();
  initAllowedValueRange();
}

StateVariable::~StateVariable() {
}

////////////////////////////////////////////////
//  AllowedallowedValueList
////////////////////////////////////////////////

void StateVariable::initAllowedValueList() {
  allowedValueList.clear();
  Node *allowedValueListNode = getStateVariableNode()->getNode(AllowedValueList::ELEM_NAME);
  if (allowedValueListNode == NULL)
    return;
  int nNode = allowedValueListNode->getNNodes();
  for (int n = 0; n < nNode; n++) {
    Node *node = allowedValueListNode->getNode(n);
    if (AllowedValue::isAllowedValueNode(node) == false)
      continue;
    AllowedValue *allowedVal = new AllowedValue(node);
    allowedValueList.add(allowedVal);
  }
}

////////////////////////////////////////////////
//  AllowedValueRange
////////////////////////////////////////////////

void StateVariable::initAllowedValueRange() {
  Node *valueRangeNode = getStateVariableNode()->getNode(AllowedValueRange::ELEM_NAME);
  allowedValueRange.setAllowedValueRangeNode(valueRangeNode);
}

////////////////////////////////////////////////
//  Value
////////////////////////////////////////////////

void StateVariable::setValue(const std::string &value) {
  // Thnaks for Tho Beisch (11/09/04)
  string currValue = getStateVariableData()->getValue();
  // Thnaks for Tho Rick Keiner (11/18/04)
  if (currValue.compare(value.c_str()) == 0)
      return;

  getStateVariableData()->setValue(value);

  // notify event
  Service *service = getService();
  if (service == NULL)
    return;
  if (isSendEvents() == false)
    return;
  service->notify(this);
}

void StateVariable::setValue(int value)  {
  string strValue;
  setValue(Integer2String(value, strValue));
}

void StateVariable::setValue(long value)  {
  string strValue;
  setValue(Long2String(value, strValue));
}

////////////////////////////////////////////////
//  set
////////////////////////////////////////////////

void StateVariable::set(StateVariable *stateVar)  {
  setName(stateVar->getName());
  setValue(stateVar->getValue());
  setDataType(stateVar->getDataType());
  setSendEvents(stateVar->isSendEvents());
}

////////////////////////////////////////////////
//  queryAction
////////////////////////////////////////////////

bool StateVariable::performQueryListener(QueryRequest *queryReq) {
  QueryListener *listener = getQueryListener();
  if (listener == NULL)
    return false;
  QueryResponse queryRes;
  StateVariable retVar;
  retVar.set(this);
  retVar.setValue("");
  retVar.setStatus(UPnP::INVALID_VAR);
  if (listener->queryControlReceived(&retVar) == true) {
    queryRes.setResponse(&retVar);
  }
  else {
    UPnPStatus *upnpStatus = retVar.getStatus();
    queryRes.setFaultResponse(upnpStatus->getCode(), upnpStatus->getDescription());
  }
  HTTPRequest *httpReq = queryReq;
  httpReq->post(&queryRes);
  return true;
}

////////////////////////////////////////////////
//  ActionControl
////////////////////////////////////////////////

bool StateVariable::postQuerylAction() {
  QueryRequest queryReq;
  queryReq.setRequest(this);
  if (Debug::isOn() == true)
    queryReq.print();
  QueryResponse *querylRes = new QueryResponse();
  queryReq.post(querylRes);
  if (Debug::isOn() == true)
    querylRes->print();
  setQueryResponse(querylRes);
  // Thanks for Dimas <cyberrate@users.sourceforge.net> and Stefano Lenzi <kismet-sl@users.sourceforge.net> (07/09/04)
  int statCode = querylRes->getStatusCode();
  setStatus(statCode);
  if (querylRes->isSuccessful() == false) {
    setValue(querylRes->getReturnValue());
    return false;
  }
  setValue(querylRes->getReturnValue());
  return true;
}
