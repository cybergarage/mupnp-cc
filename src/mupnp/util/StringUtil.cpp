/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <sstream>

#include <mupnp/util/StringUtil.h>

#include <mupnp/platform.h>

#ifdef HAVE_CTYPE_H
#include <ctype.h>
#endif

using namespace std;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

const int String::INT_STRING_MAXSIZE = 16;
const int String::LONG_STRING_MAXSIZE = 32;
const int String::LONGLONG_STRING_MAXSIZE = 32;

////////////////////////////////////////////////
//  String Functions
////////////////////////////////////////////////

String::String()
{
}

String::String(const std::string& value)
{
  setValue(value);
}

String::String(const std::string& value, int offset, int count)
{
  setValue(value, offset, count);
}

String::String(std::string& value)
{
  setValue(value.c_str());
}

String::~String()
{
}

void String::setValue(const std::string& value)
{
  clear();
  if (value.length() <= 0)
    return;
  mValue = value;
}

void String::setValue(const std::string& value, int offset, int count)
{

  if (value.length() < (offset + count))
    return;
  std::string orgValue = value;
  mValue = orgValue.substr(offset, count);
}

void String::append(const std::string& value)
{

  if (value.length() <= 0)
    return;
  mValue.append(value);
}

const char* String::getValue()
{
  return mValue.c_str();
}

void String::clear()
{
  mValue = "";
}

int String::length()
{
  return (int)mValue.length();
}

char String::charAt(int index)
{
  return mValue[index];
}

int String::indexOf(const std::string& value)
{
  return (int)mValue.find(value);
}

void String::append(char c)
{

  char value[2];
  value[0] = c;
  value[1] = '\0';
  append(value);
}

const char* String::toUppderCase()
{
  StringToUpperCase(mValue);
  return getValue();
}

const char* String::toLowerCase()
{
  StringToLowerCase(mValue);
  return getValue();
}

const char* String::trim()
{
  std::string buf;
  StringTrim(getValue(), buf);
  mValue = buf;
  return getValue();
}

int String::compareTo(const std::string& anotherString)
{
  const char* value = getValue();
  if (!value)
    return -1;
  int ret = strcmp(value, anotherString.c_str());
  return ret;
}

int String::compareToIgnoreCase(const std::string& anotherString)
{
  const char* value = getValue();
  if (!value)
    return -1;
  std::string str1(value);
  std::string str2(anotherString);
  StringToUpperCase(str1);
  StringToUpperCase(str2);
  return strcmp(str1.c_str(), str2.c_str());
}

void String::copyValueOf(const std::string& data)
{
  strcpy((char*)data.c_str(), getValue());
}

void String::copyValueOf(const char data[], int offset, int count)
{
  if (!data)
    return;
  const char* value = getValue();
  strncpy((char*)data, &value[offset], count);
}

bool String::startsWith(const std::string& prefix)
{
  if (regionMatches(0, prefix.c_str(), 0, (int)strlen(prefix.c_str())) == 0)
    return true;
  return false;
}

bool String::endsWith(const std::string& suffix)
{
  if (regionMatches(length() - (int)strlen(suffix.c_str()), suffix.c_str(), 0, (int)strlen(suffix.c_str())) == 0)
    return true;
  return false;
}

int String::regionMatchesIgnoreCase(int toffset, const std::string& other, int ooffset, int len)
{
  int n;

  int value1Len = length();
  char* value1 = new char[value1Len + 1];
  strcpy(value1, getValue());
  for (n = 0; n < value1Len; n++)
    value1[n] = (char)toupper(value1[n]);

  size_t value2Len = strlen(other.c_str());
  char* value2 = new char[value2Len + 1];
  strcpy(value2, other.c_str());
  for (n = 0; n < value2Len; n++)
    value2[n] = (char)toupper(value2[n]);

  int ret = regionMatches(toffset, other, ooffset, len);

  delete[] value1;
  delete[] value2;

  return ret;
}

int String::regionMatches(int toffset, const std::string& other, int ooffset, int len)
{
  const char* value = getValue();
  if (!value)
    return -1;
  if (length() < toffset)
    return -1;
  if ((int)strlen(other.c_str()) < ooffset + len)
    return -1;
  if (toffset < 0 || ooffset < 0)
    return -1;
  return strncmp(&value[toffset], &other[ooffset], len);
}

