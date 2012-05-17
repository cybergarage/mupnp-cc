/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: SortCapList.h
*
*	Revision;
*
*	03/24/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_SORTCAPLIST_H_
#define _CLINK_MEDIA_SORTCAPLIST_H_

#include <uhttp/util/Vector.h>

namespace CyberLink {

class SortCap;

class SortCapList : public uHTTP::Vector 
{

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	SortCapList() 
	{
	}

	~SortCapList() 
	{
		clear();
	}
	
	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	SortCap *getSortCap(int n)
	{
		return (SortCap*)Vector::get(n);
	}

	SortCap *getSortCap(const std::string &type) ;

	////////////////////////////////////////////////
	// clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif



