#include "stdafx.h"
#include "couchdatamanager.h"
#include "itemfactory.h"
#include "couchdoc.h"
#include "CouchDBManager.h"
#include "baseitem.h"
///////////////////////////////////
namespace geninfo {
	///////////////////////////////
	const string_t DEFAULT_DATABASE = U("geninfo");
	const string_t JSON_ID_KEY = U("id");
	const string_t JSON_DOC_KEY = U("doc");
	const string_t DOC_ID = U("_id");
	const string_t DOC_REV = U("_rev");
	const string_t DOC_DELETED = U("_deleted");
	/////////////////////
	CouchDataManager::CouchDataManager() :m_fact(new ItemFactory()), m_man(new CouchDBManager())
	{
		CouchDBManager *pMan = this->m_man.get();
		pMan->database(DEFAULT_DATABASE);
	}
	CouchDataManager::CouchDataManager(const string_t &url, const string_t &database) :
		m_fact(new ItemFactory()), m_man(new CouchDBManager(url, database))
	{
	}
	CouchDataManager::CouchDataManager(const string_t &url) :
		m_fact(new ItemFactory()), m_man(new CouchDBManager(url, DEFAULT_DATABASE))
	{
	}
	CouchDataManager::CouchDataManager(const CouchDataManager &other) : IDatabaseManager(other),
		m_fact(other.m_fact), m_man(other.m_man) {

	}
	CouchDataManager & CouchDataManager::operator=(const CouchDataManager &other) {
		if (this != &other) {
			IDatabaseManager::operator=(other);
			this->m_fact = other.m_fact;
			this->m_man = other.m_man;
		}
		return *this;
	}
	CouchDataManager::~CouchDataManager()
	{
	}
	const IItemFactory *CouchDataManager::item_factory(void) const {
		return this->m_fact.get();
	}
	pplx::task<UpdateResponse> CouchDataManager::maintains_item(BaseItem &item) {
		UpdateResponse ox;
		if (item.deleted()) {
			return pplx::task_from_result(ox);
		}
		if (!item.is_storeable()) {
			return pplx::task_from_result(ox);
		}
		item.check_id();
		value oMap = item.get_value();
		return this->m_man->maintains_document(oMap).then([=](pplx::task<UpdateResponse > previousTask) {
			UpdateResponse oRet;
			try {
				oRet = previousTask.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return pplx::task_from_result(oRet);
		});
	}// maintains_item
	pplx::task<UpdateResponse> CouchDataManager::remove_item(const BaseItem &item) {
		UpdateResponse ox;
		if ((!item.has_rev()) || item.deleted()) {
			return pplx::task_from_result(ox);
		}
		string_t id = item.id();
		return this->m_man->delete_document(id).then([=](pplx::task<UpdateResponse > previousTask) {
			UpdateResponse oRet;
			try {
				oRet = previousTask.get();
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return pplx::task_from_result(oRet);
		});
	}// remove_item
	pplx::task<BaseItem *> CouchDataManager::read_item(const string_t &id, bool bAttachements /*= false*/,bool bMeta /*=false*/) {
		if (id.empty()) {
			BaseItem *px = nullptr;
			return pplx::task_from_result(px);
		}
		ReadDocOptions opts;
		if (bAttachements) {
			opts.attachments = true;
		}
		if (bMeta) {
			opts.meta = true;
		}
		const IItemFactory *pFact = this->item_factory();
		return this->m_man->read_document(id,opts).then([=](pplx::task<value> previousTask) {
			BaseItem *pRet = nullptr;
			try {
				value  op = previousTask.get();
				pRet = pFact->create_item(op);
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return pplx::task_from_result(pRet);
		});
	}//load_item
	pplx::task<std::vector<string_t>> CouchDataManager::find_ids_range(const string_t &startkey, const string_t &endkey) {
		string_t key(U("id"));
		AllDocsOptions opts;
		opts.startkey = startkey;
		opts.endkey = endkey;
		return this->m_man->get_all_docs(opts).then([=](pplx::task<AllDocsResponse> previousTask) {
			std::vector<string_t> oRet;
			try {
				auto so = previousTask.get();
				AllDocsResponse *pResponse = &so;
				if (pResponse != nullptr) {
					const std::vector<value> &v = pResponse->rows();
					for (auto it = v.begin(); it != v.end(); ++it) {
						auto vv = *it;
						if ((!vv.is_null()) && vv.is_object() && vv.has_field(key)) {
							string_t id = (vv.at(key)).as_string();
							if (!id.empty()) {
								oRet.push_back(id);
							}
						}
					}// it
				}// pResponse
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return pplx::task_from_result(oRet);
		});
	}// find_ids_range
	pplx::task<std::vector<BaseItem *>> CouchDataManager::find_items_range(const string_t &startkey, const string_t &endkey, bool bAttachements /*= false*/) {
		AllDocsOptions opts;
		opts.startkey = startkey;
		opts.endkey = endkey;
		opts.include_docs = true;
		if (bAttachements) {
			opts.attachments = true;
		}
		const IItemFactory *pFact = this->item_factory();
		return this->m_man->get_all_docs(opts).then([=](pplx::task<AllDocsResponse> previousTask) {
			std::vector<BaseItem *> oRet;
			try {
				auto so = previousTask.get();
				const AllDocsResponse *pResponse = &so;
				if (pResponse != nullptr) {
					const std::vector<value> &v = pResponse->rows();
					for (auto it = v.begin(); it != v.end(); ++it) {
						const value & vv = *it;
						if ((!vv.is_null()) && vv.is_object() && vv.has_field(JSON_DOC_KEY)) {
							const value &vx = vv.at(JSON_DOC_KEY);
							BaseItem *p = pFact->create_item(vx);
							if (p != nullptr) {
								oRet.push_back(p);
							}
						}
					}// it
				}// pResponse
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return pplx::task_from_result(oRet);
		});
	}//find_items_range
	pplx::task<std::vector<BaseItem *>> CouchDataManager::find_items_array(const std::vector<string_t> &ids) {
		const IItemFactory *pFact = this->item_factory();
		return this->m_man->get_array_docs(ids).then([=](pplx::task<AllDocsResponse> previousTask) {
			std::vector<BaseItem *> oRet;
			try {
				auto so = previousTask.get();
				AllDocsResponse *pResponse = &so;
				if (pResponse != nullptr) {
					const std::vector<value> &v = pResponse->rows();
					for (auto it = v.begin(); it != v.end(); ++it) {
						auto vv = *it;
						if ((!vv.is_null()) && vv.is_object()) {
							BaseItem *p = pFact->create_item(vv);
							if (p != nullptr) {
								oRet.push_back(p);
							}
						}
					}// it
				}// pResponse
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return pplx::task_from_result(oRet);
		});
	}//find_items_array
	pplx::task<std::vector<string_t> > CouchDataManager::maintains_items(std::vector<BaseItem *> &oVec, bool bDelete /*= false*/) {
		typedef std::vector<UpdateResponse> MyVec;
		std::vector<value> oInit;
		for (auto it = oVec.begin(); it != oVec.end(); ++it) {
			BaseItem *p = *it;
			if (p != nullptr) {
				if (bDelete) {
					string_t id = p->id();
					string_t rev = p->rev();
					if ((!id.empty()) && (!rev.empty())) {
						value oMap = value::object();
						oMap[DOC_ID] = value::string(id);
						oMap[DOC_REV] = value::string(rev);
						oMap[DOC_DELETED] = value::boolean(true);
						oInit.push_back(oMap);
					}
				}
				else {
					if (p->is_storeable()) {
						p->check_id();
						value oMap = p->get_value();
						oInit.push_back(oMap);
					}// storeable
				}
			}// p
		}// it
		std::vector<string_t> oRes;
		if (oInit.empty()) {
			return pplx::task_from_result(oRes);
		}
		return this->m_man->bulk_docs(oInit).then([=](pplx::task<MyVec>  previousTask) {
			std::vector<string_t> oRet;
			try {
				MyVec orp = previousTask.get();
				MyVec *p = &orp;
				if (p != nullptr) {
					for (auto it = p->begin(); it != p->end(); ++it) {
						const UpdateResponse &r = *it;
						string_t sr;
						if (r.ok()) {
							sr = r.rev();
						}
						oRet.push_back(sr);
					}// it
				}// p
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return pplx::task_from_result(oRet);
		});
	}// maintains_items
	////////////////////////////
}// namespace geninfo
