//couchdbmanager.h
#include "stdafx.h"
#include "couchdbmanager.h"
/////////////////////////////////
namespace geninfo {
	//////////////////////////////////////
	using namespace utility;                    // Common utilities like string conversions
	using namespace web;                        // Common features like URIs.
	using namespace web::http;                  // Common HTTP functionality
	using namespace web::json;
	using namespace web::http::client;
	using namespace concurrency::streams;
	using namespace pplx;
	using namespace std;
	//////////////////////////////////////
	const string_t DEFAULT_BASEURL = U("http://localhost:5984");
	const string_t DEFAULT_DATABASE = U("geninfo");
	///////////////////////////////////////////
	const string_t ACCEPT_STRING = U("accept");
	const string_t APPLICATION_JSON_STRING = U("application/json");
	const string_t HEADER_IF_MATCH = U("If-Match");
	const string_t HEADER_ETAG = U("ETag");
	const string_t HEADER_COMMIT = U("X-Couch-Full-Commit");
	const string_t HEADER_CONTENT_TYPE = U("Content-Type");
	const string_t STRING_TRUE = U("true");
	const string_t STRING_FALSE = U("false");
	const string_t STRING_EQ = U("=");
	const string_t HEADER_LOCATION = U("Location");
	const string_t STRING_OK = U("ok");
	const string_t STRING_ID = U("_id");
	const string_t STRING_ID2 = U("id");
	const string_t STRING_REV = U("_rev");
	const string_t STRING_REV2 = U("rev");
	const string_t STRING_ATTACHMENTS = U("_attachments");
	const string_t STRING_SEPAR = U("&");
	const string_t STRING_SLASH = U("/");
	const string_t STRING_QUESTION = U("?");
	const string_t STRING_ALL_DBS = U("_all_dbs");
	const string_t STRING_UUIDS_COUNT = U("_uuids?count=");
	const string_t STRING_UUIDS = U("uuids");
	const string_t STRING_ALL_DOCS = U("_all_docs");
	const string_t STRING_KEYS = U("keys");
	const string_t STRING_DOCS = U("docs");
	const string_t STRING_DOC = U("doc");
	const string_t STRING_BULK_DOCS = U("_bulk_docs");
	const string_t STRING_DELETED = U("_deleted");
	////////////////////////////////////////////
	task<std::vector<UpdateResponse>> CouchDBManager::maintains_docs(std::vector<value> &oVal, bool bDelete /*= false */, const string_t &db /*= string_t()*/) const {
		typedef task<UpdateResponse> MyTask;
		std::vector<MyTask> oTasks;
		if (!bDelete) {
			for (auto it = oVal.begin(); it != oVal.end(); ++it) {
				oTasks.push_back(this->maintains_document(*it, db));
			}// it
		}
		else {
			for (auto it = oVal.begin(); it != oVal.end(); ++it) {
				auto v = *it;
				if (v.has_field(STRING_ID)) {
					string_t id = (v.at(STRING_ID)).as_string();
					if (!id.empty()) {
						oTasks.push_back(this->delete_document(id, db));
					}
				}
			}// it
		}
		if (oTasks.empty()) {
			std::vector < UpdateResponse> ox;
			return pplx::task_from_result(ox);
		}
		return pplx::when_all(oTasks.begin(), oTasks.end());
	}//maintains_docs
	task<std::vector<UpdateResponse>> CouchDBManager::bulk_docs(const std::vector<value> &oVal, const string_t &db /*= string_t()*/) const {
		string_t uri = (db.length() > 0) ? db : this->database();
		uri = uri + STRING_SLASH + STRING_BULK_DOCS;
		http_client client(this->baseUrl());
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
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//:bulk_docs
	task<AllDocsResponse> CouchDBManager::get_array_docs(const std::vector<string_t> &keys,
		const AllDocsOptions &options /*= AllDocsOptions() */, const string_t &db /*= String()*/) const {
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
		string_t uri = (db.empty()) ? this->database() : db;
		uri = uri + STRING_SLASH + STRING_ALL_DOCS;
		http_client client(this->baseUrl());
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
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_array_docs
	task<std::vector<value>> CouchDBManager::get_array_docs_values(const std::vector<string_t> &keys, AllDocsOptions &options /*= AllDocsOptions()*/,
		const string_t &db /*= string_t()*/) const {
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
			std::vector<value> ox;
			return task_from_result(ox);
		}
		value oAr = value::array(vx);
		value doc = value::object();
		doc[STRING_KEYS] = oAr;
		string_t uri = (db.empty()) ? this->database() : db;
		uri = uri + STRING_SLASH + STRING_ALL_DOCS;
		http_client client(this->baseUrl());
		http_request request(methods::POST);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		options.include_docs = true;
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
			std::vector<value> oRet;
			try {
				const value  &jsonvalue = previousTask.get();
				AllDocsResponse rsp = AllDocsResponse(jsonvalue);
				auto vv = rsp.rows();
				for (auto it = vv.begin(); it != vv.end(); ++it) {
					const value &vx = *it;
					if ((!vx.is_null()) && vx.is_object() && vx.has_field(STRING_DOC)) {
						value val = vx.at(STRING_DOC);
						if ((!val.is_null()) && val.is_object()) {
							oRet.push_back(val);
						}
					}
				}// it
			}
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_array_docs_values
	task<std::vector<BaseDocument>> CouchDBManager::get_array_basedocs_values(const std::vector<string_t> &keys, 
		AllDocsOptions &options /*= AllDocsOptions()*/, const string_t &db /*= string_t()*/) const {
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
			std::vector<BaseDocument> ox;
			return task_from_result(ox);
		}
		value oAr = value::array(vx);
		value doc = value::object();
		doc[STRING_KEYS] = oAr;
		string_t uri = (db.empty()) ? this->database() : db;
		uri = uri + STRING_SLASH + STRING_ALL_DOCS;
		http_client client(this->baseUrl());
		http_request request(methods::POST);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		options.include_docs = true;
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
			std::vector<BaseDocument> oRet;
			try {
				const value  &jsonvalue = previousTask.get();
				AllDocsResponse rsp = AllDocsResponse(jsonvalue);
				auto vv = rsp.rows();
				for (auto it = vv.begin(); it != vv.end(); ++it) {
					const value &vx = *it;
					if ((!vx.is_null()) && vx.is_object() && vx.has_field(STRING_DOC)) {
						const value &val = vx.at(STRING_DOC);
						if ((!val.is_null()) && val.is_object()) {
							BaseDocument doc(val);
							oRet.push_back(doc);
						}
					}
				}// it
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_array_basedocs_values
	task<AllDocsResponse>  CouchDBManager::get_all_docs(const AllDocsOptions &options /*= AllDocsOptions()*/, const string_t &db /*= string_t()*/) const {
		string_t uri = (db.empty()) ? this->database() : db;
		uri = uri + STRING_SLASH + STRING_ALL_DOCS;
		http_client client(this->baseUrl());
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
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_all_docs
	task<std::vector<string_t> >  CouchDBManager::get_all_docs_ids(const AllDocsOptions &options /*= AllDocsOptions()*/, const string_t &db /*= string_t()*/) const {
		string_t uri = (db.empty()) ? this->database() : db;
		uri = uri + STRING_SLASH + STRING_ALL_DOCS;
		http_client client(this->baseUrl());
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
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_all_docs_ids
	pplx::task<UpdateResponse>  CouchDBManager::delete_document(const string_t &docid, const string_t &db /*= string_t()*/) const {
		UpdateResponse oDef;
		if (docid.empty()) {
			return pplx::task_from_result(oDef);
		}
		string_t uri = (db.empty()) ? this->database() : db;
		uri = uri + STRING_SLASH + docid;
		http_client client(this->baseUrl());
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
			http_client cl(this->baseUrl());
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
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// delete_document
	pplx::task<UpdateResponse>  CouchDBManager::maintains_document(value &doc, const string_t &db /*= string_t()*/) const {
		if (!doc.has_field(STRING_ID)) {
			return this->create_document(doc, db);
		}
		string_t id = (doc.at(STRING_ID)).as_string();
		ReadDocOptions options;
		options.attachments = true;
		return this->read_document(id, options, db).then([=](task<value> t1) {
			value val;
			try {
				val = t1.get();
			}
			catch (...) {}
			value docx = doc;
			string_t sid = (docx.at(STRING_ID)).as_string();
			string_t rev;
			if ((!val.is_null()) && val.is_object() && val.has_field(STRING_ID)) {
				if (val.has_field(STRING_REV)) {
					rev = (val.at(STRING_REV)).as_string();
					docx[STRING_REV] = val.at(STRING_REV);
				}
				if (val.has_field(STRING_ATTACHMENTS)) {
					docx[STRING_ATTACHMENTS] = val.at(STRING_ATTACHMENTS);
				}
			}
			string_t uri = (db.empty()) ? this->database() : db;
			uri = uri + STRING_SLASH + sid;
			http_client client(this->baseUrl());
			http_request request(methods::PUT);
			request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
			if (!rev.empty()) {
				uri = uri + U("?rev=") + rev;
				request.headers().add(HEADER_IF_MATCH, rev);
			}
			request.headers().add(HEADER_COMMIT, STRING_TRUE);
			request.set_request_uri(uri);
			request.set_body(docx);
			return client.request(request);
		}).then([=](http_response response) {
			return response.extract_json();
		}).then([=](task<value> previousTask) {
			UpdateResponse oRet;
			try {
				const value & jsonvalue = previousTask.get();
				oRet = UpdateResponse(jsonvalue);
			}
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// maintains_document
	task<value>  CouchDBManager::read_document(const string_t &id, const ReadDocOptions &options /*= ReadDocOptions()*/,
		const string_t &db /* = string_t()*/) const {
		string_t uri = (db.empty()) ? this->database() : db;
		uri = uri + STRING_SLASH + id;
		http_client client(this->baseUrl());
		http_request request(methods::GET);
		string_t sreq = options.to_query_string();
		if (!sreq.empty()) {
			uri = uri + sreq;
		}
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		string_t rev = options.rev;
		if (!rev.empty()) {
			rev = U("\"") + rev + U("\"");
			request.headers().add(HEADER_IF_MATCH, rev);
		}
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) {
			value oRet;
			auto code = response.status_code();
			if ((code == status_codes::OK) || (code == status_codes::NotModified)) {
				return response.extract_json();
			}
			return task_from_result(oRet);
		}).then([=](task<value> t2) {
			value v;
			try {
				v = t2.get();
			}
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(v);
		});
	}// read_document
	task<BaseDocument>  CouchDBManager::read_basedocument(const string_t &id, const ReadDocOptions &options /*= ReadDocOptions()*/,
		const string_t &db /* = string_t()*/) const {
		string_t uri = (db.empty()) ? this->database() : db;
		uri = uri + STRING_SLASH + id;
		http_client client(this->baseUrl());
		http_request request(methods::GET);
		string_t sreq = options.to_query_string();
		if (!sreq.empty()) {
			uri = uri + sreq;
		}
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		string_t rev = options.rev;
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
			BaseDocument oRet;
			try {
				value v = t2.get();
				oRet = BaseDocument(v);
			}catch(exception &ex){
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// read_document
	task<UpdateResponse>  CouchDBManager::create_document(const value &doc, const string_t &db /*= string_t()*/) const {
		string_t uri = (db.empty()) ? this->database() : db;
		http_client client(this->baseUrl());
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
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}// create_document
	task<string_t> CouchDBManager::exists_document(const string_t &id, const string_t &db /*= string_t()*/) const {
		string_t uri = (db.empty()) ? this->database() : db;
		uri = uri + STRING_SLASH + id;
		http_client client(this->baseUrl());
		http_request request(methods::HEAD);
		request.set_request_uri(uri);
		return client.request(request).then([=](http_response response) {
			string_t sRet;
			bool bRet = (response.status_code() == status_codes::OK) || (response.status_code() == status_codes::NotModified);
			if (bRet) {
				auto headers = response.headers();
				if (headers.has(HEADER_ETAG)) {
					string_t sx = headers[HEADER_ETAG];
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
	}//exists_document
	task<bool> CouchDBManager::exists_database(const string_t &s /* = String */) const {
		string_t s_uri = (s.length() > 0) ? s : this->database();
		http_client client(this->baseUrl());
		http_request request(methods::HEAD);
		request.set_request_uri(s_uri);
		return client.request(request).then([=](http_response response) {
			bool bRet = (response.status_code() == status_codes::OK);
			if ((!bRet) && (response.status_code() != status_codes::NotFound)) {
				throw http_exception(response.status_code());
			}
			return task_from_result(bRet);
		});
	}//exists_database
	task<DatabaseInfo> CouchDBManager::get_database_info(const string_t &s /*= string_t()*/) const {
		string_t s_uri = (s.length() > 0) ? s : this->database();
		http_client client(this->baseUrl());
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.set_request_uri(s_uri);
		return client.request(request).then([=](http_response response) {
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> t1) {
			DatabaseInfo oRet;
			try {
				oRet = DatabaseInfo(t1.get());
			}
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_database_info
	task<UpdateResponse> CouchDBManager::create_database(const string_t &db) const {
		http_client client(this->baseUrl());
		http_request request(methods::PUT);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.set_request_uri(db);
		return client.request(request).then([=](http_response response) {
				return response.extract_json();
		}).then([=](task<value> t1) {
			UpdateResponse oRet;
			try {
				oRet = UpdateResponse(t1.get());
			}
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//create_database
	task<UpdateResponse> CouchDBManager::delete_database(const string_t &db) const {
		http_client client(this->baseUrl());
		http_request request(methods::DEL);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.set_request_uri(db);
		return client.request(request).then([=](http_response response) {
			return response.extract_json();
		}).then([=](task<value> t1) {
			UpdateResponse oRet;
			try {
				oRet = UpdateResponse(t1.get());
			}
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//delete_database
	task<std::vector<string_t>> CouchDBManager::get_uuids(size_t count /* = 1 */) const {
		http_client client(this->baseUrl());
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		utility::stringstream_t os;
		if (count < 1) {
			count = 1;
		}
		os << STRING_UUIDS_COUNT << count;
		string_t s = os.str();
		request.set_request_uri(s);
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
				if ((!jsonvalue.is_null()) && jsonvalue.is_object()) {
					if (jsonvalue.has_field(STRING_UUIDS)) {
						auto v = (jsonvalue.at(STRING_UUIDS)).as_array();
						size_t n = v.size();
						for (size_t i = 0; i < n; ++i) {
							string_t ss = (v.at(i)).as_string();
							oRet.push_back(ss);
						}
					}// uuids
				}// obj
			}
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_uuids
	task<std::vector<string_t> > CouchDBManager::get_all_dbs(void) const {
		http_client client(this->baseUrl());
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		request.set_request_uri(STRING_ALL_DBS);
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
				if ((!jsonvalue.is_null()) && (jsonvalue.is_array())) {
					size_t n = jsonvalue.size();
					for (size_t i = 0; i < n; ++i) {
						string_t s = (jsonvalue.at(i)).as_string();
						oRet.push_back(s);
					}
				}
			}
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(oRet);
		});
	}//get_all_dbs
	task<ServerInfo> CouchDBManager::get_server_info(void) const {
		http_client client(this->baseUrl());
		http_request request(methods::GET);
		request.headers().add(ACCEPT_STRING, APPLICATION_JSON_STRING);
		return client.request(request).then([=](http_response response) {
			if (response.status_code() == status_codes::OK) {
				return response.extract_json();
			}
			else {
				throw http_exception(response.status_code());
			}
		}).then([=](task<value> previousTask) {
			ServerInfo pRet;
			try {
				const value &jsonvalue = previousTask.get();
				pRet = ServerInfo(jsonvalue);
			}
			catch (exception &ex) {
				throw ex;
			}
			return task_from_result(pRet);
		});
	}// get_server_info
	///////////////////////////////////////////
	CouchDBManager::CouchDBManager() :_baseUrl(DEFAULT_BASEURL), _database(DEFAULT_DATABASE) {

	}
	CouchDBManager::CouchDBManager(const string_t &Url) : _baseUrl(Url), _database(DEFAULT_DATABASE) {

	}
	CouchDBManager::CouchDBManager(const string_t &Url, const string_t &data) : _baseUrl(Url), _database(data) {

	}
	CouchDBManager::CouchDBManager(const CouchDBManager &other) : _baseUrl(other._baseUrl), _database(other._database) {

	}
	CouchDBManager & CouchDBManager::operator=(const CouchDBManager &other) {
		if (this != &other) {
			this->_baseUrl = other._baseUrl;
			this->_database = other._database;
		}
		return *this;
	}
	CouchDBManager::~CouchDBManager() {

	}
	const string_t & CouchDBManager::baseUrl(void) const {
		return this->_baseUrl;
	}
	void CouchDBManager::baseUrl(const string_t &s) {
		this->_baseUrl = s;
	}
	const string_t & CouchDBManager::database(void) const {
		return this->_database;
	}
	void CouchDBManager::database(const string_t &s) {
		this->_database = s;
	}
	//////////////////////////////////////////
}// namespace geninfo
/////////////////////////////////////