/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPPacket.cpp
*
*	Revision:
*
*	03/27/03
*		- first revision
*	09/02/03
*		- Giordano Sassaroli <sassarol@cefriel.it>
*		- Problem : The API is unable to receive responses from the Microsoft UPnP stack
*		- Error : the Microsoft UPnP stack is based on ISAPI on IIS, and whenever IIS
*                 receives a post request, it answers with two responses: the first one has no 
*		          body and it is a code 100 (continue) response, which has to be ignored. The
*		          second response is the actual one and should be parsed as the response.
*	02/09/04
*		- Ralf G. R. Bergs" <Ralf@Ber.gs>
*		- Why do you strip leading and trailing white space from the response body?
*		- Disabled to trim the content string.
*	03/11/04
*		- Added some methods about InputStream content.
*		  setContentInputStream(), getContentInputStream() and hasContentInputStream().
*	03/16/04
*		- Thanks for Darrell Young
*		- Added setVersion() and getVersion();
*	03/17/04
*		- Added hasFirstLine();
*	05/19/04
*		- Changed the header include order for Cygwin.
*	05/26/04
*		- Jan Newmarch <jan.newmarch@infotech.monash.edu.au> (05/26/04)
*		- Changed setCacheControl() and getChcheControl();
*	08/04/04
*		- Changed getHeader() not to use at().
*	08/25/04
*		- Added the following methods.
*		  hasContentRange(), setContentRange(), getContentRange(), 
*		  getContentRangeFirstPosition(), getContentRangeLastPosition() and getContentRangeInstanceLength()
*	08/26/04
*		- Added the following methods.
*		  hasConnection(), setConnection(), getConnection(), 
*		  isCloseConnection() and isKeepAliveConnection()
*	08/27/04
*		- Added a updateWithContentLength paramger to setContent().
*		- Changed to HTTPPacket::set() not to change the header of Content-Length.
*	08/28/04
*		- Added init() and read().
*	09/19/04
*		- Added a onlyHeaders parameter to set().
*	10/20/04 
*		- Brent Hills <bhills@openshores.com>
*		- Changed hasContentRange() to check Content-Range and Range header.
*		- Added support for Range header to getContentRange().
*	10/24/04 
*		- Lorenzo Vicisano <lorenzo@vicisano.net>
*		- Fixed a header of set() for FreeBSD.
*	12/21/04
*		- Added support not to ostringstream.
*	02/28/05
*		- Added the following methods for chunked stream support.
*		  hasTransferEncoding(), setTransferEncoding(), getTransferEncoding(), isChunked()
*	03/01/05
*		- Changed post() to suppot chunked stream.
*	03/03/05
*		- Changed the following methods not to use iostream for TRON.
*		  setHeader(int), setHeader(long), getHeaderString(), setContentRange(), setCacheControl().
*	07/07/05
*		- Lee Peik Feng <pflee@users.sourceforge.net> (07/07/05)
*		- Fixed set() to parse the chunk size as a hex string.
*	11/09/05
*		- Added getCharSet()
*
******************************************************************/

#include <string>
#include <sstream>
#include <stdlib.h>
#include <string.h>

#include <cybergarage/http/HTTPPacket.h>
#include <cybergarage/http/HTTPStatus.h>
#include <cybergarage/net/HostInterface.h>
#include <cybergarage/util/StringUtil.h>
#include <cybergarage/util/StringTokenizer.h>
#include <cybergarage/io/InputStreamReader.h>
#include <cybergarage/io/BufferedReader.h>
#include <cybergarage/net/SocketInputStream.h>

using namespace std;
using namespace CyberHTTP;
using namespace CyberIO;
using namespace CyberUtil;
using namespace CyberNet;

////////////////////////////////////////////////
//	Constructor::
////////////////////////////////////////////////

HTTPPacket::HTTPPacket()
{
	setVersion(HTTP::VER);
	setContentInputStream(NULL);
}

HTTPPacket::HTTPPacket(HTTPPacket *httpPacket)
{
	setVersion(HTTP::VER);
	set(httpPacket);
	setContentInputStream(NULL);
}

HTTPPacket::HTTPPacket(HTTPSocket *httpSock)
{
	setVersion(HTTP::VER);
	set(httpSock);
	setContentInputStream(NULL);
}

HTTPPacket::HTTPPacket(CyberIO::InputStream *in)
{
	set(in);
	setContentInputStream(NULL);
}

HTTPPacket::~HTTPPacket()
{
	clearHeaders();
}

