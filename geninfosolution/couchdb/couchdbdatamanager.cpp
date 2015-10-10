#include "stdafx.h"
#include "couchdbdatamanager.h"
///////////////////////////////
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>
//////////////////////////////
#include <boost/function_output_iterator.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
////////////////////////////////
namespace geninfo {
	using namespace utility;                    // Common utilities like string conversions
	using namespace web;                        // Common features like URIs.
	using namespace web::http;                  // Common HTTP functionality
	using namespace web::json;
	using namespace web::http::client;
	using namespace concurrency::streams;
	using namespace pplx;
	//////////////////////////////////////
	const string_t DEFAULT_BASEURL = U("http://localhost:5984");
	const string_t DEFAULT_DATABASE = U("geninfo");
	///////////////////////////////////////////
	static std::string convert_to_string(const string_t &s)
	{
#ifdef _UTF16_STRINGS
		return utility::conversions::utf16_to_utf8(s);
#else
		std::string sRet = s;
		return sRet;
#endif
	}
	static string_t convert_from_string(const std::string &s) {
		return utility::conversions::to_string_t(s);
	}
	///////////////////////////
	namespace
	{
		std::string encimpl(std::string::value_type v)
		{
			if (isalnum(v)) {
				return std::string() + v;
			}
			std::ostringstream enc;
			enc << '%' << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << int(static_cast<unsigned char>(v));
			return enc.str();
		}
	}

	static std::string urlencode(const std::string& url)
	{
		// Find the start of the query string
		//const std::string::const_iterator start = std::find(url.begin(), url.end(), '?');

		// If there isn't one there's nothing to do!
		//if (start == url.end())
		//	return url;

		// store the modified query string
		std::string qstr;

		std::transform(url.begin(), url.end(),
			// Append the transform result to qstr
			boost::make_function_output_iterator(boost::bind(static_cast<std::string& (std::string::*)(const std::string&)>(&std::string::append), &qstr, _1)),
			encimpl);
		//return std::string(url.begin(), start + 1) + qstr;
		return qstr;
	}
	////////////////////////////////
	static string_t url_encode(const string_t &url)
	{
		std::string surl = convert_to_string(url);
		std::string sRes = urlencode(surl);
		return utility::conversions::to_string_t(sRes);
	}// url_encode
	///////////////////////////////
	static Value value_to_infovalue(const web::json::value &v) {
		Value oRet;
		if (!v.is_null()) {
			if (v.is_array()) {
				Array oAr;
				const web::json::array &aa = v.as_array();
				for (auto it = aa.begin(); it != aa.end(); ++it) {
					auto v = *it;
					Value vv = value_to_infovalue(v);
					oAr.push_back(vv);
				}// it
				oRet = oAr;
			}
			else if (v.is_object()) {
				Object oObj;
				const web::json::object &obj = v.as_object();
				for (auto it = obj.begin(); it != obj.end(); ++it) {
					string_t s = (*it).first;
					web::json::value vx = (*it).second;
					std::string key = convert_to_string(s);
					Value vv = value_to_infovalue(vx);
					oObj.push_back(json_spirit::Pair(key,vv));
				}
				oRet = oObj;
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
				string_t s = v.as_string();
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
			case json_spirit::Value_type::bool_type:
				oRet = web::json::value(v.get_bool());
				break;
			case json_spirit::Value_type::real_type:
				oRet = web::json::value(v.get_real());
				break;
			case json_spirit::Value_type::int_type:
				oRet = web::json::value(v.get_int());
				break;
			case json_spirit::Value_type::str_type:
			{
				std::string s = v.get_str();
				string_t sc = convert_from_string(s);
				oRet = web::json::value(sc);
			}
			break;
			case json_spirit::Value_type::array_type:
			{
				std::vector<web::json::value> oVec;
				const json_spirit::Array & oAr = v.get_array();
				for (auto it = oAr.begin(); it != oAr.end(); ++it) {
					auto vx = *it;
					web::json::value vz = infovalue_to_value(vx);
					if (!vz.is_null()) {
						oVec.push_back(vz);
					}
				}// it
				oRet = web::json::value::array(oVec);
			}
			break;
			case json_spirit::Value_type::obj_type:
			{
				web::json::value vt = web::json::value::object();
				web::json::object & obj = vt.as_object();
				const json_spirit::Object &oo = v.get_obj();
				for (auto it = oo.begin(); it != oo.end(); ++it) {
					std::string s = (*it).name_;
					json_spirit::Value vx = (*it).value_;
					string_t key = convert_from_string(s);
					web::json::value val = infovalue_to_value(vx);
					obj[key] = val;
				}// it
				oRet = vt;
			}
			break;
			default:
				break;
			}// type
		}// not null
		return oRet;
	}//infovalue_to_object
	 //////////////////////////////
	CouchDBDataManager::CouchDBDataManager()
	{
	}


	CouchDBDataManager::~CouchDBDataManager()
	{
	}
	///////////////////////////////
}// namespace geninfo
