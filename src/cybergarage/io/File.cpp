/******************************************************************
*
*	CyberIO for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: File.cpp
*
*	Revision;
*
*	08/18/03
*		- first revision
*	04/14/04
*		- Added the following methods.
*		  lastModified(), length(), equals().
*	04/15/04
*		- Added the following methods.
*		  listFiles(), isDirectory(), isFile();
*	04/19/04
*		- Added File(File *).
*	05/24/04
*		- Added O_TEXT, O_BINARY.
*	06/08/04
*		- Added getSuffix().
*	07/07/04
*		- Bastiaan Van Eeckhoudt <bastiaanve@gmail.com>
*		- Fixed File(dir, name) to add a separator when the dir is not end of the separator.
*	07/07/04
*		- Bastiaan Van Eeckhoudt <bastiaanve@gmail.com>
*		- Pekka Virtanen <pekka.virtanen@gmail.com>
*		- Fixed listFiles to return the valid file name on Unix platform.
*
******************************************************************/

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#include <stdio.h>
#include <string.h>

#if defined(WIN32)
#include <windows.h>
#include <sys/stat.h>
#elif defined(BTRON)
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/dirent.h>
#include <bsys/unixemu.h>
#elif !defined(ITRON) && !defined(TENGINE)
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#endif


#include <cybergarage/io/File.h>
#include <cybergarage/io/FileList.h>

#include <cybergarage/util/StringUtil.h>

using namespace std;
using namespace CyberIO;
using namespace CyberUtil;

////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////

#ifdef WIN32
const char File::separatorChar = '\\';
const char File::pathSeparatorChar = ';';
const char *File::separator = "\\";
const char *File::pathSeparator = ";";
#else
const char File::separatorChar = '/';
const char File::pathSeparatorChar = ':';
const char *File::separator = "/";
const char *File::pathSeparator = ":";
#endif

const char *File::O_TEXT = "rt";
const char *File::O_BINARY= "rb";

////////////////////////////////////////////////
//	Constructor
////////////////////////////////////////////////

File::File()
{
	absoluteFile = NULL;
	setName("");
}

File::File(const char *fname)
{
	absoluteFile = NULL;
	setName(fname);
}

File::File(const char *dir, const char *fname)
{
	absoluteFile = NULL;
	string fullname;
	fullname = dir;
	// Thanks for Bastiaan Van Eeckhoudt <bastiaanve@gmail.com>
	size_t dirLen = strlen(dir);
	if (dir[dirLen-1] != File::separatorChar)
		fullname.append(File::separator);
	fullname.append(fname);
	setName(fullname.c_str());
}

File::File(File *file)
{
	absoluteFile = NULL;
	setName(file->getName());
}

File::~File()
{
	if (absoluteFile != NULL)
		delete absoluteFile;
}

////////////////////////////////////////////////
// exists
////////////////////////////////////////////////

bool File::exists(const char *name)
{
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	FILE *fp = fopen(name, "r");
	if (fp == NULL)
		return false;
	fclose(fp);
	return true;
#elif defined(BTRON)
	int fd = open(name, O_RDONLY);
	if (fd == -1)
		return false;
	close(fd);
	return true;
#else
	return false;
#endif
}

////////////////////////////////////////////////
// load
////////////////////////////////////////////////

const char *File::load(const char *name, string &buf)
{
	const int READ_BUF_SIZE = 1024;
	char readBuf[READ_BUF_SIZE+1];

	buf = "";
	
#if defined(WIN32) || defined(HAVE_FOPEN)
	FILE *fp = fopen(name, "r");
	if (fp == NULL)
		return buf.c_str();
	size_t nread = fread(readBuf, sizeof(char), READ_BUF_SIZE, fp);
	while (0 < nread) {
		readBuf[nread] = '\0';
		buf += readBuf;
		nread = fread(readBuf, sizeof(char), READ_BUF_SIZE, fp);
	}
	fclose(fp);
#elif defined(BTRON)
	int fd = open(name, O_RDONLY);
	if (fd == -1)
		return buf.c_str();
	ssize_t nread = read(fd, readBuf, READ_BUF_SIZE);
	while (0 < nread) {
		readBuf[nread] = '\0';
		buf += readBuf;
		nread = read(fd, readBuf, READ_BUF_SIZE);
	}
	close(fd);
#endif

	return buf.c_str();
}

