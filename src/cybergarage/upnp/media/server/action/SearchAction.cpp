/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : SearchAction.cpp
*
*	Revision:
*
*	08/06/04
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/action/SearchAction.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const char *SearchAction::CONTAINER_ID = "ContainerID";
const char *SearchAction::SEARCH_CRITERIA = "SearchCriteria";
const char *SearchAction::FILTER = "Filter";
const char *SearchAction::STARTING_INDEX = "StartingIndex";
const char *SearchAction::REQUESTED_COUNT = "RequestedCount";
const char *SearchAction::SORT_CRITERIA = "SortCriteria";
	
const char *SearchAction::RESULT = "Result";
const char *SearchAction::NUMBER_RETURNED = "NumberReturned";
const char *SearchAction::TOTAL_MACHES = "TotalMatches";
const char *SearchAction::UPDATE_ID = "UpdateID";

