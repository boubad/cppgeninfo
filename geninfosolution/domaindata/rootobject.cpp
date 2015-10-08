#include "stdafx.h"
#include "rootobject.h"
//////////////////////////
namespace geninfo {
	RootObject::RootObject()
	{
	}
	RootObject::RootObject(const Object &oMap) :m_obj(oMap) {

	}
	RootObject::RootObject(const RootObject &other) : m_obj(other.m_obj) {

	}
	RootObject & RootObject::operator=(const RootObject &other) {
		if (this != &other) {
			this->m_obj = other.m_obj;
		}
		return (*this);
	}
	RootObject::RootObject(const string &sJsonText) {
		Value val;
		json_spirit::read(sJsonText, val);
		if ((!val.is_null()) && (val.type() == json_spirit::Value_type::obj_type)) {
			this->m_obj = val.get_obj();
		}
	}
	RootObject::RootObject(istream &isJsonStream) {
		Value val;
		json_spirit::read(isJsonStream, val);
		if ((!val.is_null()) && (val.type() == json_spirit::Value_type::obj_type)) {
			this->m_obj = val.get_obj();
		}
	}
	RootObject::~RootObject()
	{
	}
	string RootObject::toString(void) const {
		string oRet;
		if (!this->m_obj.empty()) {
			oRet = json_spirit::write(this->m_obj, json_spirit::Output_options::pretty_print);
		}
		return oRet;
	}
	ostream & RootObject::write_to(ostream &os) const {
		if (!this->m_obj.empty()) {
			json_spirit::write(this->m_obj, os, json_spirit::Output_options::pretty_print);
		}
		return os;
	}
	bool RootObject::is_empty(void) const {
		return (this->m_obj.empty());
	}
	bool RootObject::contains(const string &key) const {
		bool bFound = false;
		for (auto it = this->m_obj.begin(); it != this->m_obj.end(); ++it) {
			const string & s = (*it).name_;
			if (s == key) {
				bFound = true;
				break;
			}
		}// it
		return bFound;
	}
	Value RootObject::get_value(const string &key) const {
		Value oRet;
		for (auto it = this->m_obj.begin(); it != this->m_obj.end(); ++it) {
			const string & s = (*it).name_;
			if (s == key) {
				oRet = (*it).value_;
				break;
			}
		}// it
		return oRet;
	}// get_value
	bool RootObject::get_bool(const string &key) const {
		bool bRet = false;
		for (auto it = this->m_obj.begin(); it != this->m_obj.end(); ++it) {
			const string & s = (*it).name_;
			if (s == key) {
				const Value &v = (*it).value_;
				if ((!v.is_null()) && (v.type() == json_spirit::Value_type::bool_type)) {
					bRet = v.get_bool();
				}
				break;
			}
		}// it
		return bRet;
	}// get_bool
	int RootObject::get_int(const string &key) const {
		int bRet = 0;
		for (auto it = this->m_obj.begin(); it != this->m_obj.end(); ++it) {
			const string & s = (*it).name_;
			if (s == key) {
				const Value &v = (*it).value_;
				if ((!v.is_null()) && (v.type() == json_spirit::Value_type::int_type)) {
					bRet = v.get_int();
				}
				break;
			}
		}// it
		return bRet;
	}// get_int
	double RootObject::get_double(const string &key) const {
		double bRet = 0.0;
		for (auto it = this->m_obj.begin(); it != this->m_obj.end(); ++it) {
			const string & s = (*it).name_;
			if (s == key) {
				const Value &v = (*it).value_;
				if ((!v.is_null()) && (v.type() == json_spirit::Value_type::real_type)) {
					bRet = v.get_real();
				}
				break;
			}
		}// it
		return bRet;
	}// get_double
	string RootObject::get_string(const string &key) const {
		string bRet;
		for (auto it = this->m_obj.begin(); it != this->m_obj.end(); ++it) {
			const string & s = (*it).name_;
			if (s == key) {
				const Value &v = (*it).value_;
				if ((!v.is_null()) && (v.type() == json_spirit::Value_type::str_type)) {
					bRet = v.get_str();
				}
				break;
			}
		}// it
		return bRet;
	}// get_string
	date RootObject::get_date(const string &key) const {
		date bRet;
		for (auto it = this->m_obj.begin(); it != this->m_obj.end(); ++it) {
			const string & s = (*it).name_;
			if (s == key) {
				const Value &v = (*it).value_;
				if ((!v.is_null()) && (v.type() == json_spirit::Value_type::str_type)) {
					string  s = v.get_str();
					if (s.length() >= 10) {
						bRet = boost::gregorian::from_string(s);
					}
				}
				break;
			}
		}// it
		return bRet;
	}// get_date
	datetime RootObject::get_datetime(const string &key) const {
		datetime bRet;
		for (auto it = this->m_obj.begin(); it != this->m_obj.end(); ++it) {
			const string & s = (*it).name_;
			if (s == key) {
				const Value &v = (*it).value_;
				if ((!v.is_null()) && (v.type() == json_spirit::Value_type::str_type)) {
					string  s = v.get_str();
					if (s.length() >= 5) {
						bRet = boost::posix_time::time_from_string(s);
					}
				}
				break;
			}
		}// it
		return bRet;
	}//get_datetime
	Array  RootObject::get_array(const string &key) const {
		Array bRet;
		for (auto it = this->m_obj.begin(); it != this->m_obj.end(); ++it) {
			const string & s = (*it).name_;
			if (s == key) {
				const Value &v = (*it).value_;
				if ((!v.is_null()) && (v.type() == json_spirit::Value_type::array_type)) {
					bRet = v.get_array();
				}
				break;
			}
		}// it
		return bRet;
	}// get_array
	Object   RootObject::get_object(const string &key) const {
		Object bRet;
		for (auto it = this->m_obj.begin(); it != this->m_obj.end(); ++it) {
			const string & s = (*it).name_;
			if (s == key) {
				const Value &v = (*it).value_;
				if ((!v.is_null()) && (v.type() == json_spirit::Value_type::obj_type)) {
					bRet = v.get_obj();
				}
				break;
			}
		}// it
		return bRet;
	}// get_object
	//
	void  RootObject::set_value(const string &key, const Value &value) {
		string skey = trim(key);
		if ((!skey.empty()) && (!value.is_null())) {
			for (auto it = this->m_obj.begin(); it != this->m_obj.end(); ++it) {
				const string & s = (*it).name_;
				if (s == skey) {
					(*it).value_ = value;
					return;
				}
			}// it
			Value vv(value);
			this->m_obj.push_back(Pair(key, vv));
		}
	}
	void  RootObject::set_bool(const string &key, bool b) {
		Value value(b);
		this->set_value(key, value);
	}
	void  RootObject::set_int(const string &key, int b) {
		Value value(b);
		this->set_value(key, value);
	}
	void  RootObject::set_double(const string &key, double b) {
		Value value(b);
		this->set_value(key, value);
	}
	void  RootObject::set_string(const string &key, const string &b) {
		Value value(b);
		this->set_value(key, value);
	}
	void  RootObject::set_array(const string &key, const Array &b) {
		Value value(b);
		this->set_value(key, value);
	}
	void  RootObject::set_object(const string &key, const Object &b) {
		Value value(b);
		this->set_value(key, value);
	}
	////////////////////////////
}// namespace geninfo
