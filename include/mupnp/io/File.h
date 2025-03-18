/******************************************************************
 *
 * uHTTP for C++
 *
 * Copyright (C) Satoshi Konno 2002
 *
 * This is licensed under BSD-style license, see file COPYING.
 *
 ******************************************************************/

#ifndef _UHTTP_IO_FILE_H_
#define _UHTTP_IO_FILE_H_

#include <stdlib.h>
#include <string>

namespace uHTTP {
class FileList;

class File {
  std::string nameStr;
  std::string parentStr;

  File* absoluteFile;

  ////////////////////////////////////////////////
  //  Constants
  ////////////////////////////////////////////////

  public:
  static const char separatorChar;
  static const char pathSeparatorChar;
  static const char* separator;
  static const char* pathSeparator;
  static const char* O_TEXT;
  static const char* O_BINARY;

  ////////////////////////////////////////////////
  //  Constructor
  ////////////////////////////////////////////////

  public:
  File();
  File(const std::string& fname);
  File(const std::string& dir, const std::string& fname);
  File(File* file);

  ~File();

  ////////////////////////////////////////////////
  //  Name
  ////////////////////////////////////////////////

  public:
  void setName(const std::string& fname)
  {
    nameStr = fname;
    if (absoluteFile) {
      delete absoluteFile;
      absoluteFile = NULL;
    }
  }

  const char* getName()
  {
    return nameStr.c_str();
  }

  ////////////////////////////////////////////////
  //  get*
  ////////////////////////////////////////////////

  public:
  const char* getFileName(std::string& buf);

  File* getAbsoluteFile();

  const char* getParent();

  ////////////////////////////////////////////////
  //  exists
  ////////////////////////////////////////////////

  public:
  static bool exists(const std::string& name);

  bool exists()
  {
    return exists(getName());
  }

  ////////////////////////////////////////////////
  //  load
  ////////////////////////////////////////////////

  public:
  static bool load(const std::string& name, std::string& buf);

  bool load(std::string& buf)
  {
    return load(getName(), buf);
  }

  ////////////////////////////////////////////////
  // save
  ////////////////////////////////////////////////

  public:
  static bool save(const std::string& name, const std::string& buf);

  bool save(const std::string& buf)
  {
    return save(getName(), buf);
  }

  ////////////////////////////////////////////////
  //  File Type
  ////////////////////////////////////////////////

  public:
  const char* getSuffix(std::string& buf);

  static bool isXMLFileName(const std::string& name);

  ////////////////////////////////////////////////
  //  Attributes
  ////////////////////////////////////////////////

  public:
  long lastModified();
  long length();

  ////////////////////////////////////////////////
  //  Compare
  ////////////////////////////////////////////////

  public:
  bool equals(File* file);

  ////////////////////////////////////////////////
  //  FileList
  ////////////////////////////////////////////////

  public:
  size_t listFiles(FileList& fileList);

  ////////////////////////////////////////////////
  //  is*
  ////////////////////////////////////////////////

  public:
  bool isDirectory();
  bool isFile();
};

}

#endif
