/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: StringUtil.cpp
*
*	Revision;
*
*	03/27/03
*		- first revision
*	12/16/04
*		- Added support for BTRON
*		- Added support not to use ostringstream
*	03/03/05
*		- Changed the following methods not to use iostream for TRON.
*		  Integer2String(), Long2String().
*	11/09/05
*		- Added String2LongLong(), LongLong2String() and LongLong2HexString().
*
******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <cybergarage/util/StringUtil.h>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef HAVE_CTYPE_H
#  include <ctype.h>
#endif

using namespace std;
using namespace CyberUtil;

////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////

const int String::INT_STRING_MAXSIZE = 16;
const int String::LONG_STRING_MAXSIZE = 32;
const int String::LONGLONG_STRING_MAXSIZE = 32;

////////////////////////////////////////////////
//	String Functions
////////////////////////////////////////////////

String::String() 
{
}

String::String(const char *value) 
{
	setValue(value);
}

String::String(const char *value, int offset, int count) 
{
	setValue(value, offset, count);
}

String::String(std::string &value) 
{
	setValue(value.c_str());
}

String::~String() 
{
}

void String::setValue(const char *value)
{
	clear();
	if (!value)
		return;
	if (strlen(value) <= 0)
		return;
	mValue = value;
}

void String::setValue(const char *value, int offset, int count) 
{ 
	if (!value && (int)strlen(value) < (offset + count)) 
		return;
	std::string orgValue = value;
	mValue = orgValue.substr(offset, count);
}

void String::append(const char *value)
{ 
	if (!value)
		return;
	if (strlen(value) <= 0)
		return;
	mValue.append(value);
}

const char *String::getValue() 
{
	return (const char *)mValue.c_str();
}

void String::clear() 
{
	mValue = "";
}

int String::length() 
{
	return (int)mValue.length();
}

char String::charAt(int  index) 
{
	return mValue[index];
}

int String::indexOf(const char *value)
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

const char *String::toUppderCase()
{
	StringToUpperCase(mValue);
	return getValue();
}

const char *String::toLowerCase()
{
	StringToLowerCase(mValue);
	return getValue();
}

const char *String::trim()
{
	std::string buf;
	StringTrim(getValue(), buf);
	mValue = buf;
	return getValue();
}

int String::compareTo(const char *anotherString)
{
	const char *value = getValue();
	if (!value || !anotherString)
		return -1;
	int ret = strcmp(value, anotherString);
	return ret;
}

int String::compareToIgnoreCase(const char *anotherString) 
{
	const char *value = getValue();
	if (!value || !anotherString)
		return -1;
	std::string str1(value);
	std::string str2(anotherString);
	StringToUpperCase(str1);
	StringToUpperCase(str2);
	return strcmp(str1.c_str(), str2.c_str());
}

void String::copyValueOf(const char *data) 
{
	if (!data)
		return;
	strcpy((char *)data, getValue());
}

void String::copyValueOf(const char  data[], int  offset, int count)
{
	if (!data)
		return;
	const char *value = getValue();
	strncpy((char *)data, &value[offset], count);
}

bool String::startsWith(const char *prefix) 
{
	if (!prefix)
		return false;
	if (regionMatches(0, prefix, 0, (int)strlen(prefix)) == 0)
			return true;
	return false;
}

bool String::endsWith(const char *suffix) 
{
	if (!suffix)
		return false;
	if (regionMatches(length()-(int)strlen(suffix), suffix, 0, (int)strlen(suffix)) == 0)
		return true;
	return false;
}

int String::regionMatchesIgnoreCase(int toffset, const char *other, int ooffset, int len)
{
	if (!other)
		return -1;

	int n;

	int value1Len = length();
	char *value1 = new char[value1Len+1];
	strcpy(value1, getValue());
	for (n=0; n<value1Len; n++)
		value1[n] = (char)toupper(value1[n]);

	int value2Len = strlen(other);
	char *value2 = new char[value2Len+1]; 
	strcpy(value2, other);
	for (n=0; n<value2Len; n++)
		value2[n] = (char)toupper(value2[n]);
		
	int ret = regionMatches(toffset, other, ooffset, len);

	delete value1;
	delete value2;

	return ret;
}

int String::regionMatches(int toffset, const char *other, int ooffset, int len) 
{
	const char *value = getValue();
	if (!value || !other)
		return -1;
	if (length() < toffset)
		return -1;
	if ((int)strlen(other) < ooffset + len)
		return -1;
	if (toffset<0 || ooffset<0)
		return -1;
	return strncmp(&value[toffset], &other[ooffset], len);
}

