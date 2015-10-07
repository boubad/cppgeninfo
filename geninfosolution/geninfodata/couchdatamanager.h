#pragma once
#ifndef __COUCHDATAMANAGER_H__
#define  __COUCHDATAMANAGER_H__
////////////////////////////////////
#include "IDatabaseManager.h"
/////////////////////////////////////////
namespace geninfo {
	class IItemFactory;
	class BaseItem;
	class CouchDBManager;
	/////////////////////////////
	class CouchDataManager :public IDatabaseManager
	{
	public:
		CouchDataManager();
		CouchDataManager(const string_t &baseUrl);
		CouchDataManager(const string_t &baseUrl, const string_t &database);
		CouchDataManager(const CouchDataManager &other);
		CouchDataManager & operator=(const CouchDataManager &other);
		virtual ~CouchDataManager();
	public:
		virtual const IItemFactory *item_factory(void) const;
		virtual pplx::task<UpdateResponse> maintains_item(BaseItem &item);
		virtual pplx::task<UpdateResponse> remove_item(const BaseItem &item);
		virtual pplx::task<BaseItem *> read_item(const string_t &id, bool bAttachements = false,bool bMeta = false);
		//
		virtual pplx::task<std::vector<string_t>> find_ids_range(const string_t &startkey, const string_t &endkey);
		virtual pplx::task<std::vector<BaseItem *>> find_items_range(const string_t &startkey, const string_t &endkey, bool bAttachements = false);
		virtual pplx::task<std::vector<BaseItem *>> find_items_array(const std::vector<string_t> &ids);
		//
		virtual pplx::task<std::vector<string_t> > maintains_items(std::vector<BaseItem *> &oVec, bool bDelete = false);
	private:
		std::shared_ptr<IItemFactory> m_fact;
		std::shared_ptr<CouchDBManager> m_man;
	};
}// namespace geninfo
///////////////////////////////////
#endif //  __COUCHDATAMANAGER_H__
