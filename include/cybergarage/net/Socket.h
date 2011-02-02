/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Socket.h
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#ifndef _CNET_SOCKET_H_
#define _CNET_SOCKET_H_

#include <cybergarage/net/SocketImp.h>

namespace CyberNet {

class Socket : public SocketImp
{

#if defined(ITRON)
	static const int WINDOW_BUF_SIZE;
	UH *sendWinBuf;
	UH *recvWinBuf;
#endif

private:

#if defined(ITRON)
	void initWindowBuffer();
#endif

public:

	Socket();
	~Socket();

	bool listen();

	bool bind(int port, const char *addr);

	bool accept(Socket *socket);

	bool connect(const char *addr, int port);

	int send(const char *cmd, int cmdLen);
	int send(const char *cmd);

	int recv(char *buffer, int bufferLen);

};

}

#endif
