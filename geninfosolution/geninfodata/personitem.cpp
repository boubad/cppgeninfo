#include "stdafx.h"
#include "personitem.h"
#include "person.h"
#include "IDatabaseManager.h"
#include "couchdoc.h"
///////////////////////////////
namespace geninfo {
	//////////////////////////////////
	const string_t STRING_PERSONID = U("personid");
	const string_t STRING_FIRSTNAME = U("firstname");
	const string_t STRING_LASTNAME = U("lastname");
	///////////////////////////////////////
	PersonItem::PersonItem() {

	}
	PersonItem::PersonItem(const Person &oPers) {
		this->personid(oPers.id());
		this->firstname(oPers.firstname());
		this->lastname(oPers.lastname());
	}
	PersonItem::PersonItem(const value &oMap) :BaseItem(oMap) {

	}
	PersonItem::PersonItem(const PersonItem &other) : BaseItem(other) {

	}
	PersonItem & PersonItem::operator=(const PersonItem &other) {
		if (this != &other) {
			BaseItem::operator=(other);
		}
		return *this;
	}
	PersonItem::~PersonItem() {

	}
	string_t PersonItem::personid(void) const {
		string_t sRet;
		if (this->has_field(STRING_PERSONID)) {
			sRet = (this->get_value_at(STRING_PERSONID)).as_string();
		}
		return sRet;
	}
	void PersonItem::personid(const string_t &s) {
		this->set_string(STRING_PERSONID, s);
	}
	string_t PersonItem::firstname(void) const {
		string_t sRet;
		if (this->has_field(STRING_FIRSTNAME)) {
			sRet = (this->get_value_at(STRING_FIRSTNAME)).as_string();
		}
		return sRet;
	}
	string_t PersonItem::lastname(void) const {
		string_t sRet;
		if (this->has_field(STRING_LASTNAME)) {
			sRet = (this->get_value_at(STRING_LASTNAME)).as_string();
		}
		return sRet;
	}
	pplx::task<std::shared_ptr<Person> > PersonItem::get_person(IDatabaseManager &oMan) const {
		string_t id = this->personid();
		if (id.empty()) {
			std::shared_ptr<Person> ox;
			return pplx::task_from_result(ox);
		}
		return oMan.read_item(id).then([=](pplx::task<BaseItem *>t) {
			std::shared_ptr<Person> ox;
			try {
				Person *p = dynamic_cast<Person *>(t.get());
				ox.reset(p);
			}
			catch (...) {}
			return pplx::task_from_result(ox);
		});
	}// get_person
	bool PersonItem::is_storeable(void) const {
		string_t s = this->personid();
		return (!s.empty());
	}
	pplx::task<bool> PersonItem::save(IDatabaseManager &oMan) {
		this->check_id();
		std::shared_ptr<Person> ox = this->get_person(oMan).get();
		Person *pPers = ox.get();
		if (pPers != nullptr) {
			this->update_save(*pPers);
			bool bx = pPers->save(oMan).get();
		}
		return BaseItem::save(oMan);
	}// save
	pplx::task<bool> PersonItem::remove(IDatabaseManager &oMan) {
		std::shared_ptr<Person> ox = this->get_person(oMan).get();
		Person *pPers = ox.get();
		if (pPers != nullptr) {
			this->update_remove(*pPers);
			bool bx = pPers->save(oMan).get();
		}
		return BaseItem::remove(oMan);
	}// remove
	void PersonItem::update_save(Person &oPers) {
		oPers.check_id();
		this->firstname(oPers.firstname());
		this->lastname(oPers.lastname());
		string_t id = oPers.id();
		if (id.empty()) {
			this->personid(id);
		}
	}// update_save
	void PersonItem::update_remove(Person & /*oPers */) {
		// do nothing
	}
	void PersonItem::firstname(const string_t &s) {
		this->set_string(STRING_FIRSTNAME, s);
	}
	void PersonItem::lastname(const string_t &s) {
		this->set_string(STRING_LASTNAME, s);
	}
	/////////////////////////////////////
}// namespace geninfo
