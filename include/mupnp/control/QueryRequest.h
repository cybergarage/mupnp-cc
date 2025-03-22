/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_QUERYREQUEST_H_
#define _MUPMPCC_QUERYREQUEST_H_

#include <mupnp/control/ControlRequest.h>
#include <mupnp/control/QueryResponse.h>
#include <mupnp/soap/SOAP.h>

#include <sstream>

namespace mUPnP {
class Service;
class StateVariable;

class QueryRequest : public ControlRequest {
  QueryResponse queryRes;

  public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  QueryRequest()
  {
  }

  QueryRequest(uHTTP::HTTPRequest* httpReq)
  {
    set(httpReq);
  }

  ////////////////////////////////////////////////
  // Qyery
  ////////////////////////////////////////////////

  private:
  mupnp_shared_ptr<uXML::Node> getVarNameNode();

  public:
  const char* getVarName();

  ////////////////////////////////////////////////
  // setRequest
  ////////////////////////////////////////////////

  void setRequest(StateVariable* stateVar);

  ////////////////////////////////////////////////
  // Contents
  ////////////////////////////////////////////////

  private:
  uXML::Node* createContentNode(StateVariable* stateVar);

  ////////////////////////////////////////////////
  // post
  ////////////////////////////////////////////////

  public:
  QueryResponse* post(QueryResponse* actionRes);

  QueryResponse* post()
  {
    return post(&queryRes);
  }
};

}

#endif
