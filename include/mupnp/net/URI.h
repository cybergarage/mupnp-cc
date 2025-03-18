/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_NET_URI_H_
#define _UHTTP_NET_URI_H_

#include <string>

namespace uHTTP {
const int URI_KNKOWN_PORT = -1;

class URI {
  protected:
  std::string uriStr;
  std::string protocol;
  std::string user;
  std::string password;
  std::string host;
  int port;
  std::string path;
  std::string query;
  std::string fragment;

  public:
  static const char* HTTP;
  static const char* HTTPS;

  static int HTTP_PORT;
  static int HTTPS_PORT;

  public:
  static const char* PROTOCOL_DELIM;
  static const char* USER_DELIM;
  static const char* COLON_DELIM;
  static const char* SLASH_DELIM;
  static const char* SBLACET_DELIM;
  static const char* EBLACET_DELIM;
  static const char* SHARP_DELIM;
  static const char* QUESTION_DELIM;

  public:
  URI();
  URI(const std::string& uriStr);

  bool IsAbsoluteURI();

  void setString(const std::string& value);

  const char* getSting()
  {
    return uriStr.c_str();
  }

  void setProtocol(const std::string& value)
  {
    protocol = value;
  }

  const char* getProtocol()
  {
    return protocol.c_str();
  }

  bool hasProtocol()
  {
    return (0 < protocol.length());
  }

  bool isProtocol(const std::string& protocolPrefix)
  {
    return (protocol.compare(protocolPrefix) == 0) ? true : false;
  }

  bool isHTTP()
  {
    return isProtocol(HTTP);
  }

  bool isHTTPS()
  {
    return isProtocol(HTTPS);
  }

  void setUser(const std::string& value)
  {
    user = value;
  }

  const char* getUser()
  {
    return user.c_str();
  }

  void setPassword(const std::string& value)
  {
    password = value;
  }

  const char* getPassword()
  {
    return password.c_str();
  }

  void setHost(const std::string& value)
  {
    host = value;
  }

  const char* getHost()
  {
    return host.c_str();
  }

  void setPort(int value)
  {
    port = value;
  }

  int getPort()
  {
    return port;
  }

  void setPath(const std::string& value)
  {
    path = value;
  }

  const char* getPath()
  {
    return path.c_str();
  }

  bool hasPath()
  {
    return (0 < path.length());
  }

  void setQuery(const std::string& value)
  {
    query = value;
  }

  const char* getQuery()
  {
    return query.c_str();
  }

  bool hasQuery()
  {
    return (0 < query.length());
  }

  void setFragment(const std::string& value)
  {
    fragment = value;
  }

  const char* getFragment()
  {
    return fragment.c_str();
  }

  bool hasFragment()
  {
    return (0 < fragment.length());
  }

  bool isValid();

  void print();
};

}

#endif
