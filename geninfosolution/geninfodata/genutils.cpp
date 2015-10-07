//genutils.cpp
#include "stdafx.h"
////////////////////////
#include "genutils.h"
//////////////////////////////
#include <boost/function_output_iterator.hpp>
#include <boost/bind.hpp>
#include <boost/algorithm/string.hpp>
///////////////////////////////
namespace geninfo
{
	/////////////////////////////////
	extern string_t trim(const string_t &s) {
		return boost::trim_copy(s);
	}
	extern string_t to_upper(const string_t &s) {
		return boost::to_upper_copy(s);
	}
	extern string_t to_lower(const string_t &s) {
		return boost::to_lower_copy(s);
	}
	///////////////////////////
	extern std::string convert_to_string(const string_t &s)
	{
#ifdef _UTF16_STRINGS
		return utility::conversions::utf16_to_utf8(s);
#else
		std::string sRet = s;
		return sRet;
#endif
	}
	extern string_t convert_from_string(const std::string &s) {
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
	extern string_t url_encode(const string_t &url)
	{
		std::string surl = convert_to_string(url);
		std::string sRes = urlencode(surl);
		return utility::conversions::to_string_t(sRes);
	}// url_encode
	//////////////////////////////
	extern std::set<string_t> value_to_string_set(const value &v) {
		std::set<string_t> vec;
		if ((!v.is_null()) && v.is_array()) {
			const web::json::array &oAr = v.as_array();
			for (auto it = oAr.begin(); it != oAr.end(); ++it) {
				const value &vv = *it;
				if ((!vv.is_null()) && vv.is_string()) {
					string_t s = vv.as_string();
					if (!s.empty()) {
						vec.insert(s);
					}
				}
			}// it
		}// array
		return vec;
	}//value_to_string_set
	extern value string_set_to_value(const std::set<string_t> &oSet) {
		std::vector<value> vec;
		for (auto it = oSet.begin(); it != oSet.end(); ++it) {
			string_t s = *it;
			if (!s.empty()) {
				vec.push_back(value::string(s));
			}// s
		}// it
		return value::array(vec);
	}//string_set_to_value
	////////////////////////////////////////
	extern DateTime string_to_datetime(const string_t &s) {
		DateTime oRet;
		std::string sx = convert_to_string(s);
		oRet = boost::posix_time::time_from_string(sx);
		return oRet;
	}
	extern DateTime value_to_datetime(const value &v) {
		DateTime oRet;
		if ((!v.is_null()) && v.is_string()) {
			string_t s = v.as_string();
			oRet = string_to_datetime(s);
		}
		return oRet;
	}// value_to_datetime
	extern value datetime_to_value(DateTime d) {
		value oRet;
		if (!d.is_not_a_date_time()) {
			std::string s = boost::posix_time::to_iso_extended_string(d);
			string_t ss = convert_from_string(s);
			oRet = value::string(ss);
		}
		return oRet;
	}// date_to_value
	///////////////////////////////////
	extern Date string_to_date(const string_t &s) {
		Date oRet;
		if (s.length() >= 10) {
			std::string sn = convert_to_string(s);
			std::string ss = sn.substr(0, 10);
			oRet = boost::gregorian::from_string(ss);
		}
		return oRet;
	}//string_to_date
	extern Date value_to_date(const value &v) {
		Date oRet;
		if ((!v.is_null()) && v.is_string()) {
			string_t s = v.as_string();
			oRet = string_to_date(s);
		}
		return oRet;
	}// value_to_date
	extern value date_to_value(const Date &d) {
		value oRet;
		if (!d.is_not_a_date()) {
			std::string s = boost::gregorian::to_iso_extended_string(d);
			string_t ss = convert_from_string(s);
			if (ss.length() >= 10) {
				oRet = value::string(ss);
			}
		}
		return oRet;
	}// date_to_value
	 /////////////////////////////
}// namespace geninfo
