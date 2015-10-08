#pragma once
#ifndef __IDATAMANAGER_H__
#define __IDATAMANAGER_H__
////////////////////////////////
#include "baseheader.h"
////////////////////////////////////
namespace geninfo {
	//////////////////////////////////
	class IDataManager {
	public:
		IDataManager(){}
		IDataManager(const IDataManager &){}
		IDataManager & operator=(const IDataManager &) { return (*this); }
		virtual ~IDataManager(){}
	public:
		virtual Value read_doc(const string &id, bool bAttachments = false, bool bMeta = false) = 0;
		virtual Value insert_doc(const Value &doc) = 0;
		virtual Value update_doc(const Value &doc) = 0;
		virtual Value remove_doc(const Value &doc) = 0;
		virtual Value read_docs_range(const string &startkey, const string &endkey,
			int skip = 0, int limit = 0, bool bDoc = false) = 0;
		virtual Value read_docs_array(const std::vector<string> ids) = 0;
		virtual Value maintains_docs(const std::vector<Value> docs, bool bDelete = false) = 0;
	};// class IDataManager
	////////////////////////////////////
}// namespace geninfo
/////////////////////////////////
#endif // __IDATAMANAGER_H__
