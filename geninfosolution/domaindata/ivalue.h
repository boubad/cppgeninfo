#pragma once
#ifndef __IVALUE_H__
#define __IVALUE_H__
////////////////////////////////
#include <memory>
#include <string>
#include <vector>
#include <iostream>
/////////////////////////////////////
namespace geninfo {
    ///////////////////////////////////
    class Object;
    class IValue;
    /////////////////////////////////////
    typedef std::shared_ptr<Object> PObject;
    typedef std::shared_ptr<IValue> PValue;
    typedef std::vector<PValue> Array;
    ///////////////////////////////////
    class IValue {
        public:
            virtual bool is_null(void) const = 0;
            virtual bool is_bool(void) const = 0;
            virtual bool is_null(int) const = 0;
            virtual bool is_double(void) const = 0;
            virtual bool is_string(void) const = 0;
            virtual bool is_array(void) const = 0;
            virtual bool is_object(void) const = 0;
            virtual bool to_bool(void) const = 0;
            virtual int to_int(void) const = 0;
            virtual double to_double(void) const = 0;
            virtual std::string to_string(void) const = 0;
            virtual PObject to_object(void) const = 0;
            virtual Array to_array(void) const = 0;
    }; // class IValue
    ////////////////////////////////////
}// namespace geninfo
//////////////////////////////////
#endif // __IVALUE_H__
