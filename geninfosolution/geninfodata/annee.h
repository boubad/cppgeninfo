#pragma once
#ifndef __ANNEE_H__
#define __ANNEE_H__
///////////////////////////////////
#include "baseitem.h"
/////////////////////////////
namespace geninfo {
	class Semestre;
	//////////////////////////////////////
	class Annee : public DepSigleNamedItem
	{
	public:
		static const string_t ANNEE_TYPE;
	public:
		Annee();
		Annee(const Departement &oDep);
		Annee(const value &oMap);
		Annee(const Annee &other);
		Annee & operator=(const Annee &other);
		virtual ~Annee();
	public:
		Date start_date(void) const;
		void start_date(Date d);
		Date end_date(void) const;
		void end_date(Date d);
		pplx::task<std::vector<std::shared_ptr<Semestre> > > get_semestres(IDatabaseManager &oMan);
	public:
		virtual string_t create_id(void) const;
		virtual bool is_storeable(void) const;
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
	};
}// namespace geninfo
//////////////////////////
#endif // __ANNEE_H__
