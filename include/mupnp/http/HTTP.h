/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_HTTP_HTTP_H_
#define _UHTTP_HTTP_HTTP_H_

#include <mupnp/net/URL.h>
#include <string>

namespace uHTTP {
const char PRODUCT_NAME[] = "uhttp";
const char LIBRARY_NAME[] = "libuhttp++";
const char LIBRARY_VERSION[] = "0.6";

namespace HTTP {
  typedef int StatusCode;

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
  const char PUT[] = "PUT";
  const char DELETE[] = "DELETE";
  const char UPDATE[] = "UPDATE";
  const char HEAD[] = "HEAD";
  const char SUBSCRIBE[] = "SUBSCRIBE";
  const char UNSUBSCRIBE[] = "UNSUBSCRIBE";

  const char USER_AGENT[] = "User-Agent";
  const char ACCEPT[] = "Accept";
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
  const int DEFAULT_TIMEOUT_SECOND = 30;

  ////////////////////////////////////////////////
  // URL
  ////////////////////////////////////////////////

  inline bool IsAbsoluteURL(const std::string& urlStr)
  {
    return uHTTP::IsAbsoluteURL(urlStr);
  }

  inline const char* GetHost(const std::string& urlStr, std::string& buf)
  {
    return uHTTP::URLGetHost(urlStr, buf);
  }

  int GetPort(const std::string& urlStr);

  const char* GetRequestHostURL(const std::string& host, int port, std::string& buf);

  inline const char* GetRelativeURL(const std::string& urlStr, std::string& buf, bool withParam = true)
  {
    return uHTTP::URLGetRelativeURL(urlStr, buf, withParam);
  }

  const char* GetAbsoluteURL(const std::string& baseURLStr, const std::string& relURlStr, std::string& buf);

  ////////////////////////////////////////////////
  // Chunk Size
  ////////////////////////////////////////////////

  void SetChunkSize(int size);
  int GetChunkSize();

}

}

#endif
