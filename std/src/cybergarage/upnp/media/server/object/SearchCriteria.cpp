/******************************************************************
*
*	CyberLink for C++
*
*	Copyright (C) Satoshi Konno 2002-2003
*
*	File: SearchCriteria.cpp
*
*	Revision:
*
*	08/04/04
*		- first revision
*
******************************************************************/

#include <cybergarage/upnp/media/server/object/SearchCriteria.h>

using namespace CyberLink;

////////////////////////////////////////////////
//	Constants
////////////////////////////////////////////////

const char *SearchCriteria::ID = "@id";
const char *SearchCriteria::PARENT_ID = "@parentID";
const char *SearchCriteria::TITLE = "dc:title";
const char *SearchCriteria::CREATOR = "dc:creator";
const char *SearchCriteria::CLASS = "upnp:class";
const char *SearchCriteria::DATE = "dc:date";

const char *SearchCriteria::AND = "and";
const char *SearchCriteria::OR = "or";

const char *SearchCriteria::EQ = "=";
const char *SearchCriteria::NEQ = "!=";
const char *SearchCriteria::LT = "<";
const char *SearchCriteria::LE = "<=";
const char *SearchCriteria::GT = ">";
const char *SearchCriteria::GE = ">=";

const char *SearchCriteria::CONTAINS = "contains";
const char *SearchCriteria::DOESNOTCONTAIN = "doesNotContain";
const char *SearchCriteria::DERIVEDFROM = "derivedfrom";
const char *SearchCriteria::EXISTS = "exists";

const char *SearchCriteria::TRUE_STR = "true";
const char *SearchCriteria::FALSE_STR = "false";

const char *SearchCriteria::WCHARS = " \t\n\v\f\r";

