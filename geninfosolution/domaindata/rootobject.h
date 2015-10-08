#pragma once
#ifndef __ROOTOBJECT_H__
#define __ROOTOBJECT_H__
///////////////////////////
#include "baseheader.h"
///////////////////////////
namespace geninfo {
	//////////////////////////////////
	class RootObject
	{
	public:
		RootObject();
		RootObject(const string &sJsonText);
		RootObject(istream &isJsonStream);
		RootObject(const Object &oMap);
		RootObject(const RootObject &other);
		RootObject & operator=(const RootObject &other);
		virtual ~RootObject();
	public:
		operator const Object&() const {
			return (this->m_obj);
		}
		const Object & object(void) const {
			return (this->m_obj);
		}
	public:
		string to_string(void) const;
		ostream & write_to(ostream &os) const;
	public:
		std::vector<string> keys(void) const;
		Value get_value(const string &s) const;
		bool is_empty(void) const;
		bool contains(const string &key) const;
		bool get_bool(const string &key) const;
		int get_int(const string &key) const;
		double get_double(const string &key) const;
		string get_string(const string &key) const;
		date get_date(const string &key) const;
		datetime get_datetime(const string &key) const;
		Array  get_array(const string &key) const;
		Object  get_object(const string &key) const;
		void set_bool(const string &key, bool b);
		void set_int(const string &key, int b);
		void set_double(const string &key, double b);
		void set_string(const string &key, const string &b);
		void set_array(const string &key, const Array &b);
		void set_object(const string &key, const Object &b);
	protected:
		operator Object&() {
			return (this->m_obj);
		}
		
		void set_value(const string &key, const Value &value);
	private:
		Object m_obj;
	};
	///////////////////////////////////////////
}// namespace geninfo
/////////////////////////////////
template <class OSTREAM>
OSTREAM & operator<<(OSTREAM &os, const geninfo::RootObject &obj) {
	obj.write_to(os);
	return os;
}
template <class ISTREAM>
ISTREAM & operator>>(ISTREAM &is, geninfo::RootObject &obj) {
	obj = geninfo::RootObject(is);
	return is;
}
/////////////////////////////////////
#endif // __ROOTOBJECT_H__

