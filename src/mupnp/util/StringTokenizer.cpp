/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/util/StringTokenizer.h>

#include <string.h>

using namespace std;
using namespace uHTTP;

StringTokenizer::StringTokenizer(const std::string& str, const std::string& delim)
{
  hasNextTokens = true;
  strBuf = str;
  strDelim = delim;
  lastDelimPos = string::npos;

  nextToken(delim);
}

StringTokenizer::~StringTokenizer()
{
}

bool StringTokenizer::hasMoreTokens()
{
  return hasNextTokens;
}

const char* StringTokenizer::nextToken()
{
  return nextToken(strDelim.c_str());
}

const char* StringTokenizer::nextToken(const std::string& delim)
{
  strCurrToken = strNextToken;

  string::size_type findStartDelimPos = (lastDelimPos == string::npos) ? 0 : (lastDelimPos + 1);
  string::size_type startDelimPos = strBuf.find_first_not_of(delim, findStartDelimPos);
  if (startDelimPos == string::npos) {
    hasNextTokens = false;
    strNextToken = "";
    return strCurrToken.c_str();
  }

  string::size_type endDelimPos = strBuf.find_first_of(delim, startDelimPos);
  if (endDelimPos == string::npos)
    endDelimPos = strBuf.length();
  strNextToken = strBuf.substr(startDelimPos, endDelimPos - startDelimPos);

  lastDelimPos = endDelimPos;

  return strCurrToken.c_str();
}
