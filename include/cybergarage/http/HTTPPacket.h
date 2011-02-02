/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPPacket.cpp
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#ifndef _CHTTP_HTTPPACKET_H_
#define _CHTTP_HTTPPACKET_H_

#include <cybergarage/http/HTTPSocket.h>
#include <cybergarage/http/HTTP.h>
#include <cybergarage/http/HTTPHeader.h>
#include <cybergarage/http/HTTPDate.h>

#include <string>
#include <vector>
#include <sstream>

#include <stdlib.h>

namespace CyberHTTP {

class HTTPPacket 
{
	std::vector<HTTPHeader *> httpHeaderList;

	std::string firstLine;
	std::string content;
	std::string version;
	
	CyberIO::InputStream *contentInput;

public:
	
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

	HTTPPacket();

	HTTPPacket(HTTPPacket *httpPacket);

	HTTPPacket(HTTPSocket *httpSock);

	HTTPPacket(CyberIO::InputStream *in);

	~HTTPPacket();

	////////////////////////////////////////////////
	//	init
	////////////////////////////////////////////////

public:
	
	void init();

	////////////////////////////////////////////////
	//	Version
	////////////////////////////////////////////////

public:

	void setVersion(const char *ver)
	{
		version = ver;
	}

	const char *getVersion()
	{
		return version.c_str();
	}

	////////////////////////////////////////////////
	//	set
	////////////////////////////////////////////////

	bool set(CyberIO::InputStream *in, bool onlyHeaders = false);

	bool set(CyberNet::Socket *sock, bool onlyHeaders = false);

	bool set(HTTPSocket *httpSock)
	{
		return set(httpSock->getSocket());
	}

	void set(HTTPPacket *httpPacket);

	////////////////////////////////////////////////
	//	read
	////////////////////////////////////////////////

	bool read(HTTPSocket *httpSock);

	////////////////////////////////////////////////
	//	String
	////////////////////////////////////////////////

	void setFirstLine(const char *value)
	{
		firstLine = (value != NULL) ? value : "";
	}
	
	const char *getFirstLine()
	{
		return firstLine.c_str();
	}

	const char *getFirstLineToken(int num, std::string &tokenBuf);

	bool hasFirstLine()
	{
		return (0 < firstLine.length()) ? true : false;
	}

	////////////////////////////////////////////////
	//	Header
	////////////////////////////////////////////////

	int getNHeaders()
	{
		return (int)httpHeaderList.size();
	}

	void addHeader(HTTPHeader *header)
	{
		httpHeaderList.push_back(header);
	}

	void addHeader(const char *name, const char *value)
	{
		HTTPHeader *header = new HTTPHeader(name, value);
		httpHeaderList.push_back(header);
	}

	HTTPHeader *getHeader(int n)
	{
		return (HTTPHeader *)httpHeaderList[n];
		//return (HTTPHeader *)httpHeaderList.at(n);
	}

	HTTPHeader *getHeader(const char *name);

	void clearHeaders();

	bool hasHeader(const char *name)
	{
		return (getHeader(name) != NULL) ? true : false;
	}

	void setHeader(const char *name, const char *value);
	void setHeader(const char *name, int value);
	void setHeader(const char *name, long value);
#if defined(__USE_ISOC99)
	void setHeader(const char *name, long long value);
#elif defined(WIN32) && !defined(__CYGWIN__) && !defined(__MINGW32__)
	void setHeader(const char *name, __int64 value);
#endif

	void setHeader(HTTPHeader *header)
	{
		setHeader(header->getName(), header->getValue());
	}

	const char *getHeaderValue(const char *name)
	{
		HTTPHeader *header = getHeader(name);
		if (header == NULL)
			return "";
		return header->getValue();
	}

	////////////////////////////////////////////////
	// set*Value
	////////////////////////////////////////////////

	void setStringHeader(const char *name, const char *value, const char startWith, const char endWith);

	void setStringHeader(const char *name, const char *value)
	{
		setStringHeader(name, value, '\"', '\"');
	}

	const char *getStringHeaderValue(const char *name, const char startWith, const char endWith, std::string &buf);
	
	const char *getStringHeaderValue(const char *name, std::string &buf)
	{
		return getStringHeaderValue(name, '\"', '\"', buf);
	}

	void setIntegerHeader(const char *name, int value)
	{
		setHeader(name, value);
	}

	void setLongHeader(const char *name, long value)
	{
		setHeader(name, value);
	}

#if defined(__USE_ISOC99) || (defined(WIN32) && !defined(__CYGWIN__) && !defined(__MINGW32__))
	#if defined(__USE_ISOC99)
	void setLongLongHeader(const char *name, long long value)
	#elif defined(WIN32)
	void setLongLongHeader(const char *name, __int64 value)
	#endif
	{
		setHeader(name, value);
	}
#endif

	int getIntegerHeaderValue(const char *name)
	{
		HTTPHeader *header = getHeader(name);
		if (header == NULL)
			return 0;
		return atoi(header->getValue()); 
	}

	long getLongHeaderValue(const char *name)
	{
		HTTPHeader *header = getHeader(name);
		if (header == NULL)
			return 0;
		return atol(header->getValue());
	}

#if defined(__USE_ISOC99) ||  (defined(WIN32) && !defined(__CYGWIN__) && !defined(__MINGW32__))
	#if defined(__USE_ISOC99)
	long long getLongLongHeaderValue(const char *name)
	#elif defined(WIN32)
	__int64 getLongLongHeaderValue(const char *name)
	#endif
	{
		HTTPHeader *header = getHeader(name);
		if (header == NULL)
			return 0;
	#if defined(__USE_ISOC99)
		return atoll(header->getValue());
	#elif defined(WIN32)
		return _atoi64(header->getValue());
	#endif
	}
#endif

