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
#include <stdlib.h>
#include <string.h>

#include <mupnp/net/DatagramPacket.h>
#include <mupnp/net/DatagramSocket.h>
#include <mupnp/net/Socket.h>
#include <mupnp/net/SocketUtil.h>

using namespace uHTTP;

const int DGRAM_SOCKET_RECV_BUFSIZE = 512;

#if defined(ITRON)
static ER UdpCallback(ID cepid, FN fncd, VP parblk);
static ER TcpCallback(ID cepid, FN fncd, VP parblk);
#endif

////////////////////////////////////////////////
//  DatagramSocket
////////////////////////////////////////////////

DatagramSocket::DatagramSocket()
{
  setType(DGRAM);
}

DatagramSocket::DatagramSocket(int port, const std::string& bindAddr, bool bindAddrFlag, bool reuseAddrFlag)
{
  setType(DGRAM);
  bind(port, bindAddr, bindAddrFlag, reuseAddrFlag);
}

DatagramSocket::~DatagramSocket()
{
  close();
}

////////////////////////////////////////////////
//  bind
////////////////////////////////////////////////

bool DatagramSocket::bind(int bindPort, const std::string& bindAddr, bool bindAddrFlag, bool reuseAddrFlag)
{
  setLocalAddress("");
  setLocalPort(0);

  if (bindPort <= 0 || bindAddr.length() <= 0)
    return false;

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
  struct sockaddr_in sockaddr;
  if (toSocketAddrIn(bindAddr, bindPort, &sockaddr) == false)
    return false;
  sock = so_socket(PF_INET, SOCK_DGRAM, 0);
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
  struct sockaddr_in sockaddr;
  if (toSocketAddrIn(bindAddr, bindPort, &sockaddr) == false)
    return false;
  ERR sock = ka_socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
#elif defined(ITRON)
  sock = GetAvailableSocketID(STREAM);
#else
  struct addrinfo* addrInfo;
  if (toSocketAddrInfo(SOCK_DGRAM, bindAddr, bindPort, &addrInfo, bindAddrFlag) == false)
    return false;
  sock = socket(addrInfo->ai_family, addrInfo->ai_socktype, 0);
#endif

  if (sock < 0)
    return false;

  if (reuseAddrFlag == true) {
    if (setReuseAddress(true) == false)
      return false;
  }

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
  ERR ret = so_bind(sock, (SOCKADDR*)&sockaddr, sizeof(struct sockaddr_in));
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
  ERR ret = ka_bind(sock, (struct sockaddr*)&sockaddr, sizeof(struct sockaddr_in));
#elif defined(ITRON)
  T_UDP_CCEP udpccep = { 0, { IPV4_ADDRANY, UDP_PORTANY }, (FP)UdpCallback };
  if (bindAddr)
    udpccep.myaddr.ipaddr = ascii_to_ipaddr((B*)bindAddr);
  udpccep.myaddr.ipaddr = htons(bindPort);
  ER ret = udp_cre_cep(sock, &udpccep);
  if (ret != E_OK) {
    close();
    return false;
  }
#else
  int ret = ::bind(sock, addrInfo->ai_addr, addrInfo->ai_addrlen);
  freeaddrinfo(addrInfo);
#endif

  setLocalAddress(bindAddr);
  setLocalPort(bindPort);

  // Thanks for Roland Moser (09/06/05)
  if (ret != 0)
    return false;

  return true;
}

////////////////////////////////////////////////
//  recv
////////////////////////////////////////////////

