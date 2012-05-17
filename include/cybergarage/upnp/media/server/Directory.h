/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003
*
*	File : Directory.h
*
*	Revision:
*
*	03/23/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_DIRECTORY_H_
#define _CLINK_MEDIA_DIRECTORY_H_

#include <cybergarage/upnp/media/server/object/container/ContainerNode.h>
#include <uhttp/util/Mutex.h>

namespace CyberLink {

class Directory : public ContainerNode
{
private:

	uHTTP::Mutex *mutex;

	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////
	
public:

	Directory(ContentDirectory *cdir, const std::string &name)
	{
		setContentDirectory(cdir);
		setFriendlyName(name);
		mutex = new uHTTP::Mutex();
	}

	Directory(const std::string &name)
	{
		setContentDirectory(NULL);
		setFriendlyName(name);
		delete mutex;
	}
	
	////////////////////////////////////////////////
	// Name
	////////////////////////////////////////////////

public:

	void setFriendlyName(const std::string &name)
	{
		setTitle(name);
	}
	
	const char *getFriendlyName()
	{
		return getTitle();
	}
	
	
	////////////////////////////////////////////////
	// Mutex
	////////////////////////////////////////////////

public:

	void lock()
	{
		mutex->lock();
	}
	
	void unlock()
	{
		mutex->unlock();
	}

	////////////////////////////////////////////////
	// update
	////////////////////////////////////////////////
	
public:

	virtual void update() = 0;
};

}

#endif


