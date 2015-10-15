#pragma once
#ifndef __DEPARTEMENT_H__
#define  __DEPARTEMENT_H__
//////////////////////////////////
#include "siglenameditem.h"
/////////////////////////////////
namespace geninfo {
	class Departement;
	class Groupe;
	class Unite;
	//////////////////////////
	typedef std::shared_ptr<Departement> PDepartement;
	////////////////////////////////
	class Departement : public SigleNamedItem
	{
	public:
		static std::vector<PDepartement> get_all_departements(IDataManager &oMan);
	public:
		Departement();
		Departement(const Value &oMap);
		Departement(const Departement &other);
		Departement & operator=(const Departement & other);
		~Departement();
	public:
		virtual std::string store_prefix(void) const;
	public:
		std::vector<std::shared_ptr<Groupe>> groupes(IDataManager &oMan);
		std::vector<std::shared_ptr<Unite>> unites(IDataManager &oMan);
	};
}// namespace geninfo
///////////////////////////
#endif // __DEPARTEMENT_H__
