/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2003
 *
 *	File : MythRecordedItemNode.h
 *
 *	Revision:
 *
 *	06/07/04
 *		- first revision.
 *
 ******************************************************************/

#ifndef _CLINK_MEDIA_MYTHTV_RECORDEDITEMNODET_H_
#define _CLINK_MEDIA_MYTHTV_RECORDEDITEMNODET_H_

#include <mupnp/io/File.h>
#include <mupnp/io/FileInputStream.h>
#include <mupnp/upnp/media/server/directory/mythtv/MythRecordedInfo.h>
#include <mupnp/upnp/media/server/object/item/ItemNode.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef SUPPORT_MYTHTV

namespace CyberLink {

class MythRecordedItemNode : public ItemNode {
  MythRecordedInfo recInfo;

  ////////////////////////////////////////////////
  // Constants
  ////////////////////////////////////////////////

  public:
  static const char* MIME_TYPE;

  ////////////////////////////////////////////////
  // Constroctor
  ////////////////////////////////////////////////

  public:
  MythRecordedItemNode();

  ~MythRecordedItemNode();

  ////////////////////////////////////////////////
  // RecordedInfo
  ////////////////////////////////////////////////

  public:
  MythRecordedInfo* getRecordedInfo()
  {
    return &recInfo;
  }

  void setRecordedInfo(MythRecordedInfo* info);

  ////////////////////////////////////////////////
  // equals
  ////////////////////////////////////////////////

  public:
  bool equals(MythRecordedInfo* info);

  ////////////////////////////////////////////////
  // Abstract methods
  ////////////////////////////////////////////////

  public:
  const char* getContent(std::string& buf);

  long getContentLength();

  CyberIO::InputStream* getContentInputStream();

  const char* getMimeType();
};

}

#endif

#endif
