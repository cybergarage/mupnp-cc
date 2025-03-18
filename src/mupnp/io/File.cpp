/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <stdio.h>
#include <string.h>

#if defined(WIN32)
#include <sys/stat.h>
#include <windows.h>
#elif defined(BTRON)
#include <bsys/unixemu.h>
#include <fcntl.h>
#include <sys/dirent.h>
#include <sys/types.h>
#include <unistd.h>
#elif !defined(ITRON) && !defined(TENGINE)
#include <dirent.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#include <mupnp/io/File.h>
#include <mupnp/io/FileList.h>
#include <mupnp/platform.h>

#include <mupnp/util/StringUtil.h>

using namespace std;
using namespace uHTTP;
using namespace uHTTP;

////////////////////////////////////////////////
//  Constants
////////////////////////////////////////////////

#ifdef WIN32
const char File::separatorChar = '\\';
const char File::pathSeparatorChar = ';';
const char* File::separator = "\\";
const char* File::pathSeparator = ";";
#else
const char File::separatorChar = '/';
const char File::pathSeparatorChar = ':';
const char* File::separator = "/";
const char* File::pathSeparator = ":";
#endif

const char* File::O_TEXT = "rt";
const char* File::O_BINARY = "rb";

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

File::File()
{
  absoluteFile = NULL;
  setName("");
}

File::File(const std::string& fname)
{
  absoluteFile = NULL;
  setName(fname);
}

File::File(const std::string& dir, const std::string& fname)
{
  absoluteFile = NULL;
  string fullname;
  fullname = dir;
  // Thanks for Bastiaan Van Eeckhoudt <bastiaanve@gmail.com>
  size_t dirLen = dir.length();
  if (dir[dirLen - 1] != File::separatorChar)
    fullname.append(File::separator);
  fullname.append(fname);
  setName(fullname.c_str());
}

File::File(File* file)
{
  absoluteFile = NULL;
  setName(file->getName());
}

File::~File()
{
  if (absoluteFile)
    delete absoluteFile;
}

////////////////////////////////////////////////
// exists
////////////////////////////////////////////////

bool File::exists(const std::string& name)
{
#if defined(BTRON)
  int fd = open(name, O_RDONLY);
  if (fd == -1)
    return false;
  close(fd);
  return true;
#elif !defined(ITRON) && !defined(TENGINE)
  FILE* fp = fopen(name.c_str(), "r");
  if (!fp)
    return false;
  fclose(fp);
  return true;
#else
  return false;
#endif
}

////////////////////////////////////////////////
// load
////////////////////////////////////////////////

bool File::load(const std::string& name, string& buf)
{
  const int READ_BUF_SIZE = 1024;
  char readBuf[READ_BUF_SIZE + 1];

  buf = "";

#if defined(BTRON)
  int fd = open(name, O_RDONLY);
  if (fd == -1)
    return false;
  ssize_t nread = read(fd, readBuf, READ_BUF_SIZE);
  while (0 < nread) {
    readBuf[nread] = '\0';
    buf += readBuf;
    nread = read(fd, readBuf, READ_BUF_SIZE);
  }
  close(fd);
#else
  FILE* fp = fopen(name.c_str(), "r");
  if (!fp)
    return false;
  size_t nread = fread(readBuf, sizeof(char), READ_BUF_SIZE, fp);
  while (0 < nread) {
    readBuf[nread] = '\0';
    buf += readBuf;
    nread = fread(readBuf, sizeof(char), READ_BUF_SIZE, fp);
  }
  fclose(fp);
#endif

  return true;
}

////////////////////////////////////////////////
// save
////////////////////////////////////////////////

bool File::save(const std::string& name, const std::string& buf)
{
#if defined(BTRON)
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
#else
  FILE* fp = fopen(name.c_str(), "wb");
  if (!fp)
    return false;
  size_t bufSize = buf.length();
  size_t nWrote = fwrite(buf.c_str(), sizeof(char), bufSize, fp);
  while (nWrote < bufSize) {
    size_t worteByte = fwrite(buf.c_str() + nWrote, sizeof(char), (bufSize - nWrote), fp);
    if (worteByte <= 0)
      break;
    nWrote += worteByte;
  }
  fclose(fp);
#endif

  return true;
}

////////////////////////////////////////////////
// File Type
////////////////////////////////////////////////

const char* File::getSuffix(std::string& buf)
{
  string::size_type dotPos = nameStr.rfind(".");
  if (dotPos == string::npos) {
    buf = "";
    return buf.c_str();
  }
  buf = nameStr.substr(dotPos + 1);
  return buf.c_str();
}

bool File::isXMLFileName(const std::string& name)
{
  String nameStr = name;
  String lowerName(nameStr.toLowerCase());
  return lowerName.endsWith("xml");
}

////////////////////////////////////////////////
// getFileName
////////////////////////////////////////////////

const char* File::getFileName(std::string& buf)
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

