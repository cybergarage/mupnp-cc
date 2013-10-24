<<<<<<< HEAD
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Disposer.h
*
*	Revision;
*
*	01/06/04
*		- first revision
*
******************************************************************/

#ifndef _CLINK_DISPOSER_H_
#define _CLINK_DISPOSER_H_

#include <uhttp/util/Thread.h>

namespace CyberLink {

class ControlPoint;

class Disposer : public uHTTP::Thread
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	Disposer(ControlPoint *ctrlp)
	{
		setControlPoint(ctrlp);
	}
	
	////////////////////////////////////////////////
	//	Member
	////////////////////////////////////////////////

private:
	
	ControlPoint *controlPoint;

public:

	void setControlPoint(ControlPoint *ctrlp)
	{
		controlPoint = ctrlp;
	}
	
	ControlPoint *getControlPoint()
	{
		return controlPoint;
	}

	////////////////////////////////////////////////
	//	Thread
	////////////////////////////////////////////////
	
public:

	void run();

};

}

#endif

=======
/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Disposer.h
*
*	Revision;
*
*	01/06/04
*		- first revision
*
******************************************************************/

#ifndef _CLINK_DISPOSER_H_
#define _CLINK_DISPOSER_H_

#include <cybergarage/util/Thread.h>

namespace CyberLink {

class ControlPoint;

class Disposer : public CyberUtil::Thread
{
	////////////////////////////////////////////////
	//	Constructor
	////////////////////////////////////////////////

public:

	Disposer(ControlPoint *ctrlp)
	{
		setControlPoint(ctrlp);
	}
	
	////////////////////////////////////////////////
	//	Member
	////////////////////////////////////////////////

private:
	
	ControlPoint *controlPoint;

public:

	void setControlPoint(ControlPoint *ctrlp)
	{
		controlPoint = ctrlp;
	}
	
	ControlPoint *getControlPoint()
	{
		return controlPoint;
	}

	////////////////////////////////////////////////
	//	Thread
	////////////////////////////////////////////////
	
public:

	void run();

};

}

#endif

>>>>>>> a1a830b7f4caaeafd5c2db44ad78fbb5b9f304b2
