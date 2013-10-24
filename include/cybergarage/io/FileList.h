/******************************************************************
*
*	CyberIO for C++
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: FileList.h
*
*	Revision:
*
*	04/15/04
*		- first revision.
*
******************************************************************/

#ifndef _CIO_FILELIST_H_
#define _CIO_FILELIST_H_

#include <cybergarage/util/Vector.h>

namespace CyberIO {

class File;

class FileList : public CyberUtil::Vector 
{

public:
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////
	
	FileList() 
	{
	}

	~FileList() 
	{
		clear();
	}
	
	////////////////////////////////////////////////
	//	Methods
	////////////////////////////////////////////////

public:

	File *getFile(int n)
	{
		return (File*)Vector::get(n);
	}

	////////////////////////////////////////////////
	// clear
	////////////////////////////////////////////////

public:

	void clear();
};

}

#endif



