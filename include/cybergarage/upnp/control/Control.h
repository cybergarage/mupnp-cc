/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: Control.h
*
*  Revision;
*
*  07/11/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_CONTROL_H_
#define _CLINK_CONTROL_H_

#include <sstream>
#include <cybergarage/xml/Node.h>

namespace CyberLink{
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



