/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: FormatList
*
*	Revision;
*
*	03/24/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_FORMATLIST_H_
#define _CLINK_MEDIA_FORMATLIST_H_

#include <uhttp/util/Vector.h>
#include <uhttp/io/File.h>

namespace CyberLink {

class Format;

class FormatList : public uHTTP::Vector
{

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	FormatList() 
	{
	}

	~FormatList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	Format *getFormat(int n)
	{
		return (Format *)Vector::get(n);
	}

	Format *getFormat(const std::string &type);

	Format *getFormat(uHTTP::File *file);

	////////////////////////////////////////////////
	// clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif


