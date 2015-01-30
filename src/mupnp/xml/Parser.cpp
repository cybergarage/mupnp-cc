/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <string.h>
#include <string>

#include <uhttp/net/HostInterface.h>
#include <mupnp/xml/Parser.h>
#include <uhttp/http/HTTPRequest.h>

#if !defined(WIN32) && !defined(HAVE_FOPEN) && !defined(TENGINE) && !defined(ITRON) && !defined(BTRON)
#include <fcntl.h>
#include <unistd.h>
#endif

using namespace std;
using namespace uXML;
using namespace uHTTP;

////////////////////////////////////////////////////////////////////////////////////////////////t
// parse (File)
////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 

mupnp_shared_ptr<uXML::Node> Parser::parse(uHTTP::File *file) {
  const char *filename = file->getName();
#if defined(WIN32) || defined(HAVE_FOPEN)
  FILE *fp = fopen(filename, "r");
  if (!fp)
    return nullptr;
#else
  int fd = open(filename, O_RDONLY);
  if (fd == -1)
    return nullptr;
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
// parse (URL)
////////////////////////////////////////////////////////////////////////////////////////////////

mupnp_shared_ptr<uXML::Node> Parser::parse(uHTTP::URL *url) {
  const char *host = url->getHost();
  int port = url->getPort();
  const char *uri = url->getPath();
  HTTPRequest httpReq;
  httpReq.setMethod(HTTP::GET);
  httpReq.setURI(uri);
  HTTPResponse *httpRes = httpReq.post(host, port);
  if (httpRes->isSuccessful() == false)
    return nullptr;
  const char *contents = httpRes->getContent();
  return parse(contents);
}
