/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : BrowseAction.cpp
*
*	Revision:
*
*	04/03/04
*		- first revision.
*	04/27/04
*		- Changed getObjectID() to return the string value.
*	05/19/04
*		- Changed the header include order for Cygwin.
*
******************************************************************/

#include <cybergarage/upnp/media/server/action/BrowseAction.h>

using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const char *BrowseAction::OBJECT_ID = "ObjectID";
const char *BrowseAction::BROWSE_FLAG = "BrowseFlag";
const char *BrowseAction::FILTER = "Filter";
const char *BrowseAction::STARTING_INDEX = "StartingIndex";
const char *BrowseAction::REQUESTED_COUNT = "RequestedCount";
const char *BrowseAction::SORT_CRITERIA = "SortCriteria";
	
const char *BrowseAction::BROWSE_METADATA = "BrowseMetadata";
const char *BrowseAction::BROWSE_DIRECT_CHILDREN = "BrowseDirectChildren";

const char *BrowseAction::RESULT = "Result";
const char *BrowseAction::NUMBER_RETURNED = "NumberReturned";
const char *BrowseAction::TOTAL_MACHES = "TotalMatches";
const char *BrowseAction::UPDATE_ID = "UpdateID";

