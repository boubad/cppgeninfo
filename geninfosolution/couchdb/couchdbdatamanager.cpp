#include "stdafx.h"
#include "couchdbdatamanager.h"
#include "couchdoc.h"
#include "genutils.h"
/////////////////////////////
#include <iostream>
#include <iomanip>
///////////////////////////////
#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>
//////////////////////////////
namespace geninfo {
	using namespace utility;                    // Common utilities like string conversions
	using namespace web;                        // Common features like URIs.
	using namespace web::http;                  // Common HTTP functionality
	using namespace web::json;
	using namespace web::http::client;
	using namespace concurrency::streams;
	using namespace pplx;
	//////////////////////////////////////
	const std::string DEFAULT_BASEURL("http://localhost:5984");
	const std::string DEFAULT_DATABASE("geninfo");
	////////////////////////////////
	const utility::string_t ACCEPT_STRING = U("accept");
	const utility::string_t APPLICATION_JSON_STRING = U("application/json");
	const utility::string_t HEADER_IF_MATCH = U("If-Match");
	const utility::string_t HEADER_ETAG = U("ETag");
	const utility::string_t HEADER_COMMIT = U("X-Couch-Full-Commit");
	const utility::string_t HEADER_CONTENT_TYPE = U("Content-Type");
	const utility::string_t STRING_TRUE = U("true");
	const utility::string_t STRING_FALSE = U("false");
	const utility::string_t STRING_EQ = U("=");
	const utility::string_t HEADER_LOCATION = U("Location");
	const utility::string_t STRING_OK = U("ok");
	const utility::string_t STRING_ID = U("_id");
	const utility::string_t STRING_ID2 = U("id");
	const utility::string_t STRING_REV = U("_rev");
	const utility::string_t STRING_REV2 = U("rev");
	const utility::string_t STRING_ATTACHMENTS = U("_attachments");
	const utility::string_t STRING_SEPAR = U("&");
	const utility::string_t STRING_SLASH = U("/");
	const utility::string_t STRING_QUESTION = U("?");
	const utility::string_t STRING_ALL_DBS = U("_all_dbs");
	const utility::string_t STRING_UUIDS_COUNT = U("_uuids?count=");
	const utility::string_t STRING_UUIDS = U("uuids");
	const utility::string_t STRING_ALL_DOCS = U("_all_docs");
	const utility::string_t STRING_KEYS = U("keys");
	const utility::string_t STRING_DOCS = U("docs");
	const utility::string_t STRING_DOC = U("doc");
	const utility::string_t STRING_BULK_DOCS = U("_bulk_docs");
	const utility::string_t STRING_DELETED = U("_deleted");
	////////////////////////////////////////////
	static Value value_to_infovalue(const web::json::value &v) {
		Value oRet;
		if (!v.is_null()) {
			if (v.is_array()) {
				Array oAr;
				const web::json::array &aa = v.as_array();
				for (auto it = aa.begin(); it != aa.end(); ++it) {
					auto v = *it;
					Value vv = value_to_infovalue(v);
					oAr.append_value(vv);
				}// it
				PArray pp = std::make_shared<Array>(oAr);
				oRet = Value(pp);
			}
			else if (v.is_object()) {
				Object oObj;
				const web::json::object &obj = v.as_object();
				for (auto it = obj.begin(); it != obj.end(); ++it) {
					utility::string_t s = (*it).first;
					web::json::value vx = (*it).second;
					std::string key = convert_to_string(s);
					Value vv = value_to_infovalue(vx);
					oObj.set_value(key, vv);
				}
				PObject oo = std::make_shared<Object>(oObj);
				oRet = Value(oo);
			}
			else if (v.is_boolean()) {
				oRet = Value(v.as_bool());
			}
			else if (v.is_double()) {
				oRet = Value(v.as_double());
			}
			else if (v.is_integer()) {
				oRet = Value(v.as_integer());
			}
			else if (v.is_string()) {
				utility::string_t s = v.as_string();
				std::string ss = convert_to_string(s);
				oRet = Value(ss);
			}
			else if (v.is_number()) {
				oRet = Value(v.as_double());
			}
		}// not null
		return oRet;
	}//value_to_infovalue
	static web::json::value infovalue_to_value(const Value &v) {
		web::json::value oRet;
		if (!v.is_null()) {
			switch (v.type()) {
			case value_type::boolean_type:
				oRet = web::json::value(v.as_bool());
				break;
			case value_type::double_type:
				oRet = web::json::value(v.as_double());
				break;
			case value_type::integer_type:
				oRet = web::json::value(v.as_integer());
				break;
			case value_type::string_type:
			{
				std::string s = v.as_string();
				utility::string_t sc = convert_from_string(s);
				oRet = web::json::value(sc);
			}
			break;
			case value_type::array_type:
			{
				std::vector<web::json::value> oVec;
				Array *pAr = v.as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue pv = (*pAr)[i];
						Value *v = pv.get();
						if (v != nullptr) {
							web::json::value vz = infovalue_to_value(*v);
							if (!vz.is_null()) {
								oVec.push_back(vz);
							}
						}// v
					}// i
				}// pAr
				oRet = web::json::value::array(oVec);
			}
			break;
			case value_type::object_type:
			{
				web::json::value vt = web::json::value::object();
				web::json::object & obj = vt.as_object();
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::set<std::string> keys = pObj->keys();
					for (auto it = keys.begin(); it != keys.end(); ++it) {
						std::string key = *it;
						Value *p = pObj->at(key);
						if (p != nullptr) {
							web::json::value val = infovalue_to_value(*p);
							utility::string_t ss = convert_from_string(key);
							obj[ss] = val;
						}
					}// it
				}// pObj
				oRet = vt;
			}
			break;
			default:
				break;
			}// type
		}// not null
		return oRet;
	}//infovalue_to_object
	////////////////////////////////
	static task<utility::string_t> st_exists_doc(const utility::string_t &baseUrl, const utility::string_t &db, const utility::string_t &id) {
		utility::string_t uri = db;
		uri = uri + STRING_SLASH + id;
		http_client client(baseUrl);
		http_request request(methods::HEAD);
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) {
			utility::string_t sRet;
			bool bRet = (response.status_code() == status_codes::OK) || (response.status_code() == status_codes::NotModified);
			if (bRet) {
				auto headers = response.headers();
				if (headers.has(HEADER_ETAG)) {
					utility::string_t sx = headers[HEADER_ETAG];
					size_t n = sx.length();
					if (n > 2) {
						sRet = sx.substr(1, n - 2);
					}
				}
			}
			else if (response.status_code() != status_codes::NotFound) {
				throw http_exception(response.status_code());
			}
			return task_from_result(sRet);
		});
	}//st_exists_doc
	static task<value>  st_read_doc(const utility::string_t &baseUrl, const utility::string_t &db, const utility::string_t &id, const ReadDocOptions &options) {
		utility::string_t uri = db;
		uri = uri + STRING_SLASH + id;
		http_client client(baseUrl);
		http_request request(methods::GET);
		utility::string_t sreq = options.to_query_string();
		if (!sreq.empty()) {
			uri = uri + sreq;
		}
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		utility::string_t rev = options.rev;
		if (!rev.empty()) {
			rev = U("\"") + rev + U("\"");
			request.headers().add(HEADER_IF_MATCH, rev);
		}
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) {
			auto code = response.status_code();
			if ((code == status_codes::OK) || (code == status_codes::NotModified)) {
				return response.extract_json();
			}
			return task_from_result(value());
		}).then([=](task<value> t2) {
			value oRet;
			try {
				oRet = t2.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// st_read_doc
	static task<UpdateResponse>  st_create_doc(const utility::string_t &baseUrl, const utility::string_t &db, const value &doc) {
		utility::string_t uri = db;
		http_client client(baseUrl);
		http_request request(methods::POST);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.headers().add(HEADER_COMMIT, STRING_TRUE);
		request.set_request_uri(uri);
		request.set_body(doc);
		return client.request(request).then([=](http_response response) {
			return response.extract_json();
		}).then([=](task<value> previousTask) {
			UpdateResponse oRet;
			try {
				const value & jsonvalue = previousTask.get();
				oRet = UpdateResponse(jsonvalue);
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// st_create_doc
	static pplx::task<UpdateResponse>  st_maintains_doc(const utility::string_t &baseUrl, const utility::string_t &db, const value &doc) {
		if (!doc.is_object()) {
			UpdateResponse r;
			return task_from_result(r);
		}
		utility::string_t id;
		std::set<utility::string_t> oSet;
		value docx(doc);
		utility::string_t UNDERSCORE(U("_"));
		object obj = docx.as_object();
		for (auto it = obj.begin(); it != obj.end(); ++it) {
			utility::string_t key = (*it).first;
			if (key != STRING_ID) {
				if (key.find_first_of(UNDERSCORE) == 0) {
					oSet.insert(key);
				}
			}
		}// it
		for (auto it = oSet.begin(); it != oSet.end(); ++it) {
			obj.erase(*it);
		}
		if (obj.find(STRING_ID) != obj.end()) {
			id = (obj[STRING_ID]).as_string();
		}
		std::vector<std::pair<utility::string_t, value>> vec;
		for (auto it = obj.begin(); it != obj.end(); ++it) {
			vec.push_back(std::make_pair((*it).first, (*it).second));
		}
		value vNew = value::object(vec);
		if (id.empty()) {
			return st_create_doc(baseUrl, db, vNew);
		}
		utility::string_t rev = st_exists_doc(baseUrl, db, id).get();
		if (rev.empty()) {
			return st_create_doc(baseUrl, db, vNew);
		}
		ReadDocOptions options;
		options.attachments = true;
		return st_read_doc(baseUrl, db, id, options).then([&](task<value> t1) {
			value val;
			try {
				val = t1.get();
			}
			catch (...) {}
			if ((!val.is_null()) && val.is_object() && val.has_field(STRING_ID)) {
				object oo = val.as_object();
				if (oo.find(STRING_REV) != oo.end()) {
					rev = (oo[STRING_REV]).as_string();
					vNew[STRING_REV] = value(rev);
				}
				if (val.has_field(STRING_ATTACHMENTS)) {
					vNew[STRING_ATTACHMENTS] = val.at(STRING_ATTACHMENTS);
				}
			}
			utility::string_t uri = db;
			uri = uri + STRING_SLASH + id;
			http_client client(baseUrl);
			http_request request(methods::PUT);
			request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
			if (!rev.empty()) {
				uri = uri + U("?rev=") + rev;
				request.headers().add(HEADER_IF_MATCH, rev);
			}
			request.headers().add(HEADER_COMMIT, STRING_TRUE);
			request.set_request_uri(uri);
			request.set_body(vNew);
			return client.request(request);
		}).then([=](http_response response) {
			return response.extract_json();
		}).then([=](task<value> previousTask) {
			UpdateResponse oRet;
			try {
				const value & jsonvalue = previousTask.get();
				oRet = UpdateResponse(jsonvalue);
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// st_maintains_doc
	static pplx::task<UpdateResponse>  st_del_doc(const utility::string_t &baseUrl,
		const utility::string_t &db, const utility::string_t &docid) {
		UpdateResponse oDef;
		if (docid.empty()) {
			return pplx::task_from_result(oDef);
		}
		string_t uri = db;
		uri = uri + STRING_SLASH + docid;
		http_client client(baseUrl);
		http_request request(methods::HEAD);
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) {
			string_t rev;
			bool bRet = (response.status_code() == status_codes::OK) || (response.status_code() == status_codes::NotModified);
			if (bRet) {
				auto headers = response.headers();
				if (headers.has(HEADER_ETAG)) {
					string_t sx = headers[HEADER_ETAG];
					size_t n = sx.length();
					if (n > 2) {
						rev = sx.substr(1, n - 2);
					}
				}
			}
			else {
				throw http_exception(response.status_code());
			}
			http_client cl(baseUrl);
			http_request req(methods::DEL);
			req.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
			req.headers().add(HEADER_IF_MATCH, rev);
			req.headers().add(HEADER_COMMIT, STRING_TRUE);
			req.set_request_uri(uri);
			return cl.request(req);
		}).then([=](http_response response) {
			return response.extract_json();
		}).then([=](task<value> previousTask) {
			UpdateResponse oRet;
			try {
				const value & jsonvalue = previousTask.get();
				oRet = UpdateResponse(jsonvalue);
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// st_del_doc
	static task<std::vector<string_t> >  st_docs_ids(const string_t &baseUrl, const string_t &db, const AllDocsOptions &options) {
		string_t uri = db;
		uri = uri + STRING_SLASH + STRING_ALL_DOCS;
		http_client client(baseUrl);
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		string_t sreq = options.to_query_string();
		if (!sreq.empty()) {
			uri = uri + sreq;
		}
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) {
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> previousTask) {
			std::vector<string_t> oRet;
			try {
				const value  & jsonvalue = previousTask.get();
				AllDocsResponse rsp = AllDocsResponse(jsonvalue);
				auto vv = rsp.rows();
				for (auto it = vv.begin(); it != vv.end(); ++it) {
					const value &vx = *it;
					if ((!vx.is_null()) && vx.is_object() && vx.has_field(STRING_ID2)) {
						string_t s = (vx.at(STRING_ID2)).as_string();
						if (!s.empty()) {
							oRet.push_back(s);
						}
					}
				}// it
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//st_docs_ids
	static task<AllDocsResponse>  st_get_all_docs(const string_t &baseUrl, const string_t &db, const AllDocsOptions &options) {
		string_t uri = db;
		uri = uri + STRING_SLASH + STRING_ALL_DOCS;
		http_client client(baseUrl);
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		string_t sreq = options.to_query_string();
		if (!sreq.empty()) {
			uri = uri + sreq;
		}
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) {
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> previousTask) {
			AllDocsResponse oRet;
			try {
				const value  & jsonvalue = previousTask.get();
				oRet = AllDocsResponse(jsonvalue);
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_all_docs
	static task<std::vector<UpdateResponse>> st_bulk_docs(const string_t &baseUrl,
		const string_t &db, const std::vector<value> &oVal) {
		string_t uri = db;
		uri = uri + STRING_SLASH + STRING_BULK_DOCS;
		http_client client(baseUrl);
		http_request request(methods::POST);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.set_request_uri(uri);
		value oAr = value::array(oVal);
		value doc = value::object();
		doc[STRING_DOCS] = oAr;
		request.set_body(doc);
		return client.request(request).then([=](http_response response) {
			if (response.status_code() == status_codes::Created) {
				return response.extract_json();
			}
			throw http_exception(response.status_code());
		}).then([=](task<value> previousTask) {
			std::vector<UpdateResponse> oRet;
			try {
				const value & jsonvalue = previousTask.get();
				if ((!jsonvalue.is_null()) && jsonvalue.is_array()) {
					size_t n = jsonvalue.size();
					for (size_t i = 0; i < n; ++i) {
						const value &v = jsonvalue.at(i);
						UpdateResponse inf(v);
						oRet.push_back(inf);
					}// i
				}// array
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//:bulk_docs
	static task<AllDocsResponse> st_array_docs(const string_t &baseUrl, const string_t &db,
		const std::vector<string_t> &keys,
		const AllDocsOptions &options) {
		std::vector<value> vx;
		size_t nx = keys.size();
		for (size_t i = 0; i < nx; ++i) {
			string_t s = keys[i];
			if (!s.empty()) {
				value vw(s);
				vx.push_back(vw);
			}
		}// i
		if (vx.empty()) {
			AllDocsResponse ox;
			return task_from_result(ox);
		}
		value oAr = value::array(vx);
		value doc = value::object();
		doc[STRING_KEYS] = oAr;
		string_t uri = db;
		uri = uri + STRING_SLASH + STRING_ALL_DOCS;
		http_client client(baseUrl);
		http_request request(methods::POST);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		string_t sreq = options.to_query_string();
		if (!sreq.empty()) {
			uri = uri + sreq;
		}
		request.set_request_uri(uri);
		request.set_body(doc);
		return client.request(request).then([=](http_response response) {
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> previousTask) {
			AllDocsResponse oRet;
			try {
				const value  &jsonvalue = previousTask.get();
				oRet = AllDocsResponse(jsonvalue);
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_array_docs
	 //////////////////////////////
	CouchDBDataManager::CouchDBDataManager() :
		m_baseurl(DEFAULT_BASEURL), m_database(DEFAULT_DATABASE)
	{
	}


	CouchDBDataManager::~CouchDBDataManager()
	{
	}
	CouchDBDataManager::CouchDBDataManager(const std::string &baseUrl,
		const std::string &database) :m_baseurl(baseUrl), m_database(database) {
		/*
		std::string m_baseurl;
		std::string m_database;
		*/
	}
	CouchDBDataManager::CouchDBDataManager(const CouchDBDataManager &other) :
		m_baseurl(other.m_baseurl), m_database(other.m_database) {

	}
	CouchDBDataManager & CouchDBDataManager::operator=(const CouchDBDataManager &other) {
		if (this != &other) {
			this->m_baseurl = other.m_baseurl;
			this->m_database = other.m_database;
		}
		return (*this);
	}
	///////////////////////////////

	/////////////////////////////////
}// namespace geninfo