File* File::getAbsoluteFile()
{
  if (!absoluteFile)
    absoluteFile = new File();
  absoluteFile->setName("");
#if defined(WIN32)
  char fullpath[_MAX_PATH];
  if (_fullpath(fullpath, nameStr.c_str(), _MAX_PATH))
    absoluteFile->setName(fullpath);
#elif defined(HAVE_REALPATH)
  char fullpath[MAXPATHLEN];
  if (realpath(nameStr.c_str(), fullpath))
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

const char* File::getParent()
{
  File* fullfile = getAbsoluteFile();
  const char* fullpath = fullfile->getName();
  string fullpathStr = fullpath;
  size_t pos = fullpathStr.rfind("/");
  if (pos == string::npos)
    pos = fullpathStr.rfind("\\");
  parentStr = "";
  if (pos != string::npos)
    parentStr = fullpathStr.substr(0, pos + 1);
  return parentStr.c_str();
}

////////////////////////////////////////////////
//  Attributes
////////////////////////////////////////////////

long File::lastModified()
{
#if defined(BTRON)
  struct stat buf;
  if (u_stat(getName(), &buf) == -1)
    return 0;
  return buf.st_mtime;
#elif !defined(ITRON) && !defined(TENGINE)
  struct stat buf;
  if (stat(getName(), &buf) == -1)
    return 0;
  return buf.st_mtime;
#else
  return 0;
#endif
}

long File::length()
{
#if defined(BTRON)
  struct stat buf;
  if (u_stat(getName(), &buf) == -1)
    return 0;
  return buf.st_size;
#elif !defined(ITRON) && !defined(TENGINE)
  struct stat buf;
  if (stat(getName(), &buf) == -1)
    return 0;
  return buf.st_size;
#else
  return 0;
#endif
}

////////////////////////////////////////////////
//  is*
////////////////////////////////////////////////

bool File::isDirectory()
{
#if defined(BTRON)
  struct stat buf;
  if (u_stat(getName(), &buf) == -1)
    return false;
#elif !defined(ITRON) && !defined(TENGINE)
  struct stat buf;
  if (stat(getName(), &buf) == -1)
    return false;
#else
  return false;
#endif
#if defined(WIN32)
  return ((buf.st_mode & _S_IFMT) == _S_IFDIR) ? true : false;
#elif !defined(ITRON) && !defined(TENGINE)
  return ((buf.st_mode & S_IFMT) == S_IFDIR) ? true : false;
#endif
}

bool File::isFile()
{
#if defined(BTRON)
  struct stat buf;
  if (u_stat(getName(), &buf) == -1)
    return false;
#elif !defined(ITRON) && !defined(TENGINE)
  struct stat buf;
  if (stat(getName(), &buf) == -1)
    return false;
#else
  return false;
#endif
#if defined(WIN32)
  return ((buf.st_mode & _S_IFMT) == _S_IFREG) ? true : false;
#elif !defined(ITRON) && !defined(TENGINE)
  return ((buf.st_mode & S_IFMT) == S_IFREG) ? true : false;
#endif
}

////////////////////////////////////////////////
//  Compare
////////////////////////////////////////////////

bool File::equals(File* file)
{
  string fileName1 = getName();
  string fileName2 = file->getName();
  return (fileName1.compare(fileName2) == 0) ? true : false;
}

////////////////////////////////////////////////
//  FileList
////////////////////////////////////////////////

size_t File::listFiles(FileList& fileList)
{
  if (isDirectory() == false)
    return 0;

  string dir = getName();

#if defined(WIN32)
  string findDir = dir + "\\*.*";
  WIN32_FIND_DATA fd;
  HANDLE hFind;
  hFind = FindFirstFile(findDir.c_str(), &fd);
  if (hFind != INVALID_HANDLE_VALUE) {
    do {
      string findFilename = fd.cFileName;
      if (findFilename.compare(".") != 0 && findFilename.compare("..") != 0) {
        File* file = new File(dir.c_str(), findFilename.c_str());
        fileList.add(file);
      }
    } while (FindNextFile(hFind, &fd) != FALSE);
  }
  FindClose(hFind);
#elif defined(BTRON)
  int fd = open(dir.c_str(), O_RDONLY);
  if (fd == -1)
    return fileList.size();
  char buf[1024];
  int cnt;
  while (0 < (cnt = u_getdents(fd, (dirent*)buf, sizeof(buf)))) {
    for (struct dirent* p = (struct dirent*)buf; (char*)p < &buf[cnt]; p = (struct dirent*)((int)p + (p->d_reclen))) {
      File* file = new File(dir.c_str(), p->d_name);
      fileList.add(file);
    }
  }
  close(fd);
#elif !defined(ITRON) && !defined(TENGINE)
  struct dirent** namelist;
  int n = scandir(dir.c_str(), &namelist, 0, alphasort);
  if (0 <= n) {
    while (n--) {
      string filename = namelist[n]->d_name;
      if (filename.compare(".") != 0 && filename.compare("..") != 0) {
        // Thanks for Pekka Virtanen <pekka.virtanen@gmail.com> and Bastiaan Van Eeckhoudt <bastiaanve@gmail.com>
        File* file = new File(dir.c_str(), filename.c_str());
        fileList.add(file);
      }
      free(namelist[n]);
    }
    free(namelist);
  }
#endif

  return fileList.size();
}
