/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SearchCriteriaList.cpp
*
*	Revision;
*
*	08/06/04
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/SearchCap.h>
#include <cybergarage/upnp/media/server/object/SearchCapList.h>
#include <cybergarage/upnp/media/server/object/SearchCapList.h>
#include <cybergarage/upnp/media/server/object/SearchCriteriaList.h>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// compare
////////////////////////////////////////////////

bool SearchCriteriaList::compare(ContentNode *cnode, SearchCapList *searchCapList)
{
	int n;
	int searchCriCnt = size();
	
	// Set compare result
	for (n=0; n<searchCriCnt; n++) {
		SearchCriteria *searchCri = getSearchCriteria(n);
		const char *property = searchCri->getProperty();
		if (property == NULL) {
			searchCri->setResult(true);
			continue;
		}
		SearchCap *searchCap = searchCapList->getSearchCap(property);
		if (searchCap == NULL) {
			searchCri->setResult(true);
			continue;
		}
		bool cmpResult = searchCap->compare(searchCri, cnode);
		searchCri->setResult(cmpResult);
	}

	// Eval only logical ADD operation at first;
	SearchCriteriaList orSearchCriList;
	for (n=0; n<searchCriCnt; n++) {
		SearchCriteria *currSearchCri = getSearchCriteria(n);
		if (n<(searchCriCnt-1)) {
			if (currSearchCri->isLogicalAND() == true) {
				SearchCriteria *nextSearchCri = getSearchCriteria(n+1);
				bool currResult = currSearchCri->getResult();
				bool nextResult = nextSearchCri->getResult();
				bool logicalAND = (currResult & nextResult) ? true : false;
				nextSearchCri->setResult(logicalAND);
				continue;
			}
		}
		SearchCriteria *orSearchCri = new SearchCriteria(currSearchCri);
		orSearchCriList.add(orSearchCri);
	}

	// Eval logical OR operation;
	int orSearchCriCnt = orSearchCriList.size();
	for (n=0; n<orSearchCriCnt; n++) {
		SearchCriteria *searchCri = getSearchCriteria(n);
		if (searchCri->getResult() == true)
			return true;
	}

	return false;
}

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void SearchCriteriaList::clear() 
{
	int nSort = size();
	for (int n=0; n<nSort; n++) {
		SearchCriteria *searchCri = getSearchCriteria(n);
		delete searchCri;
	}
	Vector::clear();
}
