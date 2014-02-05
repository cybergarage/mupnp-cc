/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ActionRequest.h
*
*  Revision;
*
*  07/14/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_ACTIONREQUEST_H_
#define _CLINK_ACTIONREQUEST_H_

#include <cybergarage/upnp/control/ControlRequest.h>
#include <cybergarage/upnp/control/ActionResponse.h>
#include <cybergarage/upnp/ArgumentList.h>
#include <cybergarage/soap/SOAP.h>

#include <sstream>

namespace CyberLink {
class Action;

class ActionRequest : public ControlRequest {
  ArgumentList argumentList;
  ActionResponse actionRes;

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
 public:
  ActionRequest() {
  }

  ActionRequest(uHTTP::HTTPRequest *httpReq) {
    set(httpReq);
    initArgumentList();
  }

  ////////////////////////////////////////////////
  //  Action
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
  //  setRequest
  ////////////////////////////////////////////////

 public:
  void setRequest(Action *action, ArgumentList *argList);

  ////////////////////////////////////////////////
  //  Contents
  ////////////////////////////////////////////////

private:

  CyberXML::Node *createContentNode(Service *service, Action *action, ArgumentList *argList);

  ////////////////////////////////////////////////
  //  post
  ////////////////////////////////////////////////

 public:
  ActionResponse *post(ActionResponse *actionRes);

  ActionResponse *post() {
    return post(&actionRes);
  }

};

}

#endif
