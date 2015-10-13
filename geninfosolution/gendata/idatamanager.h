#pragma once
#ifndef __IDATAMANAGER_H__
#define __IDATAMANAGER_H__
////////////////////////////////
#include "basedoc.h"
////////////////////////////////////
namespace geninfo {
	//////////////////////////////////
	class IDataManager {
	public:
		virtual Value read_doc(const std::string &id, bool bAttachments = false, bool bMeta = false) = 0;
		virtual Value insert_doc(const Value &doc) = 0;
		virtual Value update_doc(const Value &doc) = 0;
		virtual Value remove_doc(const Value &doc) = 0;
		virtual Value read_docs_range(const std::string &startkey, const std::string &endkey,
			int skip = 0, int limit = 0, bool bDoc = false) = 0;
		virtual Value read_docs_array(const std::vector<std::string> &ids) = 0;
		virtual Value maintains_docs(const std::vector<Value> &docs, bool bDelete = false) = 0;
	};// class IDataManager
	  ////////////////////////////////////
}// namespace geninfo
 /////////////////////////////////
#endif // __IDATAMANAGER_H__

