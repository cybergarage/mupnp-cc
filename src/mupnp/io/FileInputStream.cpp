/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#include <mupnp/io/FileInputStream.h>

using namespace uHTTP;

////////////////////////////////////////////////
//  Constructor
////////////////////////////////////////////////

FileInputStream::FileInputStream(File* file, const std::string& mode)
{
  inBuf = new char[FILE_INBUF_SIZE];
  fp = fopen(file->getName(), mode.c_str());
  if (!fp)
    return;
}

////////////////////////////////////////////////
//  Destructor
////////////////////////////////////////////////

FileInputStream::~FileInputStream()
{
  delete[] inBuf;
}

////////////////////////////////////////////////
//  read
////////////////////////////////////////////////

ssize_t FileInputStream::read(std::string& b, size_t len)
{
  if (!fp)
    return 0;

  int readCnt = 0;
  while (readCnt < len) {
    size_t readSize = len - readCnt;
    if (FILE_INBUF_SIZE < readSize)
      readSize = FILE_INBUF_SIZE;
    size_t readLen = fread(inBuf, sizeof(char), readSize, fp);
    if (readLen <= 0)
      break;
    if (0 < readLen) {
      b.append(inBuf, 0, readLen);
      readCnt += readLen;
    }
  }
  return readCnt;
}

ssize_t FileInputStream::read(char* b, size_t len)
{
  if (!fp)
    return 0;

  int readCnt = 0;
  while (readCnt < len) {
    size_t readSize = len - readCnt;
    size_t readLen = fread(b + readCnt, sizeof(char), readSize, fp);
    if (readLen <= 0)
      break;
    readCnt += readLen;
  }
  return readCnt;
}

////////////////////////////////////////////////
//  unread
////////////////////////////////////////////////

void FileInputStream::unread(std::string& b, size_t off, size_t len)
{
  // Not Implemented
}

////////////////////////////////////////////////
//  skip
////////////////////////////////////////////////

long FileInputStream::skip(long n)
{
  if (!fp)
    return 0;
  int ret = fseek(fp, n, SEEK_CUR);
  return (ret == 0) ? n : 0;
}

////////////////////////////////////////////////
//  close
////////////////////////////////////////////////

void FileInputStream::close()
{
  if (!fp)
    return;
  fclose(fp);
}
