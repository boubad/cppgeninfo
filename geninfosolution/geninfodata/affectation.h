#pragma once
#ifndef __AFFECTATION_H__
#define  __AFFECTATION_H__
//////////////////////////////
#include "personitem.h"
//////////////////////////////
namespace geninfo {
	class Semestre;
	class Groupe;
	class Matiere;
	class Etudiant;
	class Enseignant;
	class Annee;
	////////////////////////////
	class Affectation : public PersonItem
	{
	public:
		Affectation();
		Affectation(const Semestre &oSem, const Groupe &oGroupe);
		Affectation(const value &oMap);
		Affectation(const Affectation &other);
		Affectation & operator=(const Affectation &other);
		virtual ~Affectation();
	public:
		string_t semestreid(void) const;
		string_t groupeid(void) const;
		Date start_date(void) const;
		void start_date(Date d);
		Date end_date(void) const;
		void end_date(Date d);
	public:
		pplx::task<std::shared_ptr<Semestre> > get_semestre(IDatabaseManager &oMan) const;
		pplx::task<std::shared_ptr<Groupe> > get_groupe(IDatabaseManager &oMan) const;
		pplx::task<std::shared_ptr<Annee> > get_annee(IDatabaseManager &oMan) const;
	public:
		virtual bool is_storeable(void) const;
		virtual string_t start_key(void) const;
		virtual pplx::task<bool> save(IDatabaseManager &oMan);
	protected:
		virtual void update_save(Person &oPers);
		void semestreid(const string_t &s);
		void groupeid(const string_t &s);
	}; // class Affectation
	////////////////////////////////////////
	class EnseignantAffectation : public Affectation
	{
	public:
		static const string_t ENSEIGNANTAFFECTATION_TYPE;
	public:
		EnseignantAffectation();
		EnseignantAffectation(const Enseignant &oProf, const Matiere &oMat, const Semestre &oSem, const Groupe &oGroupe);
		EnseignantAffectation(const value &oMap);
		EnseignantAffectation(const EnseignantAffectation &other);
		EnseignantAffectation & operator=(const EnseignantAffectation &other);
		virtual ~EnseignantAffectation();
	public:
		string_t enseignantid(void) const;
		string_t matiereid(void) const;
	public:
		pplx::task<std::shared_ptr<Enseignant> > get_enseignant(IDatabaseManager &oMan) const;
		pplx::task<std::shared_ptr<Matiere> > get_matiere(IDatabaseManager &oMan) const;
	public:
		virtual bool is_storeable(void) const;
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
		virtual string_t start_key(void) const;
		virtual string_t create_id(void) const;
		virtual pplx::task<bool> save(IDatabaseManager &oMan);
	protected:
		virtual void update_save(Person &oPers);
		void enseignantid(const string_t &s);
		void matiereid(const string_t &s);
	}; // class EnseignantAffectation
	///////////////////////////////////
	class EtudiantAffectation : public Affectation
	{
	public:
		static const string_t ETUDIANTAFFECTATION_TYPE;
	public:
		EtudiantAffectation();
		EtudiantAffectation(const Etudiant &oEtud,const Semestre &oSem, const Groupe &oGroupe);
		EtudiantAffectation(const value &oMap);
		EtudiantAffectation(const EtudiantAffectation &other);
		EtudiantAffectation & operator=(const EtudiantAffectation &other);
		virtual ~EtudiantAffectation();
	public:
		string_t etudiantid(void) const;
	public:
		pplx::task<std::shared_ptr<Etudiant> > get_etudiant(IDatabaseManager &oMan) const;
	public:
		virtual bool is_storeable(void) const;
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
		virtual string_t start_key(void) const;
		virtual string_t create_id(void) const;
	protected:
		virtual void update_save(Person &oPers);
	private:
		void etudiantid(const string_t &s);
	}; // class EnseignantAffectation
	////////////////////////////////////
}// namespace geninfo
//////////////////////////////
#endif //  __AFFECTATION_H__
