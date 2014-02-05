/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ActionResponse.h
*
*  Revision;
*
*  07/29/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_ACTIONRESPONSE_H_
#define _CLINK_ACTIONRESPONSE_H_

#include <cybergarage/upnp/control/ControlResponse.h>
#include <uhttp/http/HTTPStatus.h>
#include <cybergarage/upnp/ArgumentList.h>

#include <sstream>

namespace CyberLink {
class Action;

class ActionResponse : public ControlResponse {
  ArgumentList argList;

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
 public:
  ActionResponse();
  ActionResponse(CyberSOAP::SOAPResponse *soapRes);

  ////////////////////////////////////////////////
  //  Response
  ////////////////////////////////////////////////

 public:
  void setResponse(Action *action);

private:

  CyberXML::Node *createResponseNode(Action *action);

  ////////////////////////////////////////////////
  //  getResponse
  ////////////////////////////////////////////////

private:

  CyberXML::Node *getActionResponseNode();
  
 public:
  ArgumentList *getResponse();

};

}

#endif
