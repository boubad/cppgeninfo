#pragma once
#ifndef __GROUPEEVENT_H__
#define __GROUPEEVENT_H__
/////////////////////////////////
#include "personitem.h"
/////////////////////////////
namespace geninfo {
	//////////////////////////////
	class EnseignantAffectation;
	class EtudiantEvent;
	class Semestre;
	class Matiere;
	//////////////////////////////
	class GroupeEvent : public PersonItem
	{
	public:
		static pplx::task<std::vector<std::shared_ptr<GroupeEvent>>> get_semestre_groupeevents(IDatabaseManager &oMan, const Semestre &oSem);
		static pplx::task<std::vector<std::shared_ptr<GroupeEvent>>> get_semestre_matiere_groupeevents(IDatabaseManager &oMan, const Semestre &oSem, const Matiere &oMat);
	public:
		GroupeEvent();
		GroupeEvent(const value &oMap);
		GroupeEvent(const EnseignantAffectation &oAff);
		GroupeEvent(const GroupeEvent &other);
		GroupeEvent & operator=(const GroupeEvent &other);
		virtual ~GroupeEvent();
	public:
		string_t semestreid(void) const;
		string_t matiereid(void) const;
		string_t enseignantaffectationid(void) const;
		Date event_date(void) const;
		void event_date(Date d);
		string_t name(void) const;
		void name(const string_t &s);
		string_t genre(void) const;
		void genre(const string_t &s);
		string_t location(void) const;
		void location(const string_t &s);
		double coefficient(void) const;
		void coefficient(double d);
		DateTime start_time(void) const;
		void start_time(DateTime d);
		DateTime end_time(void) const;
		void end_time(DateTime d);
		double min_note(void) const;
		void min_note(double d);
		double max_note(void) const;
		void max_note(double d);
	public:
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
		virtual bool is_storeable(void) const;
		virtual string_t start_key(void) const;
		virtual string_t create_id(void) const;
		pplx::task<std::shared_ptr<EnseignantAffectation> > get_enseignantaffectation(IDatabaseManager &oMan) const;
		pplx::task<std::vector<std::shared_ptr<EtudiantEvent>>> get_etudiantevents(IDatabaseManager &oMan) const;
	protected:
		virtual void update_save(Person &oPers);
	private:
		void enseignantaffectationid(const string_t &s);
		void matiereid(const string_t &s);
		void semestreid(const string_t &s);
	};// class GroupeEvent
	/////////////////////////////
}// namespace geninfo
///////////////////////////
#endif // __GROUPEEVENT_H__

