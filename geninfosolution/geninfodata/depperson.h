#pragma once
#ifndef __DEPPERSON_H__
#define  __DEPPERSON_H__
//////////////////////////////
#include "personitem.h"
/////////////////////////
namespace geninfo {
	class Departement;
	////////////////////////////////
	class DepartementPerson : public PersonItem
	{
	public:
		DepartementPerson();
		DepartementPerson(const Departement &oDep, const Person &oPers);
		DepartementPerson(const value &oMap);
		DepartementPerson(const DepartementPerson &other);
		DepartementPerson & operator=(const DepartementPerson &other);
		virtual ~DepartementPerson();
	public:
		string_t departementid(void) const;
	public:
		pplx::task<std::shared_ptr<Departement> > get_departement(IDatabaseManager &oMan) const;
	public:
		virtual bool is_storeable(void) const;
		virtual string_t start_key(void) const;
		virtual string_t create_id(void) const;
	protected:
		virtual void update_save(Person &oPers);
		void departementid(const string_t &s);
	};
	///////////////////////////////////////////////
	class Etudiant : public DepartementPerson {
	public:
		static const string_t ETUDIANT_TYPE;
	public:
		Etudiant();
		Etudiant(const Departement &oDep, const Person &oPers);
		Etudiant(const value &oMap);
		Etudiant(const Etudiant &other);
		Etudiant & operator=(const Etudiant &other);
		virtual ~Etudiant();
	public:
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
	protected:
		virtual void update_save(Person &oPers);
	}; // class Etudiant
	////////////////////////////////
	class Enseignant : public DepartementPerson {
	public:
		static const string_t ENSEIGNANT_TYPE;
	public:
		Enseignant();
		Enseignant(const Departement &oDep, const Person &oPers);
		Enseignant(const value &oMap);
		Enseignant(const Enseignant &other);
		Enseignant & operator=(const Enseignant &other);
		virtual ~Enseignant();
	public:
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
	protected:
		virtual void update_save(Person &oPers);
	}; // class Enseignant
	//////////////////////////////////////
	class Administrator : public DepartementPerson {
	public:
		static const string_t ADMINISTRATOR_TYPE;
	public:
		Administrator();
		Administrator(const Departement &oDep, const Person &oPers);
		Administrator(const value &oMap);
		Administrator(const Administrator &other);
		Administrator & operator=(const Administrator &other);
		virtual ~Administrator();
	public:
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
	protected:
		virtual void update_save(Person &oPers);
	}; // class Administrator
	///////////////////////////////////
}// namespace geninfo
////////////////////////////
#endif //  __DEPPERSON_H__
