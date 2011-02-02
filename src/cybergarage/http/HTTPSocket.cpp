/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPSocket.cpp
*
*	Revision;
*
*	03/27/03
*		- first revision
*	03/11/04
*		- Added the following methods about chunk size.
*		  setChunkSize(), getChunkSize().
*	08/26/04
*		- Added a isOnlyHeader to post().
*	03/01/05
*		- Changed post() to suppot chunked stream.
*	06/10/05
*		- Changed post() to add a Date headedr to the HTTPResponse before the posting.
*	07/07/05
*		- Lee Peik Feng <pflee@users.sourceforge.net>
*		- Fixed post() to output the chunk size as a hex string.
*
******************************************************************/

#include <cybergarage/http/HTTPSocket.h>
#include <cybergarage/http/HTTPResponse.h>
#include <cybergarage/util/StringUtil.h>

using namespace std;
using namespace CyberHTTP;
using namespace CyberNet;
using namespace CyberIO;
using namespace CyberUtil;

static const int DEFAULT_CHUNK_SIZE = 512 * 1024;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

HTTPSocket::HTTPSocket(CyberNet::Socket *socket)
{
	setSocket(socket);
	open();
}

HTTPSocket::HTTPSocket(HTTPSocket *socket)
{
	setSocket((socket != NULL) ? socket->getSocket() : NULL);
}
	
HTTPSocket::~HTTPSocket()
{
	close();
}
	
////////////////////////////////////////////////
//	open/close
////////////////////////////////////////////////

bool HTTPSocket::open()
{
	return true;
}

bool HTTPSocket::close()
{
	Socket *sock = getSocket();
	if (sock != NULL) {
		sock->close();
		setSocket(NULL);
	}
	return true;
}

////////////////////////////////////////////////
//	post
////////////////////////////////////////////////
	
bool HTTPSocket::post(HTTPResponse *httpRes, const char *content, int contentOffset, int contentLength, bool isOnlyHeader, bool isChunked)
{
	HTTPDate now;
	httpRes->setDate(&now);

	Socket *sock = getSocket();
	
	httpRes->setContentLength(contentLength);

	string header;
	sock->send(httpRes->getHeader(header));
	sock->send(HTTP::CRLF);

	if (isOnlyHeader == true)
		return true;

	if (isChunked == true) {
		string chunSizeBuf;
		Integer2HexString(contentLength, chunSizeBuf);
		sock->send(chunSizeBuf.c_str());
		sock->send(HTTP::CRLF);
	}

	sock->send((content + contentOffset), contentLength);

	if (isChunked == true) {
		sock->send(HTTP::CRLF);
		sock->send("0");
		sock->send(HTTP::CRLF);
	}
		
	return true;
}

bool HTTPSocket::post(HTTPResponse *httpRes, InputStream *in, long contentOffset, long contentLength, bool isOnlyHeader, bool isChunked)
{
	HTTPDate now;
	httpRes->setDate(&now);

	Socket *sock = getSocket();

	httpRes->setContentLength(contentLength);

	string header;
	sock->send(httpRes->getHeader(header));
	sock->send(HTTP::CRLF);

	if (isOnlyHeader == true)
		return true;

	if (0 < contentOffset)
		in->skip(contentOffset);

	int chunkSize = HTTP::GetChunkSize();
	char *chunkBuf = new char[chunkSize+1];

	string readBuf;
	string chunSizeBuf;
	long readCnt = 0;
	long readSize = (chunkSize < contentLength) ? chunkSize : contentLength;
	int readLen = in->read(chunkBuf, (int)readSize);
	while (0 < readLen && readCnt < contentLength) {
		if (isChunked == true) {
			Integer2HexString(readLen, chunSizeBuf);
			sock->send(chunSizeBuf.c_str());
			sock->send(HTTP::CRLF);
		}
		if (sock->send(chunkBuf, readLen) <=0)
			break;
		if (isChunked == true)
			sock->send(HTTP::CRLF);
		readCnt += readLen;
		readBuf = "";
		readSize = (chunkSize < (contentLength-readCnt)) ? chunkSize : (contentLength-readCnt);
		readLen = in->read(chunkBuf, (int)readSize);
	}

	if (isChunked == true) {
		sock->send("0");
		sock->send(HTTP::CRLF);
	}
	
	delete []chunkBuf;

	return true;
}

bool HTTPSocket::post(HTTPResponse *httpRes, int contentOffset, int contentLength, bool isOnlyHeader, bool isChunked)
{
	if (httpRes->hasContentInputStream() == true)
		return post(httpRes,httpRes->getContentInputStream(), contentOffset, contentLength, isOnlyHeader, isChunked);
	return post(httpRes,httpRes->getContent(), contentOffset, contentLength, isOnlyHeader, isChunked);
}
