#pragma once
#ifndef __ROOTOBJECT_H__
#define __ROOTOBJECT_H__
//////////////////////////////
#include "genutils.h"
////////////////////////////
namespace geninfo
{
	//////////////////////////////////////
	class AttachmentDesc
	{
	public:
		AttachmentDesc();
		AttachmentDesc(const value &oMap);
		AttachmentDesc(const AttachmentDesc &other);
		AttachmentDesc & operator=(const AttachmentDesc &other);
		~AttachmentDesc();
	public:
		bool stub;
		size_t revpos;
		size_t length;
		size_t encoded_length;
		string_t encoding;
		string_t content_type;
		string_t data;
		string_t digest;
		string_t name;
	};
	//////////////////////////////////
	class RevisionsData {
	public:
		RevisionsData();
		RevisionsData(const value &oMap);
		RevisionsData(const RevisionsData &other);
		RevisionsData & operator=(const RevisionsData &other);
		~RevisionsData();
	public:
		const size_t  start(void) const;
		const std::vector<string_t> & ids(void) const;
	private:
		size_t _start;
		std::vector<string_t> _ids;
	};// class RevisionsData
	class RevisionInfo {
	public:
		RevisionInfo();
		RevisionInfo(const value &oMap);
		RevisionInfo(const RevisionInfo &other);
		RevisionInfo & operator=(const RevisionInfo &other);
		~RevisionInfo();
	public:
		const string_t & rev(void) const;
		const string_t & status(void) const;
		bool is_available(void) const;
		bool is_deleted(void) const;
	private:
		string_t _rev;
		string_t _status;
	};// class RevisionInfo
	/////////////////////////////////
	class BaseDocument {
		friend class CouchDataManager;
	public:
		BaseDocument();
		BaseDocument(const value &oMap);
		BaseDocument(const BaseDocument &other);
		BaseDocument & operator=(const BaseDocument &other);
		virtual ~BaseDocument();
	public:
		const value & operator()() const {
			return this->_m_val;
		}
		const value & get_value(void) const;
	public:
		bool deleted(void) const;
		size_t local_seq(void) const;
		string_t  id(void) const;
		string_t  rev(void) const;
		std::vector<string_t>  conflicts(void) const;
		std::vector<string_t>  deleted_conflicts(void) const;
		std::vector<RevisionInfo>  revs_info(void) const;
		RevisionsData  revisions(void) const;
		std::map<string_t, AttachmentDesc>  attachments(void) const;
	public:
		const value &at(const string_t &s) const {
			return this->_m_val.at(s);
		}
		value &at(const string_t &s) {
			return this->_m_val.at(s);
		}
	public:
		void set_bool(const string_t &key, bool b) {
			this->set_value_at(key, value::boolean(b));
		}
		void set_int(const string_t &key, int b) {
			this->set_value_at(key, value::number(b));
		}
		void set_size_t(const string_t &key, size_t b) {
			this->set_value_at(key, value::number(b));
		}
		void set_float(const string_t &key, float b) {
			this->set_value_at(key, value::number(b));
		}
		void set_double(const string_t &key, double b) {
			this->set_value_at(key, value::number(b));
		}
		void set_string(const string_t &key, const string_t & b) {
			this->set_value_at(key, value::string(b));
		}
	public:
		
		bool has_id(void) const;
		bool has_rev(void) const;
		ostream_t & write_to(ostream_t &os) const;
	protected:
		value & get_value(void);
		void id(const string_t &s);
		void rev(const string_t &s);
		bool has_field(const string_t &s) const;
		const value & get_value_at(const string_t &s) const;
		void set_value_at(const string_t &s, value v);
	protected:
		value _m_val;
	};// class BaseDocument
	/////////////////////////////
}// namespace geninfo
////////////////////////////////
inline utility::ostream_t & operator<<(utility::ostream_t &os, const geninfo::BaseDocument &doc) {
	return doc.write_to(os);
}
///////////////////////////
#endif // __ROOTOBJECT_H__
