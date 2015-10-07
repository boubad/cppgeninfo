#pragma once
#ifndef __PERSON_H__
#define  __PERSON_H__
//////////////////////////////
#include "baseitem.h"
///////////////////////////////
namespace geninfo {
	class Person : public BaseItem
	{
	public:
		static const string_t PERSON_TYPE;
		static pplx::task<Person *> find_person_by_username(IDatabaseManager &oMan, const string_t &susername, bool bAttachments = false);
	public:
		Person();
		Person(const value &oMap);
		Person(const Person &other);
		Person & operator=(const Person &other);
		virtual ~Person();
	public:
		string_t username(void) const;
		void username(const string_t &s);
		string_t password(void) const;
		void password(const string_t &s);
		string_t firstname(void) const;
		void firstname(const string_t &s);
		string_t lastname(void) const;
		void lastname(const string_t &s);
		string_t email(void) const;
		void email(const string_t &s);
		string_t phone(void) const;
		void phone(const string_t &s);
	public:
		void reset_password(void);
		bool check_password(const string_t &sc) const;
		void change_password(const string_t &sc);
	public:
		std::set<string_t> departementids(void) const;
		bool add_departementid(const string_t &id);
		std::set<string_t> anneeids(void) const;
		bool add_anneeid(const string_t &id);
		std::set<string_t> semestreids(void) const;
		bool add_semestreid(const string_t &id);
		std::set<string_t> uniteids(void) const;
		bool add_uniteid(const string_t &id);
		std::set<string_t> matiereids(void) const;
		bool add_matiereid(const string_t &id);
		std::set<string_t> groupeids(void) const;
		bool add_groupeid(const string_t &id);
		std::set<string_t> affectationids(void) const;
		bool add_affectationid(const string_t &id);
		std::set<string_t>  eventids(void) const;
		bool add_eventid(const string_t &id);
		std::set<string_t>  operatorids(void) const;
		bool add_operatorid(const string_t &id);
		std::set<string_t>  enseignantids(void) const;
		bool add_enseignantid(const string_t &id);
		std::set<string_t>  etudiantids(void) const;
		bool add_etudiantid(const string_t &id);
	public:
		std::vector<string_t> get_all_items_ids(void);
	public:
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
		virtual bool is_storeable(void) const;
		virtual string_t create_id(void) const;
	}; // class Person
	///////////////////////////////////
	class EtudiantPerson : public Person {
	public:
		static const string_t ETUDIANTPERSON_TYPE;
	public:
		EtudiantPerson();
		EtudiantPerson(const value &oMap);
		EtudiantPerson(const EtudiantPerson &other);
		EtudiantPerson & operator=(const EtudiantPerson &other);
		virtual ~EtudiantPerson();
	public:
		string_t dossier(void) const;
		void dossier(const string_t &s);
		string_t sexe(void) const;
		void sexe(const string_t &s);
		Date birth_date(void) const;
		void birth_date(Date s);
		string_t ville(void) const;
		void ville(const string_t &s);
		string_t etablissement(void) const;
		void etablissement(const string_t &s);
		string_t serie_bac(void) const;
		void serie_bac(const string_t &s);
		string_t option_bac(void) const;
		void option_bac(const string_t &s);
		string_t mention_bac(void) const;
		void mention_bac(const string_t &s);
		string_t etudes_superieures(void) const;
		void etudes_superieures(const string_t &s);
		string_t apb(void) const;
		void apb(const string_t &s);
		string_t redoublant(void) const;
		void redoublant(const string_t &s);
	public:
		virtual string_t type(void) const;
	};// class EtudiantPerson
	/////////////////////////////////////
	class EnseignantPerson : public Person {
	public:
		static const string_t ENSEIGNANTPERSON_TYPE;
	public:
		EnseignantPerson();
		EnseignantPerson(const value &oMap);
		EnseignantPerson(const EnseignantPerson &other);
		EnseignantPerson & operator=(const EnseignantPerson &other);
		virtual ~EnseignantPerson();
	public:
		virtual string_t type(void) const;
	};// class EnseignantPerson
	///////////////////////////////////////
	class OperatorPerson : public Person {
	public:
		static const string_t OPERATORPERSON_TYPE;
	public:
		OperatorPerson();
		OperatorPerson(const value &oMap);
		OperatorPerson(const OperatorPerson &other);
		OperatorPerson & operator=(const OperatorPerson &other);
		virtual ~OperatorPerson();
	public:
		virtual string_t type(void) const;
	};// class OperatorPerson
	/////////////////////////////////////////
	class SuperAdminPerson : public Person {
	public:
		static const string_t SUPERADMINPERSON_TYPE;
	public:
		SuperAdminPerson();
		SuperAdminPerson(const value &oMap);
		SuperAdminPerson(const SuperAdminPerson &other);
		SuperAdminPerson & operator=(const SuperAdminPerson &other);
		virtual ~SuperAdminPerson();
	public:
		virtual string_t type(void) const;
	};// class SuperAdminPerson
	/////////////////////////////////////////
}// namespace geninfo
//////////////////////////
#endif //  __PERSON_H__