////////////////////////////////////////////////
// save
////////////////////////////////////////////////

bool File::save(const char *name, const char *buf)
{
	if (buf == NULL)
		return false;

#if defined(WIN32) || defined(HAVE_FOPEN)
	FILE *fp = fopen(name, "wb");
	if (fp == NULL)
		return false;
	size_t bufSize = strlen(buf);
	size_t nWrote = fwrite(buf, sizeof(char), bufSize, fp);
	while (nWrote < bufSize) {
		size_t worteByte = fwrite(buf + nWrote, sizeof(char), (bufSize-nWrote), fp);
		if (worteByte <= 0)
			break;
		nWrote += worteByte;
	}
	fclose(fp);
#elif defined(BTRON)
	int fd = open(name, O_WRONLY);
	if (fd == -1)
		return false;
	size_t bufSize = strlen(buf);
	size_t nWrote = write(fd, buf, bufSize);
	while (nWrote < bufSize) {
		size_t worteByte = write(fd, buf, bufSize);
		if (worteByte <= 0)
			break;
		nWrote += worteByte;
	}
	close(fd);
#endif

	return true;
}

////////////////////////////////////////////////
// File Type
////////////////////////////////////////////////

const char *File::getSuffix(std::string &buf)
{
	string::size_type dotPos = nameStr.rfind(".");
	if (dotPos == string::npos) {
		buf = "";
		return buf.c_str();
	}
	buf = nameStr.substr(dotPos+1);
	return buf.c_str();
}

bool File::isXMLFileName(const char *name)
{
	if (name == NULL)
		return false;
	String nameStr = name;
	String lowerName = nameStr.toLowerCase();
	return lowerName.endsWith("xml");
}

////////////////////////////////////////////////
// getFileName
////////////////////////////////////////////////

const char *File::getFileName(std::string &buf)
{
	string::size_type sepPos = nameStr.rfind(separator);
	if (sepPos != string::npos)
		sepPos++;
	else
		sepPos = 0;
	buf = nameStr.substr(sepPos);
	return buf.c_str();
}

////////////////////////////////////////////////
// getAbsoluteFile
////////////////////////////////////////////////

File *File::getAbsoluteFile()
{
	if (absoluteFile == NULL)
		absoluteFile = new File();
	absoluteFile->setName("");
#if defined(WIN32)
	char fullpath[_MAX_PATH];
	if (_fullpath(fullpath, nameStr.c_str(), _MAX_PATH ) != NULL)
		absoluteFile->setName(fullpath);
#elif defined(HAVE_REALPATH)
	char fullpath[MAXPATHLEN];
	if (realpath(nameStr.c_str(), fullpath) != NULL)
		absoluteFile->setName(fullpath);
#elif defined(BTRON) || defined(ITRON) || defined(TENGINE) 
	// Not Implemented yet
	absoluteFile->setName(nameStr.c_str());
#else
	char fullpath[PATH_MAX];
	getcwd(fullpath, sizeof(fullpath));
	strcat(fullpath, File::separator);
	strcat(fullpath, nameStr.c_str());
	absoluteFile->setName(fullpath);
#endif

	return absoluteFile;
}

////////////////////////////////////////////////
// getParent
////////////////////////////////////////////////
	
const char *File::getParent()
{
	File *fullfile = getAbsoluteFile();
	const char *fullpath = fullfile->getName();
	string fullpathStr = fullpath;
	size_t pos = fullpathStr.rfind("/");
	if (pos == string::npos)
		pos = fullpathStr.rfind("\\");
	parentStr = "";
	if (pos != string::npos)
		parentStr = fullpathStr.substr(0, pos+1);
	return parentStr.c_str();
}

////////////////////////////////////////////////
//	Attributes
////////////////////////////////////////////////

