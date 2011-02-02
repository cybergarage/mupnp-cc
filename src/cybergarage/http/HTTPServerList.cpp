/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPServerList.cpp
*
*	Revision:
*
*	05/18/03
*		- first revision
*	05/19/04
*		- Changed the header include order for Cygwin.
*	07/16/03
*		- Thanks for Ilkka Poutanen <poutsi at users.sourceforge.net >and Stefano Lenzi <kismet-sl@users.sourceforge.net >.
*		- Changed open() not to abort when the interface can not be bound.
*	07/17/04
*		- Added clear() to call in close().
*		- Changed the destructor to call stop() and close();
*
******************************************************************/

#include <cybergarage/http/HTTPServerList.h>
#include <cybergarage/util/StringUtil.h>
#include <cybergarage/util/Debug.h>

#include <sstream>

using namespace std;
using namespace CyberHTTP;
using namespace CyberUtil;
using namespace CyberNet;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

HTTPServerList::HTTPServerList()
{
}

HTTPServerList::~HTTPServerList()
{
	stop();
	close();
}

////////////////////////////////////////////////
//	addRequestListener
////////////////////////////////////////////////

void HTTPServerList::addRequestListener(HTTPRequestListener *listener)
{
	int nServers = size();
	for (int n=0; n<nServers; n++) {
		HTTPServer *server = getHTTPServer(n);
		server->addRequestListener(listener);
	}
}

////////////////////////////////////////////////
//	open/close
////////////////////////////////////////////////

void HTTPServerList::close()
{
	int nServers = size();
	for (int n=0; n<nServers; n++) {
		HTTPServer *server = getHTTPServer(n);
		server->close();
	}
	clear();
}

bool HTTPServerList::open(int port)
{
	bool ret = true;
	int nHostAddrs = GetNHostAddresses();
	for (int n=0; n<nHostAddrs; n++) {
		string buf;
		const char *bindAddr = GetHostAddress(n, buf);
		HTTPServer *httpServer = new HTTPServer();
		// Thanks for Ilkka Poutanen and Stefano Lenzi (07/16/04)
		if (httpServer->open(bindAddr, port) == false) {
			string msg;
			string ibuf;
			msg += "Couldn't bind to ";
			msg += bindAddr;
			msg += ":";
			msg += Integer2String(port, ibuf);;
			Debug::warning(msg.c_str());
			ret = false;
			continue;
		}
		add(httpServer);
	}
	return ret;
}

////////////////////////////////////////////////
//	start/stop
////////////////////////////////////////////////

void HTTPServerList::start()
{
	int nServers = size();
	for (int n=0; n<nServers; n++) {
		HTTPServer *server = getHTTPServer(n);
		server->start();
	}
}

void HTTPServerList::stop()
{
	int nServers = size();
	for (int n=0; n<nServers; n++) {
		HTTPServer *server = getHTTPServer(n);
		server->stop();
	}
}

////////////////////////////////////////////////
// clear
////////////////////////////////////////////////

void HTTPServerList::clear()
{
	int nServers = size();
	for (int n=0; n<nServers; n++) {
		HTTPServer *server = getHTTPServer(n);
		delete server;
	}
	Vector::clear();
}
