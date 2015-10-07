#pragma once
#ifndef __GENDEFS_H__
#define __GENDEFS_H__
///////////////////////////////
#include <cpprest/json.h>
#include <cpprest/http_client.h>
#include <pplx/pplxtasks.h>
/////////////////////////////////
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
////////////////////////////////////
namespace geninfo {
	//////////////////////////////////////
	typedef utility::string_t string_t;
	typedef utility::ostream_t ostream_t;
	typedef utility::istream_t istream_t;
	typedef utility::ostringstream_t ostringstream_t;
	typedef utility::istringstream_t istringstream_t;
	typedef utility::stringstream_t stringstream_t;
	typedef utility::ifstream_t ifstream_t;
	typedef utility::ofstream_t ofstream_t;
	////////////////////////////////////////////
	typedef web::json::value value;
	///////////////////////////////////
	typedef boost::gregorian::date Date;
	typedef boost::posix_time::ptime DateTime;
	///////////////////////////////
}// namespace geninfo
////////////////////////////////
#endif //__GENDEFS_H__
