/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: SearchCap.h
*
*	Revision;
*
*	08/07/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_SEARCHCAP_H_
#define _CLINK_MEDIA_SEARCHCAP_H_

namespace CyberLink {

class ContentNode;
class SearchCriteria;

class SearchCap
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:
		SearchCap()
		{
		}

		virtual ~SearchCap()
		{
		}

	////////////////////////////////////////////////
	//	abstruct methods
	////////////////////////////////////////////////

public:

	virtual const char *getPropertyName() = 0;
	virtual bool compare(SearchCriteria *searchCri, ContentNode *conNode) = 0;
};

}

#endif
