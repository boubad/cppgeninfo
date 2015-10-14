#pragma once
#ifndef __DEPARTEMENT_H__
#define  __DEPARTEMENT_H__
//////////////////////////////////
#include "siglenameditem.h"
/////////////////////////////////
namespace geninfo {
	class Departement;
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
	};
}// namespace geninfo
///////////////////////////
#endif // __DEPARTEMENT_H__
