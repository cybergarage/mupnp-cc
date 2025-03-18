/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_UTIL_STRINGUTIL_H_
#define _UHTTP_UTIL_STRINGUTIL_H_

#include <string>
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
#include <iostream>
#endif

namespace uHTTP {
////////////////////////////////////////////////////////////////////////////////////////////////
//  String Class
////////////////////////////////////////////////////////////////////////////////////////////////

class String {
  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////

  public:
  static const int INT_STRING_MAXSIZE;
  static const int LONG_STRING_MAXSIZE;
  static const int LONGLONG_STRING_MAXSIZE;

  ////////////////////////////////////////////////
  //  Member
  ////////////////////////////////////////////////

  private:
  std::string mValue;

  public:
  String();
  String(const std::string& value);
  String(const std::string& value, int offset, int count);
  String(std::string& value);

  ~String();

  String operator=(String value);
  String operator=(const std::string& value);
  String operator=(const char* value);
  String operator+(String value);
  String operator+(const std::string& value);
  String operator+(const char* value);

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE)
  friend std::ostream& operator<<(std::ostream& s, String& value);
  friend std::ostream& operator<<(std::ostream& s, String* value);
#endif

  void setValue(const std::string& value);
  void setValue(const std::string& value, int offset, int count);
  void append(const std::string& value);
  void append(const char c);

  const char* getValue();
  void clear();

  int length();

  char charAt(int index);
  int indexOf(const std::string& value);

  const char* toUppderCase();
  const char* toLowerCase();
  const char* trim();

  int compareTo(const std::string& anotherString);
  int compareToIgnoreCase(const std::string& anotherString);

  bool equals(const std::string& anotherString) { return compareTo(anotherString) == 0 ? true : false; }
  bool equalsIgnoreCase(const std::string& anotherString) { return compareToIgnoreCase(anotherString) == 0 ? true : false; }

  void concat(const std::string& str);
  void copyValueOf(const std::string& data);
  void copyValueOf(const char* data, int offset, int count);

  int regionMatches(int toffset, const std::string& other, int ooffset, int len);
  int regionMatchesIgnoreCase(int toffset, const std::string& other, int ooffset, int len);

  bool startsWith(const std::string& prefix);
  bool startsWith(String& str) { return startsWith(str.getValue()); }

  bool endsWith(const std::string& suffix);
  bool endsWith(String& str) { return endsWith(str.getValue()); }

  const char* substring(int idx, int len, String& buf);
};

////////////////////////////////////////////////////////////////////////////////////////////////
//  String Functions
////////////////////////////////////////////////////////////////////////////////////////////////

bool StringHasData(const std::string& value);
int StringLength(const std::string& value);
bool StringEquals(const std::string& value1, const std::string& value2);
bool StringEqualsIgnoreCase(const std::string& value1, const std::string& value2);
bool StringStartsWith(const std::string& value, const std::string& startsWith);
bool StringEndsWith(const std::string& value, const std::string& endsWith);
bool StringStartsWith(const std::string& value, const char startsWith);
bool StringEndsWith(const std::string& value, const char endsWith);
int StringIndexOf(const std::string& value, char c);

int String2Integer(const std::string& value);
long String2Long(const std::string& value);
size_t String2Sizet(const std::string& value);

int HexString2Integer(const std::string& value);
long HexString2Long(const std::string& value);
size_t HexString2Sizet(const std::string& value);

const char* Integer2String(int value, std::string& valueBuf);
const char* Integer2HexString(int value, std::string& valueBuf);
const char* Long2String(long value, std::string& valueBuf);
const char* Long2HexString(long value, std::string& valueBuf);
const char* Sizet2String(size_t value, std::string& valueBuf);
const char* Sizet2HexString(size_t value, std::string& valueBuf);

const char* StringTrim(const std::string& value, const std::string& trimChars, std::string& buf);
const char* StringTrim(const std::string& value, std::string& buf);

const char* StringToUpperCase(std::string& str);
const char* StringToLowerCase(std::string& str);
const char* StringReplaceChars(std::string& str, const std::string& fromChars, const std::string& toChanrs);

}

#endif
