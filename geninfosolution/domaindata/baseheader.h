#pragma once
#ifndef __BASEHEADER_H__
#define __BASEHEADER_H__
///////////////////////////////
#include <memory>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <iterator>
#include <iomanip>
////////////////////////////////
#include <boost/algorithm/string.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
///////////////////////////////////
#include "json_spirit.h"
////////////////////////////////////
namespace geninfo {
	/////////////////////////////////////
	typedef std::string string;
	typedef std::istream istream;
	typedef std::ostream ostream;
	////////////////////////////////////////
	typedef boost::gregorian::date date;
	typedef boost::posix_time::ptime datetime;
	///////////////////////////////
	typedef json_spirit::Value Value;
	typedef json_spirit::Array Array;
	typedef json_spirit::Object Object;
	typedef json_spirit::Pair Pair;
	//////////////////////////////////
	inline string trim(const string &s) {
		return boost::trim_copy(s);
	}
	inline string to_upper(const string &s) {
		return boost::to_upper_copy(s);
	}
	inline string to_lower(const string &s) {
		return boost::to_lower_copy(s);
	}
	inline datetime string_to_datetime(const string &s) {
		return boost::posix_time::time_from_string(s);
	}
	inline date string_to_date(const string &s) {
		return boost::gregorian::from_string(s);
	}//string_to_date
	///////////////////////////////////
}// namespace geninfo
////////////////////////////////////
#endif // __BASEHEADER_H__
