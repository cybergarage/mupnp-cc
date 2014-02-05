/******************************************************************
*
*  CyberXML for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File:  Parser.cpp
*
*  Revision;
*
*  05/20/03
*    - first revision
*  04/19/04
*    - Fixed the parse() to read under the buffer size.
*  04/27/04
*    - Chaged XMLCh2Char() to return the value using string buffer.
*  05/19/04
*    - Changed the header include order for Cygwin.
*
******************************************************************/

#include <stdio.h>
#include <string.h>
#include <string>

#include <uhttp/net/HostInterface.h>
#include <cybergarage/xml/Parser.h>
#include <uhttp/http/HTTPRequest.h>

#if !defined(WIN32) && !defined(HAVE_FOPEN) && !defined(TENGINE) && !defined(ITRON) && !defined(BTRON)
#include <fcntl.h>
#include <unistd.h>
#endif

using namespace std;
using namespace CyberXML;
using namespace uHTTP;
using namespace uHTTP;

////////////////////////////////////////////////////////////////////////////////////////////////t
//  parse (File)
////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 

Node *Parser::parse(uHTTP::File *file) {
  const char *filename = file->getName();
#if defined(WIN32) || defined(HAVE_FOPEN)
  FILE *fp = fopen(filename, "r");
  if (!fp)
    return NULL;
#else
  int fd = open(filename, O_RDONLY);
  if (fd == -1)
    return NULL;
#endif
  char readBuf[PARSER_DEFAULT_READ_BUF_SIZE+1];
  string contents;
#if defined(WIN32) || defined(HAVE_FOPEN)
  int nRead = fread(readBuf, sizeof(char), PARSER_DEFAULT_READ_BUF_SIZE, fp);
  while (0 < nRead) {
    readBuf[nRead] = '\0';
    //cout << readBuf << endl;
    contents += readBuf;
    nRead = fread(readBuf, sizeof(char), PARSER_DEFAULT_READ_BUF_SIZE, fp);
  }  
  fclose(fp);
#else
  ssize_t nRead = read(fd, readBuf, PARSER_DEFAULT_READ_BUF_SIZE);
  while (0 < nRead) {
    readBuf[nRead] = '\0';
    //cout << readBuf << endl;
    contents += readBuf;
    nRead = read(fd, readBuf, PARSER_DEFAULT_READ_BUF_SIZE);
  }  
  close(fd);
#endif
  //cout << contents << endl;
  return parse(&contents);
}

#endif

////////////////////////////////////////////////////////////////////////////////////////////////t
//  parse (URL)
////////////////////////////////////////////////////////////////////////////////////////////////

Node *Parser::parse(uHTTP::URL *url) {
  const char *host = url->getHost();
  int port = url->getPort();
  const char *uri = url->getPath();
  HTTPRequest httpReq;
  httpReq.setMethod(HTTP::GET);
  httpReq.setURI(uri);
  HTTPResponse *httpRes = httpReq.post(host, port);
  if (httpRes->isSuccessful() == false)
    return NULL;
  const char *contents = httpRes->getContent();
  return parse(contents);
}
