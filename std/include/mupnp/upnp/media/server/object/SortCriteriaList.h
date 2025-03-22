/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: SortCriterionList.h
*
*	Revision:
*
*	04/06/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_SORTCRITERIONLIST_H_
#define _CLINK_MEDIA_SORTCRITERIONLIST_H_

#include <string>
#include <mupnp/util/Vector.h>

namespace CyberLink {

class SortCriteriaList : public CyberUtil::Vector
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
public:

	SortCriteriaList() 
	{
	}
	
	~SortCriteriaList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	const char *getSortCriteria(int n)
	{
		std::string *sortStr = (std::string *)get(n);
		return sortStr->c_str();
	}

	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif
