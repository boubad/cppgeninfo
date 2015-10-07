#pragma once
#ifndef __GENUTILS_H__
#define __GENUTILS_H__
/////////////////////////////////
#include "gendefs.h"
///////////////////////////////
namespace geninfo {
	//////////////////////////////
	extern string_t trim(const string_t &s);
	extern string_t to_upper(const string_t &s);
	extern string_t to_lower(const string_t &s);
	////////////////////////////
	extern std::string convert_to_string(const string_t &s);
	extern string_t convert_from_string(const std::string &s);
	extern string_t url_encode(const string_t &url);
	///////////////////////////////
	extern std::set<string_t> value_to_string_set(const value &v);
	extern value string_set_to_value(const std::set<string_t> &oSet);
	/////////////////////////////////
	extern Date string_to_date(const string_t &s);
	extern Date value_to_date(const value &v);
	extern value date_to_value(const Date &d);
	/////////////////////////////////////
	extern DateTime string_to_datetime(const string_t &s);
	extern DateTime value_to_datetime(const value &v);
	extern value datetime_to_value(DateTime d);
	////////////////////////////////////
	extern string_t to_md5(const string_t &s);
	////////////////////////////////////
}// geninfo
/////////////////////////////////
#endif // __GENUTILS_H__
