#pragma once
/////////////////////////////
#ifndef __COUCHDBMANAGER_H__
#define __COUCHDBMANAGER_H__
//////////////////////////////////
#include "couchdoc.h"
#include "rootobject.h"
///////////////////////////////////
namespace geninfo {
	class CouchDBManager
	{
	public:
		CouchDBManager();
		CouchDBManager(const string_t &baseUrl);
		CouchDBManager(const string_t &baseUrl, const string_t &data);
		CouchDBManager(const CouchDBManager &other);
		CouchDBManager & operator=(const CouchDBManager &other);
		virtual ~CouchDBManager();
	public:
		const string_t & baseUrl(void) const;
		void baseUrl(const string_t &s);
		const string_t & database(void) const;
		void database(const string_t &s);
	public:
		pplx::task<ServerInfo> get_server_info(void) const;
		pplx::task<std::vector<string_t>> get_all_dbs(void) const;
		pplx::task<std::vector<string_t>> get_uuids(size_t count = 1) const;
		pplx::task<bool> exists_database(const string_t &s = string_t()) const;
		pplx::task<DatabaseInfo> get_database_info(const string_t &s = string_t()) const;
		pplx::task<UpdateResponse> create_database(const string_t &db) const;
		pplx::task<UpdateResponse> delete_database(const string_t &db) const;
		//
		pplx::task<string_t> exists_document(const string_t &id, const string_t &db = string_t()) const;
		pplx::task<UpdateResponse>  create_document(const value &doc, const string_t &db = string_t()) const;
		pplx::task<value> read_document(const string_t &id, const ReadDocOptions &options = ReadDocOptions(), const string_t &db = string_t()) const;
		pplx::task<UpdateResponse>  maintains_document(value &doc, const string_t &db = string_t()) const;
		pplx::task<UpdateResponse>  delete_document(const string_t &docid, const string_t &db = string_t()) const;
		//
		pplx::task<AllDocsResponse> get_all_docs(const AllDocsOptions &options = AllDocsOptions(), const string_t &db = string_t()) const;
		pplx::task<std::vector<string_t> > get_all_docs_ids(const AllDocsOptions &options = AllDocsOptions(), const string_t &db = string_t()) const;
		pplx::task<AllDocsResponse> get_array_docs(const std::vector<string_t> &keys, const AllDocsOptions &options = AllDocsOptions(), const string_t &db = string_t()) const;
		pplx::task<std::vector<value>> get_array_docs_values(const std::vector<string_t> &keys, AllDocsOptions &options = AllDocsOptions(), const string_t &db = string_t()) const;
		pplx::task<std::vector<UpdateResponse>> bulk_docs(const std::vector<value> &oVal, const string_t &db = string_t()) const;
		pplx::task<std::vector<UpdateResponse>> maintains_docs(std::vector<value> &oVal, bool bDelete = false, const string_t &db = string_t()) const;
		//
		pplx::task<BaseDocument> read_basedocument(const string_t &id, const ReadDocOptions &options = ReadDocOptions(), const string_t &db = string_t()) const;
		pplx::task<std::vector<BaseDocument>> get_array_basedocs_values(const std::vector<string_t> &keys, AllDocsOptions &options = AllDocsOptions(), const string_t &db = string_t()) const;
	private:
		string_t _baseUrl;
		string_t _database;
	}; // class CouchDBLanager
}// namespace couchdb
 /////////////////////////////////
#endif // __COUCHDBMANAGER_H__
