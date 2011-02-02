/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPServer.cpp
*
*	Revision;
*
*	03/27/03
*		- first revision
*	10/21/03
*		- Improved the HTTP server using multithreading.
*	05/19/04
*		- Changed the header include order for Cygwin.
*	08/27/04
*		- Changed accept() to set a default timeout, HTTP::DEFAULT_TIMEOUT, to the socket.
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#if defined(HAVE_UNAME)
#include <sys/utsname.h>
#endif

#include <cybergarage/http/HTTPServer.h>
#include <cybergarage/http/HTTPServerThread.h>

#include <sstream>

using namespace std;
using namespace CyberHTTP;
using namespace CyberNet;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////
	
HTTPServer::HTTPServer()
{
	serverSock = NULL;
}

HTTPServer::~HTTPServer()
{
	stop();
	close();
}

////////////////////////////////////////////////
//	ServerSocket
////////////////////////////////////////////////

bool HTTPServer::open(const char *addr, int port)
{
	if (serverSock != NULL)
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

bool HTTPServer::close()
{
	if (serverSock == NULL)
		return true;
	serverSock->close();
	serverSock = NULL;
	return true;
}

bool HTTPServer::accept(CyberNet::Socket *socket)
{
	if (serverSock == NULL)
		return false;
	if (serverSock->accept(socket) == false)
		return false;
	serverSock->setTimeout(HTTP::DEFAULT_TIMEOUT * 1000);
	return true;
}

bool HTTPServer::isOpened()
{
	return (serverSock != NULL) ? true : false;
}

////////////////////////////////////////////////
//	run
////////////////////////////////////////////////

void HTTPServer::run()
{
	if (isOpened() == false)
		return;

	while (isRunnable() == true) {
		Socket *sock = new Socket();
		if (accept(sock) == false) {
			delete sock;
			continue;
		}
		ServerSocket *serverSock = getServerSock();
		if (serverSock == NULL) {
			delete sock;
			continue;
		}

		HTTPServerThread *httpServThread = new HTTPServerThread(this, sock);
		httpServThread->start();
	}
}

////////////////////////////////////////////////
//	Server Functions
////////////////////////////////////////////////

const char *CyberHTTP::GetServerName(string &buf)
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
#elif defined(HAVE_UNAME)
	struct utsname unameBuf;
	if (uname(&unameBuf) == 0) {
		osName = unameBuf.sysname;
		osVer = unameBuf.release;
	}
#endif

	buf = osName;
	buf += "/";
	buf += osVer;

	return buf.c_str();
}
