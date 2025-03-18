/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdlib.h>

#include <mupnp/http/HTTP.h>
#include <mupnp/http/HTTPStatus.h>
#include <mupnp/util/StringTokenizer.h>
#include <mupnp/util/StringUtil.h>

using namespace uHTTP;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

HTTPStatus::HTTPStatus()
{
  setVersion("");
  setStatusCode(0);
  setReasonPhrase("");
}

HTTPStatus::HTTPStatus(const std::string& ver, int code, const std::string& reason)
{
  setVersion(ver);
  setStatusCode(code);
  setReasonPhrase(reason);
}

HTTPStatus::HTTPStatus(const std::string& lineStr)
{
  set(lineStr);
}

////////////////////////////////////////////////
//  set
////////////////////////////////////////////////

void HTTPStatus::set(const std::string& lineStr)
{
  if (lineStr.length() <= 0) {
    setVersion(HTTP::VER);
    setStatusCode(HTTP::INTERNAL_SERVER_ERROR);
    setReasonPhrase(HTTP::StatusCodeToString(HTTP::INTERNAL_SERVER_ERROR));
    return;
  }

  StringTokenizer st(lineStr, HTTP::STATUS_LINE_DELIM);
  std::string trimBuf;

  if (st.hasMoreTokens() == false)
    return;
  std::string ver = st.nextToken();
  setVersion(StringTrim(ver.c_str(), trimBuf));

  if (st.hasMoreTokens() == false)
    return;
  std::string codeStr = st.nextToken();
  int code = atoi(codeStr.c_str());
  setStatusCode(code);

  std::string reason = "";
  while (st.hasMoreTokens() == true) {
    if (0 < reason.length())
      reason.append(" ");
    reason.append(st.nextToken());
  }
  setReasonPhrase(StringTrim(reason.c_str(), trimBuf));
}

////////////////////////////////////////////////
//  IsStatusCodeSuccess
////////////////////////////////////////////////

bool uHTTP::HTTP::IsStatusCodeSuccess(int statCode)
{
  if (200 <= statCode && statCode < 300)
    return true;
  return false;
}

////////////////////////////////////////////////
//  StatusCodeToString
////////////////////////////////////////////////

const std::string& uHTTP::HTTP::StatusCodeToString(int code)
{
  int errType = code - (code % 100);

  if (errType == 100) {
    switch (code) {
    case PROCESSING:
      return PROCESSING_STRING;
    }
    return CONTINUE_STRING;
  }

  if (errType == 200) {
    switch (code) {
    case ACCEPTED:
      return ACCEPTED_STRING;
    case NO_CONTENT:
      return NO_CONTENT_STRING;
    case PARTIAL_CONTENT:
      return PARTIAL_CONTENT_STRING;
    }
    return OK_REQUEST_STRING;
  }

  if (errType == 300) {
    switch (code) {
    case MOVED_PERMANENTLY:
      return MOVED_PERMANENTLY_STRING;
    case FOUND:
      return FOUND_STRING;
    }
    return FOUND_STRING;
  }

  if (errType == 400) {
    switch (code) {
    case NOT_FOUND:
      return NOT_FOUND_STING;
    case NOT_ACCEPTABLE:
      return NOT_ACCEPTABLE_STING;
    case PRECONDITION_FAILED:
      return PRECONDITION_FAILED_STING;
    case INVALID_RANGE:
      return INVALID_RANGE_STING;
    }
    return BAD_REQUEST_STRING;
  }

  if (errType == 500) {
    return INTERNAL_SERVER_ERROR_STRING;
  }

  if (errType == 600) {
    return INTERNAL_CLIENT_ERROR_STRING;
  }

  return UNKOWN_ERROR_STRING;
}
