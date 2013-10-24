/******************************************************************
*
*	CyberHTTP for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: HTTPHeader.cpp
*
*	Revision;
*
*	03/22/03
*		- first revision
*	05/26/04
*		- Jan Newmarch <jan.newmarch@infotech.monash.edu.au> (05/26/04)
*		- Fixed getValue() to compare using String::equals() instead of String::startWidth().
*
******************************************************************/

#include <stdlib.h>

#include <string>
#include <cybergarage/http/HTTPHeader.h>
#include <cybergarage/util/StringUtil.h>
#include <cybergarage/io/StringReader.h>

using namespace std;
using namespace CyberHTTP;
using namespace CyberIO;
using namespace CyberUtil;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

HTTPHeader::HTTPHeader(const char *lineStr)
{
	if (StringHasData(lineStr) == false)
		return;

	int colonIdx = StringIndexOf(lineStr, ':');
	if (colonIdx < 0)
		return;

	string strLine = lineStr;
	String name = strLine.substr(0, colonIdx).c_str();
	String value = strLine.substr(colonIdx+1, strLine.length()-colonIdx-1).c_str();

	setName(name.trim());
	setValue(value.trim());
}

HTTPHeader::HTTPHeader(const char *name, const char *value)
{
	setName(name);
	setValue(value);
}

HTTPHeader::HTTPHeader(HTTPHeader *header)
{
	setName(header->getName());
	setValue(header->getValue());
}

HTTPHeader::~HTTPHeader()
{
}

////////////////////////////////////////////////
//	HTTPHeaderGetValue
////////////////////////////////////////////////
	
const char *CyberHTTP::HTTPHeaderGetValue(LineNumberReader *reader, const char *name, std::string &buf)
{
	buf = "";
	String bigName = name;
	bigName.toUppderCase();
	const char *lineStr = reader->readLine();
	while (lineStr != NULL&& 0 < StringLength(lineStr)) {
		HTTPHeader header(lineStr);
		if (header.hasName() == false) {
			 lineStr = reader->readLine();
			continue;
		}
		String bigLineHeaderName = header.getName();
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

const char *CyberHTTP::HTTPHeaderGetValue(const char *data, const char *name, std::string &buf)
{
	if (StringHasData(data) == false) {
		buf = "";
		return buf.c_str();
	}
	StringReader strReader(data);
	LineNumberReader lineReader(&strReader);
	return HTTPHeaderGetValue(&lineReader, name, buf);
}

int CyberHTTP::HTTPHeaderGetIntegerValue(const char *data, const char *name)
{
	std::string buf;
	return atoi((HTTPHeaderGetValue(data, name, buf)));
}
