//couchdoc.cpp
#include "stdafx.h"
////////////////////////////
#include "couchdoc.h"
/////////////////////////////
namespace geninfo {
	///////////////////////////////////////////
	const string_t QUESTION_STRING = (U("?"));
	const string_t AND_STRING = (U("&"));
	const string_t QUOTE_STRING = U("\"");
	//
	const string_t COMMITTED_UPDATE_SEQ = U("committed_update_seq");
	const string_t COMPACT_RUNNING = U("compact_running");
	const string_t DB_NAME = U("db_name");
	const string_t DISK_FORMAT_VERSION = U("disk_format_version");
	const string_t DATA_SIZE = U("data_size");
	const string_t DISK_SIZE = U("disk_size");
	const string_t DOC_COUNT = U("doc_count");
	const string_t DOC_DEL_COUNT = U("doc_del_count");
	const string_t INSTANCE_START_TIME = U("instance_start_time");
	const string_t PURGE_SEQ = U("purge_seq");
	const string_t UPDATE_SEQ = U("update_seq");
	/////////////////////////////////////////////////
	DatabaseInfo::DatabaseInfo(){}
	DatabaseInfo::DatabaseInfo(const value &oMap) {
		if ((!oMap.is_null()) && oMap.is_object()) {
			this->_m_val = oMap;
		}
	}
	DatabaseInfo::DatabaseInfo(const DatabaseInfo &other) : _m_val(other._m_val) {

	}
	DatabaseInfo & DatabaseInfo::operator=(const DatabaseInfo &other) {
		if (this != &other) {
			this->_m_val = other._m_val;
		}
		return *this;
	}
	DatabaseInfo::~DatabaseInfo() {

	}
	ostream_t & DatabaseInfo::write_to(ostream_t &os) const {
		os << this->_m_val;
		return os;
	}
	size_t DatabaseInfo::committed_update_seq(void) const {
		size_t nRet = 0;
		if ((!this->_m_val.is_null()) && this->_m_val.is_object()) {
			if (this->_m_val.has_field(COMMITTED_UPDATE_SEQ)) {
				nRet = (this->_m_val.at(COMMITTED_UPDATE_SEQ)).as_integer();
			}
		}// val
		return nRet;
	}
	bool DatabaseInfo::compact_running(void) const {
		bool bRet = false;
		if ((!this->_m_val.is_null()) && this->_m_val.is_object()) {
			if (this->_m_val.has_field(COMPACT_RUNNING)) {
				bRet = (this->_m_val.at(COMPACT_RUNNING)).as_bool();
			}
		}// val
		return bRet;
	}
	string_t DatabaseInfo::db_name(void) const {
		string_t sRet;
		if ((!this->_m_val.is_null()) && this->_m_val.is_object()) {
			if (this->_m_val.has_field(DB_NAME)) {
				sRet = (this->_m_val.at(DB_NAME)).as_string();
			}
		}// val
		return sRet;
	}
	size_t DatabaseInfo::disk_format_version(void) const {
		size_t nRet = 0;
		if ((!this->_m_val.is_null()) && this->_m_val.is_object()) {
			if (this->_m_val.has_field(DISK_FORMAT_VERSION)) {
				nRet = (this->_m_val.at(DISK_FORMAT_VERSION)).as_integer();
			}
		}// val
		return nRet;
	}
	size_t DatabaseInfo::data_size(void) const {
		size_t nRet = 0;
		if ((!this->_m_val.is_null()) && this->_m_val.is_object()) {
			if (this->_m_val.has_field(DATA_SIZE)) {
				nRet = (this->_m_val.at(DATA_SIZE)).as_integer();
			}
		}// val
		return nRet;
	}
	size_t DatabaseInfo::disk_size(void) const {
		size_t nRet = 0;
		if ((!this->_m_val.is_null()) && this->_m_val.is_object()) {
			if (this->_m_val.has_field(DISK_SIZE)) {
				nRet = (this->_m_val.at(DISK_SIZE)).as_integer();
			}
		}// val
		return nRet;
	}
	size_t DatabaseInfo::doc_count(void) const {
		size_t nRet = 0;
		if ((!this->_m_val.is_null()) && this->_m_val.is_object()) {
			if (this->_m_val.has_field(DOC_COUNT)) {
				nRet = (this->_m_val.at(DOC_COUNT)).as_integer();
			}
		}// val
		return nRet;
	}
	size_t DatabaseInfo::doc_del_count(void) const {
		size_t nRet = 0;
		if ((!this->_m_val.is_null()) && this->_m_val.is_object()) {
			if (this->_m_val.has_field(DOC_DEL_COUNT)) {
				nRet = (this->_m_val.at(DOC_DEL_COUNT)).as_integer();
			}
		}// val
		return nRet;
	}
	string_t DatabaseInfo::instance_start_time(void) const {
		string_t sRet;
		if ((!this->_m_val.is_null()) && this->_m_val.is_object()) {
			if (this->_m_val.has_field(INSTANCE_START_TIME)) {
				sRet = (this->_m_val.at(INSTANCE_START_TIME)).as_string();
			}
		}// val
		return sRet;
	}
	size_t DatabaseInfo::purge_seq(void) const {
		size_t nRet = 0;
		if ((!this->_m_val.is_null()) && this->_m_val.is_object()) {
			if (this->_m_val.has_field(PURGE_SEQ)) {
				nRet = (this->_m_val.at(PURGE_SEQ)).as_integer();
			}
		}// val
		return nRet;
	}
	size_t DatabaseInfo::update_seq(void) const {
		size_t nRet = 0;
		if ((!this->_m_val.is_null()) && this->_m_val.is_object()) {
			if (this->_m_val.has_field(UPDATE_SEQ)) {
				nRet = (this->_m_val.at(UPDATE_SEQ)).as_integer();
			}
		}// val
		return nRet;
	}
	//////////////////////////////////////////////
	ReadDocOptions::ReadDocOptions() :attachments(false), att_encoding_info(false), conflicts(false), deleted_conflicts(false),
		local_seq(false), meta(false), revs(false), revs_info(false) {}
	ReadDocOptions::ReadDocOptions(const ReadDocOptions &other) : attachments(other.attachments), att_encoding_info(other.att_encoding_info),
		conflicts(other.conflicts), deleted_conflicts(other.deleted_conflicts),
		local_seq(other.local_seq), meta(other.meta), revs(other.revs), revs_info(other.revs_info), rev(other.rev) {}
	ReadDocOptions & ReadDocOptions::operator=(const ReadDocOptions &other) {
		if (this != &other) {
			this->attachments = other.attachments;
			this->att_encoding_info = other.att_encoding_info;
			this->conflicts = other.conflicts;
			this->deleted_conflicts = other.deleted_conflicts;
			this->local_seq = other.local_seq;
			this->meta = other.meta;
			this->revs = other.revs;
			this->revs_info = other.revs_info;
			this->rev = other.rev;
		}
		return *this;
	}
	string_t ReadDocOptions::to_query_string(void) const {
		string_t sRet;
		bool bFirst = true;
		if (!this->rev.empty()) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("rev=") + url_encode(QUOTE_STRING + this->rev + QUOTE_STRING);
		}// endkey

