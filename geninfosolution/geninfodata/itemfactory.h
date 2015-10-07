#pragma once
#pragma once
#ifndef __ITEMFACTORY_H__
#define __ITEMFACTORY_H__
//////////////////////////////////
#include "IDatabaseManager.h"
///////////////////////////////
namespace geninfo {
	class ItemFactory : public IItemFactory
	{
	public:
		ItemFactory();
		ItemFactory(const ItemFactory &other);
		ItemFactory & operator=(const ItemFactory &other);
		virtual ~ItemFactory();
	public:
		virtual BaseItem *create_item(const value &oMap, const string_t &type = string_t()) const;
	};
}// namespace gen_info
 /////////////////////////////
#endif // __ITEMFACTORY_H__
