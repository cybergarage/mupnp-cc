/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: SortCap.h
*
*	Revision;
*
*	03/24/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_SORTCAP_H_
#define _CLINK_MEDIA_SORTCAP_H_

namespace CyberLink {

class ContentNode;

class SortCap
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:
		SortCap()
		{
		}

		virtual ~SortCap()
		{
		}

	////////////////////////////////////////////////
	//	abstruct methods
	////////////////////////////////////////////////

public:

	virtual const char *getType() = 0;
	virtual int compare(ContentNode *conNode1, ContentNode *conNode2) = 0;
};

}

#endif
