#pragma once
#ifndef __GENINFO_EXCEPTION_H__
#define __GENINFO_EXCEPTION_H__
////////////////////////////////
#include "gendefs.h"
#include <stdexcept>
////////////////////////////////////
namespace geninfo {
	class geninfo_exception : public std::exception
	{
	private:
		int _code;
		std::string _message;
	public:

		geninfo_exception():_code(0)
		{
		}
		geninfo_exception(const utility::char_t * const &message, int xcode = 0) :_code(xcode),_message(utility::conversions::to_utf8string(message))
		{
		}
		geninfo_exception() :_code(0)
		{
		}
		geninfo_exception(const geninfo_exception &other) :_code(other._code),_message(other._message)
		{
		}
		geninfo_exception & operator=(const geninfo_exception &other)
		{
			if (this != &other) {
				this->_code = other._code;
				this->_message = other._message;
			}
			return *this;
		}
		virtual ~geninfo_exception()
		{
		}
		const char* what() const CPPREST_NOEXCEPT
		{
			return this->_message.c_str();
		}
		int code(void) const CPPREST_NOEXCEPT {
			return this->_code;
		}
	}; // class geninfo_exception
	/////////////////////
}// namespace geninfo
////////////////////////
#endif // __GENINFO_EXCEPTION_H__