////////////////////////////////////////////////
//	init
////////////////////////////////////////////////

void HTTPPacket::init()
{
	setFirstLine("");
	clearHeaders();
	setContent("", false);
	setContentInputStream(NULL);
}

////////////////////////////////////////////////
//	String
////////////////////////////////////////////////

const char *HTTPPacket::getFirstLineToken(int num, string &tokenBuf)
{
	StringTokenizer st(firstLine.c_str(), HTTP::REQEST_LINE_DELIM);
	const char *lastToken = "";
	for (int n=0; n<=num; n++) {
		if (st.hasMoreTokens() == false) {
			tokenBuf = "";
			return tokenBuf.c_str();
		}
		lastToken = st.nextToken();
	}
	tokenBuf = lastToken;
	return tokenBuf.c_str();
}

////////////////////////////////////////////////
//	Header
////////////////////////////////////////////////

HTTPHeader *HTTPPacket::getHeader(const char *name)
{
	int nHeaders = getNHeaders();
	for (int n=0; n<nHeaders; n++) {
		HTTPHeader *header = getHeader(n);
		const char *headerName = header->getName();
		if (StringEqualsIgnoreCase(headerName, name) == true)
			return header;			
	}
	return NULL;
}

void HTTPPacket::clearHeaders()
{
	int nHeaders = getNHeaders();
	for (int n=0; n<nHeaders; n++) {
		HTTPHeader *header = getHeader(n);
		delete header;
	}
	httpHeaderList.clear();
}

void HTTPPacket::setHeader(const char *name, const char *value)
{
	HTTPHeader *header = getHeader(name);
	if (header != NULL) {
		header->setValue(value);
		return;
	}
	addHeader(name, value);
}

void HTTPPacket::setHeader(const char *name, int value)
{
	string valueStr;
	setHeader(name, Integer2String(value, valueStr));
}

void HTTPPacket::setHeader(const char *name, long value)
{
	string valueStr;
	setHeader(name, Long2String(value, valueStr));
}

#if defined(__USE_ISOC99) || (defined(WIN32) && !defined(__CYGWIN__) && !defined(__MINGW32__))

#if defined(__USE_ISOC99)
void HTTPPacket::setHeader(const char *name, long long value)
#elif defined(WIN32)
void HTTPPacket::setHeader(const char *name, __int64 value)
#endif
{
	string valueStr;
	setHeader(name, LongLong2String(value, valueStr));
}

#endif

////////////////////////////////////////////////
//	set
////////////////////////////////////////////////

bool HTTPPacket::set(InputStream *in, bool onlyHeaders)
{
	if (in == NULL)
		return false;

	InputStreamReader inReader(in);
	BufferedReader bufReader(&inReader);

	const char *firstLine = bufReader.readLine();
	if (firstLine == NULL || strlen(firstLine) <= 0)
		return false;

	setFirstLine(firstLine);

	// Thanks for Giordano Sassaroli <sassarol@cefriel.it> (09/03/03)
	HTTPStatus httpStatus(firstLine);
	int statCode = httpStatus.getStatusCode();
	if (statCode == HTTP::CONTINUE){
		//ad hoc code for managing iis non-standard behaviour
		//iis sends 100 code response and a 200 code response in the same
		//stream, so the code should check the presence of the actual
		//response in the stream.
		//skip all header lines
		const char *headerLine = bufReader.readLine();
		while (StringHasData(headerLine) == true) {
			HTTPHeader header(headerLine);
			if (header.hasName() == true)
				setHeader(&header);
			headerLine = bufReader.readLine();
		}
		//look forward another first line
		const char *actualFirstLine = bufReader.readLine();
		if (StringHasData(actualFirstLine) == true) {
			//this is the actual first line
			setFirstLine(actualFirstLine);
		}else{
			return true;
		}
	}

	const char *headerLine = bufReader.readLine();
	while (StringHasData(headerLine) == true) {
		HTTPHeader header(headerLine);
		if (header.hasName() == true)
			setHeader(&header);
		headerLine = bufReader.readLine();
	}

	if (onlyHeaders == true) {
		setContent("", false);
		return true;
	}

	bool isChunkedStream = isChunked();

	long contentLen = 0;
	if (isChunkedStream == true) {
		const char *chunkSize = bufReader.readLine();
		// Thanks for Lee Peik Feng <pflee@users.sourceforge.net> (07/07/05)
		contentLen = HexString2Long(chunkSize);
	}
	else
		contentLen = getContentLength();

	string content;

	int chunkSize = HTTP::GetChunkSize();
	while (0 < contentLen) {
		long readCnt = 0;		
		while (readCnt < contentLen) {
			long noReadLen = contentLen - readCnt;
			int readLen = (noReadLen < chunkSize) ? noReadLen : chunkSize; 
			int len = bufReader.read(content, readLen);
			if (len < 0)
				break;
			readCnt += len;
		}
		if (isChunkedStream == true) {
				// skip CRLF
				long skipLen = 0;
				do {
					long skipCnt = bufReader.skip(HTTP::CRLF_LEN - skipLen);
					if (skipCnt < 0) {
						contentLen = 0;
						break;
					}
					skipLen += skipCnt;
				} while (skipLen < HTTP::CRLF_LEN);
			// read next chunk size
			const char *chunkSize = bufReader.readLine();
			// Thanks for Lee Peik Feng <pflee@users.sourceforge.net> (07/07/05)
			contentLen = HexString2Long(chunkSize);
		}
		else
				contentLen = 0;
	}

	if (0 < content.length()) {
		// Thanks for Ralf G. R. Bergs (02/09/04)
		//String charStr = new String(content);
		//String trimStr = charStr.trim();
		setContent(content, false);
	}

	return true;
}

