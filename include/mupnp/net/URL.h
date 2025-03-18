/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_NET_URL_H_
#define _UHTTP_NET_URL_H_

#include <string>
#include <mupnp/net/URI.h>

namespace uHTTP {
class URL : public URI {
  public:
  URL();
  URL(const std::string& urlStr);
};

bool IsAbsoluteURL(const std::string& urlStr);
const char* URLGetHost(const std::string& urlStr, std::string& buf);
int URLGetPort(const std::string& urlStr);
const char* URLGetRelativeURL(const std::string& urlStr, std::string& buf, bool withParam = true);
const char* URLGetAbsoluteURL(const std::string& baseURLStr, const std::string& relURlStr, std::string& buf);
const char* GetHostURL(const std::string& host, int port, const std::string& uri, std::string& buf);

}

#endif
