#pragma once
#ifndef __BASEITEM_H__
#define __BASEITEM_H__
/////////////////////////////
#include "basedoc.h"
/////////////////////////////
namespace geninfo {
    //////////////////////////////
    class IDataManager;
    ///////////////////////////////
    class BaseItem : public BaseDoc {
        public:
            BaseItem();
            BaseItem(const Value &oMap);
            BaseItem(const BaseItem &other);
            BaseItem & operator=(const BaseItem &other);
            virtual ~BaseItem();
        public:
            virtual std::string store_prefix(void) const;
            virtual std::string start_key(void) const;
            virtual std::string create_id(void) const;
            virtual bool is_storeable(void) const;
            //
            virtual bool load(IDataManager &oMan);
            virtual bool save(IDataManager &oMan);
            virtual bool remove(IDataManager &oMan);
        public:
            std::string type(void) const;
            std::string end_key(void) const;
            void check_id(void);
    }; // class BaseItem
    ///////////////////////////////
}// name
//////////////////////////////
#endif // __BASEITEM_H__
