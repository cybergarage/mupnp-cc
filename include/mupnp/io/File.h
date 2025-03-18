/******************************************************************
*
*	CyberIO for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: File.h
*
*	Revision:
*
*	08/13/03
*		- first revision
*	02/08/05
*		- Added save()
*
******************************************************************/

#ifndef _CIO_FILE_H_
#define _CIO_FILE_H_

#include <string>
#include <stdlib.h>

namespace CyberIO {

class FileList;

class File
{
	std::string nameStr;
	std::string parentStr;

	File *absoluteFile;

	////////////////////////////////////////////////
	//	Constants
	////////////////////////////////////////////////

public:

	static const char separatorChar;
	static const char pathSeparatorChar;
	static const char *separator;
	static const char *pathSeparator;
	static const char *O_TEXT;
	static const char *O_BINARY;

	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	File();
	File(const char *fname);
	File(const char *dir, const char *fname);
	File(File *file);

	~File();

	////////////////////////////////////////////////
	//	Name
	////////////////////////////////////////////////

public:

	void setName(const char *fname)
	{
		nameStr = fname;
		if (absoluteFile != NULL) {
			delete absoluteFile;
			absoluteFile = NULL;
		}
	}

	const char *getName()
	{
		return nameStr.c_str();
	}

	////////////////////////////////////////////////
	//	get*
	////////////////////////////////////////////////

public:

	const char *getFileName(std::string &buf);

	File *getAbsoluteFile();

	const char *getParent();

	////////////////////////////////////////////////
	//	exists
	////////////////////////////////////////////////

public:

	static bool exists(const char *name);
	
	bool exists()
	{
		return exists(getName());
	}

	////////////////////////////////////////////////
	//	load
	////////////////////////////////////////////////

public:

	static const char *load(const char *name, std::string &buf);

	const char *load(std::string &buf)
	{
		return load(getName(), buf);
	}

	////////////////////////////////////////////////
	//save
	////////////////////////////////////////////////

public:

	static bool save(const char *name, const char *buf);

	bool save(const char *buf)
	{
		return save(getName(), buf);
	}

	////////////////////////////////////////////////
	//	File Type
	////////////////////////////////////////////////

public:

	const char *getSuffix(std::string &buf);

	static bool isXMLFileName(const char *name);

	////////////////////////////////////////////////
	//	Attributes
	////////////////////////////////////////////////

public:

	long lastModified();
	long length();

	////////////////////////////////////////////////
	//	Compare
	////////////////////////////////////////////////

public:

	bool equals(File *file);

	////////////////////////////////////////////////
	//	FileList
	////////////////////////////////////////////////

public:

	int listFiles(FileList &fileList);

	////////////////////////////////////////////////
	//	is*
	////////////////////////////////////////////////

public:

	bool isDirectory();
	bool isFile();
};

}

#endif
