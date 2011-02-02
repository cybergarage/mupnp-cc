/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: ID3Frame.h
*
*	Revision:
*
*	06/08/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_ID3FRAME_H_
#define _CLINK_MEDIA_ID3FRAME_H_

#include <string>

namespace CyberLink {

class ID3Frame
{
	std::string frameId;
	int flag;
	int size;

	unsigned char *data;

	////////////////////////////////////////////////
	// Constants
	////////////////////////////////////////////////

public:

	static const char *TIT1;
	static const char *TIT2;
	static const char *TIT3;

	static const char *TPE1;
	static const char *TPE2;
	static const char *TPE3;
	static const char *TPE4;
	
	////////////////////////////////////////////////
	// Constroctor
	////////////////////////////////////////////////

public:

	ID3Frame();
	~ID3Frame();

	////////////////////////////////////////////////
	// ID
	////////////////////////////////////////////////

public:

	void setID(const char *val) {
		frameId = val;
	}

	const char *getID() {
		return frameId.c_str();
	}

	////////////////////////////////////////////////
	// Size
	////////////////////////////////////////////////
	
public:

	void setFlag(int val) {
		flag = val;
	}

	int getFlag() {
		return flag;
	}

	////////////////////////////////////////////////
	// Size
	////////////////////////////////////////////////
	
public:

	void setSize(int val) {
		size = val;
	}

	int getSize() {
		return size;
	}

	////////////////////////////////////////////////
	// Data
	////////////////////////////////////////////////
	
public:

	void setData(unsigned char *val, int len);

	unsigned char *getData() 
	{
		return data;
	}

	const char *getData(std::string &buf);
	const char *getStringData(std::string &buf);
};

}

#endif


