//rootobject.cpp
#include "stdafx.h"
///////////////////////
#include "rootobject.h"
///////////////////////
namespace geninfo {
	using namespace web::json;
	//////////////////////////////////
	const string_t STRING_DELETED = U("_deleted");
	const string_t STRING_LOCAL_SEQ = U("_local_seq");
	const string_t STRING_CONFLICTS = U("_conflicts");
	const string_t STRING_DELETED_CONFLICTS = U("_deleted_conflicts");
	const string_t STRING_REVS_INFO = U("_revs_info");
	const string_t STRING_REVISIONS = U("_revisions");
	const string_t STRING_ATTACHMENTS = U("_attachments");
	const string_t STRING_ID = U("_id");
	const string_t STRING_REV = U("_rev");
	const string_t STRING_REV2 = U("rev");
	const string_t STRING_STATUS = U("status");
	const string_t STRING_START = U("start");
	const string_t STRING_IDS = U("ids");
	const string_t STUB = U("stub");
	const string_t REVPOS = U("revpos");
	const string_t LENGTH = U("length");
	const string_t ENCODED_LENGTH = U("encoded_length");
	const string_t ENCODING = U("encoding");
	const string_t CONTENT_TYPE = U("content_type");
	const string_t DATA = U("data");
	const string_t DIGEST = U("digest");
	const string_t STRING_DELETED2 = U("deleted");
	const string_t STRING_AVAILABLE = U("available");
	////////////////////////////////////////////
	AttachmentDesc::AttachmentDesc() :stub(false), revpos(0), length(0), encoded_length(0)
	{
	}
	AttachmentDesc::AttachmentDesc(const value &oMap) : stub(false), revpos(0), length(0), encoded_length(0) {
		if ((!oMap.is_null()) && oMap.is_object()) {
			if (oMap.has_field(STUB)) {
				const value &v = oMap.at(STUB);
				if ((!v.is_null()) && v.is_boolean()) {
					this->stub = v.as_bool();
				}
			}
			if (oMap.has_field(REVPOS)) {
				const value &v = oMap.at(REVPOS);
				if ((!v.is_null()) && v.is_integer()) {
					this->revpos = v.as_integer();
				}
			}
			if (oMap.has_field(LENGTH)) {
				const value &v = oMap.at(LENGTH);
				if ((!v.is_null()) && v.is_integer()) {
					this->length = v.as_integer();
				}
			}
			if (oMap.has_field(ENCODED_LENGTH)) {
				const value &v = oMap.at(ENCODED_LENGTH);
				if ((!v.is_null()) && v.is_integer()) {
					this->encoded_length = v.as_integer();
				}
			}
			if (oMap.has_field(ENCODING)) {
				const value &v = oMap.at(ENCODING);
				if ((!v.is_null()) && v.is_string()) {
					this->encoding = v.as_string();
				}
			}
			if (oMap.has_field(CONTENT_TYPE)) {
				const value &v = oMap.at(CONTENT_TYPE);
				if ((!v.is_null()) && v.is_string()) {
					this->content_type = v.as_string();
				}
			}
			if (oMap.has_field(DATA)) {
				const value &v = oMap.at(DATA);
				if ((!v.is_null()) && v.is_string()) {
					this->data = v.as_string();
				}
			}
			if (oMap.has_field(DIGEST)) {
				const value &v = oMap.at(DIGEST);
				if ((!v.is_null()) && v.is_string()) {
					this->digest = v.as_string();
				};
			}
		}// oMap
	}// AttachmentDesc
	AttachmentDesc::AttachmentDesc(const AttachmentDesc &other) :stub(other.stub), revpos(other.revpos), length(other.length), encoded_length(other.encoded_length),
		encoding(other.encoding), content_type(other.content_type), data(other.data), digest(other.digest) {
	}
	AttachmentDesc & AttachmentDesc::operator=(const AttachmentDesc &other) {
		if (this != &other) {
			this->stub = other.stub;
			this->revpos = other.revpos;
			this->length = other.length;
			this->encoded_length = other.encoded_length;
			this->encoding = other.encoding;
			this->content_type = other.content_type;
			this->data = other.data;
			this->digest = other.digest;
		}
		return *this;
	}
	AttachmentDesc::~AttachmentDesc()
	{
	}
	///////////////////////////////////////
	RevisionsData::RevisionsData() :_start(0) {
	}
	RevisionsData::RevisionsData(const value &oMap) : _start(0) {
		if ((!oMap.is_null()) && oMap.is_object()) {
			if (oMap.has_field(STRING_START)) {
				const value &v = oMap.at(STRING_START);
				if ((!v.is_null()) && v.is_integer()) {
					this->_start = v.as_integer();
				}
			}
			if (oMap.has_field(STRING_IDS)) {
				const value &v = oMap.at(STRING_IDS);
				if ((!v.is_null()) && v.is_array()) {
					const array &oAr = v.as_array();
					std::vector<string_t> &vec = this->_ids;
					std::for_each(oAr.begin(), oAr.end(), [&vec](const value &s) {
						vec.push_back(s.as_string());
					});
				}
			}
		}// oMap
	}
	RevisionsData::RevisionsData(const RevisionsData &other) :_start(other._start),
		_ids(other._ids) {

	}
	RevisionsData & RevisionsData::operator=(const RevisionsData &other) {
		if (this != &other) {
			this->_start = other._start;
			this->_ids = other._ids;
		}
		return *this;
	}
	RevisionsData::~RevisionsData() {

	}
	const size_t  RevisionsData::start(void) const {
		return this->_start;
	}
	const std::vector<string_t> & RevisionsData::ids(void) const {
		return this->_ids;
	}
	/////////////////////////////////////
	RevisionInfo::RevisionInfo() {

	}
	RevisionInfo::RevisionInfo(const value &oMap) {
		if ((!oMap.is_null()) && oMap.is_object()) {
			if (oMap.has_field(STRING_REV2)) {
				const value &v = oMap.at(STRING_REV2);
				if ((!v.is_null()) && v.is_string()) {
					this->_rev = v.as_string();
				}
			}
			if (oMap.has_field(STRING_STATUS)) {
				const value &v = oMap.at(STRING_STATUS);
				if ((!v.is_null()) && v.is_string()) {
					this->_status = v.as_string();
				}
			}
		}// oMap
	}
	RevisionInfo::RevisionInfo(const RevisionInfo &other) :_rev(other._rev),
		_status(other._status) {

	}
	RevisionInfo & RevisionInfo::operator=(const RevisionInfo &other) {
		if (this != &other) {
			this->_rev = other._rev;
			this->_status = other._status;
		}
		return *this;
	}
	RevisionInfo::~RevisionInfo() {

	}
	const string_t & RevisionInfo::rev(void) const {
		return this->_rev;
	}
	const string_t & RevisionInfo::status(void) const {
		return this->_status;
	}
	bool RevisionInfo::is_available(void) const {
		return (!this->_status.empty()) && (this->_status == STRING_AVAILABLE);
	}
	bool RevisionInfo::is_deleted(void) const {
		return (!this->_status.empty()) && (this->_status == STRING_DELETED2);
	}
	////////////////////////////////
	BaseDocument::BaseDocument()
	{
		this->_m_val = value::object();
	}//BaseDocument
	BaseDocument::BaseDocument(const value &oMap) {
		if ((!oMap.is_null()) && oMap.is_object()) {
			this->_m_val = oMap;
		}
		else {
			this->_m_val = value::object();
		}
	}// BaseDocument
	BaseDocument::BaseDocument(const BaseDocument &other) :_m_val(other._m_val)
	{
	}
	BaseDocument & BaseDocument::operator=(const BaseDocument &other) {
		if (this != &other) {
			this->_m_val = other._m_val;
		}
		return (*this);
	}
	BaseDocument::~BaseDocument() {
	}
	value & BaseDocument::get_value(void) {
		return this->_m_val;
	}
	const value & BaseDocument::get_value(void) const {
		return this->_m_val;
	}
	bool BaseDocument::has_field(const string_t &s) const {
		return ((!this->_m_val.is_null()) && this->_m_val.has_field(s));
	}
	const value & BaseDocument::get_value_at(const string_t &s) const {
		static value x;
		return (this->_m_val.has_field(s)) ? this->_m_val.at(s) : x;
	}
	void BaseDocument::set_value_at(const string_t &s, value v) {
		this->_m_val[s] = v;
	}
	void BaseDocument::id(const string_t &s) {
		string_t ss = trim(s);
		if (!ss.empty()) {
			this->set_value_at(STRING_ID, value::string(ss));
		}
	}// id
	void BaseDocument::rev(const string_t &s) {
		this->set_value_at(STRING_REV, value::string(s));
	}// id
	string_t BaseDocument::id(void) const {
		const value &v = this->get_value_at(STRING_ID);
		return ((!v.is_null()) && v.is_string()) ? v.as_string() : string_t();
	}
	string_t  BaseDocument::rev(void) const {
		const value &v = this->get_value_at(STRING_REV);
		return ((!v.is_null()) && v.is_string()) ? v.as_string() : string_t();
	}
	bool BaseDocument::deleted(void) const {
		bool bRet = false;
		if (this->_m_val.has_field(STRING_DELETED)) {
			const value &v = this->_m_val.at(STRING_DELETED);
			if ((!v.is_null()) && v.is_boolean()) {
				bRet = v.as_bool();
			}
		}
		return bRet;
	}
	size_t BaseDocument::local_seq(void) const {
		size_t nRet = 0;
		if (this->_m_val.has_field(STRING_LOCAL_SEQ)) {
			const value &v = this->_m_val.at(STRING_LOCAL_SEQ);
			if ((!v.is_null()) && v.is_integer()) {
				nRet = v.as_integer();
			}
		}
		return nRet;
	}
	std::vector<string_t>  BaseDocument::conflicts(void) const {
		std::vector<string_t> vec;
		if (this->_m_val.has_field(STRING_CONFLICTS)) {
			const value &v = this->_m_val.at(STRING_CONFLICTS);
			if ((!v.is_null()) && v.is_array()) {
				const array &oAr = v.as_array();
				std::for_each(oAr.begin(), oAr.end(), [&vec](const value &s) {
					vec.push_back(s.as_string());
				});
			}
		}
		return vec;
	}
	std::vector<string_t>  BaseDocument::deleted_conflicts(void) const {
		std::vector<string_t> vec;
		if (this->_m_val.has_field(STRING_DELETED_CONFLICTS)) {
			const value &v = this->_m_val.at(STRING_DELETED_CONFLICTS);
			if ((!v.is_null()) && v.is_array()) {
				const array &oAr = v.as_array();
				std::for_each(oAr.begin(), oAr.end(), [&vec](const value &s) {
					vec.push_back(s.as_string());
				});
			}
		}
		return vec;
	}
	std::vector<RevisionInfo>  BaseDocument::revs_info(void) const {
		std::vector<RevisionInfo> vec;
		if (this->_m_val.has_field(STRING_REVS_INFO)) {
			const value &v = this->_m_val.at(STRING_REVS_INFO);
			if ((!v.is_null()) && v.is_array()) {
				const array &oAr = v.as_array();
				std::for_each(oAr.begin(), oAr.end(), [&vec](const value &s) {
					RevisionInfo inf(s);
					vec.push_back(inf);
				});
			}
		}
		return vec;
	}
	RevisionsData  BaseDocument::revisions(void) const {
		RevisionsData oRet;
		if (this->_m_val.has_field(STRING_REVISIONS)) {
			const value &v = this->_m_val.at(STRING_REVISIONS);
			if ((!v.is_null()) && v.is_object()) {
				oRet = RevisionsData(v);
			}
		}
		return oRet;
	}
	std::map<string_t, AttachmentDesc>  BaseDocument::attachments(void) const {
		std::map<string_t, AttachmentDesc> oRet;
		if (this->_m_val.has_field(STRING_ATTACHMENTS)) {
			const value &v = this->_m_val.at(STRING_ATTACHMENTS);
			if ((!v.is_null()) && v.is_object()) {
				const object &obj = v.as_object();
				for (auto it = obj.begin(); it != obj.end(); ++it) {
					const string_t key = (*it).first;
					const value &vv = (*it).second;
					AttachmentDesc oDesc(vv);
					oRet[key] = oDesc;
				}// it
			}// object
		}// attachment
		return oRet;
	}
	ostream_t &  BaseDocument::write_to(ostream_t &os) const {
		if (!this->_m_val.is_null()) {
			os << this->_m_val;
		}
		return os;
	}
	bool BaseDocument::has_id(void) const {
		string_t s = trim(this->id());
		return (!s.empty());
	}
	bool BaseDocument::has_rev(void) const {
		string_t s = trim(this->id());
		string_t st = trim(this->rev());
		return (!s.empty()) && (!st.empty());
	}
	//////////////////////////////////
}// namespace geninfo