const char *String::substring(int idx, int len, String &buf)
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

String String::operator=(std::string other)
{
	setValue(other.c_str());
	return *this;
};

String String::operator=(const char *value)
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

String String::operator+(std::string other)
{
	append(other.c_str());
	return *this;
};

String String::operator+(const char *value)
{
	append(value);
	return *this;
};

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 

std::ostream& CyberUtil::operator<<(std::ostream &s, String &value)
{
	return s << value.getValue();
}

std::ostream& CyberUtil::operator<<(std::ostream &s, String *value)
{
	return s << value->getValue();
}

#endif

////////////////////////////////////////////////
//	String Functions
////////////////////////////////////////////////

bool CyberUtil::StringHasData(const char *value)
{
	if (value == NULL)
		return false;
	if (0 < strlen(value))
		return true;
	return false;
}

int CyberUtil::StringLength(const char *value)
{
	if (value == NULL)
		return 0;
	return (int)strlen(value);
}

int CyberUtil::String2Integer(const char *value)
{
	if (value == NULL)
		return 0;
	return atoi(value);
}

int CyberUtil::HexString2Integer(const char *value)
{
	if (value == NULL)
		return 0;
	return (int)strtol(value, NULL, 16);
}

long CyberUtil::String2Long(const char *value)
{
	if (value == NULL)
		return 0;
	return atol(value);
}

long CyberUtil::HexString2Long(const char *value)
{
	if (value == NULL)
		return 0;
	return strtol(value, NULL, 16);
}

#if defined(__USE_ISOC99) || defined (WIN32)

#if defined(__USE_ISOC99)
long long CyberUtil::String2LongLong(const char *value)
#else
__int64 CyberUtil::String2LongLong(const char *value)
#endif
{
	if (value == NULL)
		return 0;
#if defined(WIN32)
		return _atoi64(value);
#else
	return atoll(value);
#endif
}

#endif

const char *CyberUtil::Integer2String(int value, std::string &valueBuf)
{
	// INT_MAX 2147483647
 	// UINT_MAX 4294967295U
	char strBuf[String::INT_STRING_MAXSIZE];
#if defined(HAVE_SNPRINTF)
	snprintf(strBuf, sizeof(strBuf)-1, "%d", value);
#else
	sprintf(strBuf, "%d", value);
#endif
	valueBuf = strBuf;
	return valueBuf.c_str();
}

const char *CyberUtil::Long2String(long value, std::string &valueBuf)
{
	// UINT_LONG : 18446744073709551615UL
	// LONG_MAX :	9223372036854775807L
	char strBuf[String::LONG_STRING_MAXSIZE];
#if defined(HAVE_SNPRINTF)
	snprintf(strBuf, sizeof(strBuf)-1, "%ld", value);
#else
	sprintf(strBuf, "%ld", value);
#endif
	valueBuf = strBuf;
	return valueBuf.c_str();
}

#if defined(__USE_ISOC99) || defined (WIN32)

#if defined(__USE_ISOC99)
const char *CyberUtil::LongLong2String(long long value, std::string &valueBuf)
#else
const char *CyberUtil::LongLong2String(__int64 value, std::string &valueBuf)
#endif
{
	// UINT_LONG : 18446744073709551615UL
	// LONG_MAX :	9223372036854775807L
	char strBuf[String::LONGLONG_STRING_MAXSIZE];
#if defined (WIN32)
	_i64toa(value, strBuf, 10); 
#elif defined (HAVE_SNPRINTF)
	snprintf(strBuf, sizeof(strBuf)-1, "%lld", value);
#else
	sprintf(strBuf, "%lld", value);
#endif
	valueBuf = strBuf;
	return valueBuf.c_str();
}

#endif

const char *CyberUtil::Integer2HexString(int value, std::string &valueBuf)
{
	// INT_MAX 2147483647
 	// UINT_MAX 4294967295U
	char strBuf[String::INT_STRING_MAXSIZE];
#if defined(HAVE_SNPRINTF)
	snprintf(strBuf, sizeof(strBuf)-1, "%x", value);
#else
	sprintf(strBuf, "%x", value);
#endif
	valueBuf = strBuf;
	return valueBuf.c_str();
}

