/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/platform.h>

#if defined(HAVE_UNAME) || defined(__APPLE__)
#include <sys/utsname.h>
#endif

#include <mupnp/http/HTTPServer.h>
#include <mupnp/http/HTTPWorkerThread.h>
#include <mupnp/util/TimeUtil.h>

#include <sstream>

using namespace std;
using namespace uHTTP;

const size_t HTTPServer::DEFAULT_SERVER_WORKER_THREAD_NUM = 10;
const long HTTPServer::DEFAULT_SERVER_THREAD_WAIT_TIME = 250;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

HTTPServer::HTTPServer()
{
  serverSock = NULL;
  setWorkerCount(DEFAULT_SERVER_WORKER_THREAD_NUM);
}

HTTPServer::~HTTPServer()
{
  stop();
  close();
}

////////////////////////////////////////////////
//  ServerSocket
////////////////////////////////////////////////

bool HTTPServer::bind(int port, const std::string& addr)
{
  if (serverSock)
    return true;

  serverSock = new ServerSocket();
  if (serverSock->bind(port, addr) == false) {
    delete serverSock;
    serverSock = NULL;
    return false;
  }
  if (serverSock->listen() == false) {
    delete serverSock;
    serverSock = NULL;
    return false;
  }
  return true;
}

bool HTTPServer::open(int port, const std::string& addr)
{
  return bind(port, addr);
}

bool HTTPServer::close()
{
  if (!serverSock)
    return true;

  serverSock->close();
  delete serverSock;
  serverSock = NULL;

  return true;
}

bool HTTPServer::accept(uHTTP::Socket* socket)
{
  if (!serverSock)
    return false;
  if (serverSock->accept(socket) == false)
    return false;
  if (serverSock->setTimeout(HTTP::DEFAULT_TIMEOUT_SECOND) == false)
    return false;
  return true;
}

bool HTTPServer::isOpened()
{
  return (serverSock) ? true : false;
}

////////////////////////////////////////////////
//  run
////////////////////////////////////////////////

void HTTPServer::run()
{
  if (isOpened() == false)
    return;

  Socket* sock = NULL;

  while (isRunnable() == true) {
    sock = new Socket();
    if (!sock)
      continue;

    if (accept(sock) == false) {
      delete sock;
      continue;
    }

    HTTPMessage* httpMsg = new HTTPMessage(sock);
    this->messageQueue.pushMessage(httpMsg);

    sock = NULL;
  }

  if (sock) {
    delete sock;
    ;
  }
}

////////////////////////////////////////////////
//  start
////////////////////////////////////////////////

bool HTTPServer::start()
{
  stop();

  bool areAllOperationsSuccess = true;

  if (messageQueue.reset() == false) {
    areAllOperationsSuccess = false;
  }

  size_t workerThreadMax = getWorkerCount();
  for (size_t n = 0; n < workerThreadMax; n++) {
    HTTPWorkerThread* workerThread = new HTTPWorkerThread(this);
    workerThreadList.add(workerThread);
  }
  if (!workerThreadList.start()) {
    stop();
    return false;
  }

  return Thread::start();
}

////////////////////////////////////////////////
//  stop
////////////////////////////////////////////////

bool HTTPServer::stop()
{

  bool areAllOperationsSuccess = true;

  if (!workerThreadList.stop()) {
    areAllOperationsSuccess = false;
  }

  if (messageQueue.clear() == false) {
    areAllOperationsSuccess = false;
  }

  if (!Thread::stop()) {
    areAllOperationsSuccess = false;
  }

  return areAllOperationsSuccess;
}

////////////////////////////////////////////////
//  Server Functions
////////////////////////////////////////////////

const char* uHTTP::GetServerName(string& buf)
{
  buf = "";
  string osName = "Platform";
  string osVer = "1.0";
#if defined(WIN32) && !defined(ITRON)
  OSVERSIONINFO verInfo;
  ZeroMemory(&verInfo, sizeof(OSVERSIONINFO));
  verInfo.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  if (GetVersionEx(&verInfo)) {
    osName = "Windows";
    ostringstream verBuf;
    verBuf << verInfo.dwMajorVersion << "." << verInfo.dwMinorVersion;
    osVer = verBuf.str();
  }
#elif defined(BTRON)
  T_VER verInfo;
  if (get_ver(&verInfo) == 0) {
    osName = "BTRON";
    char verStr[32];
    sprintf(verStr, "%hd", verInfo.spver);
    osVer = verStr;
  }
#elif defined(ITRON)
  osName = "uITRON";
  osVer = "4.0";
#elif defined(TENGINE)
  osName = "T-Engine";
  osVer = "1.0";
#elif defined(HAVE_UNAME) || defined(__APPLE__)
  struct utsname unameBuf;
  if (uname(&unameBuf) == 0) {
    osName = unameBuf.sysname;
    osVer = unameBuf.release;
  }
#endif

  buf = osName;
  buf += "/";
  buf += osVer;
  buf += " ";
  buf += uHTTP::LIBRARY_NAME;
  buf += "/";
  buf += uHTTP::LIBRARY_VERSION;

  return buf.c_str();
}
