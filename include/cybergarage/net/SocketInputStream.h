/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SocketInputStream.h
*
*	Revision;
*
*	04/02/03
*		- first revision
*	05/19/04
*		- Changed the header include order for Cygwin.
*
******************************************************************/

#ifndef _CNET_SOCKETINPUTSTREAM_H_
#define _CNET_SOCKETINPUTSTREAM_H_

#include <cybergarage/net/Socket.h>
#include <cybergarage/io/InputStream.h>
#include <string>

namespace CyberNet {

const long SOCKET_RECV_WAIT_TIME = 100;
const long SOCKET_RECV_RETRY_CNT = 10;
const long SOCKET_INBUF_SIZE = 512*1024;

class SocketInputStream : public CyberIO::InputStream
{
	Socket *sock;
	std::string unputBuf;
	char *inBuf;

public:

	SocketInputStream(Socket *sock);

	virtual ~SocketInputStream();

	int read(std::string &b, int len);  
	int read(char *b, int len);  // Not support the unput buffer;

	void unread(std::string &b, int off, int len);  

	long skip(long n);

	void close();
};

}

#endif
