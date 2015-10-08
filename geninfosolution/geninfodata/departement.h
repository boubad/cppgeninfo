#pragma once
#ifndef __DEPARTEMENT_H__
#define  __DEPARTEMENT_H__
///////////////////////////////
#include "baseitem.h"
/////////////////////////////
namespace geninfo {
	class Groupe;
	class Unite;
	class Annee;
	////////////////////////
	class Departement : public SigleNamedItem
	{
	public:
		static pplx::task<std::vector<std::shared_ptr<Departement>>> get_all_departements(IDatabaseManager &oMan);
	public:
		Departement();
		Departement(const value &oMap);
		Departement(const Departement &other);
		Departement & operator=(const Departement &other);
		virtual ~Departement();
	public:
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
	public:
		pplx::task<std::vector<std::shared_ptr<Groupe> > > get_groupes(IDatabaseManager &oMan);
		pplx::task<std::vector<std::shared_ptr<Unite> > > get_unites(IDatabaseManager &oMan);
		pplx::task<std::vector<std::shared_ptr<Annee> > > get_annees(IDatabaseManager &oMan);
	}; // class Departement
}// namespace geninfo
/////////////////////////
#endif //  __DEPARTEMENT_H__
