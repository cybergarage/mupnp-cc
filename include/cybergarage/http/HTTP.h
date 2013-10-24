/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTP.h
*
*	Revision;
*
*	03/18/03
*		- first revision
*
******************************************************************/

#ifndef _CHTTP_HTTP_H_
#define _CHTTP_HTTP_H_

#include <string>
#include <cybergarage/net/URL.h>

namespace CyberHTTP {

namespace HTTP {

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////

const char HOST[] = "HOST";
const char VER_10[] = "1.0";
const char VER_11[] = "1.1";
const char VER[] = "1.1";
const char CRLF[] = "\r\n";
const char TAB[] = "\t";
const int CRLF_LEN = 2;

const char SOAP_ACTION[] = "SOAPACTION";
const char M_SEARCH[] = "M-SEARCH";
const char NOTIFY[] = "NOTIFY";
const char POST[] = "POST";
const char GET[] = "GET";
const char HEAD[] = "HEAD";
const char SUBSCRIBE[] = "SUBSCRIBE";
const char UNSUBSCRIBE[] = "UNSUBSCRIBE";	

const char DATE[] = "Date";
const char CACHE_CONTROL[] = "Cache-Control";
	const char NO_CACHE[] = "no-cache";
	const char MAX_AGE[] = "max-age";
const char CONNECTION[] = "Connection";
	const char CLOSE[] = "close";
	const char KEEP_ALIVE[] = "Keep-Alive";
const char CONTENT_TYPE[] = "Content-Type";
	const char CHARSET[] = "charset";
const char CONTENT_LENGTH[] = "Content-Length";
const char CONTENT_RANGE[] = "Content-Range";
	const char CONTENT_RANGE_BYTES[] = "bytes"; 
const char LOCATION[] = "Location";
const char SERVER[] = "Server";
// Thanks for Brent Hills (10/20/04)
const char RANGE[] = "Range";
const char TRANSFER_ENCODING[] = "Transfer-Encoding";
	const char CHUNKED[] = "Chunked";

const char ST[] = "ST";
const char MX[] = "MX";
const char MAN[] = "MAN";
const char NT[] = "NT";
const char NTS[] = "NTS";
const char USN[] = "USN";
const char EXT[] = "EXT";
const char SID[] = "SID";
const char SEQ[] = "SEQ";
const char CALBACK[] = "CALLBACK";
const char TIMEOUT[] = "TIMEOUT";
// Thanks for Brent Hills (10/20/04)
const char MYNAME[] = "MYNAME"; // readable name used by Gateway Connected DVD 

const char REQEST_LINE_DELIM[] = " ";
const char HEADER_LINE_DELIM[] = " :";
const char STATUS_LINE_DELIM[] = " ";

const int DEFAULT_PORT = 80;
const int DEFAULT_CHUNK_SIZE = 512 * 1024;
const int DEFAULT_TIMEOUT = 30;

////////////////////////////////////////////////
// URL
////////////////////////////////////////////////

inline bool IsAbsoluteURL(const char *urlStr)
{
	return CyberNet::IsAbsoluteURL(urlStr);
}

inline const char *GetHost(const char *urlStr, std::string &buf)
{
	return CyberNet::URLGetHost(urlStr, buf);
}

int GetPort(const char *urlStr);

const char *GetRequestHostURL(const char *host, int port, std::string &buf);

inline const char *GetRelativeURL(const char *urlStr, std::string &buf, bool withParam = true)
{
	return CyberNet::URLGetRelativeURL(urlStr, buf, withParam);
}

const char *GetAbsoluteURL(const char *baseURLStr, const char *relURlStr, std::string &buf);

////////////////////////////////////////////////
// Chunk Size
////////////////////////////////////////////////
	
void SetChunkSize(int size);
int GetChunkSize();
	
}

}

#endif
