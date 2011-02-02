/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: ID3Frame.cpp
*
*	Revision:
*
*	06/08/04
*		- first revision.
*
******************************************************************/

#include <string.h>
#include <cybergarage/upnp/media/server/object/format/ID3Frame.h>

using namespace std;
using namespace CyberLink;

////////////////////////////////////////////////
// Constants
////////////////////////////////////////////////
	
const char *ID3Frame::TIT1 = "TIT1";
const char *ID3Frame::TIT2 = "TIT2";
const char *ID3Frame::TIT3 = "TIT3";

const char *ID3Frame::TPE1 = "TPE1";
const char *ID3Frame::TPE2 = "TPE2";
const char *ID3Frame::TPE3 = "TPE3";
const char *ID3Frame::TPE4 = "TPE4";
	
////////////////////////////////////////////////
// Constroctor
////////////////////////////////////////////////
	
ID3Frame::ID3Frame()
{
	setID("");
	setFlag(0);
	setSize(0);
	data = NULL;
}

ID3Frame::~ID3Frame()
{
	if (data != NULL)
		delete []data;
}

////////////////////////////////////////////////
// Data
////////////////////////////////////////////////
	
void ID3Frame::setData(unsigned char *val, int len)
{
	if (data != NULL)
		delete []data;
	data = new unsigned char[len+1];
	memcpy(data, val, len);
}

const char *ID3Frame::getData(std::string &buf)
{
	int frameSize = getSize();
	char *frameData = new char[frameSize+1];
	memcpy(frameData, data, frameSize);
	frameData[frameSize] = '\0';
	buf = frameData;
	delete []frameData;
	return buf.c_str();
}

const char *ID3Frame::getStringData(std::string &buf)
{
	int frameSize = getSize();
	char *frameData = new char[(frameSize-1)+1];
	memcpy(frameData, (data+1), frameSize-1);
	frameData[frameSize-1] = '\0';
	buf = frameData;
	delete []frameData;
	return buf.c_str();
}
