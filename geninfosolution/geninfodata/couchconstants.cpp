#include "stdafx.h"
#include "couchconstants.h"
////////////////////////////////
namespace geninfo {
	/////////////////////////////
	const string_t CouchConstants::BASEURL(U("http://localhost:5984"));
	const string_t CouchConstants::DATABASE(U("geninfo"));
	///////////////////////////////////////////
	const string_t CouchConstants::QUESTION_STRING(U("?"));
	const string_t CouchConstants::AND_STRING(U("&"));
	const string_t CouchConstants::QUOTE_STRING(U("\""));
	//
	const string_t CouchConstants::COMMITTED_UPDATE_SEQ(U("committed_update_seq"));
	const string_t CouchConstants::COMPACT_RUNNING(U("compact_running"));
	const string_t CouchConstants::DB_NAME(U("db_name"));
	const string_t CouchConstants::DISK_FORMAT_VERSION(U("disk_format_version"));
	const string_t CouchConstants::DATA_SIZE(U("data_size"));
	const string_t CouchConstants::DISK_SIZE(U("disk_size"));
	const string_t CouchConstants::DOC_COUNT(U("doc_count"));
	const string_t CouchConstants::DOC_DEL_COUNT(U("doc_del_count"));
	const string_t CouchConstants::INSTANCE_START_TIME(U("instance_start_time"));
	const string_t CouchConstants::PURGE_SEQ(U("purge_seq"));
	const string_t CouchConstants::UPDATE_SEQ(U("update_seq"));
	////////////////////////////////
	const string_t CouchConstants::WELCOME(U("Welcome"));
	const string_t CouchConstants::VENDOR(U("vendor"));
	const string_t CouchConstants::COUCHDB(U("couchdb"));
	const string_t CouchConstants::UUID(U("uuid"));
	const string_t CouchConstants::VERSION(U("version"));
	const string_t CouchConstants::NAME(U("name"));
	///////////////////////////////////////////
	const string_t  CouchConstants::LOCATION(U("Location"));
	const string_t  CouchConstants::REASON(U("reason"));
	const string_t  CouchConstants::ERROR(U("error"));
	const string_t  CouchConstants::REV(U("rev"));
	const string_t  CouchConstants::ID(U("id"));
	const string_t  CouchConstants::OK(U("ok"));
	/////////////////////////////////////
	const string_t CouchConstants::OFFSET(U("offset"));
	const string_t CouchConstants::TOTAL_ROWS(U("total_rows"));
	const string_t CouchConstants::ROWS(U("rows"));
	/////////////////////////////////////////
}// namespace geninfo
