#pragma once
//////////////////////////////////
#ifndef __UNITE_H__
#define __UNITE_H__
////////////////////////////////
#include "baseitem.h"
/////////////////////////////
namespace geninfo {
	class Matiere;
	//////////////////////////////////////
	class Unite : public DepSigleNamedItem
	{
	public:
		static const string_t UNITE_TYPE;
	public:
		Unite();
		Unite(const Departement &oDep);
		Unite(const value &oMap);
		Unite(const Unite &other);
		Unite & operator=(const Unite &other);
		virtual ~Unite();
	public:
		size_t order(void) const;
		void order(size_t n);
		pplx::task<std::vector<std::shared_ptr<Matiere> > > get_matieres(IDatabaseManager &oMan);
	public:
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
	};
}// namespace geninfo
////////////////////////////
#endif // __UNITE_H__
