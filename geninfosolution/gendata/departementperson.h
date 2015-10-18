#pragma once
#ifndef __DEPARTEMENTPERSON_H__
#define __DEPARTEMENTPERSON_H__
////////////////////////////////////
#include "baseitem.h"
////////////////////////////
namespace geninfo {
	class Person;
	class Departement;
	/////////////////////////////////////////
	class DepartementPerson : public BaseItem
	{
	public:
		DepartementPerson();
		DepartementPerson(const Departement &oDep, const Person &oPers);
		DepartementPerson(const Value &oMap);
		DepartementPerson(const DepartementPerson &other);
		DepartementPerson & operator=(const DepartementPerson &other);
		virtual ~DepartementPerson();
	public:
		void person(const Person &oPers);
		void departement(const Departement &oDep);
		std::string departementid(void) const;
		std::string personid(void) const;
		std::string firstname(void) const;
		std::string lastname(void) const;
		std::string fullname(void) const;
		std::shared_ptr<Person> get_person(IDataManager &oMan);
		std::shared_ptr<Departement> get_departement(IDataManager &oMan);
	public:
		virtual std::string start_key(void) const;
		virtual std::string create_id(void) const;
		virtual bool is_storeable(void) const;
		virtual std::string text(void) const;
		virtual bool save(IDataManager &oMan);
	protected:
		virtual bool check_person(Person &oPers);
	};
	/////////////////////////////////////////////
}// namespace geninfo
//////////////////////////////////////
#endif // __DEPARTEMENTPERSON_H__