void HTTPPacket::set(HTTPPacket *httpPacket)
{
	if (httpPacket == NULL)
		return;

	setFirstLine(httpPacket->getFirstLine());
		
	clearHeaders();
	int nHeaders = httpPacket->getNHeaders();
	for (int n=0; n<nHeaders; n++) {
		HTTPHeader *header = new HTTPHeader(httpPacket->getHeader(n));
		addHeader(header);
	}
	setContent(httpPacket->getContent());
}

bool HTTPPacket::set(CyberNet::Socket *sock, bool onlyHeaders)
{
	CyberNet::SocketInputStream sockIn(sock);
	return set(&sockIn, onlyHeaders);
}

////////////////////////////////////////////////
//	read
////////////////////////////////////////////////

bool HTTPPacket::read(HTTPSocket *httpSock)
{
	init();
	return set(httpSock);
}
	
////////////////////////////////////////////////
//	set
////////////////////////////////////////////////

const char *HTTPPacket::getHeaderString(string &headerStr)
{
	int nHeaders = getNHeaders();
	headerStr = "";
	for (int n=0; n<nHeaders; n++) {
		HTTPHeader *header = getHeader(n);
		headerStr += header->getName();
		headerStr += ": ";
		headerStr += header->getValue();
		headerStr += HTTP::CRLF;
	}
	return headerStr.c_str();
}

////////////////////////////////////////////////
// set*Value
////////////////////////////////////////////////

void HTTPPacket::setStringHeader(const char *name, const char *value, const char startWith, const char endWith)
{
	string headerValue = value;
	if (StringStartsWith(value, startWith) == false) {
		char buf[2];
		buf[0] = startWith;
		buf[1] = '\0';
		headerValue = buf;
		headerValue.append(value);
	}
	if (StringEndsWith(value, endWith) == false) {
		char buf[2];
		buf[0] = endWith;
		buf[1] = '\0';
		headerValue.append(buf);
	}
	setHeader(name, headerValue.c_str());
}

const char *HTTPPacket::getStringHeaderValue(const char *name, const char startWith, const char endWith, string &buf)
{
	string headerValue = getHeaderValue(name);
	if (StringStartsWith(headerValue.c_str(), startWith) == true)
		headerValue = headerValue.substr(1, headerValue.length()-1);
	if (StringEndsWith(headerValue.c_str(), endWith) == true)
		headerValue = headerValue.substr(0, headerValue.length()-1);
	buf = headerValue;
	return buf.c_str();
}

////////////////////////////////////////////////
//	Host
////////////////////////////////////////////////

void HTTPPacket::setHost(const char *host, int port)
{
	char str[256];
	if (IsIPv6Address(host) == true)
		sprintf(str, "[%s]:%d", host, port);
	else
		sprintf(str, "%s:%d", host, port);
	setHeader(HTTP::HOST, str);
}

void HTTPPacket::setHost(const char *host)
{
	char str[256];
	if (IsIPv6Address(host) == true)
		sprintf(str, "[%s]", host);
	else
		sprintf(str, "%s", host);
	setHeader(HTTP::HOST, str);
}

