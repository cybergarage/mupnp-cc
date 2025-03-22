/******************************************************************
 *
 *	MediaServer for CyberLink
 *
 *	Copyright (C) Satoshi Konno 2003
 *
 *	File: FormatList
 *
 *	Revision;
 *
 *	06/09/04
 *		- first revision.
 *
 ******************************************************************/

#ifndef _CLINK_MEDIA_ID3FRAMELIST_H_
#define _CLINK_MEDIA_ID3FRAMELIST_H_

#include <mupnp/upnp/media/server/object/format/ID3Frame.h>
#include <mupnp/util/Vector.h>
#include <string>

namespace CyberLink {

class ID3FrameList : public CyberUtil::Vector {

  ////////////////////////////////////////////////
  // Constroctor
  ////////////////////////////////////////////////

  public:
  ID3FrameList();
  ~ID3FrameList();

  ////////////////////////////////////////////////
  // get*
  ////////////////////////////////////////////////

  public:
  ID3Frame* getFrame(int n)
  {
    return (ID3Frame*)get(n);
  }

  ID3Frame* getFrame(const char* name);
  unsigned char* getFrameData(const char* name);
  const char* getFrameData(const char* name, std::string& buf);
  const char* getFrameStringData(const char* name, std::string& buf);

  ////////////////////////////////////////////////
  // clear
  ////////////////////////////////////////////////

  public:
  void clear();
};

}

#endif
