#pragma once
#ifndef __IROOTOBJECT_H__
#define __IROOTOBJECT_H__
////////////////////////////////
#include "ivalue.h"
////////////////////////
#include <sstream>
#include <map>
#include <algorithm>
/////////////////////////////////////
namespace geninfo {
    ////////////////////////////////////
    class Object {
        public:
            Object(){}
            Object(const std::map<std::string,PValue> &m):m_map(m){}
            Object(const Object &other):m_map(other.m_map){}
            Object & operator=(const Object &other){
                if (this != &other){
                    this->m_map = other.m_map;
                }
                return (*this);
            }
            ~Object(){}
        public:
        std::ostream & write_to(std::ostream &os) const {
            os << "{";
            auto iend = m_map.end();
            auto istart = m_map.begin();
            for (auto it = istart; it != iend; ++it){
                if (it != iend){
                    os << ",";
                }
                os << "\"" << (*it).first << "\":";
                const PValue &v = (*it).second;
                const IValue *p = v.get();
                if (p->is_bool()){
                    os << (p->to_bool()) ? "true" : "false";
                } else if (p->is_int()){
                    os << p->to_int();
                } else if (p->is_double()){
                    os << p->to_double();
                } else if (p->is_string()){
                    os << "\"" << p->to_string() << "\"";
                } else if (p->is_array()){
                    os << "[";
                    auto oAr = p->to_array();
                    auto i1 = oAr.begin();
                    auto i2 = oAr.end();
                    for (auto jt = i1; jt != i2; ++jt){
                        if (jt != i1){
                            os << ",";
                        }
                        auto vv = *it;
                        vv.write_to(os);
                    }// jt
                    os << "]";
                } else if (p->is_object()){
                    auto obj = p->to_object();
                    const Object *px = obj.get();
                    px->write_to(os);
                }
            }// it
            os << "}";
        }
            std::string to_string(void) const {
                std::stringstream os;
                this->write_to(os);
                return os.str();
            }
		    
		    //
		    std::vector<std::string> keys(void) const {
		        std::vector<std::string> oRet;
		        std::for_each(m_map.begin(),m_map.end(),[&oRet](const std::pair<std::string,PValue> &p){
		            oRet.push_back(p.first);
		        });
		        return (oRet);
		    }
		    bool is_empty(void) const{
		        return (m_map.empty());
		    }
		    bool contains(const std::string &key) const {
		        return (m_map.find(key) == m_map.end());
		    }
		    bool get_bool(const std::string &key) const {
		        bool bRet = false;
		        auto it = m_map.find(key);
		        if (it != m_map.end()){
		            const PValue & v = (*it).second;
		            if (v->is_bool()){
		                bRet = v->to_bool();
		            }
		        }
		        return bRet;
		    }
		   int get_int(const std::string &key) const {
		        int bRet = 0;
		        auto it = m_map.find(key);
		        if (it != m_map.end()){
		            const PValue & v = (*it).second;
		            if (v->is_int()){
		                bRet = v->to_int();
		            }
		        }
		        return bRet;
		    }
		    double get_double(const std::string &key) const {
		       double bRet = 0.0;
		        auto it = m_map.find(key);
		        if (it != m_map.end()){
		            const PValue & v = (*it).second;
		            if (v->is_double()){
		                bRet = v->to_double();
		            }
		        }
		        return bRet;
		    }
		    std::string get_string(const std::string &key) const {
		        std::string bRet;
		        auto it = m_map.find(key);
		        if (it != m_map.end()){
		            const PValue & v = (*it).second;
		            if (v->is_string()){
		                bRet = v->to_string();
		            }
		        }
		        return bRet;
		    }
		    PObject get_object(const std::string &key) const {
		        PObject bRet;
		        auto it = m_map.find(key);
		        if (it != m_map.end()){
		            const PValue & v = (*it).second;
		            if (v->is_object()){
		                bRet = v->to_object();
		            }
		        }
		        return bRet;
		    }
		    Array get_string(const std::string &key) const {
		        Array bRet;
		        auto it = m_map.find(key);
		        if (it != m_map.end()){
		            const PValue & v = (*it).second;
		            if (v->is_array()){
		                bRet = v->to_array();
		            }
		        }
		        return bRet;
		    }
		    void remove(const std::string &key) {
		        auto it = m_map.find(key);
		        if (it != m_map.end()){
		            m_map.remove(it);
		        }
		    }
		    void set_value(const std::string &key, const PValue &val){
                if ((!key.empty()) && (val.get() != nullptr)){
                    m_map[key] = val;
                }		        
		    }
		private:
		    std::map<std::string,PValue> m_map;
    }; // Object
    /////////////////////////////////////
}// namespace geninfo
///////////////////////////////////
#endif // __IROOTOBJECT_H__
