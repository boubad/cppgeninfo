#pragma once
#ifndef __IDATABASEMANAGER_H__
#define __IDATABASEMANAGER_H__
//////////////////////////////////////
#include "genutils.h"
///////////////////////////////////////
namespace geninfo {
	//////////////////////////////////
	class UpdateResponse;
	//////////////////////////////////
	class BaseItem;
	//////////////////////////////////////
	class IItemFactory {
	public:
		IItemFactory(){}
		IItemFactory(const IItemFactory & /* other*/){}
		IItemFactory & operator=(const IItemFactory & /*other*/) { return *this; }
		virtual ~IItemFactory(){}
	public:
		virtual BaseItem *create_item(const value &oMap, const string_t &type = string_t()) const = 0;
	};// class IItemFactory
	////////////////////////////////////
	class IDatabaseManager
	{
	public:
		IDatabaseManager(){}
		IDatabaseManager(const IDatabaseManager &/*other*/){}
		IDatabaseManager & operator=(const IDatabaseManager & /*other */) { return *this; }
		virtual ~IDatabaseManager(){}
	public:
		virtual const IItemFactory *item_factory(void) const = 0;
		virtual pplx::task<BaseItem *> read_item(const string_t &id,bool bAttachements = false,bool bMeta = false) = 0;
		virtual pplx::task<UpdateResponse> maintains_item(BaseItem &item) = 0;
		virtual pplx::task<UpdateResponse> remove_item(const BaseItem &item) = 0;
		//
		virtual pplx::task<std::vector<string_t>> find_ids_range(const string_t &startkey, const string_t &endkey) = 0;
		virtual pplx::task<std::vector<BaseItem *>> find_items_range(const string_t &startkey, const string_t &endkey, bool bAttachements = false) = 0;
		virtual pplx::task<std::vector<BaseItem *>> find_items_array(const std::vector<string_t> &ids) = 0;
		//
		virtual pplx::task<std::vector<string_t> > maintains_items(std::vector<BaseItem *> &oVec, bool bDelete = false ) = 0;
	public:
		template <class T >
		pplx::task<std::shared_ptr<T> > load_item(const T & model, const string_t &id, bool bAttachements = false, bool bMeta = false) {
			return this->read_item(id,bAttachements,bMeta).then([=](pplx::task<BaseItem *> t) {
				T * p = dynamic_cast<T *>(t.get());
				std::shared_ptr<T> o(p);
				return pplx::task_from_result(o);
			});
		}// load_item
		template <class T>
		pplx::task<std::vector<std::shared_ptr<T>>> load_items_range(const T &model,const string_t &startkey, const string_t &endkey, bool bAttachements = false) {
			return this->find_items_range(startkey, endkey, bAttachements).then([=](pplx::task<std::vector<BaseItem* >> t) {
				std::vector<BaseItem *> v0 = t.get();
				std::vector<std::shared_ptr<T>> oRet;
				for (auto it = v0.begin(); it != v0.end(); ++it) {
					BaseItem *px = *it;
					T *pp = dynamic_cast<T *>(px);
					std::shared_ptr<T> o(pp);
					oRet.push_back(o);
				}// it
				return pplx::task_from_result(oRet);
			});
		}//load_items_range
		template <class T>
		pplx::task<std::vector<std::shared_ptr<T>>> load_items_array(const T &model, const std::vector<string_t> &ids) {
			return this->find_items_array(ids).then([=](pplx::task<std::vector<BaseItem *>> t) {
				std::vector<BaseItem *> v0 = t.get();
				std::vector<std::shared_ptr<T>> oRet;
				for (auto it = v0.begin(); it != v0.end(); ++it) {
					BaseItem *px = *it;
					T *pp = dynamic_cast<T *>(px);
					std::shared_ptr<T> o(pp);
					oRet.push_back(o);
				}// it
				return pplx::task_from_result(oRet);
			});
		}//load_items_array
	};
}// namespace geninfo
/////////////////////////////
#endif // __IDATABASEMANAGER_H__
