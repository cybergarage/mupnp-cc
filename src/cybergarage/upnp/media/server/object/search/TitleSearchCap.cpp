/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: TitleSearchCap.cpp
*
*	Revision;
*
*	08/07/04
*		- first revision.
*
******************************************************************/

#include <string.h>
#include <string>
#include <cybergarage/upnp/media/server/object/ContentNode.h>
#include <cybergarage/upnp/media/server/object/search/TitleSearchCap.h>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// compare
////////////////////////////////////////////////

bool TitleSearchCap::compare(SearchCriteria *searchCri, ContentNode *conNode)
{
	const char *searchCriTitle = searchCri->getValue();
	const char *conTitle = conNode->getTitle();
	if (searchCriTitle == NULL || conTitle == NULL)
			return false;
	int cmpRet = strcmp(conTitle, searchCriTitle);
	if (cmpRet == 0 && (searchCri->isEQ() || searchCri->isLE() || searchCri->isGE()))
			return true;
	else if (cmpRet < 0 && searchCri->isLT())
		return true;
	else if (0 < cmpRet && searchCri->isGT())
		return true;
	string conTitleStr = conTitle;
	int idxRet = (int)conTitleStr.find(searchCriTitle);
	if (0 <= idxRet && searchCri->isContains())
		return true;
	else if (searchCri->isDoesNotContain())
		return true;
	return false;
}

