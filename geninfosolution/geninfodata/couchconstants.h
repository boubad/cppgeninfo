#pragma once
#ifndef __COUCHCONSTANTS_H__
#define __COUCHCONSTANTS_H__
////////////////////////////////
#include "gendefs.h"
/////////////////////////////
namespace geninfo {
	class CouchConstants
	{
	public:
		static const string_t BASEURL;
		static const string_t DATABASE;
		//
		static const string_t QUESTION_STRING;
		static const string_t AND_STRING;
		static const string_t QUOTE_STRING;
		//
		static const string_t COMMITTED_UPDATE_SEQ;
		static const string_t COMPACT_RUNNING;
		static const string_t DB_NAME;
		static const string_t DISK_FORMAT_VERSION;
		static const string_t DATA_SIZE;
		static const string_t DISK_SIZE;
		static const string_t DOC_COUNT;
		static const string_t DOC_DEL_COUNT;
		static const string_t INSTANCE_START_TIME;
		static const string_t PURGE_SEQ;
		static const string_t UPDATE_SEQ;
		//
		static const string_t WELCOME;
		static const string_t VENDOR;
		static const string_t COUCHDB;
		static const string_t UUID;
		static const string_t VERSION;
		static const string_t NAME;
		//
		static const string_t LOCATION;
		static const string_t REASON;
		static const string_t ERROR;
		static const string_t REV;
		static const string_t ID;
		static const string_t OK;
		//
		static const string_t OFFSET;
		static const string_t TOTAL_ROWS;
		static const string_t ROWS;
	};
}// namespace geninfo
#endif // __COUCHCONSTANTS_H__