////////////////////////////////////////////////
//	ContentRange
////////////////////////////////////////////////

bool HTTPPacket::hasContentRange()
{
	// Thanks for Brent Hills (10/20/04)
	return ( hasHeader(HTTP::CONTENT_RANGE) || hasHeader(HTTP::RANGE));
}

void HTTPPacket::setContentRange(long firstPos, long lastPos, long length)
{
	string ibuf;
	string rangeStr;
	rangeStr += HTTP::CONTENT_RANGE_BYTES;
	rangeStr += " ";
	rangeStr += Long2String(firstPos, ibuf);
	rangeStr += "-";
	rangeStr += Long2String(lastPos, ibuf);
	rangeStr += "/";
	if (0 < length)
		rangeStr += Long2String(length, ibuf);
	else
		rangeStr += "*";
	setHeader(HTTP::CONTENT_RANGE, rangeStr.c_str());
}

void HTTPPacket::getContentRange(long range[])
{
	range[0] = range[1] = range[2] = 0;
	if (hasContentRange() == false)
		return;
	const char *rangeLine = getHeaderValue(HTTP::CONTENT_RANGE);
	// Thanks for Brent Hills (10/20/04)
	if (rangeLine == NULL || strlen(rangeLine) <= 0)
		rangeLine = getHeaderValue(HTTP::RANGE);
	if (rangeLine == NULL || strlen(rangeLine) <= 0)
		return;
	StringTokenizer strToken(rangeLine, " =");
	// Skip bytes
	if (strToken.hasMoreTokens() == false)
		return;
	string bytesStr = strToken.nextToken(" -");
	// Get first-byte-pos
	if (strToken.hasMoreTokens() == false)
		return;
	string firstPosStr = strToken.nextToken("-/");
	range[0] = atol(firstPosStr.c_str());
	if (strToken.hasMoreTokens() == false)
		return;
	string lastPosStr = strToken.nextToken("/");
	range[1] = atol(lastPosStr.c_str());
	if (strToken.hasMoreTokens() == false)
		return;
	string lengthStr = strToken.nextToken("");
	range[2] = atol(lengthStr.c_str());
	return;
}

////////////////////////////////////////////////
//	Connection
////////////////////////////////////////////////

bool HTTPPacket::isCloseConnection()
{
	if (hasConnection() == false)
		return false;
	const char *connection = getConnection();
	if (connection == NULL)
		return false;
	return StringEqualsIgnoreCase(HTTP::CLOSE, connection);
}

bool HTTPPacket::isKeepAliveConnection()
{
	if (hasConnection() == false)
		return false;
	const char *connection = getConnection();
	if (connection == NULL)
		return false;
	return StringEqualsIgnoreCase(HTTP::KEEP_ALIVE, connection);
}

////////////////////////////////////////////////
//	CacheControl
////////////////////////////////////////////////

void HTTPPacket::setCacheControl(const char *directive, int value)
{
	string ibuf;
	string valStr;
	valStr += directive;
	valStr += "=";
	valStr += Integer2String(value, ibuf);
	setHeader(HTTP::CACHE_CONTROL, valStr.c_str());
}

////////////////////////////////////////////////
//	Transfer-Encoding
////////////////////////////////////////////////

bool HTTPPacket::isChunked()
{
	if (hasTransferEncoding() == false)
		return false;
	const char *transEnc = getTransferEncoding();
	if (transEnc == NULL)
		return false;
	return StringEqualsIgnoreCase(HTTP::CHUNKED, transEnc);
}


////////////////////////////////////////////////
//	CharSet
////////////////////////////////////////////////

const char *HTTPPacket::getCharSet(std::string &buf)
{
	buf = "";

	if (getContentType() == NULL)
		return buf.c_str();
	string contentType = getContentType();
	StringToLowerCase(contentType);
	string::size_type charSetIdx = contentType.find(HTTP::CHARSET);
	if (charSetIdx < 0)
		return buf.c_str();
	string::size_type charSetEndIdx = charSetIdx + strlen(HTTP::CHARSET) + 1;
	string::size_type contentTypeSize = contentType.size();
	if ((contentTypeSize-1) < charSetEndIdx)
		return buf.c_str();
	if (contentType[charSetEndIdx] == '\"')
		charSetEndIdx++;
	if (contentType[contentTypeSize] == '\"')
		contentTypeSize--;
	buf = contentType.substr(charSetEndIdx, (contentType.length() - charSetEndIdx));

	return buf.c_str();
}



