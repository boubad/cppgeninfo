#include "stdafx.h"
#include "departementperson.h"
#include "departement.h"
#include "person.h"
#include "domainconstants.h"
#include "idatamanager.h"
//////////////////////////////////////
namespace geninfo {
	/////////////////////////////////
	DepartementPerson::DepartementPerson() {

	}
	DepartementPerson::DepartementPerson(const Departement &oDep, const Person &oPers) {
		this->person(oPers);
		this->departement(oDep);
	}
	DepartementPerson::DepartementPerson(const Value &oMap) :BaseItem(oMap) {

	}
	DepartementPerson::DepartementPerson(const DepartementPerson &other) : BaseItem(other) {

	}
	DepartementPerson & DepartementPerson::operator=(const DepartementPerson &other) {
		if (this != &other) {
			BaseItem::operator=(other);
		}
		return (*this);
	}
	DepartementPerson::~DepartementPerson() {

	}
	void DepartementPerson::person(const Person &oPers) {
		this->set_string(DomainConstants::PERSONID, oPers.id());
		this->set_string(DomainConstants::FIRSTNAME, oPers.firstname());
		this->set_string(DomainConstants::LASTNAME, oPers.lastname());
	}
	void DepartementPerson::departement(const Departement &oDep) {
		this->set_string(DomainConstants::DEPARTEMENTID, oDep.id());
	}
	std::string DepartementPerson::departementid(void) const {
		return this->get_string(DomainConstants::DEPARTEMENTID);
	}
	std::string DepartementPerson::personid(void) const {
		return this->get_string(DomainConstants::PERSONID);
	}
	std::string DepartementPerson::firstname(void) const {
		return this->get_string(DomainConstants::FIRSTNAME);
	}
	std::string DepartementPerson::lastname(void) const {
		return this->get_string(DomainConstants::LASTNAME);
	}
	std::string DepartementPerson::fullname(void) const {
		std::string s = this->lastname() + std::string(" ") + this->firstname();
		return trim(s);
	}
	std::shared_ptr<Person> DepartementPerson::get_person(IDataManager &oMan) {
		std::shared_ptr<Person> oRet;
		std::string id = this->personid();
		if (id.empty()) {
			Value v = oMan.read_doc(id);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Person>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	std::shared_ptr<Departement> DepartementPerson::get_departement(IDataManager &oMan) {
		std::shared_ptr<Departement> oRet;
		std::string id = this->personid();
		if (id.empty()) {
			Value v = oMan.read_doc(id);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Departement>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	std::string DepartementPerson::start_key(void) const {
		return (this->store_prefix() + this->departementid());
	}
	std::string DepartementPerson::create_id(void) const {
		return this->start_key()  + this->personid();
	}
	bool DepartementPerson::is_storeable(void) const {
		std::string s2 = this->personid();
		return (!s2.empty()) && BaseItem::is_storeable();
	}
	std::string DepartementPerson::text(void) const {
		return this->fullname();
	}
	bool DepartementPerson::save(IDataManager &oMan) {
		std::string s1 = this->departementid();
		std::string s2 = this->personid();
		if (s1.empty() || s2.empty()) {
			return (false);
		}
		std::shared_ptr<Person> o = this->get_person(oMan);
		Person *pPers = o.get();
		if (pPers == nullptr) {
			return false;
		}
		if (!pPers->is_storeable()) {
			return false;
		}
		bool b = this->check_person(*pPers);
		if (b) {
			if (!pPers->save(oMan)) {
				return (false);
			}
		}
		return BaseItem::save(oMan);
	}//save
	bool DepartementPerson::check_person(Person &oPers) {
		bool bRet = false;
		std::string s = this->personid();
		if (s != oPers.id()) {
			this->set_string(DomainConstants::PERSONID, oPers.id());
		}
		s = this->firstname();
		if (s != oPers.firstname()) {
			this->set_string(DomainConstants::FIRSTNAME, oPers.firstname());
		}
		s = this->lastname();
		if (s != oPers.lastname()) {
			this->set_string(DomainConstants::LASTNAME, oPers.lastname());
		}
		return bRet;
	}
}// namespace geninfo
