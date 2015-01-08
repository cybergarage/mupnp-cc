/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: StateVariableData.h
*
*  Revision;
*
*  07/20/03
*    - first revision
*
******************************************************************/

#ifndef _MUPMPCC_STATEVARIABLEDATA_H_
#define _MUPMPCC_STATEVARIABLEDATA_H_

#include <string>
#include <mupnp/xml/Node.h>
#include <mupnp/xml/NodeData.h>

namespace mUPnP {
class QueryResponse;
class QueryListener;

class StateVariableData : public CyberXML::NodeData {
  std::string value;
  QueryResponse *queryRes;
  QueryListener *queryListener;

  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

 public:
  StateVariableData();

  ~StateVariableData();

  ////////////////////////////////////////////////
  // value
  ////////////////////////////////////////////////

 public:
  const char *getValue() {
    return value.c_str();
  }

  void setValue(const std::string &val) {
    value = val;
  }

  ////////////////////////////////////////////////
  // QueryListener
  ////////////////////////////////////////////////

 public:
  QueryListener *getQueryListener() 
  {
    return queryListener;
  }

  void setQueryListener(QueryListener *listener) 
  {
    queryListener = listener;
  }

  ////////////////////////////////////////////////
  // QueryResponse
  ////////////////////////////////////////////////

 public:
  QueryResponse *getQueryResponse() 
  {
    return queryRes;
  }

  void setQueryResponse(QueryResponse *res);

};

}

#endif
