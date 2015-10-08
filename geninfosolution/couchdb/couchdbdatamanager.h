#pragma once
#ifndef __COUCHDBDATAMANAGER_H__
#define __COUCHDBDATAMANAGER_H__
////////////////////////////////
#include <idatamanager.h>
///////////////////////////////
namespace geninfo {
	//////////////////////////////
	class CouchDBDataManager : public IDataManager
	{
	public:
		CouchDBDataManager();
		CouchDBDataManager(const string &baseUrl, const string &database);
		CouchDBDataManager(const CouchDBDataManager &other);
		CouchDBDataManager & operator=(const CouchDBDataManager &other);
		virtual ~CouchDBDataManager();
	public:
		virtual Value read_doc(const string &id, bool bAttachments = false, bool bMeta = false);
		virtual Value insert_doc(const Value &doc);
		virtual Value update_doc(const Value &doc);
		virtual Value remove_doc(const Value &doc);
		virtual Value read_docs_range(const string &startkey, const string &endkey,
			int skip = 0, int limit = 0, bool bDoc = false);
		virtual Value read_docs_array(const std::vector<string> ids);
		virtual Value maintains_docs(const std::vector<Value> docs, bool bDelete = false);
	private:
		string m_baseurl;
		string m_database;
	};
	////////////////////////
}// namespace geninfo
/////////////////////////////////////
#endif // __COUCHDBDATAMANAGER_H__
