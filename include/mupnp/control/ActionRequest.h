/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ActionRequest.h
*
*  Revision;
*
*  07/14/03
*    - first revision
*
******************************************************************/

#ifndef _MUPMPCC_ACTIONREQUEST_H_
#define _MUPMPCC_ACTIONREQUEST_H_

#include <mupnp/control/ControlRequest.h>
#include <mupnp/control/ActionResponse.h>
#include <mupnp/ArgumentList.h>
#include <cybergarage/soap/SOAP.h>

#include <sstream>

namespace mUPnP {
class Action;

class ActionRequest : public ControlRequest {
  ArgumentList argumentList;
  ActionResponse actionRes;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
 public:
  ActionRequest() {
  }

  ActionRequest(uHTTP::HTTPRequest *httpReq) {
    set(httpReq);
    initArgumentList();
  }

  ////////////////////////////////////////////////
  // Action
  ////////////////////////////////////////////////

 public:
  CyberXML::Node *getActionNode();

  const char *getActionName(std::string &buf);

private:

  void initArgumentList();

 public:
  ArgumentList *getArgumentList() {
    return &argumentList;
  }

  ////////////////////////////////////////////////
  // setRequest
  ////////////////////////////////////////////////

 public:
  void setRequest(Action *action, ArgumentList *argList);

  ////////////////////////////////////////////////
  // Contents
  ////////////////////////////////////////////////

private:

  CyberXML::Node *createContentNode(Service *service, Action *action, ArgumentList *argList);

  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////

 public:
  ActionResponse *post(ActionResponse *actionRes);

  ActionResponse *post() {
    return post(&actionRes);
  }

};

}

#endif
