/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2003
 **
 *	File: iTunesItemNodeList.h
 *
 *	Revision;
 *
 *	03/14/06
 *		- first revision.
 *
 ******************************************************************/

#ifndef _CLINK_MEDIA_ITUNESITEMNODELIST_H_
#define _CLINK_MEDIA_ITUNESITEMNODELIST_H_

#include <mupnp/upnp/media/server/object/item/itunes/iTunesItemNode.h>
#include <mupnp/util/Vector.h>

namespace CyberLink {

class iTunesItemNodeList : public CyberUtil::Vector {
  ////////////////////////////////////////////////
  //	Constructor
  ////////////////////////////////////////////////

  public:
  iTunesItemNodeList()
  {
  }

  ~iTunesItemNodeList()
  {
    clear();
  }

  ////////////////////////////////////////////////
  //	Methods
  ////////////////////////////////////////////////

  public:
  iTunesItemNode* getiTunesItemNode(int n)
  {
    return (iTunesItemNode*)Vector::get(n);
  }

  iTunesItemNode* getItemNode(CyberIO::File* file);

  ////////////////////////////////////////////////
  //	clear
  ////////////////////////////////////////////////

  public:
  void clear();
};

}

#endif
