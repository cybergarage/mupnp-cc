/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2003
 **
 *	File: MythRecordedInfoList.h
 *
 *	Revision;
 *
 *	06/07/04
 *		- first revision.
 *
 ******************************************************************/

#ifndef _CLINK_MEDIA_MYTHTV_RECORDEDINFOLIST_H_
#define _CLINK_MEDIA_MYTHTV_RECORDEDINFOLIST_H_

#include <mupnp/upnp/media/server/directory/mythtv/MythRecordedInfo.h>
#include <mupnp/util/Vector.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef SUPPORT_MYTHTV

namespace CyberLink {

class MythRecordedInfoList : public CyberUtil::Vector {
  ////////////////////////////////////////////////
  //	Constructor
  ////////////////////////////////////////////////

  public:
  MythRecordedInfoList()
  {
  }

  ~MythRecordedInfoList()
  {
    clear();
  }

  ////////////////////////////////////////////////
  //	Methods
  ////////////////////////////////////////////////

  public:
  MythRecordedInfo* getRecordedInfo(int n)
  {
    return (MythRecordedInfo*)Vector::get(n);
  }

  ////////////////////////////////////////////////
  //	clear
  ////////////////////////////////////////////////

  public:
  void clear();
};

}

#endif

#endif
