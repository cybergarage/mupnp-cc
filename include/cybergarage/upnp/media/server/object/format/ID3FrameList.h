/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
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

#include <uhttp/util/Vector.h>
#include <cybergarage/upnp/media/server/object/format/ID3Frame.h>
#include <string>

namespace CyberLink {

class ID3FrameList : public uHTTP::Vector
{
	
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

	ID3Frame *getFrame(int n)
	{
		return (ID3Frame *)get(n);
	}

	ID3Frame *getFrame(const std::string &name);
	unsigned char *getFrameData(const std::string &name);
	const char *getFrameData(const std::string &name, std::string &buf);
	const char *getFrameStringData(const std::string &name, std::string &buf);

	////////////////////////////////////////////////
	// clear
	////////////////////////////////////////////////

public:

	void clear();

};

}

#endif


