/******************************************************************
*
*  CyberLink for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File: ControlRequest.h
*
*  Revision;
*
*  07/11/03
*    - first revision
*
******************************************************************/

#ifndef _CLINK_CONTROLREQUEST_H_
#define _CLINK_CONTROLREQUEST_H_

#include <cybergarage/soap/SOAPRequest.h>
#include <cybergarage/upnp/control/Control.h>

#include <sstream>

namespace CyberLink {
class Service;

class ControlRequest : public CyberSOAP::SOAPRequest {
public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////
  
  ControlRequest() {
  }

  ControlRequest(uHTTP::HTTPRequest *httpReq) {
    set(httpReq);
  }

  ////////////////////////////////////////////////
  //  Query
  ////////////////////////////////////////////////

  bool isQueryControl() {
    return isSOAPAction(Control::QUERY_SOAPACTION);
  }
  
  bool isActionControl() {
    return !isQueryControl();
  }

  ////////////////////////////////////////////////
  //  setRequest
  ////////////////////////////////////////////////

protected:
  
  void setRequestHost(Service *service);

};

}

#endif


