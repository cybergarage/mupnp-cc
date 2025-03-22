/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_CONTROL_H_
#define _MUPMPCC_CONTROL_H_

#include <mupnp/xml/Node.h>
#include <sstream>

namespace mUPnP {
namespace Control {
  const char NS[] = "u";
  const char QUERY_SOAPACTION[] = "urn:schemas-upnp-org:control-1-0#QueryStateVariable";
  const char XMLNS[] = "urn:schemas-upnp-org:control-1-0";
  const char QUERY_STATE_VARIABLE[] = "QueryStateVariable";
  const char QUERY_STATE_VARIABLE_RESPONSE[] = "QueryStateVariableResponse";
  const char VAR_NAME[] = "varName";
  const char RETURN[] = "return";

}

}

#endif