ssize_t DatagramSocket::receive(DatagramPacket& dataPack)
{
  dataPack.setAddress("");
  dataPack.setPort(0);

  char recvBuf[DGRAM_SOCKET_RECV_BUFSIZE + 1];

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
  struct sockaddr_in from;
  W fromLen = sizeof(sockaddr_in);
  int recvLen = so_recvfrom(sock, recvBuf, sizeof(recvBuf) - 1, 0, (struct sockaddr*)&from, &fromLen);
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
  struct sockaddr_in from;
  int fromLen = sizeof(from);
  int recvLen = ka_recvfrom(sock, recvBuf, sizeof(recvBuf) - 1, 0, (struct sockaddr*)&from, &fromLen);
#elif defined(ITRON)
  T_IPV4EP remoteHost;
  int recvLen = udp_rcv_dat(sock, &remoteHost, recvBuf, sizeof(recvBuf) - 1, TMO_FEVR);
#else
  struct sockaddr_storage from;
  socklen_t fromLen = sizeof(from);
  ssize_t recvLen = ::recvfrom(sock, recvBuf, sizeof(recvBuf) - 1, 0, (struct sockaddr*)&from, &fromLen);
#endif

  if (recvLen <= 0)
    return 0;

  recvBuf[recvLen] = '\0';
  dataPack.setData(recvBuf);

  char remoteAddr[32];
  char remotePort[32];

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
  dataPack.setAddress(inet_ntoa(from.sin_addr));
  dataPack.setPort(ntohl(from.sin_port));
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
  ka_tfInetToAscii((unsigned long)from.sin_addr.s_addr, remoteAddr);
  dataPack.setAddress(remoteAddr);
  dataPack.setPort(ka_ntohl(from.sin_port));
#elif defined(ITRON)
  ipaddr_to_ascii((B*)remoteAddr, remoteHost.ipaddr);
  dataPack.setAddress(remoteAddr);
  dataPack.setPort(ntohs(remoteHost.portno));
#else
  int ret = getnameinfo((struct sockaddr*)&from, fromLen, remoteAddr, sizeof(remoteAddr), remotePort, sizeof(remotePort), NI_NUMERICHOST | NI_NUMERICSERV);
  if (ret == 0) {
    dataPack.setAddress(remoteAddr);
    dataPack.setPort(atoi(remotePort));
  }
#endif

  return recvLen;
}

////////////////////////////////////////////////
//  send
////////////////////////////////////////////////

ssize_t DatagramSocket::send(const std::string& addr, int port, const std::string& data, size_t dataLen)
{
  if (dataLen <= 0)
    dataLen = data.length();

  if (dataLen <= 0)
    return 0;

  bool isBoundFlag = isBound();

#if defined(BTRON) || (defined(TENGINE) && !defined(TENGINE_NET_KASAGO))
  struct sockaddr_in sockaddr;
  if (toSocketAddrIn(addr, port, &sockaddr, true) == false)
    return 0;

  if (isBoundFlag == false)
    sock = so_socket(PF_INET, SOCK_DGRAM, 0);

  if (sock < 0)
    return -1;

  ssize_t sentLen = so_sendto(sock, (B*)data, dataLen, 0, (SOCKADDR*)&sockaddr, sizeof(sockaddr_in));
#elif defined(TENGINE) && defined(TENGINE_NET_KASAGO)
  struct sockaddr_in sockaddr;
  if (toSocketAddrIn(addr, port, &sockaddr, true) == false)
    return 0;

  if (isBoundFlag == FALSE) {
    sock = ka_socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    setMulticastInterface(NULL);
  }

  if (sock < 0)
    return -1;
  ssize_t sentLen = ka_sendto(sock, (char*)data, dataLen, 0, (struct sockaddr*)&sockaddr, sizeof(struct sockaddr_in));
#elif defined(ITRON)
  if (isBoundFlag == FALSE) {
    sock = GetAvailableSocketID(DGRAM);
    if (sock < 0)
      return FALSE;
    T_UDP_CCEP udpccep = { 0, { IPV4_ADDRANY, UDP_PORTANY }, (FP)UdpCallback };
    if (udp_cre_cep(sock, &udpccep) != E_OK)
      return FALSE;
  }
  T_IPV4EP dstaddr;
  dstaddr.ipaddr = ascii_to_ipaddr((B*)addr);
  dstaddr.portno = htons(port);
  ssize_t sentLen = udp_snd_dat(sock, &dstaddr, data, dataLen, TMO_FEVR);
#else
  struct addrinfo* addrInfo;
  if (toSocketAddrInfo(SOCK_DGRAM, addr, port, &addrInfo, true) == false)
    return false;

  if (isBoundFlag == false)
    sock = socket(addrInfo->ai_family, addrInfo->ai_socktype, 0);

  if (sock < 0)
    return -1;

  ssize_t sentLen = ::sendto(sock, data.c_str(), dataLen, 0, addrInfo->ai_addr, addrInfo->ai_addrlen);
#endif

  if (isBoundFlag == false)
    close();

  return sentLen;
}

ssize_t DatagramSocket::send(DatagramPacket* dataPack)
{
  InetSocketAddress* sockAddr = dataPack->getSocketAddress();
  return send(sockAddr->getAddress(), sockAddr->getPort(), dataPack->getData());
}

////////////////////////////////////////////////
//  UdpCallback (ITRON)
////////////////////////////////////////////////

#if defined(ITRON)

static ER UdpCallback(ID cepid, FN fncd, VP parblk)
{
  return E_OK;
}

#endif