const char *CyberUtil::Long2HexString(long value, std::string &valueBuf)
{
	// UINT_LONG : 18446744073709551615UL
	// LONG_MAX :	9223372036854775807L
	char strBuf[String::LONG_STRING_MAXSIZE];
#if defined(HAVE_SNPRINTF)
	snprintf(strBuf, sizeof(strBuf)-1, "%lx", value);
#else
	sprintf(strBuf, "%lx", value);
#endif
	valueBuf = strBuf;
	return valueBuf.c_str();
}

#if defined(__USE_ISOC99) || defined (WIN32)

#if defined(__USE_ISOC99)
const char *CyberUtil::LongLong2HexString(long long value, std::string &valueBuf)
#else
const char *CyberUtil::LongLong2HexString(__int64 value, std::string &valueBuf)
#endif
{
	// UINT_LONG : 18446744073709551615UL
	// LONG_MAX :	9223372036854775807L
	char strBuf[String::LONGLONG_STRING_MAXSIZE];
#if defined (WIN32)
	_i64toa(value, strBuf, 16); 
#elif defined (HAVE_SNPRINTF)
	snprintf(strBuf, sizeof(strBuf)-1, "%llx", value);
#else
	sprintf(strBuf, "%llx", value);
#endif
	valueBuf = strBuf;
	return valueBuf.c_str();
}

#endif

bool CyberUtil::StringEquals(const char *value1, const char *value2)
{
	if (strcmp(value1, value2) == 0)
		return true;
	return false;
}

const char *CyberUtil::StringToUpperCase(std::string &str)
{
	int len = (int)str.length();
	for (int n=0; n<len; n++)
		str[n] = toupper(str.at(n));
	return str.c_str();
}

const char *CyberUtil::StringToLowerCase(std::string &str)
{
	int len = (int)str.length();
	for (int n=0; n<len; n++)
		str[n] = tolower(str.at(n));
	return str.c_str();
}
bool CyberUtil::StringEqualsIgnoreCase(const char *value1, const char *value2)
{
	std::string str1(value1);
	std::string str2(value2);
	StringToUpperCase(str1);
	StringToUpperCase(str2);
	return StringEquals(str1.c_str(), str2.c_str());
}

bool CyberUtil::StringStartsWith(const char *value, const char *startsWith)
{
	if (StringHasData(value) == false || StringHasData(startsWith) == false)
		return false;
	int startsLen = StringLength(startsWith);
	int ret = strncmp(value, startsWith, startsLen);
	if (ret == 0)
		return true;
	return false;
}

bool CyberUtil::StringStartsWith(const char *value, const char startsWith)
{
	int len = StringLength(value);
	if (len <= 0)
		return false;
	if (value[0] == startsWith)
		return true;
	return false;
}

bool CyberUtil::StringEndsWith(const char *value, const char *endsWith)
{
	if (StringHasData(value) == false || StringHasData(endsWith) == false)
		return false;
	int valueLen = StringLength(value);
	int endsLen = StringLength(endsWith);
	if (valueLen < endsLen)
		return false;
	int ret = strncmp(value + (valueLen - endsLen), endsWith, endsLen);
	if (ret == 0)
		return true;
	return false;
}

bool CyberUtil::StringEndsWith(const char *value, const char endsWith)
{
	int len = StringLength(value);
	if (len <= 0)
		return false;
	if (value[len-1] == endsWith)
		return true;
	return false;
}

int CyberUtil::StringIndexOf(const char *value, char c)
{
	int len = StringLength(value);
	for (int n = 0; n<len; n++) {
		if (value[n] == c)
			return n;
	}
	return -1;
}

const char *CyberUtil::StringTrim(const char *value, const char *trimChars, std::string &buf)
{
	std::string trimStr = value;
	int spIdx =(int) trimStr.find_first_not_of(trimChars);
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
	buf = trimStr2.substr(0, spIdx+1);
	return buf.c_str();
}

const char *CyberUtil::StringTrim(const char *value, std::string &buf)
{
	return StringTrim(value, " ", buf);
}

const char *CyberUtil::StringReplaceChars(std::string &str,  const char *fromChars, const char *toChanrs)
{
	string::size_type idx = 0;
	string::size_type pos = 0;
	string fromStr = fromChars;
	string toStr = toChanrs;
	while ((idx = str.find(fromStr,pos)) != std::string::npos) {
		str.replace(idx,fromStr.size(),toStr);
		pos = idx + toStr.size();
	}
	return str.c_str();
}
