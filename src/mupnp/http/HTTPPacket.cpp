/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <mupnp/http/HTTPPacket.h>
#include <mupnp/http/HTTPStatus.h>
#include <mupnp/io/BufferedReader.h>
#include <mupnp/io/InputStreamReader.h>
#include <mupnp/net/HostInterface.h>
#include <mupnp/net/SocketInputStream.h>
#include <mupnp/util/StringTokenizer.h>
#include <mupnp/util/StringUtil.h>

using namespace std;
using namespace uHTTP;
using namespace uHTTP;
using namespace uHTTP;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constructor::
////////////////////////////////////////////////

HTTPPacket::HTTPPacket()
{
  setVersion(HTTP::VER);
  setContentInputStream(NULL);
}

HTTPPacket::HTTPPacket(HTTPPacket* httpPacket)
{
  setVersion(HTTP::VER);
  set(httpPacket);
  setContentInputStream(NULL);
}

HTTPPacket::HTTPPacket(HTTPSocket* httpSock)
{
  setVersion(HTTP::VER);
  set(httpSock);
  setContentInputStream(NULL);
}

HTTPPacket::HTTPPacket(uHTTP::InputStream* in)
{
  set(in);
  setContentInputStream(NULL);
}

HTTPPacket::~HTTPPacket()
{
  clearHeaders();
}

////////////////////////////////////////////////
//  init
////////////////////////////////////////////////

void HTTPPacket::init()
{
  setFirstLine("");
  clearHeaders();
  setContent("", false);
  setContentInputStream(NULL);
}

////////////////////////////////////////////////
//  String
////////////////////////////////////////////////

