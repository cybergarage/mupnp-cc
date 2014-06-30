/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SortCriterionList.cpp
*
*	Revision;
*
*	08/13/03
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/SortCriteriaList.h>

using namespace std;
using namespace CyberLink;

///////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void SortCriteriaList::clear() 
{
	int nSort = size();
	for (int n=0; n<nSort; n++) {
		std::string *sortStr = (std::string *)get(n);
		delete sortStr;
	}
	Vector::clear();
}