const char* String::substring(int idx, int len, String& buf)
{
  buf = mValue.substr(idx, len);
  return buf.getValue();
}

////////////////////////////////////////////////////
// operator
////////////////////////////////////////////////////

String String::operator=(String other)
{
  if (this == &other)
    return *this;
  setValue(other.getValue());
  return *this;
};

String String::operator=(const std::string& value)
{
  setValue(value);
  return *this;
};

String String::operator=(const char* value)
{
  setValue(value);
  return *this;
};

String String::operator+(String other)
{
  if (this == &other)
    return *this;
  append(other.getValue());
  return *this;
};

String String::operator+(const std::string& value)
{
  append(value);
  return *this;
};

String String::operator+(const char* value)
{
  append(value);
  return *this;
};

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)

std::ostream& uHTTP::operator<<(std::ostream& s, String& value)
{
  return s << value.getValue();
}

std::ostream& uHTTP::operator<<(std::ostream& s, String* value)
{
  return s << value->getValue();
}

#endif

////////////////////////////////////////////////
//  String Functions
////////////////////////////////////////////////

bool uHTTP::StringHasData(const std::string& value)
{
  if (0 < strlen(value.c_str()))
    return true;
  return false;
}

int uHTTP::StringLength(const std::string& value)
{
  return (int)strlen(value.c_str());
}

int uHTTP::String2Integer(const std::string& value)
{
  return atoi(value.c_str());
}

int uHTTP::HexString2Integer(const std::string& value)
{
  return (int)strtol(value.c_str(), NULL, 16);
}

long uHTTP::String2Long(const std::string& value)
{
  return atol(value.c_str());
}

long uHTTP::HexString2Long(const std::string& value)
{
  return strtol(value.c_str(), NULL, 16);
}

size_t uHTTP::String2Sizet(const std::string& value)
{
  return atol(value.c_str());
}

size_t uHTTP::HexString2Sizet(const std::string& value)
{
  return strtol(value.c_str(), NULL, 16);
}

const char* uHTTP::Integer2String(int value, std::string& valueBuf)
{
  // INT_MAX 2147483647
  // UINT_MAX 4294967295U
  char strBuf[String::INT_STRING_MAXSIZE];
#if defined(HAVE_SNPRINTF)
  snprintf(strBuf, sizeof(strBuf) - 1, "%d", value);
#else
  sprintf(strBuf, "%d", value);
#endif
  valueBuf = strBuf;
  return valueBuf.c_str();
}

const char* uHTTP::Long2String(long value, std::string& valueBuf)
{
  // UINT_LONG : 18446744073709551615UL
  // LONG_MAX :  9223372036854775807L
  char strBuf[String::LONG_STRING_MAXSIZE];
#if defined(HAVE_SNPRINTF)
  snprintf(strBuf, sizeof(strBuf) - 1, "%ld", value);
#else
  sprintf(strBuf, "%ld", value);
#endif
  valueBuf = strBuf;
  return valueBuf.c_str();
}

const char* uHTTP::Integer2HexString(int value, std::string& valueBuf)
{
  // INT_MAX 2147483647
  // UINT_MAX 4294967295U
  char strBuf[String::INT_STRING_MAXSIZE];
#if defined(HAVE_SNPRINTF)
  snprintf(strBuf, sizeof(strBuf) - 1, "%x", value);
#else
  sprintf(strBuf, "%x", value);
#endif
  valueBuf = strBuf;
  return valueBuf.c_str();
}

const char* uHTTP::Long2HexString(long value, std::string& valueBuf)
{
  // UINT_LONG : 18446744073709551615UL
  // LONG_MAX :  9223372036854775807L
  char strBuf[String::LONG_STRING_MAXSIZE];
#if defined(HAVE_SNPRINTF)
  snprintf(strBuf, sizeof(strBuf) - 1, "%lx", value);
#else
  sprintf(strBuf, "%lx", value);
#endif
  valueBuf = strBuf;
  return valueBuf.c_str();
}

