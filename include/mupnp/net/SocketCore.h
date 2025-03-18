/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_NET_SOCKETCORE_H_
#define _UHTTP_NET_SOCKETCORE_H_

#include <mupnp/platform.h>

#include <time.h>

#if defined(WIN32) && defined(ITRON) && defined(_AFXDLL)
#include <afxwin.h>
#endif

#if (defined(WIN32) || defined(__CYGWIN__)) && !defined(ITRON)
#include <winsock2.h>
#include <ws2tcpip.h>
#elif defined(BTRON) || defined(TENGINE)
#include <typedef.h>
#elif defined(ITRON)
#include <kernel.h>
#endif

#include <string>

#if (!defined(WIN32) && !defined(__CYGWIN__)) || defined(ITRON)
#if defined(BTRON) || defined(TENGINE)
typedef W SOCKET;
#elif defined(ITRON)
typedef ER SOCKET;
#else
typedef int SOCKET;
#endif
#endif

#include <mupnp/util/Vector.h>

namespace uHTTP {

class SocketList;

class SocketCore {
  public:
  SocketCore();
  virtual ~SocketCore();

  ////////////////////////////////////////////////
  // Static Members
  ////////////////////////////////////////////////

  public:
  static const int STREAM;
  static const int DGRAM;

  ////////////////////////////////////////////////
  //  Static Methods
  ////////////////////////////////////////////////

  static size_t GetInstanceCount();
  static SocketList* GetInstanceList();

  ////////////////////////////////////////////////
  //  Socket
  ////////////////////////////////////////////////

  public:
  void setSocket(SOCKET value)
  {
    sock = value;
  }

  SOCKET getSocket()
  {
    return sock;
  }

  ////////////////////////////////////////////////
  // bind
  ////////////////////////////////////////////////

  public:
  bool isBound();

  ////////////////////////////////////////////////
  // close
  ////////////////////////////////////////////////

  public:
  bool close();

  ////////////////////////////////////////////////
  //  Local address/port
  ////////////////////////////////////////////////

  public:
  void setLocalAddress(const std::string& addr)
  {
    localAddr = addr;
    // StripIPv6ScopeID(addr, localAddr);
  }

  const char* getLocalAddress()
  {
    return localAddr.c_str();
  }

  void setLocalPort(int port)
  {
    localPort = port;
  }

  int getLocalPort()
  {
    return localPort;
  }

  ////////////////////////////////////////////////
  // Type
  ////////////////////////////////////////////////

  protected:
  void setType(int value)
  {
    type = value;
  }

  public:
  int getType()
  {
    return type;
  }

  ////////////////////////////////////////////////
  // Error Code
  ////////////////////////////////////////////////

  protected:
  void setErrorCode(int code)
  {
    this->errorCode = code;
  }

  public:
  int getErrorCode() const
  {
    return this->errorCode;
  }

  ////////////////////////////////////////////////
  //  Socket Option
  ////////////////////////////////////////////////

  public:
  bool setReuseAddress(bool on);
  bool setTimeout(time_t timeout);

#if defined(TENGINE) && defined(TENGINE_NET_KASAGO)
  bool setMulticastInterface(const std::string& ifaddr);
#endif

  private:
  int type;
  std::string localAddr;
  int localPort;
  int errorCode;

  protected:
  SOCKET sock;
};

class SocketList : public WeakVector<SocketCore> {

  public:
  SocketList()
  {
  }
};

void SocketStartup();
void SocketCleanup();

}

#endif
