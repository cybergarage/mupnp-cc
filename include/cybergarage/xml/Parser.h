/******************************************************************
*
*	CyberXML for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File:	Parser.h
*
*	Revision;
*
*	05/20/03
*		- first revision
*
******************************************************************/

#ifndef _CXML_PARSER_H_
#define _CXML_PARSER_H_

#include <stdio.h>
#include <string.h>
#include <string>
#include <cybergarage/xml/XML.h>
#include <cybergarage/xml/Node.h>
<<<<<<< HEAD
#include <uhttp/io/File.h>
#include <uhttp/net/URL.h>
=======
#include <cybergarage/io/File.h>
#include <cybergarage/net/URL.h>
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
#include <cybergarage/xml/ParserException.h>

namespace CyberXML {

const int PARSER_DEFAULT_READ_BUF_SIZE = 1024;

class Parser 
{

public:

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

	Parser();
	~Parser();

	////////////////////////////////////////////////
	//	parse (File)
	////////////////////////////////////////////////

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
<<<<<<< HEAD
	Node *parse(uHTTP::File *file);
#endif

	Node *parse(uHTTP::URL *url);
	
	Node *parse(const std::string &data, int len);

	Node *parse(const std::string &data)
	{
		return parse(data, data.length());
=======
	Node *parse(CyberIO::File *file);
#endif

	Node *parse(CyberNet::URL *url);
	
	Node *parse(const char *data, int len);

	Node *parse(const char *data)
	{
		return parse(data, (int)strlen(data));
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}
	
	Node *parse(std::string *data)
	{
		return parse(data->c_str(), (int)data->length());
	}
	
	Node *parse(UnicodeStr *data, int len)
	{
<<<<<<< HEAD
		return parse((const std::string &)data, len);
=======
		return parse((const char *)data, len);
>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
	}
};

}

#endif
