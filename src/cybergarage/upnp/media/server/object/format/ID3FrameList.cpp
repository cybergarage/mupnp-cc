/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File: ID3FrameList.cpp
*
*	Revision;
*
*	06/09/04
*		- first revision.
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/format/ID3FrameList.h>
#include <string>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// Constroctor
////////////////////////////////////////////////

ID3FrameList::ID3FrameList() 
{
}

ID3FrameList::~ID3FrameList() 
{
	clear();
}
	
////////////////////////////////////////////////
// get*
////////////////////////////////////////////////

ID3Frame *ID3FrameList::getFrame(const std::string &name) 
{
	string nameStr = name;
	int nLists = size(); 
	for (int n=0; n<nLists; n++) {
		ID3Frame *frame = getFrame(n);
		if (nameStr.compare(frame->getID()) == 0)
			return frame;
	}
	return NULL;
}

unsigned char *ID3FrameList::getFrameData(const std::string &name) 
{
	ID3Frame *frame = getFrame(name);
	if (frame == NULL)
		return NULL;
	return frame->getData();
}

const char *ID3FrameList::getFrameData(const std::string &name, std::string &buf) 
{
	ID3Frame *frame = getFrame(name);
	if (frame == NULL)
		return NULL;
	return frame->getData(buf);
}

const char *ID3FrameList::getFrameStringData(const std::string &name, std::string &buf) 
{
	ID3Frame *frame = getFrame(name);
	if (frame == NULL)
		return NULL;
	return frame->getStringData(buf);
}

////////////////////////////////////////////////
//	clear
////////////////////////////////////////////////

void ID3FrameList::clear() 
{
	int nFrame = size();
	for (int n=0; n<nFrame; n++) {
		ID3Frame *frame = getFrame(n);
		delete frame;
	}
	Vector::clear();
}
