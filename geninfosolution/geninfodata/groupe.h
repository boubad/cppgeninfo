#pragma once
#ifndef __GROUPE_H__
#define __GROUPE_H__
////////////////////////////
#include "baseitem.h"
/////////////////////////////
namespace geninfo {
	//////////////////////////////////////
	class Groupe : public DepSigleNamedItem
	{
	public:
		static std::vector<string_t> genres(void);
	public:
		Groupe();
		Groupe(const Departement &oDep);
		Groupe(const value &oMap);
		Groupe(const Groupe &other);
		Groupe & operator=(const Groupe &other);
		virtual ~Groupe();
	public:
		string_t genre(void) const;
		void genre(const string_t &s);
		bool add_child(const Groupe &g);
		bool remove_child(const Groupe &g);
		std::set<string_t> children_ids(void) const;
		pplx::task<std::vector<std::shared_ptr<Groupe>>> get_children(IDatabaseManager &oMan) const;
	public:
		virtual bool is_storeable(void) const;
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
	};
}// namespace geninfo
//////////////////////////
#endif // __GROUPE_H__
