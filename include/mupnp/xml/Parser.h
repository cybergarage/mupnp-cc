/******************************************************************
 *
 * mUPnP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _MUPMPCC_PARSER_H_
#define _MUPMPCC_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <string>

#include <mupnp/io/File.h>
#include <mupnp/net/URL.h>

#include <mupnp/xml/Node.h>
#include <mupnp/xml/ParserException.h>
#include <mupnp/xml/XML.h>

namespace uXML {

const int PARSER_DEFAULT_READ_BUF_SIZE = 1024;

class Parser {
  public:
  ////////////////////////////////////////////////
  // Constructor
  ////////////////////////////////////////////////

  Parser();
  ~Parser();

  ////////////////////////////////////////////////
  // parse (File)
  ////////////////////////////////////////////////

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
  mupnp_shared_ptr<uXML::Node> parse(uHTTP::File* file);
#endif

  mupnp_shared_ptr<uXML::Node> parse(uHTTP::URL* url);

  mupnp_shared_ptr<uXML::Node> parse(const std::string& data, size_t len);

  mupnp_shared_ptr<uXML::Node> parse(const std::string& data)
  {
    return parse(data, data.length());
  }

  mupnp_shared_ptr<uXML::Node> parse(std::string* data)
  {
    return parse(data->c_str(), data->length());
  }

  mupnp_shared_ptr<uXML::Node> parse(UnicodeStr* data, size_t len)
  {
    return parse((const std::string&)data, len);
  }
};

}

#endif
