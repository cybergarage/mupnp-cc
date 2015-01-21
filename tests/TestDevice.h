/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_TESTDEVICE_H_
#define _MUPMPCC_TESTDEVICE_H_

#include <mupnp/mUPnP.h>

using namespace mUPnP;
using namespace uHTTP;

const char PRESENTATION_URI[] = "/presentation";

class TestDevice : public Device, public ActionListener, public QueryListener
{
  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

private:

  static const char *DEVICE_DESCRIPTION;
  static const char *SERVICE_DESCRIPTION;

  ////////////////////////////////////////////////
  // Member
  ////////////////////////////////////////////////

  int count;
  
public:

  TestDevice();

  ////////////////////////////////////////////////
  // ActionListener
  ////////////////////////////////////////////////

  bool actionControlReceived(Action *action);

  ////////////////////////////////////////////////
  // QueryListener
  ////////////////////////////////////////////////

  bool queryControlReceived(StateVariable *stateVar);

  ////////////////////////////////////////////////
  // HttpRequestListner
  ////////////////////////////////////////////////

  uHTTP::HTTP::StatusCode httpRequestRecieved(HTTPRequest *httpReq);

  ////////////////////////////////////////////////
  // update
  ////////////////////////////////////////////////

  void update();
};

#endif

