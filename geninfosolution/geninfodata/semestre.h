#pragma once
#ifndef __SEMESTRE_H__
#define __SEMESTRE_H__
///////////////////////////////
#include "baseitem.h"
/////////////////////////////
namespace geninfo {
	/////////////////////////////////////
	class Annee;
	//////////////////////////////////////
	class Semestre : public SigleNamedItem
	{
	public:
		static const string_t SEMESTRE_TYPE;
	public:
		Semestre();
		Semestre(const Annee &oAnnee);
		Semestre(const value &oMap);
		Semestre(const Semestre &other);
		Semestre & operator=(const Semestre &other);
		virtual ~Semestre();
	public:
		string_t anneeid(void) const;
		Date start_date(void) const;
		void start_date(Date d);
		Date end_date(void) const;
		void end_date(Date d);
		pplx::task<std::shared_ptr<Annee> > get_annee(IDatabaseManager &oMan);
	public:
		virtual string_t start_key(void) const;
		virtual string_t create_id(void) const;
		virtual bool is_storeable(void) const;
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
	protected:
		void anneeid(const string_t &s);
	};
}// namespace geninfo
/////////////////////////
#endif //
