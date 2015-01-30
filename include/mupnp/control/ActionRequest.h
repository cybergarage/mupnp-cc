/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_ACTIONREQUEST_H_
#define _MUPMPCC_ACTIONREQUEST_H_

#include <mupnp/control/ControlRequest.h>
#include <mupnp/control/ActionResponse.h>
#include <mupnp/ArgumentList.h>
#include <mupnp/soap/SOAP.h>

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

  ActionRequest(uHTTP::HTTPRequest *httpReq) : ControlRequest(httpReq) {
    initArgumentList();
  }

  ////////////////////////////////////////////////
  // Action
  ////////////////////////////////////////////////

 public:
  mupnp_shared_ptr<uXML::Node> getActionNode();

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

  uXML::Node *createContentNode(Service *service, Action *action, ArgumentList *argList);

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
