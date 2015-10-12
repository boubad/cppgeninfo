#include "stdafx.h"
#include "baseitem.h"
#include "idatamanager.h"
#include "domainconstants.h"
////////////////////////////
namespace geninfo {
    /////////////////////////////////
     BaseItem::BaseItem(){
         
     }
    BaseItem::BaseItem(const Value &oMap):BaseDoc(oMap){
        
    }
    BaseItem::BaseItem(const BaseItem &other):BaseDoc(other){
        
    }
    BaseItem &  BaseItem::operator=(const BaseItem &other){
        if (this != &other){
            BaseDoc::operator=(other);
        }
        return (*this);
    }
    BaseItem::~BaseItem(){
        
    }
    std::string  BaseItem::store_prefix(void) const{
        return (std::string());
    }
    std::string  BaseItem::start_key(void) const{
        return (this->store_prefix());
    }
    std::string  BaseItem::create_id(void) const{
        return (std::string());
    }
    bool  BaseItem::is_storeable(void) const{
        std::string s1 = this->type();
        std::string s2 = this->store_prefix();
        return ((!s1.empty()) && (!s2.empty()));
    }
    std::string  BaseItem::type(void) const{
        return this->get_string(DomainConstants::TYPE);
    }
    std::string  BaseItem::end_key(void) const{
        std::string s1 = this->start_key();
        char cend = (char)0xff;
        s1 += cend;
        return s1;
    }
    void  BaseItem::check_id(void){
        std::string s = this->id();
        if (s.empty()){
            this->id(this->create_id());
        }
    }
    bool  BaseItem::load(IDataManager &oMan){
        bool bRet = false;
        return bRet;
    }
    bool  BaseItem::save(IDataManager &oMan){
        bool bRet = false;
        return bRet;
    }
    bool  BaseItem::remove(IDataManager &oMan){
        bool bRet = false;
        return bRet;
    }
            
    /////////////////////////////////
}// namespace geninfo
////////////////////////////
