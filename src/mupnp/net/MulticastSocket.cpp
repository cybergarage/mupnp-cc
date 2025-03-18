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

#include <mupnp/net/HostInterface.h>
#include <mupnp/net/MulticastSocket.h>
#include <mupnp/net/SocketUtil.h>
#include <mupnp/util/StringUtil.h>

#include <mupnp/util/Log.h>

using namespace uHTTP;

////////////////////////////////////////////////
//  MulticastSocket
////////////////////////////////////////////////

MulticastSocket::MulticastSocket()
{
}

MulticastSocket::MulticastSocket(int port, const std::string& bindAddr)
{
  bind(port, bindAddr);
}

MulticastSocket::~MulticastSocket()
{
}

////////////////////////////////////////////////
//  joinGroup
////////////////////////////////////////////////

bool MulticastSocket::bind(int port, const std::string& addr)
{
  return DatagramSocket::bind(port, addr, false, true);
}

////////////////////////////////////////////////
//  joinGroup
////////////////////////////////////////////////

bool MulticastSocket::joinGroup(const std::string& mcastAddr, const std::string& ifAddr)
{
  bool ret = true;

#if defined(TENGINE) && defined(TENGINE_NET_KASAGO)
  struct ip_mreq ipmr;
  u_long ifInetAddr = ka_inet_addr((char*)ifAddr);
  ka_inet_pton(AF_INET, (char*)mcastAddr, &(ipmr.imr_multiaddr));
  memcpy(&ipmr.imr_interface, &ifInetAddr, sizeof(struct in_addr));
  int sockOptRetCode = ka_setsockopt(sock, IP_PROTOIP, IPO_ADD_MEMBERSHIP, (char*)&ipmr, sizeof(ipmr));
  if (sockOptRetCode != 0)
    ret = FALSE;
#elif defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
  /**** Not Suppoted ****/
  return false;
#elif defined(ITRON)
  UW optval = ascii_to_ipaddr((B*)mcastAddr);
  ER optSuccess = udp_set_opt(sock, IP_ADD_MEMBERSHIP, &optval, sizeof(optval));
  if (optSuccess != E_OK)
    return false;
  ret = true;
#else
  struct addrinfo hints;
  memset(&hints, 0, sizeof(hints));
  hints.ai_flags = AI_NUMERICHOST | AI_PASSIVE;

  struct addrinfo *mcastAddrInfo, *ifAddrInfo;
  // Thanks for Lorenzo Vicisano (10/24/04)
  if (getaddrinfo(mcastAddr.c_str(), NULL, &hints, &mcastAddrInfo) != 0)
    return false;
  // Thanks for Lorenzo Vicisano (10/24/04)
  if (getaddrinfo(ifAddr.c_str(), NULL, &hints, &ifAddrInfo) != 0) {
    LogFatal("error %d: %s", 0, DecodeSocketError(GetSocketLastErrorCode()));
    freeaddrinfo(mcastAddrInfo);
    return false;
  }

  int retCode;

  if (IsIPv6Address(mcastAddr) == true) {
    struct ipv6_mreq ipv6mr;
    struct sockaddr_in6 toaddr6, ifaddr6;
    memcpy(&toaddr6, mcastAddrInfo->ai_addr, sizeof(struct sockaddr_in6));
    memcpy(&ifaddr6, ifAddrInfo->ai_addr, sizeof(struct sockaddr_in6));
    ipv6mr.ipv6mr_multiaddr = toaddr6.sin6_addr;
    int scopeID = GetIPv6ScopeID(ifAddr);
    ipv6mr.ipv6mr_interface = scopeID /*if_nametoindex*/;
    SOCKET sock = getSocket();
    retCode = setsockopt(sock, IPPROTO_IPV6, IPV6_MULTICAST_IF, (char*)&scopeID, sizeof(scopeID));
    if (retCode != 0) {
      LogFatal("error %d: %s", ret, DecodeSocketError(GetSocketLastErrorCode()));
      ret = false;
    }
    retCode = setsockopt(sock, IPPROTO_IPV6, IPV6_JOIN_GROUP, (char*)&ipv6mr, sizeof(ipv6mr));
    if (retCode != 0) {
      LogFatal("error %d: %s", ret, DecodeSocketError(GetSocketLastErrorCode()));
      ret = false;
    }
  }
  else {
    struct ip_mreq ipmr;
    struct sockaddr_in toaddr, ifaddr;
    memcpy(&toaddr, mcastAddrInfo->ai_addr, sizeof(struct sockaddr_in));
    memcpy(&ifaddr, ifAddrInfo->ai_addr, sizeof(struct sockaddr_in));
    memcpy(&ipmr.imr_multiaddr.s_addr, &toaddr.sin_addr, sizeof(struct in_addr));
    memcpy(&ipmr.imr_interface.s_addr, &ifaddr.sin_addr, sizeof(struct in_addr));
    SOCKET sock = getSocket();
    retCode = setsockopt(sock, IPPROTO_IP, IP_MULTICAST_IF, (char*)&ipmr.imr_interface.s_addr, sizeof(struct in_addr));
    if (retCode != 0) {
      LogFatal("error %d: %s", ret, DecodeSocketError(GetSocketLastErrorCode()));
      ret = false;
    }
    retCode = setsockopt(sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&ipmr, sizeof(ipmr));
    if (retCode != 0) {
      LogFatal("error %d: %s", ret, DecodeSocketError(GetSocketLastErrorCode()));
      ret = false;
    }
  }

  freeaddrinfo(mcastAddrInfo);
  freeaddrinfo(ifAddrInfo);
#endif

  setLocalAddress((ret == true) ? ifAddr : NULL);

  return ret;
}

////////////////////////////////////////////////
//  setTimeToLive
////////////////////////////////////////////////

void MulticastSocket::setTimeToLive(int ttl)
{
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
  SOCKET sock = getSocket();
  unsigned char ucttl = ttl & 0xFF;
  setsockopt(sock, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ucttl, sizeof(ucttl));
#endif
}
