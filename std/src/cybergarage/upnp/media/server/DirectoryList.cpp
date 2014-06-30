/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: DirectoryList.cpp
*
*	Revision;
*
*	03/23/04
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/media/server/DirectoryList.h>

using namespace CyberLink;

////////////////////////////////////////////////
// getDirectory
////////////////////////////////////////////////

Directory *DirectoryList::getDirectory(const char *name)
{
	if (name == NULL)
		return NULL;
	std::string nameStr = name;
	int dirCnt = (int)size();
	for (int n=0; n<dirCnt; n++) {
		Directory *dir = getDirectory(n);
		const char *dirName = dir->getFriendlyName();
		if (dirName == NULL)
			continue;
		if (nameStr.compare(dirName) == 0)
			return dir;
	}
	return NULL;
}

////////////////////////////////////////////////
//	clear
////////////////////////////////////////////////

void DirectoryList::clear() 
{
	int nProp = (int)size();
	for (int n=0; n<nProp; n++) {
		Directory *dir = getDirectory(n);
		delete dir;
	}
	Vector::clear();
}

////////////////////////////////////////////////
// update
////////////////////////////////////////////////

void DirectoryList::update()
{
	int dirCnt = (int)size();
	for (int n=0; n<dirCnt; n++) {
		Directory *dir = getDirectory(n);
		dir->update();
	}
}
