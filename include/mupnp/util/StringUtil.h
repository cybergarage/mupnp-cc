/******************************************************************
*
*	CyberUtil for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: StringUtil.h
*
*	Revision;
*
*	03/27/03
*		- first revision
*
******************************************************************/

#ifndef _CUTIL_STRINGUTIL_H_
#define _CUTIL_STRINGUTIL_H_

#include <string>
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
#include <iostream>
#endif

namespace CyberUtil {

////////////////////////////////////////////////////////////////////////////////////////////////
//	String Class
////////////////////////////////////////////////////////////////////////////////////////////////

class  String
{

	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////

public:

	static const int INT_STRING_MAXSIZE;
	static const int LONG_STRING_MAXSIZE;
	static const int LONGLONG_STRING_MAXSIZE;
	
	////////////////////////////////////////////////
	//	Member
	////////////////////////////////////////////////

private:

	std::string	mValue;

	
public:

	String();
	String(const char *value);
	String(const char *value, int offset, int count);
	String(std::string &value);

	~String();

	String operator=(String value);
	String operator=(std::string value);
	String operator=(const char *value);
	String operator+(String value);
	String operator+(std::string value);
	String operator+(const char *value);

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	friend std::ostream& operator<<(std::ostream &s, String &value);
	friend std::ostream& operator<<(std::ostream &s, String *value);
#endif

	void setValue(const char *value);
	void setValue(const char *value, int offset, int count);
	void append(const char *value);
	void append(const char c);

	const char *getValue();
	void clear();

	int length();

	char charAt(int  index);
	int indexOf(const char *value);

	const char *toUppderCase();
	const char *toLowerCase();
	const char *trim();

	int compareTo(const char *anotherString);
	int compareToIgnoreCase(const char *anotherString);

	bool equals(const char *anotherString) {return compareTo(anotherString) == 0 ? true : false; }
	bool equalsIgnoreCase(const char *anotherString) {return compareToIgnoreCase(anotherString) == 0 ? true : false; }

	void concat(const char *str);
	void copyValueOf(const char *data);
	void copyValueOf(const char  *data, int  offset, int count);

	int regionMatches(int toffset, const char *other, int ooffset, int len);
	int regionMatchesIgnoreCase(int toffset, const char *other, int ooffset, int len);

	bool startsWith(const char *prefix);
	bool startsWith(String &str) {return startsWith(str.getValue());}

	bool endsWith(const char *suffix);
	bool endsWith(String &str) {return endsWith(str.getValue());}

	const char *substring(int idx, int len, String &buf);
};

////////////////////////////////////////////////////////////////////////////////////////////////
//	String Functions
////////////////////////////////////////////////////////////////////////////////////////////////

bool StringHasData(const char *value);
int StringLength(const char *value);
bool StringEquals(const char *value1, const char *value2);
bool StringEqualsIgnoreCase(const char *value1, const char *value2);
bool StringStartsWith(const char *value, const char *startsWith);
bool StringEndsWith(const char *value, const char *endsWith);
bool StringStartsWith(const char *value, const char startsWith);
bool StringEndsWith(const char *value, const char endsWith);
int StringIndexOf(const char *value, char c);

int String2Integer(const char *value);
int HexString2Integer(const char *value);
long String2Long(const char *value);
long HexString2Long(const char *value);
#if defined(__USE_ISOC99)
long long String2LongLong(const char *value);
#elif defined(WIN32)
__int64 String2LongLong(const char *value);
#endif

const char *Integer2String(int value, std::string &valueBuf);
const char *Integer2HexString(int value, std::string &valueBuf);
const char *Long2String(long value, std::string &valueBuf);
const char *Long2HexString(long value, std::string &valueBuf);
#if defined(__USE_ISOC99)
const char *LongLong2String(long long value, std::string &valueBuf);
const char *LongLong2HexString(long long value, std::string &valueBuf);
#elif defined(WIN32)
const char *LongLong2String(__int64 value, std::string &valueBuf);
const char *LongLong2HexString(__int64 value, std::string &valueBuf);
#endif

const char *StringTrim(const char *value, const char *trimChars, std::string &buf);
const char *StringTrim(const char *value, std::string &buf);

const char *StringToUpperCase(std::string &str);
const char *StringToLowerCase(std::string &str);
const char *StringReplaceChars(std::string &str, const char *fromChars, const char *toChanrs);

}

#endif


