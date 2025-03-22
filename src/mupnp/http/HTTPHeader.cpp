/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdlib.h>

#include <mupnp/http/HTTPHeader.h>
#include <mupnp/io/StringReader.h>
#include <mupnp/util/StringUtil.h>
#include <string>

using namespace std;
using namespace uHTTP;
using namespace uHTTP;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

HTTPHeader::HTTPHeader(const std::string& lineStr)
{
  if (lineStr.length() <= 0)
    return;

  int colonIdx = StringIndexOf(lineStr, ':');
  if (colonIdx < 0)
    return;

  String name = lineStr.substr(0, colonIdx);
  String value = lineStr.substr(colonIdx + 1, lineStr.length() - colonIdx - 1);

  setName(name.trim());
  setValue(value.trim());
}

HTTPHeader::HTTPHeader(const std::string& name, const std::string& value)
{
  setName(name);
  setValue(value);
}

HTTPHeader::HTTPHeader(HTTPHeader* header)
{
  setName(header->getName());
  setValue(header->getValue());
}

HTTPHeader::~HTTPHeader()
{
}

////////////////////////////////////////////////
//  HTTPHeaderGetValue
////////////////////////////////////////////////

const char* uHTTP::HTTPHeaderGetValue(LineNumberReader* reader, const std::string& name, std::string& buf)
{
  buf = "";
  String bigName = name;
  bigName.toUppderCase();
  const char* lineStr = reader->readLine();
  while (lineStr && 0 < StringLength(lineStr)) {
    HTTPHeader header(lineStr);
    if (header.hasName() == false) {
      lineStr = reader->readLine();
      continue;
    }
    String bigLineHeaderName(header.getName());
    bigLineHeaderName.toUppderCase();
    // Thanks for Jan Newmarch <jan.newmarch@infotech.monash.edu.au> (05/26/04)
    if (bigLineHeaderName.equals(bigName.getValue()) == false) {
      lineStr = reader->readLine();
      continue;
    }
    buf = header.getValue();
    break;
  }
  return buf.c_str();
}

const char* uHTTP::HTTPHeaderGetValue(const std::string& data, const std::string& name, std::string& buf)
{
  if (data.length() <= 0) {
    buf = "";
    return buf.c_str();
  }
  StringReader strReader(data);
  LineNumberReader lineReader(&strReader);
  return HTTPHeaderGetValue(&lineReader, name, buf);
}

int uHTTP::HTTPHeaderGetIntegerValue(const std::string& data, const std::string& name)
{
  std::string buf;
  return atoi((HTTPHeaderGetValue(data, name, buf)));
}