const char* HTTPPacket::getFirstLineToken(int num, string& tokenBuf)
{
  StringTokenizer st(firstLine.c_str(), HTTP::REQEST_LINE_DELIM);
  const char* lastToken = "";
  for (int n = 0; n <= num; n++) {
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
//  Header
////////////////////////////////////////////////

HTTPHeader* HTTPPacket::getHeader(size_t n)
{
  size_t nHeaders = httpHeaderList.size();
  if (nHeaders < (n + 1))
    return nullptr;
  return httpHeaderList.at(n);
}

HTTPHeader* HTTPPacket::getHeader(const std::string& name)
{
  size_t nHeaders = httpHeaderList.size();
  for (size_t n = 0; n < nHeaders; n++) {
    HTTPHeader* header = httpHeaderList.at(n);
    if (!header)
      continue;
    const char* headerName = header->getName();
    if (StringEqualsIgnoreCase(headerName, name) == true)
      return header;
  }
  return nullptr;
}

void HTTPPacket::clearHeaders()
{
  size_t nHeaders = getNHeaders();
  for (size_t n = 0; n < nHeaders; n++) {
    HTTPHeader* header = getHeader(n);
    delete header;
  }
  httpHeaderList.clear();
}

void HTTPPacket::setHeader(const std::string& name, const std::string& value)
{
  HTTPHeader* header = getHeader(name);
  if (header) {
    header->setValue(value);
    return;
  }
  addHeader(name, value);
}

void HTTPPacket::setHeader(const std::string& name, int value)
{
  string valueStr;
  setHeader(name, Integer2String(value, valueStr));
}

void HTTPPacket::setHeader(const std::string& name, long value)
{
  string valueStr;
  setHeader(name, Long2String(value, valueStr));
}

void HTTPPacket::setHeader(const std::string& name, size_t value)
{
  string valueStr;
  setHeader(name, Sizet2String(value, valueStr));
}

bool HTTPPacket::addHeader(const std::string& name, const std::string& value)
{
  if (name.length() <= 0)
    return false;
  HTTPHeader* header = new HTTPHeader(name, value);
  if (!header)
    return false;
  httpHeaderList.push_back(header);
  return true;
}

////////////////////////////////////////////////
//  set
////////////////////////////////////////////////

bool HTTPPacket::set(InputStream* in, bool onlyHeaders)
{
  if (!in)
    return false;

  InputStreamReader inReader(in);
  BufferedReader bufReader(&inReader);

  std::string firstLine = bufReader.readLine();
  if (firstLine.length() <= 0)
    return false;

  setFirstLine(firstLine);

  // Thanks for Giordano Sassaroli <sassarol@cefriel.it> (09/03/03)
  HTTPStatus httpStatus(firstLine);
  int statCode = httpStatus.getStatusCode();
  if (statCode == HTTP::CONTINUE) {
    // ad hoc code for managing iis non-standard behaviour
    // iis sends 100 code response and a 200 code response in the same
    // stream, so the code should check the presence of the actual
    // response in the stream.
    // skip all header lines
    std::string headerLine = bufReader.readLine();
    while (0 < headerLine.length()) {
      HTTPHeader header(headerLine);
      if (header.hasName() == true)
        setHeader(&header);
      headerLine = bufReader.readLine();
    }
    // look forward another first line
    std::string actualFirstLine = bufReader.readLine();
    if (0 < actualFirstLine.length()) {
      // this is the actual first line
      setFirstLine(actualFirstLine);
    }
    else {
      return true;
    }
  }

  std::string headerLine = bufReader.readLine();
  while (0 < headerLine.length()) {
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

  size_t contentLen = 0;
  if (isChunkedStream == true) {
    const char* chunkSize = bufReader.readLine();
    // Thanks for Lee Peik Feng <pflee@users.sourceforge.net> (07/07/05)
    contentLen = HexString2Long(chunkSize);
  }
  else
    contentLen = getContentLength();

  string content;

  int chunkSize = HTTP::GetChunkSize();
  while (0 < contentLen) {
    size_t readCnt = 0;
    while (readCnt < contentLen) {
      size_t noReadLen = contentLen - readCnt;
      size_t readLen = (noReadLen < ((size_t)chunkSize)) ? ((int)noReadLen) : chunkSize;
      ssize_t len = bufReader.read(content, readLen);
      if (len < 0)
        break;
      readCnt += len;
    }
    if (isChunkedStream == true) {
      // skip CRLF
      long skipLen = 0;
      do {
        long skipCnt = bufReader.skip(HTTP::CRLF_LEN - skipLen);
        if (skipCnt <= 0) {
          contentLen = 0;
          break;
        }
        skipLen += skipCnt;
      } while (skipLen < HTTP::CRLF_LEN);
      // read next chunk size
      const char* chunkSize = bufReader.readLine();
      // Thanks for Lee Peik Feng <pflee@users.sourceforge.net> (07/07/05)
      contentLen = HexString2Long(chunkSize);
    }
    else
      contentLen = 0;
  }

  if (0 < content.length()) {
    // Thanks for Ralf G. R. Bergs (02/09/04)
    // String charStr = new String(content);
    // String trimStr = charStr.trim();
    setContent(content, false);
  }

  return true;
}

void HTTPPacket::set(HTTPPacket* httpPacket)
{
  if (!httpPacket)
    return;

  setFirstLine(httpPacket->getFirstLine());

  clearHeaders();
  size_t nHeaders = httpPacket->getNHeaders();
  for (size_t n = 0; n < nHeaders; n++) {
    HTTPHeader* header = new HTTPHeader(httpPacket->getHeader(n));
    addHeader(header);
  }
  setContent(httpPacket->getContent());
}

bool HTTPPacket::set(uHTTP::Socket* sock, bool onlyHeaders)
{
  uHTTP::SocketInputStream sockIn(sock);
  return set(&sockIn, onlyHeaders);
}

bool HTTPPacket::set(HTTPSocket* httpSock)
{
  if (!httpSock)
    return false;
  return set(httpSock->getSocket());
}

////////////////////////////////////////////////
//  read
////////////////////////////////////////////////

bool HTTPPacket::read(HTTPSocket* httpSock)
{
  init();
  return set(httpSock);
}

////////////////////////////////////////////////
//  set
////////////////////////////////////////////////

const char* HTTPPacket::getHeaderString(string& headerStr)
{
  size_t nHeaders = getNHeaders();
  headerStr = "";
  for (size_t n = 0; n < nHeaders; n++) {
    HTTPHeader* header = getHeader(n);
    if (!header)
      continue;
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

void HTTPPacket::setStringHeader(const std::string& name, const std::string& value, const char startWith, const char endWith)
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

const char* HTTPPacket::getStringHeaderValue(const std::string& name, const char startWith, const char endWith, string& buf)
{
  string headerValue = getHeaderValue(name);
  if (StringStartsWith(headerValue.c_str(), startWith) == true)
    headerValue = headerValue.substr(1, headerValue.length() - 1);
  if (StringEndsWith(headerValue.c_str(), endWith) == true)
    headerValue = headerValue.substr(0, headerValue.length() - 1);
  buf = headerValue;
  return buf.c_str();
}

////////////////////////////////////////////////
//  Host
////////////////////////////////////////////////

void HTTPPacket::setHost(const std::string& host, int port)
{
  if (port == HTTP::DEFAULT_PORT) {
    setHost(host);
    return;
  }

  std::ostringstream os;
  if (IsIPv6Address(host) == true)
    os << "[" << host << "]:" << port;
  else
    os << host << ":" << port;

  setHeader(HTTP::HOST, os.str());
}

void HTTPPacket::setHost(const std::string& host)
{
  std::ostringstream os;
  if (IsIPv6Address(host) == true)
    os << "[" << host << "]";
  else
    os << host;
  setHeader(HTTP::HOST, os.str());
}

////////////////////////////////////////////////
//  ContentRange
////////////////////////////////////////////////

bool HTTPPacket::hasContentRange()
{
  // Thanks for Brent Hills (10/20/04)
  return (hasHeader(HTTP::CONTENT_RANGE) || hasHeader(HTTP::RANGE));
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
  const char* rangeLine = getHeaderValue(HTTP::CONTENT_RANGE);
  // Thanks for Brent Hills (10/20/04)
  if (!rangeLine || strlen(rangeLine) <= 0)
    rangeLine = getHeaderValue(HTTP::RANGE);
  if (!rangeLine || strlen(rangeLine) <= 0)
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
//  Connection
////////////////////////////////////////////////

bool HTTPPacket::isCloseConnection()
{
  if (hasConnection() == false)
    return false;
  const char* connection = getConnection();
  if (!connection)
    return false;
  return StringEqualsIgnoreCase(HTTP::CLOSE, connection);
}

bool HTTPPacket::isKeepAliveConnection()
{
  if (hasConnection() == false)
    return false;
  const char* connection = getConnection();
  if (!connection)
    return false;
  return StringEqualsIgnoreCase(HTTP::KEEP_ALIVE, connection);
}

////////////////////////////////////////////////
//  CacheControl
////////////////////////////////////////////////

void HTTPPacket::setCacheControl(const std::string& directive, int value)
{
  string ibuf;
  string valStr;
  valStr += directive;
  valStr += "=";
  valStr += Integer2String(value, ibuf);
  setHeader(HTTP::CACHE_CONTROL, valStr.c_str());
}

////////////////////////////////////////////////
//  Transfer-Encoding
////////////////////////////////////////////////

bool HTTPPacket::isChunked()
{
  if (hasTransferEncoding() == false)
    return false;
  const char* transEnc = getTransferEncoding();
  if (!transEnc)
    return false;
  return StringEqualsIgnoreCase(HTTP::CHUNKED, transEnc);
}

////////////////////////////////////////////////
//  CharSet
////////////////////////////////////////////////

const char* HTTPPacket::getCharSet(std::string& buf)
{
  buf = "";

  if (!getContentType())
    return buf.c_str();
  string contentType = getContentType();
  StringToLowerCase(contentType);
  string::size_type charSetIdx = contentType.find(HTTP::CHARSET);
  if (charSetIdx <= 0)
    return buf.c_str();
  string::size_type charSetEndIdx = charSetIdx + strlen(HTTP::CHARSET) + 1;
  string::size_type contentTypeSize = contentType.size();
  if ((contentTypeSize - 1) < charSetEndIdx)
    return buf.c_str();
  if (contentType[charSetEndIdx] == '\"')
    charSetEndIdx++;
  if (contentType[contentTypeSize] == '\"')
    contentTypeSize--;
  buf = contentType.substr(charSetEndIdx, (contentType.length() - charSetEndIdx));

  return buf.c_str();
}

////////////////////////////////////////////////
//  Clear
////////////////////////////////////////////////

void HTTPPacket::clear()
{
  clearHeaders();
  setFirstLine("");
  setContent("");
}
