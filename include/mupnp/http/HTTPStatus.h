/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_HTTPSTATUS_H_
#define _UHTTP_HTTPSTATUS_H_

#include <string>

namespace uHTTP {

namespace HTTP {
  // 1xx Informational
  const int CONTINUE = 100;
  const int PROCESSING = 102;

  // 2xx Success
  const int OK_REQUEST = 200;
  const int ACCEPTED = 202;
  const int NO_CONTENT = 204;
  const int PARTIAL_CONTENT = 206;

  // 3xx Redirection
  const int MOVED_PERMANENTLY = 301;
  const int FOUND = 302;

  // 4xx Client Error
  const int BAD_REQUEST = 400;
  const int NOT_FOUND = 404;
  const int NOT_ACCEPTABLE = 406;
  const int PRECONDITION_FAILED = 412;

  const int INVALID_RANGE = 416;

  // 5xx Server Error
  const int INTERNAL_SERVER_ERROR = 500;

  // xxx uHTTP Extentions
  const int INTERNAL_CLIENT_ERROR = 600;
}

namespace HTTP {
  // 1xx Informational
  const std::string CONTINUE_STRING = "Continue";
  const std::string PROCESSING_STRING = "Processing";

  // 2xx Success
  const std::string OK_REQUEST_STRING = "OK";
  const std::string ACCEPTED_STRING = "Accepted";
  const std::string NO_CONTENT_STRING = "No Content";
  const std::string PARTIAL_CONTENT_STRING = "Partial Content";

  // 3xx Redirection
  const std::string MOVED_PERMANENTLY_STRING = "Moved Permanently";
  const std::string FOUND_STRING = "Found";

  // 4xx Client Error
  const std::string BAD_REQUEST_STRING = "Bad Request";
  const std::string NOT_FOUND_STING = "Not Found";
  const std::string NOT_ACCEPTABLE_STING = "Not Acceptable";
  const std::string PRECONDITION_FAILED_STING = "Precondition Failed";
  const std::string INVALID_RANGE_STING = "Invalid Range";

  // 5xx Server Error
  const std::string INTERNAL_SERVER_ERROR_STRING = "Internal Server Error";

  // 6xx uHTTP Extentions
  const std::string INTERNAL_CLIENT_ERROR_STRING = "Internal Client Error";

  // xxx
  const std::string UNKOWN_ERROR_STRING = "Unknown Error";
}

namespace HTTP {
  bool IsStatusCodeSuccess(int code);
  const std::string& StatusCodeToString(int code);
}

class HTTPStatus {
  std::string version;
  int statusCode;
  std::string reasonPhrase;

  public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

  HTTPStatus();
  HTTPStatus(const std::string& lineStr);
  HTTPStatus(const std::string& ver, int code, const std::string& reason);

  ////////////////////////////////////////////////
  //  Member
  ////////////////////////////////////////////////

  public:
  void setVersion(const std::string& value)
  {
    this->version = value;
  }

  void setStatusCode(int value)
  {
    this->statusCode = value;
  }

  void setReasonPhrase(const std::string& value)
  {
    this->reasonPhrase = value;
  }

  const char* getVersion()
  {
    return version.c_str();
  }

  int getStatusCode()
  {
    return statusCode;
  }

  const char* getReasonPhrase()
  {
    return reasonPhrase.c_str();
  }

  ////////////////////////////////////////////////
  //  Status
  ////////////////////////////////////////////////

  public:
  bool isSuccessful()
  {
    return HTTP::IsStatusCodeSuccess(getStatusCode());
  }

  ////////////////////////////////////////////////
  //  set
  ////////////////////////////////////////////////

  public:
  void set(const std::string& lineStr);
};

}

#endif
