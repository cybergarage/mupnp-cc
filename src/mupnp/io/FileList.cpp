/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	CyberIO for C++
*
*	Revision;
*
*	04/15/04
*		- first revision.
*
******************************************************************/

#include <cybergarage/io/File.h>
#include <cybergarage/io/FileList.h>

using namespace CyberIO;

////////////////////////////////////////////////
//	Methods
////////////////////////////////////////////////

void FileList::clear() 
{
	int nNode = size();
	for (int n=0; n<nNode; n++) {
		File *file = getFile(n);
		delete file;
	}
	Vector::clear();
}


