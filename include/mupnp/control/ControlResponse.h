/******************************************************************
*
*  mUPnP for C++
*
*  Copyright (C) Satoshi Konno 2002
*
*  File: ControlResponse.h
*
*  Revision;
*
*  07/29/03
*    - first revision
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
class ControlResponse : public CyberSOAP::SOAPResponse {
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

  ControlResponse(CyberSOAP::SOAPResponse *soapRes) {
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
  
  CyberXML::Node *createFaultResponseNode(int errCode, const std::string &errDescr);

  ////////////////////////////////////////////////
  // UPnP Error
  ////////////////////////////////////////////////

private:

  CyberXML::Node *getUPnPErrorNode() {
    CyberXML::Node *detailNode = getFaultDetailNode();
    if (detailNode == NULL)
      return NULL;
    return detailNode->getNodeEndsWith(CyberSOAP::SOAP::UPNP_ERROR);
  }

  CyberXML::Node *getUPnPErrorCodeNode() {
    CyberXML::Node *errorNode = getUPnPErrorNode();
    if (errorNode == NULL)
      return NULL;
    return errorNode->getNodeEndsWith(CyberSOAP::SOAP::ERROR_CODE);
  }

  CyberXML::Node *getUPnPErrorDescriptionNode() {
    CyberXML::Node *errorNode = getUPnPErrorNode();
    if (errorNode == NULL)
      return NULL;
    return errorNode->getNodeEndsWith(CyberSOAP::SOAP::ERROR_DESCRIPTION);
  }

 public:
  int getUPnPErrorCode() {
    CyberXML::Node *errorCodeNode = getUPnPErrorCodeNode();
    if (errorCodeNode == NULL)
      return -1;
    const char *errorCodeStr = errorCodeNode->getValue();
    return atoi(errorCodeStr);
  }

  const char *getUPnPErrorDescription() {
    CyberXML::Node *errorDescNode = getUPnPErrorDescriptionNode();
    if (errorDescNode == NULL)
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