const char* uHTTP::Sizet2String(size_t value, std::string& valueBuf)
{
  std::stringstream strBuf;
  strBuf << value;
  valueBuf = strBuf.str();
  return valueBuf.c_str();
}

const char* uHTTP::Sizet2HexString(size_t value, std::string& valueBuf)
{
  std::stringstream strBuf;
  strBuf << hex << value;
  valueBuf = strBuf.str();
  return valueBuf.c_str();
}

bool uHTTP::StringEquals(const std::string& value1, const std::string& value2)
{
  if (strcmp(value1.c_str(), value2.c_str()) == 0)
    return true;
  return false;
}

const char* uHTTP::StringToUpperCase(std::string& str)
{
  int len = (int)str.length();
  for (int n = 0; n < len; n++)
    str[n] = toupper(str.at(n));
  return str.c_str();
}

const char* uHTTP::StringToLowerCase(std::string& str)
{
  int len = (int)str.length();
  for (int n = 0; n < len; n++)
    str[n] = tolower(str.at(n));
  return str.c_str();
}
bool uHTTP::StringEqualsIgnoreCase(const std::string& value1, const std::string& value2)
{
  std::string str1(value1);
  std::string str2(value2);
  StringToUpperCase(str1);
  StringToUpperCase(str2);
  return StringEquals(str1.c_str(), str2.c_str());
}

bool uHTTP::StringStartsWith(const std::string& value, const std::string& startsWith)
{
  if (StringHasData(value) == false || StringHasData(startsWith) == false)
    return false;
  int startsLen = StringLength(startsWith);
  int ret = strncmp(value.c_str(), startsWith.c_str(), startsLen);
  if (ret == 0)
    return true;
  return false;
}

bool uHTTP::StringStartsWith(const std::string& value, const char startsWith)
{
  int len = StringLength(value);
  if (len <= 0)
    return false;
  if (value[0] == startsWith)
    return true;
  return false;
}

bool uHTTP::StringEndsWith(const std::string& value, const std::string& endsWith)
{
  if (StringHasData(value) == false || StringHasData(endsWith) == false)
    return false;
  int valueLen = StringLength(value);
  int endsLen = StringLength(endsWith);
  if (valueLen < endsLen)
    return false;
  int ret = strncmp(value.c_str() + (valueLen - endsLen), endsWith.c_str(), endsLen);
  if (ret == 0)
    return true;
  return false;
}

bool uHTTP::StringEndsWith(const std::string& value, const char endsWith)
{
  int len = StringLength(value);
  if (len <= 0)
    return false;
  if (value[len - 1] == endsWith)
    return true;
  return false;
}

int uHTTP::StringIndexOf(const std::string& value, char c)
{
  int len = StringLength(value);
  for (int n = 0; n < len; n++) {
    if (value[n] == c)
      return n;
  }
  return -1;
}

const char* uHTTP::StringTrim(const std::string& value, const std::string& trimChars, std::string& buf)
{
  std::string trimStr = value;
  int spIdx = (int)trimStr.find_first_not_of(trimChars);
  if (spIdx == (int)std::string::npos) {
    buf = trimStr;
    return buf.c_str();
  }
  std::string trimStr2 = trimStr.substr(spIdx, trimStr.length() - spIdx);
  spIdx = (int)trimStr2.find_last_not_of(trimChars);
  if (spIdx == (int)std::string::npos) {
    buf = trimStr2;
    return buf.c_str();
  }
  buf = trimStr2.substr(0, spIdx + 1);
  return buf.c_str();
}

const char* uHTTP::StringTrim(const std::string& value, std::string& buf)
{
  return StringTrim(value, " ", buf);
}

const char* uHTTP::StringReplaceChars(std::string& str, const std::string& fromChars, const std::string& toChanrs)
{
  string::size_type idx = 0;
  string::size_type pos = 0;
  string fromStr = fromChars;
  string toStr = toChanrs;
  while ((idx = str.find(fromStr, pos)) != std::string::npos) {
    str.replace(idx, fromStr.size(), toStr);
    pos = idx + toStr.size();
  }
  return str.c_str();
}
