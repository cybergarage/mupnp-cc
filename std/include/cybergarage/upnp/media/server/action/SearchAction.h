/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : SearchAction.h
*
*	Revision:
*
*	04/03/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_SEARCHACTION_H_
#define _CLINK_MEDIA_SEARCHACTION_H_

#include <cybergarage/upnp/Action.h>

#include <string>

namespace CyberLink {

class SearchAction
{
	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////
	
public:

	static const char *CONTAINER_ID;
	static const char *SEARCH_CRITERIA;
	static const char *FILTER;
	static const char *STARTING_INDEX;
	static const char *REQUESTED_COUNT;
	static const char *SORT_CRITERIA;
	
	static const char *RESULT;
	static const char *NUMBER_RETURNED;
	static const char *TOTAL_MACHES;
	static const char *UPDATE_ID;

	////////////////////////////////////////////////
	// Member
	////////////////////////////////////////////////

public:

	Action *action;

	////////////////////////////////////////////////
	// Constrictor
	////////////////////////////////////////////////
	
public:

	SearchAction(Action *action)
	{
		this->action = action;
	}

	////////////////////////////////////////////////
	// getArgument
	////////////////////////////////////////////////

public:

	Argument *getArgument(const char *name)
	{
		return action->getArgument(name);
	}

	////////////////////////////////////////////////
	// Request
	////////////////////////////////////////////////

public:

	const char *getContainerID()
	{
		return action->getArgumentValue(CONTAINER_ID);
	}

	const char *getSearchCriteria()
	{
		return action->getArgumentValue(SEARCH_CRITERIA);
	}


	int getStartingIndex()
	{
		return action->getArgumentIntegerValue(STARTING_INDEX);
	}

	int getRequestedCount()
	{
		return action->getArgumentIntegerValue(REQUESTED_COUNT);
	}
	
	const char *getSortCriteria()
	{
		return action->getArgumentValue(SORT_CRITERIA);
	}

	const char *getFilter()
	{
		return action->getArgumentValue(FILTER);
	}

	////////////////////////////////////////////////
	// Request
	////////////////////////////////////////////////

public:

	void getContainerID(const char *containerID)
	{
		action->setArgumentValue(CONTAINER_ID, containerID);
	}

	void setSearchCriteria(const char *searchCaiteria)
	{
		action->setArgumentValue(SEARCH_CRITERIA, searchCaiteria);
	}

	void setStartingIndex(int idx)
	{
		action->setArgumentValue(STARTING_INDEX, idx);
	}

	void setRequestedCount(int count)
	{
		action->setArgumentValue(REQUESTED_COUNT, count);
	}
	
	void setFilter(const char *filter)
	{
		action->setArgumentValue(FILTER, filter);
	}

	void setSortCriteria(const char *sortCaiteria)
	{
		action->setArgumentValue(SORT_CRITERIA, sortCaiteria);
	}

	////////////////////////////////////////////////
	// Result
	////////////////////////////////////////////////

public:

	void setResult(const char *value)
	{
		action->setArgumentValue(RESULT, value);
	}

	void setNumberReturned(int value)
	{
		action->setArgumentValue(NUMBER_RETURNED, value);
	}

	void setTotalMaches(int value)
	{
		action->setArgumentValue(TOTAL_MACHES, value);
	}

	void setUpdateID(int value)
	{
		action->setArgumentValue(UPDATE_ID, value);
	}

	////////////////////////////////////////////////
	// post
	////////////////////////////////////////////////

public:

	bool postControlAction()
	{
		return action->postControlAction();
	}
};

}

#endif


