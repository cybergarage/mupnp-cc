/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPNP_SOAP_H_
#define _MUPNP_SOAP_H_

#include <mupnp/xml/Node.h>

namespace uSOAP {
namespace SOAP {
  const char ENVELOPE[] = "Envelope";
  const char BODY[] = "Body";
  const char RESPONSE[] = "Response";
  const char FAULT[] = "Fault";
  const char FAULT_CODE[] = "faultcode";
  const char FAULT_STRING[] = "faultstring";
  const char FAULTACTOR[] = "faultactor";
  const char DETAIL[] = "detail";

  const char RESULTSTATUS[] = "ResultStatus";
  const char UPNP_ERROR[] = "UPnPError";
  const char ERROR_CODE[] = "errorCode";
  const char ERROR_DESCRIPTION[] = "errorDescription";

  // const char XMLNS[] = "SOAP-ENV";
  const char XMLNS[] = "s";
  const char METHODNS[] = "u";
  const char DELIM[] = ":";

  const char XMLNS_URL[] = "http://schemas.xmlsoap.org/soap/envelope/";
  const char ENCSTYLE_URL[] = "http://schemas.xmlsoap.org/soap/encoding/";

  const char CONTENT_TYPE[] = "text/xml; charset=\"utf-8\"";

  const char ENCORDING[] = "encoding";
  const char UTF_8[] = "utf-8";
  const char VERSION_HEADER[] = "<?xml version=\"1.0\" encoding=\"utf-8\"?>";

  mupnp_shared_ptr<uXML::Node> CreateEnvelopeBodyNode();

  const char* GetHeader(const std::string& content, std::string& header);
  const char* GetEncording(const std::string& content, std::string& encording);
  bool IsEncording(const std::string& content, const std::string& encType);

}

}

#endif
