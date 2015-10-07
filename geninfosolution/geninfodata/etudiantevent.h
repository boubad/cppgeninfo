#pragma once
#ifndef __ETUDIANTEVENT_H__
#define __ETUDIANTEVENT_H__
///////////////////////////////////
#include "personitem.h"
/////////////////////////////////
namespace geninfo {
	//////////////////////////
	class GroupeEvent;
	class EtudiantAffectation;
	////////////////////////////
	class EtudiantEvent : public PersonItem
	{
	public:
		static const string_t ETUDIANTEVENT_TYPE;
	public:
		EtudiantEvent();
		EtudiantEvent(const GroupeEvent &gvt, const EtudiantAffectation &oAff);
		EtudiantEvent(const value &oMap);
		EtudiantEvent(const EtudiantEvent &other);
		EtudiantEvent & operator=(const EtudiantEvent &other);
		virtual ~EtudiantEvent();
	public:
		string_t etudiantaffectationid(void) const;
		string_t groupeeventid(void) const;
		string_t genre(void) const;
		void genre(const string_t &s);
		bool has_note(void) const;
		double note(void) const;
		void note(double d);
	public:
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
		virtual bool is_storeable(void) const;
		virtual string_t start_key(void) const;
		virtual string_t create_id(void) const;
		pplx::task<std::shared_ptr<EtudiantAffectation> > get_etudiantaffectation(IDatabaseManager &oMan) const;
		pplx::task<std::shared_ptr<GroupeEvent> > get_groupeevent(IDatabaseManager &oMan) const;
	protected:
		virtual void update_save(Person &oPers);
	private:
		void etudiantaffectationid(const string_t &s);
		void groupeeventid(const string_t &s);
	};// class EtudiantEvent
}// namespace geninfo
//////////////////////////////
#endif // __ETUDIANTEVENT_H__
