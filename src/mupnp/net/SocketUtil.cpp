/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <string.h>

#include <mupnp/net/SocketCore.h>
#include <mupnp/net/SocketUtil.h>

using namespace uHTTP;

////////////////////////////////////////////////
//  DecodeError
////////////////////////////////////////////////

int uHTTP::GetSocketLastErrorCode()
{
#if (defined(WIN32) || defined(__CYGWIN__)) && !defined(ITRON)
  return WSAGetLastError();
#else
  return 0;
#endif
}

const char* uHTTP::DecodeSocketError(int ErrorCode)
{
  static char msg[1024];

#if defined(WIN32) || defined(__CYGWIN__)
  FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_MAX_WIDTH_MASK,
      NULL,
      ErrorCode,
      MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
      (LPSTR)msg,
      1024,
      NULL);
#else
  msg[0] = '\0';
#endif
  return msg;
}

////////////////////////////////////////////////
//  toSocketAddrIn
////////////////////////////////////////////////

#if !defined(ITRON)

bool uHTTP::toSocketAddrIn(const std::string& addr, int port, struct sockaddr_in* sockaddr, bool isBindAddr)
{
  SocketStartup();

  memset(sockaddr, 0, sizeof(sockaddr_in));

#if defined(TENGINE) && defined(TENGINE_NET_KASAGO)
  sockaddr->sin_family = AF_INET;
  sockaddr->sin_addr.s_addr = ka_htonl(INADDR_ANY);
  sockaddr->sin_port = ka_htons((unsigned short)port);
#else
  sockaddr->sin_family = AF_INET;
  sockaddr->sin_addr.s_addr = htonl(INADDR_ANY);
  sockaddr->sin_port = htons((unsigned short)port);
#endif

  if ((isBindAddr == true) || (0 < addr.length())) {
#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
    sockaddr->sin_addr.s_addr = inet_addr(addr);
    if (sockaddr->sin_addr.s_addr == -1 /*INADDR_NONE*/) {
      struct hostent hent;
      B hostBuf[HBUFLEN];
      if (so_gethostbyname((B*)addr, &hent, hostBuf) != 0)
        return false;
      memcpy(&(sockaddr->sin_addr), hent.h_addr, hent.h_length);
    }
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
    sockaddr->sin_addr.s_addr = ka_inet_addr((char*)addr);
#else
    sockaddr->sin_addr.s_addr = inet_addr(addr.c_str());
    if (sockaddr->sin_addr.s_addr == INADDR_NONE) {
      struct hostent* hent = gethostbyname(addr.c_str());
      if (!hent)
        return false;
      memcpy(&(sockaddr->sin_addr), hent->h_addr, hent->h_length);
    }
#endif
  }

  return true;
}

#endif

////////////////////////////////////////////////
//  toSocketAddrInfo
////////////////////////////////////////////////

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)

bool uHTTP::toSocketAddrInfo(int sockType, const std::string& addr, int port, struct addrinfo** addrInfo, bool isBindAddr)
{
  SocketStartup();

  int errorn;

  struct addrinfo hints;
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_socktype = sockType;
  hints.ai_flags = /*AI_NUMERICHOST | */ AI_PASSIVE;

  char portStr[32];
  sprintf(portStr, "%d", port);

  if ((errorn = getaddrinfo(addr.c_str(), portStr, &hints, addrInfo)) != 0) {
    return false;
  }

  if (isBindAddr)
    return true;

  hints.ai_family = (*addrInfo)->ai_family;
  freeaddrinfo(*addrInfo);
  if ((errorn = getaddrinfo(NULL, portStr, &hints, addrInfo)) != 0) {
    return false;
  }

  return true;
}

#endif
