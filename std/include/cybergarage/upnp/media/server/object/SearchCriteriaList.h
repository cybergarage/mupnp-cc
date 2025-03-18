/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: SearchCriteriaList.h
*
*	Revision:
*
*	08/06/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_SEARCHCRITERIALIST_H_
#define _CLINK_MEDIA_SEARCHCRITERIALIST_H_

#include <mupnp/util/Vector.h>
#include <mupnp/upnp/media/server/object/SearchCriteria.h>

namespace CyberLink {

class SearchCapList;
class ContentNode;

class SearchCriteriaList : public CyberUtil::Vector
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
public:

	SearchCriteriaList() 
	{
	}
	
	~SearchCriteriaList() 
	{
		clear();
	}

	////////////////////////////////////////////////
	//	get
	////////////////////////////////////////////////

public:

	SearchCriteria *getSearchCriteria(int n)
	{
		return (SearchCriteria *)Vector::get(n);
	}

	////////////////////////////////////////////////
	// compare
	////////////////////////////////////////////////

public:

	bool compare(ContentNode *cnode, SearchCapList *searchCapList);

	////////////////////////////////////////////////
	//	clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif
