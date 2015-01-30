/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
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
  ActionResponse(SOAPResponse *soapRes);

  ////////////////////////////////////////////////
  // Response
  ////////////////////////////////////////////////

 public:
  void setResponse(Action *action);

private:

  uXML::Node *createResponseNode(Action *action);

  ////////////////////////////////////////////////
  // getResponse
  ////////////////////////////////////////////////

private:

  mupnp_shared_ptr<uXML::Node> getActionResponseNode();
  
 public:
  ArgumentList *getResponse();

};

}

#endif