long File::lastModified()
{
#if defined(BTRON)
	struct stat buf ;
	if(u_stat(getName(),&buf ) == -1)
		return 0;
	return buf.st_mtime;
#elif !defined(ITRON) && !defined(TENGINE)
	struct stat buf ;
	if(stat(getName(),&buf ) == -1)
		return 0;
	return buf.st_mtime;
#else
	return 0;
#endif
}

long File::length()
{
#if defined(BTRON)
	struct stat buf ;
	if(u_stat(getName(),&buf ) == -1)
		return 0;
	return buf.st_size;
#elif !defined(ITRON) && !defined(TENGINE)
	struct stat buf ;
	if(stat(getName(),&buf ) == -1)
		return 0;
	return buf.st_size;
#else
	return 0;
#endif
}

////////////////////////////////////////////////
//	is*
////////////////////////////////////////////////

bool File::isDirectory()
{
#if defined(BTRON)
	struct stat buf ;
	if(u_stat(getName(),&buf ) == -1)
		return false;
#elif !defined(ITRON) && !defined(TENGINE)
	struct stat buf ;
	if(stat(getName(),&buf ) == -1)
		return false;
#else
	return false;
#endif
#if defined(WIN32)
	return ((buf.st_mode & _S_IFMT)==_S_IFDIR) ? true : false;
#elif !defined(ITRON) && !defined(TENGINE)
	return ((buf.st_mode & S_IFMT)==S_IFDIR) ? true : false;
#endif
}

bool File::isFile()
{
#if defined(BTRON)
	struct stat buf ;
	if(u_stat(getName(),&buf ) == -1)
		return false;
#elif !defined(ITRON) && !defined(TENGINE)
	struct stat buf ;
	if(stat(getName(),&buf ) == -1)
		return false;
#else
		return false;
#endif
#if defined(WIN32)
	return ((buf.st_mode & _S_IFMT)==_S_IFREG) ? true : false;
#elif !defined(ITRON) && !defined(TENGINE)
	return ((buf.st_mode & S_IFMT)==S_IFREG) ? true : false;
#endif
}

////////////////////////////////////////////////
//	Compare
////////////////////////////////////////////////

bool File::equals(File *file)
{
	string fileName1 = getName();
	string fileName2 = file->getName();
	return (fileName1.compare(fileName2) == 0) ? true : false;
}

////////////////////////////////////////////////
//	FileList
////////////////////////////////////////////////

int File::listFiles(FileList &fileList)
{
	fileList.clear();
	if (isDirectory() == false)
		return 0;

	string dir = getName();

#if defined(WIN32)
	string findDir = dir + "\\*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind;
	hFind = FindFirstFile(findDir.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do{
			string findFilename = fd.cFileName;
			if (findFilename.compare(".") != 0 && findFilename.compare("..") != 0) {
				File *file = new File(dir.c_str(), findFilename.c_str());
				fileList.add(file);
			}
		} while(FindNextFile(hFind,&fd) != FALSE);
	}
	FindClose(hFind);
#elif defined(BTRON)
	int fd = open(dir.c_str(), O_RDONLY);
	if( fd == -1 )
		return fileList.size();
	char buf[1024] ;
	int cnt;
	while(0 < (cnt = u_getdents(fd, (dirent *)buf, sizeof(buf)))) {
		for(struct dirent *p = (struct dirent *)buf ; (char *)p < &buf[cnt]; p=(struct dirent *) ((int)p+(p->d_reclen)) ) {
				File *file = new File(dir.c_str(), p->d_name);
				fileList.add(file);
		}
  	}
	close(fd);
#elif !defined(ITRON) && !defined(TENGINE)
	struct dirent **namelist;
	int n = scandir(dir.c_str(), &namelist, 0, alphasort);
	if (0 <= n) {
		while(n--) {
			string filename =  namelist[n]->d_name;
			if (filename.compare(".") != 0 && filename.compare("..") != 0) {
				// Thanks for Pekka Virtanen <pekka.virtanen@gmail.com> and Bastiaan Van Eeckhoudt <bastiaanve@gmail.com>
				File *file = new File(dir.c_str(), filename.c_str());
				fileList.add(file);
			}
			free(namelist[n]);
		}
		free(namelist);
	}
#endif

	return fileList.size();
}
