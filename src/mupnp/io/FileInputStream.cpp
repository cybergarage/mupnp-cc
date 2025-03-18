/******************************************************************
*
*	CyberNet for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: FileInputStream.cpp
*
*	Revision;
*
*	04/14/04
*		- first revision
*	05/24/04
*		- Added read(chat *, int).
*	08/29/04
*		- Added skip().
*
******************************************************************/

#include <cybergarage/io/FileInputStream.h>

using namespace CyberIO;

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

FileInputStream::FileInputStream(File *file, const char *mode)
{
	inBuf = new char[FILE_INBUF_SIZE];
	fp = fopen(file->getName(), mode);
	if (fp == NULL)
		return;
}

////////////////////////////////////////////////
//	Destructor
////////////////////////////////////////////////

FileInputStream::~FileInputStream()
{
	delete[] inBuf;
}

////////////////////////////////////////////////
//	read
////////////////////////////////////////////////

int FileInputStream::read(std::string &b, int len)
{
	if (fp == NULL)
		return 0;

	int readCnt = 0;
	while (readCnt < len) {
		int readSize = len - readCnt;
		if (FILE_INBUF_SIZE < readSize)
			readSize = FILE_INBUF_SIZE;
		int readLen = fread(inBuf, sizeof(char), readSize, fp);
		if (readLen <= 0)
			break;
		if (0 < readLen) {
			b.append(inBuf, 0, readLen);
			readCnt += readLen;
		}
	}
	return readCnt;
}

int FileInputStream::read(char *b, int len)
{
	if (fp == NULL)
		return 0;

	int readCnt = 0;
	while (readCnt < len) {
		int readSize = len - readCnt;
		int readLen = fread(b+readCnt, sizeof(char), readSize, fp);
		if (readLen <= 0)
			break;
		readCnt += readLen;
	}
	return readCnt;
}

////////////////////////////////////////////////
//	unread
////////////////////////////////////////////////

void FileInputStream::unread(std::string &b, int off, int len)
{
	// Not Implemented
}

////////////////////////////////////////////////
//	skip
////////////////////////////////////////////////

long FileInputStream::skip(long n)
{
	if (fp == NULL)
		return 0;
	int ret = fseek(fp, n, SEEK_CUR);
	return (ret == 0) ? n : 0;
}

////////////////////////////////////////////////
//	close
////////////////////////////////////////////////

void FileInputStream::close()
{
	if (fp == NULL)
		return;
	fclose(fp);
}
