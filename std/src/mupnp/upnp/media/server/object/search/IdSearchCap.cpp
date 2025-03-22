/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2002
 *
 *	File: IdSearchCap.cpp
 *
 *	Revision;
 *
 *	08/07/04
 *		- first revision.
 *
 ******************************************************************/

#include <mupnp/upnp/media/server/object/ContentNode.h>
#include <mupnp/upnp/media/server/object/search/IdSearchCap.h>
#include <string.h>
#include <string>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// compare
////////////////////////////////////////////////

bool IdSearchCap::compare(SearchCriteria* searchCri, ContentNode* conNode)
{
  const char* searchCriID = searchCri->getValue();
  const char* conID = conNode->getID();
  if (searchCriID == NULL || conID == NULL)
    return false;
  if (searchCri->isEQ() == true)
    return (strcmp(searchCriID, conID) == 0) ? true : false;
  return false;
}
