/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: SearchCapList.h
*
*	Revision;
*
*	08/07/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_SEARCHCAPLIST_H_
#define _CLINK_MEDIA_SEARCHCAPLIST_H_

#include <cybergarage/util/Vector.h>

namespace CyberLink {

class SearchCap;

class SearchCapList : public CyberUtil::Vector 
{

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	SearchCapList() 
	{
	}

	~SearchCapList() 
	{
		clear();
	}
	
	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	SearchCap *getSearchCap(int n)
	{
		return (SearchCap*)Vector::get(n);
	}

	SearchCap *getSearchCap(const char *propertyName) ;

	////////////////////////////////////////////////
	// clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif



