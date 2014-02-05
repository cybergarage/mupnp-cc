/******************************************************************
*
*  CyberXML for C++
*
*  Copyright (C) Satoshi Konno 2002-2003
*
*  File:  Parser.h
*
*  Revision;
*
*  05/20/03
*    - first revision
*
******************************************************************/

#ifndef _CXML_PARSER_H_
#define _CXML_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <string>
#include <cybergarage/xml/XML.h>
#include <cybergarage/xml/Node.h>
#include <uhttp/io/File.h>
#include <uhttp/net/URL.h>
#include <cybergarage/xml/ParserException.h>

namespace CyberXML {
const int PARSER_DEFAULT_READ_BUF_SIZE = 1024;

class Parser  {
 public:
  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

  Parser();
  ~Parser();

  ////////////////////////////////////////////////
  //  parse (File)
  ////////////////////////////////////////////////

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
  Node *parse(uHTTP::File *file);
#endif

  Node *parse(uHTTP::URL *url);
  
  Node *parse(const std::string &data, size_t len);

  Node *parse(const std::string &data) {
    return parse(data, data.length());
  }
  
  Node *parse(std::string *data) {
    return parse(data->c_str(), data->length());
  }
  
  Node *parse(UnicodeStr *data, size_t len) {
    return parse((const std::string &)data, len);
  }
};

}

#endif
