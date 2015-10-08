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
	 //////////////////////////////
	CouchDBDataManager::CouchDBDataManager()
	{
	}


	CouchDBDataManager::~CouchDBDataManager()
	{
	}
	///////////////////////////////
}// namespace geninfo
