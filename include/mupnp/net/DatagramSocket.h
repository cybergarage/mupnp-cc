/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: DatagramSocket.h
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#ifndef _CNET_DATAGRAMSOCKET_H_
#define _CNET_DATAGRAMSOCKET_H_

#include <cybergarage/net/SocketImp.h>
#include <cybergarage/net/DatagramPacket.h>

namespace CyberNet {

class DatagramSocket : public SocketImp
{

public:

	DatagramSocket();
	DatagramSocket(int port, const char *bindAddr, bool bindAddrFlag = true, bool reuseAddrFlag = false);
	~DatagramSocket();

	bool bind(int port, const char *addr, bool bindAddrFlag = true, bool reuseAddrFlag = false);

	int send(const char *addr, int port, const char *data, int dataLen = -1);

	int send(DatagramPacket *dataPack);

	int receive(DatagramPacket &dataPack);

};

}

#endif
