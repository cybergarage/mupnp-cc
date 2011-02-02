/******************************************************************
*
*	CyberIO for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: FileInputStream.h
*
*	Revision;
*
*	04/14/04
*		- first revision
*
******************************************************************/

#ifndef _CIO_FILEINPUTSTREAM_H_
#define _CIO_FILEINPUTSTREAM_H_

#include <stdio.h>
#include <string>
#include <cybergarage/io/File.h>
#include <cybergarage/io/InputStream.h>

namespace CyberIO {

const long FILE_INBUF_SIZE = 512*1024;

class FileInputStream : public InputStream
{
	FILE *fp;
	char *inBuf;

public:

	FileInputStream(File *file, const char *mode);
	~FileInputStream();

	int read(std::string &b, int len);
	int read(char *b, int len);

	void unread(std::string &b, int off, int len);  // Not Implemented

	long skip(long n);

	void close();
};

}

#endif
