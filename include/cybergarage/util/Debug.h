/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: Debug.h
*
*	Revision;
*
*	08/16/03
*		- first revision
*
******************************************************************/

#ifndef _CUTIL_DEBUG_H_
#define _CUTIL_DEBUG_H_

#include <stdio.h>
#include <string>
#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
#include <iostream>
#include <sstream>
#include <fstream>
#endif

#include <cybergarage/util/Exception.h>

namespace CyberUtil {

class Debug
{
	static bool enabled;

public:

	static void on()
	{
		enabled = true;
	}

	static void off()
	{
		enabled = false;
	}

	static bool isOn()
	{
		return enabled;
	}

	static void message(const char *s)
	{
		if (enabled == true)
			printf("CyberGarage message : %s\n", s);
	}

	static void message(std::string &s)
	{
		message(s.c_str());
	}

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	static void message(std::ostringstream &s)
	{
		message(s.str().c_str());
	}
#endif

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	static void message(const char *s, const char *fname)
	{
		if (enabled == true) {
			std::fstream fout(fname, std::ios::out|std::ios::app);
			if (fout.fail())
				return;
			fout << "CyberGarage message : " << s << std::endl;
			fout.close();
		}
	}
#endif

	static void warning(const char *s)
	{
		printf("CyberGarage warning : %s\n", s);
	}

	static void warning(std::string &s)
	{
		warning(s.c_str());
	}

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	static void warning(std::ostringstream &s)
	{
		warning(s.str().c_str());
	}
#endif

	static void warning(CyberUtil::Exception &e)
	{
		warning(e.getMessage());
	}

#if !defined(BTRON) && !defined(ITRON) && !defined(TENGINE) 
	static void warning(const char *s, const char *fname)
	{
		std::fstream fout(fname, std::ios::out|std::ios::app);
		if (fout.fail())
			return;
		fout << "CyberGarage warning : " << s << std::endl;
		fout.close();
	}
#endif
};

}

#endif
