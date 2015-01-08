/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ActionResponse.h
*
*  Revision;
*
*  07/29/03
*    - first revision
*
******************************************************************/

#ifndef _MUPMPCC_ACTIONRESPONSE_H_
#define _MUPMPCC_ACTIONRESPONSE_H_

#include <mupnp/control/ControlResponse.h>
#include <uhttp/http/HTTPStatus.h>
#include <mupnp/ArgumentList.h>

#include <sstream>

namespace mUPnP {
class Action;

class ActionResponse : public ControlResponse {
  ArgumentList argList;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
 public:
  ActionResponse();
  ActionResponse(CyberSOAP::SOAPResponse *soapRes);

  ////////////////////////////////////////////////
  // Response
  ////////////////////////////////////////////////

 public:
  void setResponse(Action *action);

private:

  CyberXML::Node *createResponseNode(Action *action);

  ////////////////////////////////////////////////
  // getResponse
  ////////////////////////////////////////////////

private:

  CyberXML::Node *getActionResponseNode();
  
 public:
  ArgumentList *getResponse();

};

}

#endif
