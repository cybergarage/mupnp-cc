/******************************************************************
*
*	MediaServer for CyberLink
*
*	Copyright (C) Satoshi Konno 2003-2004
*
*	File: MythRecordedInfo.h
*
*	Revision;
*
*	06/05/04
*		- first revision.
*
******************************************************************/

#ifndef _CLINK_MEDIA_MYTH_RECORDEDINFO_H_
#define _CLINK_MEDIA_MYTH_RECORDEDINFO_H_

#include <string>

#ifdef HAVE_CONFIG_H
#  include "config.h"
#endif

#ifdef SUPPORT_MYTHTV

namespace CyberLink {

class MythRecordedInfo
{
	////////////////////////////////////////////////
	// Member
	////////////////////////////////////////////////

	std::string recordFilePrefix;
	std::string category;
	int chanID;
	std::string description;
	long endTime;
	std::string recGroup;
	int recordID;
	long startTime;
	std::string title;
	std::string subTitle;
	
	////////////////////////////////////////////////
	// Constructor
	////////////////////////////////////////////////

public:

	MythRecordedInfo()
	{
	}

	////////////////////////////////////////////////
	// RecordFilePrefix
	////////////////////////////////////////////////

public:

	void setRecordFilePrefix(const char *value)
	{
		recordFilePrefix = value;
	}

	const char *getRecordFilePrefix()
	{
		return recordFilePrefix.c_str();
	}

	////////////////////////////////////////////////
	// Category
	////////////////////////////////////////////////

public:

	void setCategory(const char *value) {
		category = value;
	}

	const char *getCategory() {
		return category.c_str();
	}

	////////////////////////////////////////////////
	// chanID
	////////////////////////////////////////////////

public:

	void setChanID(int i) {
		chanID = i;
	}

	int getChanID() {
		return chanID;
	}

	////////////////////////////////////////////////
	// Descripton
	////////////////////////////////////////////////
		
public:

	void setDescription(const char *value) {
		description = value;
	}
	
	const char *getDescription() {
		return description.c_str();
	}

	////////////////////////////////////////////////
	// EndTime
	////////////////////////////////////////////////
		
public:

	void setEndTime(long l) {
		endTime = l;
	}

	long getEndTime() {
		return endTime;
	}

	////////////////////////////////////////////////
	// recGroup
	////////////////////////////////////////////////
	
public:

	void setRecGroup(const char *value) {
		recGroup = value;
	}
	
	const char *getRecGroup() {
		return recGroup.c_str();
	}

	////////////////////////////////////////////////
	// recordID
	////////////////////////////////////////////////
	
public:

	void setRecordID(int i) {
		recordID = i;
	}
	
	int getRecordID() {
		return recordID;
	}

	////////////////////////////////////////////////
	// startTime
	////////////////////////////////////////////////
	
public:

	void setStartTime(long l) {
		startTime = l;
	}

	long getStartTime() {
		return startTime;
	}

	////////////////////////////////////////////////
	// Title
	////////////////////////////////////////////////
	
public:

	void setTitle(const char *value) {
		title = value;
	}
	
	const char *getTitle() {
		return title.c_str();
	}

	////////////////////////////////////////////////
	// subTitle
	////////////////////////////////////////////////
	
public:

	void setSubTitle(const char *value) {
		subTitle = value;
	}

	const char *getSubTitle() {
		return subTitle.c_str();
	}

	////////////////////////////////////////////////
	// file
	////////////////////////////////////////////////

public:

	const char *getFileName(std::string &buf);

	////////////////////////////////////////////////
	// print
	////////////////////////////////////////////////

public:

	void set(MythRecordedInfo *info);

	////////////////////////////////////////////////
	// print
	////////////////////////////////////////////////

public:

	void print();

};

}

#endif

#endif