		if (this->local_seq) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("local_seq=true");
		}// descending
		if (this->att_encoding_info) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("att_encoding_info=true");
		}// att_encoding_info
		if (this->attachments) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("attachments=true");
		}// attachments
		if (this->deleted_conflicts) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("deleted_conflicts=true");
		}// include_docs
		if (this->meta) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("meta=true");
		}// group
		if (this->revs) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("revs=true");
		}// descending
		if (this->revs_info) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("revs_info=true");
		}// descending
		if (this->conflicts) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("conflicts=true");
		}// conflicts
		return sRet;
	}// to_query_string
	ReadDocOptions::~ReadDocOptions() {}
	//////////////////////////////////////////
	AllDocsOptions::AllDocsOptions() : conflicts(false), descending(false), group(false), include_docs(false),
		attachments(false), att_encoding_info(false), inclusive_end(false), reduce(false), update_seq(false),
		group_level(0), limit(0), skip(0) {
	}
	AllDocsOptions::AllDocsOptions(const AllDocsOptions &other) : conflicts(other.conflicts), descending(other.descending),
		group(other.group), include_docs(other.include_docs),
		attachments(other.attachments), att_encoding_info(other.att_encoding_info), inclusive_end(other.inclusive_end),
		reduce(other.reduce), update_seq(other.update_seq),
		group_level(other.group_level), limit(other.limit), skip(other.skip),
		endkey(other.endkey), end_key(other.end_key), endkey_docid(other.endkey_docid), end_key_doc_id(other.end_key_doc_id),
		key(other.key), stale(other.stale), startkey(other.startkey), start_key(other.start_key), startkey_docid(other.startkey_docid),
		start_key_doc_id(other.startkey_docid) {}
	AllDocsOptions & AllDocsOptions::operator=(const AllDocsOptions &other) {
		if (this != &other) {
			this->conflicts = other.conflicts;
			this->descending = other.descending;
			this->group = other.group;
			this->include_docs = other.include_docs;
			this->attachments = other.attachments;
			this->att_encoding_info = other.att_encoding_info;
			this->inclusive_end = other.inclusive_end;
			this->reduce = other.reduce;
			this->update_seq = other.update_seq;
			this->group_level = other.group_level;
			this->limit = other.limit;
			this->skip = other.skip;
			this->endkey = other.endkey;
			this->end_key = other.end_key;
			this->endkey_docid = other.endkey_docid;
			this->end_key_doc_id = other.end_key_doc_id;
			this->key = other.key;
			this->stale = other.stale;
			this->startkey = other.startkey;
			this->start_key = other.start_key;
			this->startkey_docid = other.startkey_docid;
			this->start_key_doc_id = other.start_key_doc_id;
		}
		return *this;
	}
	AllDocsOptions::~AllDocsOptions() {}
	string_t AllDocsOptions::to_query_string(void) const {
		string_t sRet;
		bool bFirst = true;
		if (!this->start_key_doc_id.empty()) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("start_key_doc_id=") + url_encode(QUOTE_STRING + this->start_key_doc_id + QUOTE_STRING);
		}// endkey
		if (!this->startkey_docid.empty()) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("startkey_docid=") + url_encode(QUOTE_STRING + this->startkey_docid + QUOTE_STRING);
		}// endkey
		if (!this->start_key.empty()) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("start_key=") + url_encode(QUOTE_STRING + this->start_key + QUOTE_STRING);
		}// endkey
		if (!this->startkey.empty()) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("startkey=") + url_encode(QUOTE_STRING+this->startkey+QUOTE_STRING);
		}// endkey
		if (!this->stale.empty()) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("stale=") + url_encode(QUOTE_STRING + this->stale + QUOTE_STRING);
		}// endkey
		if (!this->key.empty()) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("key=") + url_encode(QUOTE_STRING + this->key + QUOTE_STRING);
		}// endkey
		if (!this->end_key_doc_id.empty()) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("end_key_doc_id=") + url_encode(QUOTE_STRING + this->end_key_doc_id + QUOTE_STRING);
		}// endkey
		if (!this->endkey_docid.empty()) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("endkey_docid=") + url_encode(QUOTE_STRING + this->endkey_docid + QUOTE_STRING);
		}// endkey
		if (!this->end_key.empty()) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("end_key=") + url_encode(QUOTE_STRING + this->end_key + QUOTE_STRING);
		}// endkey
		if (!this->endkey.empty()) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("endkey=") + url_encode(QUOTE_STRING + this->endkey + QUOTE_STRING);
		}// endkey
		if (this->skip > 0) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			stringstream_t os;
			os << U("skip=") << this->skip;
			sRet = sRet + os.str();
		}// group_limit
		if (this->limit > 0) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			stringstream_t os;
			os << U("limit=") << this->limit;
			sRet = sRet + os.str();
		}// group_limit
		if (this->group_level > 0) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			stringstream_t os;
			os << U("group_level=") << this->group_level;
			sRet = sRet + os.str();
		}// group_limit
		if (this->update_seq) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("update_seq=true");
		}// descending
		if (this->reduce) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("reduce=true");
		}// descending
		if (this->inclusive_end) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("inclusive_end=true");
		}// inclusive_end
		if (this->att_encoding_info) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("att_encoding_info=true");
		}// att_encoding_info
		if (this->attachments) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("attachments=true");
		}// attachments
		if (this->include_docs) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("include_docs=true");
		}// include_docs
		if (this->group) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("group=true");
		}// group
		if (this->descending) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("descending=true");
		}// descending
		if (this->conflicts) {
			if (bFirst) {
				bFirst = false;
				sRet = QUESTION_STRING;
			}
			else if (!sRet.empty()) {
				sRet = sRet + AND_STRING;
			}
			sRet = sRet + U("conflicts=true");
		}// conflicts
		return sRet;
	}// to_query_string
	////////////////////////////////////////
	AllDocsResponse::AllDocsResponse() : _offset(0), _total_rows(0), _update_seq(0) {}
	AllDocsResponse::AllDocsResponse(const value &val) : _offset(0), _total_rows(0), _update_seq(0) {
		if ((!val.is_null()) && (val.is_object())) {
			if (val.has_field(U("offset"))) {
				this->_offset = val.at(U("offset")).as_integer();
			}
			if (val.has_field(U("total_rows"))) {
				this->_total_rows = val.at(U("total_rows")).as_integer();
			}
			if (val.has_field(U("update_seq"))) {
				this->_update_seq = val.at(U("update_seq")).as_integer();
			}
			if (val.has_field(U("rows"))) {
				const value & v = val.at(U("rows"));
				if ((!v.is_null()) && v.is_array()) {
					auto oAr = v.as_array();
					for (auto it = oAr.begin(); it != oAr.end(); ++it) {
						auto vv = *it;
						this->_rows.push_back(vv);
					}// it
				}// array
			}// rows
		}// val
	}
	AllDocsResponse::AllDocsResponse(const AllDocsResponse &other) :_offset(other._offset),
		_total_rows(other._total_rows), _update_seq(other._update_seq),
		_rows(other._rows) {}
	AllDocsResponse & AllDocsResponse::operator=(const AllDocsResponse &other) {
		if (this != &other) {
			this->_offset = other._offset;
			this->_total_rows = other._total_rows;
			this->_update_seq = other._update_seq;
			this->_rows = other._rows;
		}
		return *this;
	}
	AllDocsResponse::~AllDocsResponse() {}
	size_t AllDocsResponse::offset(void) const { return _offset; }
	size_t AllDocsResponse::total_rows(void) const { return _total_rows; }
	size_t AllDocsResponse::update_seq(void) const { return _update_seq; }
	const std::vector<value> & AllDocsResponse::rows(void) const { return _rows; }
	///////////////////////////////////////
	UpdateResponse::UpdateResponse() :_ok(false) {}
	UpdateResponse::UpdateResponse(bool b, const string_t &sid  /*= string_t() */, const string_t &srev /*= string_t()*/,
		const string_t &err /*= string_t() */, const string_t &reas /*= string_t()*/) : _ok(b), _id(sid), _rev(srev), _error(err), _reason(reas) {}
	UpdateResponse::UpdateResponse(const value &val) : _ok(false) {
		if ((!val.is_null()) && (val.is_object())) {
			if (val.has_field(U("id"))) {
				this->_id = val.at(U("id")).as_string();
			}
			if (val.has_field(U("rev"))) {
				this->_rev = val.at(U("rev")).as_string();
			}
			if (val.has_field(U("error"))) {
				this->_error = val.at(U("error")).as_string();
			}
			if (val.has_field(U("reason"))) {
				this->_reason = val.at(U("reason")).as_string();
			}
			if (val.has_field(U("Location"))) {
				this->_location = val.at(U("Location")).as_string();
			}
			if (val.has_field(U("ok"))) {
				const value &v = val.at(U("ok"));
				if ((!v.is_null()) && v.is_boolean()) {
					this->_ok = v.as_bool();
				}
			}
		}
	}
	UpdateResponse::UpdateResponse(const UpdateResponse &other) :_ok(other._ok), _id(other._id),
		_rev(other._rev), _error(other._error), _reason(other._reason), _location(other._location) {}
	UpdateResponse & UpdateResponse::operator=(const UpdateResponse &other) {
		if (this != &other) {
			this->_ok = other._ok;
			this->_id = other._id;
			this->_rev = other._rev;
			this->_error = other._error;
			this->_reason = other._reason;
			this->_location = other._location;
		}
		return *this;
	}
	UpdateResponse::~UpdateResponse() {}
	bool UpdateResponse::ok(void) const { return _ok; }
	const string_t & UpdateResponse::id(void) const { return _id; }
	const string_t & UpdateResponse::rev(void) const { return _rev; }
	const string_t & UpdateResponse::error(void) const { return _error; }
	const string_t & UpdateResponse::reason(void) const { return _reason; }
	const string_t & UpdateResponse::location(void) const { return _location; }
	void UpdateResponse::to_map(value &oMap) const {
		if (oMap.is_object()) {
			oMap[U("ok")] = value(this->_ok);
			if (!this->_id.empty()) {
				oMap[U("id")] = value(this->_id);
			}
			if (!this->_rev.empty()) {
				oMap[U("rev")] = value(this->_rev);
			}
			if (!this->_error.empty()) {
				oMap[U("error")] = value(this->_error);
			}
			if (!this->_reason.empty()) {
				oMap[U("reason")] = value(this->_reason);
			}
			if (!this->_location.empty()) {
				oMap[U("Location")] = value(this->_location);
			}
		}
	}
	ostream_t & UpdateResponse::write_to(ostream_t &os) const {
		value oMap = value::object();
		this->to_map(oMap);
		os << oMap;
		return os;
	}
	////////////////////////////////////////
	VendorInfo::VendorInfo() {}
	VendorInfo::VendorInfo(const value &val) {
		if ((!val.is_null()) && (val.is_object())) {
			if (val.has_field(U("version"))) {
				this->_version = val.at(U("version")).as_string();
			}
			if (val.has_field(U("name"))) {
				this->_name = val.at(U("name")).as_string();
			}
		}
	}
	VendorInfo::VendorInfo(const VendorInfo &other) :_version(other._version),
		_name(other._name) {}
	VendorInfo & VendorInfo::operator=(const VendorInfo &other) {
		if (this != &other) {
			this->_version = other._version;
			this->_name = other._name;
		}
		return *this;
	}
	VendorInfo::~VendorInfo() {}
	const string_t & VendorInfo::version(void) const {
		return _version;
	}
	const string_t & VendorInfo::name(void) const {
		return _name;
	}
	void VendorInfo::to_map(value &oMap) const {
		if (oMap.is_object()) {
			oMap[U("version")] = value(this->_version);
			oMap[U("name")] = value(this->_name);
		}
	}
	ServerInfo::ServerInfo() {}
	ServerInfo::ServerInfo(const value &val) {
		if ((!val.is_null()) && (val.is_object())) {
			if (val.has_field(U("version"))) {
				this->_version = val.at(U("version")).as_string();
			}
			if (val.has_field(U("uuid"))) {
				this->_uuid = val.at(U("uuid")).as_string();
			}
			if (val.has_field(U("couchdb"))) {
				this->_couchdb = val.at(U("couchdb")).as_string();
			}
			if (val.has_field(U("vendor"))) {
				const value &v = val.at(U("vendor"));
				this->_vendor = VendorInfo(v);
			}
		}// val
	}
	void ServerInfo::to_map(value &oMap) const {
		if (oMap.is_object()) {
			oMap[U("version")] = value(this->_version);
			oMap[U("uuid")] = value(this->_uuid);
			oMap[U("couchdb")] = value(this->_couchdb);
			value val = value::object();
			this->_vendor.to_map(val);
			oMap[U("vendor")] = val;
		}
	}
	ostream_t & ServerInfo::write_to(ostream_t &os) const {
		value oMap = value::object();
		this->to_map(oMap);
		os << oMap;
		return os;
	}
	ServerInfo::ServerInfo(const ServerInfo &other) :_couchdb(other._couchdb),
		_uuid(other._uuid), _version(other._version), _vendor(other._vendor) {}
	ServerInfo & ServerInfo::operator=(const ServerInfo &other) {
		if (this != &other) {
			this->_couchdb = other._couchdb;
			this->_uuid = other._uuid;
			this->_version = other._version;
			this->_vendor = other._vendor;
		}
		return *this;
	}
	ServerInfo::~ServerInfo() {}
	const string_t & ServerInfo::couchdb(void) const {
		return _couchdb;
	}
	const string_t & ServerInfo::uuid(void) const {
		return _uuid;
	}
	const string_t & ServerInfo::version(void) const {
		return _version;
	}
	const VendorInfo & ServerInfo::vendor(void) const {
		return _vendor;
	}
	bool ServerInfo::is_online(void) const {
		return (this->_couchdb == U("Welcome"));
	}
	/////////////////////////////////////////
}// namespace geninfo