	////////////////////////////////////////////////
	//	getHeaderString
	////////////////////////////////////////////////
	
	const char *getHeaderString(std::string &headerStr);

	////////////////////////////////////////////////
	//	Contents
	////////////////////////////////////////////////

	void setContent(const char *data, bool updateWithContentLength = true)
	{
		content = data;
		if (updateWithContentLength == true)
			setContentLength(content.length());
	}

	void setContent(std::string &data, bool updateWithContentLength = true)
	{
		setContent(data.c_str(), updateWithContentLength);
	}

	const char *getContent()
	{
		return content.c_str();
	}

	bool hasContent()
	{
		return (content.length() > 0) ? true : false;
	}

	////////////////////////////////////////////////
	//	Contents (InputStream)
	////////////////////////////////////////////////

	void setContentInputStream(CyberIO::InputStream *in)
	{
		contentInput = in;
	}

	CyberIO::InputStream *getContentInputStream()
	{
		return contentInput;
	}

	bool hasContentInputStream()
	{
		return (contentInput != NULL) ? true : false;
	}

	////////////////////////////////////////////////
	//	ContentType
	////////////////////////////////////////////////

	void setContentType(const char *type)
	{
		setHeader(HTTP::CONTENT_TYPE, type);
	}

	const char *getContentType()
	{
		return getHeaderValue(HTTP::CONTENT_TYPE);
	}

	const char *getCharSet(std::string &buf);

	////////////////////////////////////////////////
	//	ContentLength
	////////////////////////////////////////////////

#if defined(__USE_ISOC99) || (defined(WIN32) && !defined(__CYGWIN__) && !defined(__MINGW32__))
	#if defined(__USE_ISOC99)
	void setContentLength(long long len)
	#elif defined(WIN32)
	void setContentLength(__int64 len)
	#endif
	{
		setLongLongHeader(HTTP::CONTENT_LENGTH, len);
	}

	#if defined(__USE_ISOC99)
	long long getContentLength()
	#elif defined(WIN32)
	__int64 getContentLength()
	#endif
	{
		return getLongLongHeaderValue(HTTP::CONTENT_LENGTH);
	}

#else

	void setContentLength(long len)
	{
		setLongHeader(HTTP::CONTENT_LENGTH, len);
	}

	long getContentLength()
	{
		return getLongHeaderValue(HTTP::CONTENT_LENGTH);
	}

#endif

	////////////////////////////////////////////////
	//	Connection
	////////////////////////////////////////////////

public:

	bool hasConnection()
	{
		return hasHeader(HTTP::CONNECTION);
	}

	void setConnection(const char *value)
	{
		setHeader(HTTP::CONNECTION, value);
	}

	const char *getConnection()
	{
		return getHeaderValue(HTTP::CONNECTION);
	}

	bool isCloseConnection();

	bool isKeepAliveConnection();

	////////////////////////////////////////////////
	//	ContentRange
	////////////////////////////////////////////////

public:

	bool hasContentRange();
	
	void setContentRange(long firstPos, long lastPos, long length);

	void getContentRange(long range[]);
	
	long getContentRangeFirstPosition()
	{
		long range[3];
		getContentRange(range);
		return range[0];
	}

	long getContentRangeLastPosition()
	{
		long range[3];
		getContentRange(range);
		return range[1];
	}

	long getContentRangeInstanceLength()
	{
		long range[3];
		getContentRange(range);
		return range[2];
	}

	////////////////////////////////////////////////
	//	CacheControl
	////////////////////////////////////////////////

public:

	void setCacheControl(const char *directive)
	{
		setHeader(HTTP::CACHE_CONTROL, directive);
	}
	
	void setCacheControl(const char *directive, int value);
	
	void setCacheControl(int value)
	{
		setCacheControl(HTTP::MAX_AGE, value);
	}

	const char *getCacheControl()
	{
		return getHeaderValue(HTTP::CACHE_CONTROL);
	}

	////////////////////////////////////////////////
	//	Server
	////////////////////////////////////////////////

public:

	void setServer(const char *name)
	{
		setHeader(HTTP::SERVER, name);
	}

	const char *getServer()
	{
		return getHeaderValue(HTTP::SERVER);
	}

	////////////////////////////////////////////////
	//	Host
	////////////////////////////////////////////////

public:

	void setHost(const char *host, int port);
	void setHost(const char *host);

	const char *getHost()
	{
		return getHeaderValue(HTTP::HOST);
	}

	////////////////////////////////////////////////
	//	Date
	////////////////////////////////////////////////

public:

	void setDate(HTTPDate *date)
	{
		setHeader(HTTP::DATE, date->getDateString());
	}

	const char *getDate()
	{
		return getHeaderValue(HTTP::DATE);
	}

	////////////////////////////////////////////////
	//	Transfer-Encoding
	////////////////////////////////////////////////

public:

	bool hasTransferEncoding()
	{
		return hasHeader(HTTP::TRANSFER_ENCODING);
	}

	void setTransferEncoding(const char *value)
	{
		setHeader(HTTP::TRANSFER_ENCODING, value);
	}

	const char *getTransferEncoding()
	{
		return getHeaderValue(HTTP::TRANSFER_ENCODING);
	}

	bool isChunked();

};

}

#endif
