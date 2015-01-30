/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_CONTROLRESPONSE_H_
#define _MUPMPCC_CONTROLRESPONSE_H_

#include <mupnp/soap/SOAPResponse.h>
#include <mupnp/xml/Node.h>
#include <mupnp/soap/SOAP.h>
#include <mupnp/UPnP.h>
#include <mupnp/UPnPStatus.h>

#include <sstream>

namespace mUPnP {
class ControlResponse : public uSOAP::SOAPResponse {
  UPnPStatus upnpErr;

public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  static const char *FAULT_CODE;
  static const char *FAULT_STRING;

public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////
  
  ControlResponse() {
    std::string serverName;
    setServer(UPnP::GetServerName(serverName));
  }

  ControlResponse(SOAPResponse *soapRes) {
    set(soapRes);
  }

  ////////////////////////////////////////////////
  // FaultResponse
  ////////////////////////////////////////////////

public:
  
  void setFaultResponse(int errCode, const std::string &errDescr);
  void setFaultResponse(int errCode) {
    setFaultResponse(errCode, UPnP::StatusCodeToString(errCode));
  }

private:
  
  uXML::Node *createFaultResponseNode(int errCode, const std::string &errDescr);

  ////////////////////////////////////////////////
  // UPnP Error
  ////////////////////////////////////////////////

private:

  mupnp_shared_ptr<uXML::Node> getUPnPErrorNode() {
    mupnp_shared_ptr<uXML::Node> detailNode = getFaultDetailNode();
    if (!detailNode)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return detailNode->getNodeEndsWith(uSOAP::SOAP::UPNP_ERROR);
  }

  mupnp_shared_ptr<uXML::Node> getUPnPErrorCodeNode() {
    mupnp_shared_ptr<uXML::Node> errorNode = getUPnPErrorNode();
    if (!errorNode)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return errorNode->getNodeEndsWith(uSOAP::SOAP::ERROR_CODE);
  }

  mupnp_shared_ptr<uXML::Node> getUPnPErrorDescriptionNode() {
    mupnp_shared_ptr<uXML::Node> errorNode = getUPnPErrorNode();
    if (!errorNode)
      return mupnp_shared_ptr<uXML::Node>((uXML::Node *)nullptr);
    return errorNode->getNodeEndsWith(uSOAP::SOAP::ERROR_DESCRIPTION);
  }

 public:
  int getUPnPErrorCode() {
    mupnp_shared_ptr<uXML::Node> errorCodeNode = getUPnPErrorCodeNode();
    if (!errorCodeNode)
      return -1;
    const char *errorCodeStr = errorCodeNode->getValue();
    return atoi(errorCodeStr);
  }

  const char *getUPnPErrorDescription() {
    mupnp_shared_ptr<uXML::Node> errorDescNode = getUPnPErrorDescriptionNode();
    if (!errorDescNode)
      return "";
    return errorDescNode->getValue();
  }

  UPnPStatus *getUPnPError() {
    upnpErr.setCode(getUPnPErrorCode());
    upnpErr.setDescription(getUPnPErrorDescription());
    return &upnpErr;
  }

};

}

#endif

