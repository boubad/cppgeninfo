#include "stdafx.h"
#include "etudiantevent.h"
#include "groupeevent.h"
#include "affectation.h"
#include "person.h"
#include "IDatabaseManager.h"
////////////////////////////////////
namespace geninfo {
/////////////////////////////////////////
	const string_t EtudiantEvent::ETUDIANTEVENT_TYPE(U("etudiantevent"));
	const string_t ETUDIANTEVENT_PREFIX = U("ETV");
	const string_t STRING_ETUDIANTAFFECTATIONID = U("etudiantaffectationid");
	const string_t STRING_GROUPEEVENTID = U("groupeeventid");
	const string_t STRING_GENRE = U("genre");
	const string_t STRING_NOTE = U("note");
	/////////////////////////////////////////////
	EtudiantEvent::EtudiantEvent() {
		this->set_string(BaseItem::TYPE_KEY, ETUDIANTEVENT_TYPE);
	}
	EtudiantEvent::EtudiantEvent(const GroupeEvent &gvt, const EtudiantAffectation &oAff) {
		this->personid(oAff.personid());
		this->etudiantaffectationid(oAff.id());
		this->groupeeventid(gvt.id());
		this->set_string(BaseItem::TYPE_KEY, ETUDIANTEVENT_TYPE);
	}
	EtudiantEvent::EtudiantEvent(const value &oMap) :PersonItem(oMap) {
		this->set_string(BaseItem::TYPE_KEY, ETUDIANTEVENT_TYPE);
	}
	EtudiantEvent::EtudiantEvent(const EtudiantEvent &other) : PersonItem(other) {

	}
	EtudiantEvent & EtudiantEvent::operator=(const EtudiantEvent &other) {
		if (this != &other) {
			PersonItem::operator=(other);
		}
		return *this;
	}
	EtudiantEvent::~EtudiantEvent() {

	}
	string_t EtudiantEvent::etudiantaffectationid(void) const {
		string_t sRet;
		if (this->has_field(STRING_ETUDIANTAFFECTATIONID)) {
			sRet = (this->get_value_at(STRING_ETUDIANTAFFECTATIONID)).as_string();
		}
		return sRet;
	}
	string_t EtudiantEvent::groupeeventid(void) const {
		string_t sRet;
		if (this->has_field(STRING_GROUPEEVENTID)) {
			sRet = (this->get_value_at(STRING_GROUPEEVENTID)).as_string();
		}
		return sRet;
	}
	string_t EtudiantEvent::genre(void) const {
		string_t sRet;
		if (this->has_field(STRING_GENRE)) {
			sRet = (this->get_value_at(STRING_GENRE)).as_string();
		}
		return sRet;
	}
	void EtudiantEvent::genre(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_GENRE, ss);
	}
	bool EtudiantEvent::has_note(void) const {
		return this->has_field(STRING_NOTE);
	}
	double EtudiantEvent::note(void) const {
		double dRet = 0.0;
		if (this->has_field(STRING_NOTE)) {
			value v = this->get_value_at(STRING_NOTE);
			if ((!v.is_null()) && v.is_double()) {
				dRet = v.as_double();
			}
		}
		return dRet;
	}
	void EtudiantEvent::note(double d) {
		this->set_double(STRING_NOTE, d);
	}
	string_t EtudiantEvent::type(void) const {
		return ETUDIANTEVENT_TYPE;
	}
	string_t EtudiantEvent::store_prefix(void) const {
		return ETUDIANTEVENT_PREFIX;
	}
	bool EtudiantEvent::is_storeable(void) const {
		string_t s1 = this->groupeeventid();
		string_t s2 = this->etudiantaffectationid();
		string_t s3 = this->genre();
		return (!s1.empty()) && (!s2.empty()) && (!s3.empty()) && PersonItem::is_storeable();
	}
	string_t EtudiantEvent::start_key(void) const {
		string_t s1 = this->store_prefix();
		string_t s2 = this->groupeeventid();
		return (s1 + s2);
	}
	string_t EtudiantEvent::create_id(void) const {
		string_t s1 = this->start_key();
		string_t s2 = this->etudiantaffectationid();
		string_t s3 = this->genre();
		return (s1 + s2 + s3);
	}
	pplx::task<std::shared_ptr<EtudiantAffectation> > EtudiantEvent::get_etudiantaffectation(IDatabaseManager &oMan) const {
		string_t id = this->etudiantaffectationid();
		EtudiantAffectation model;
		return oMan.load_item(model, id);
	}
	pplx::task<std::shared_ptr<GroupeEvent> > EtudiantEvent::get_groupeevent(IDatabaseManager &oMan) const {
		string_t id = this->groupeeventid();
		GroupeEvent model;
		return oMan.load_item(model, id);
	}
	void EtudiantEvent::update_save(Person &oPers) {
		PersonItem::update_save(oPers);
		oPers.add_eventid(this->id());
	}
	void EtudiantEvent::etudiantaffectationid(const string_t &s) {
		this->set_string(STRING_ETUDIANTAFFECTATIONID, s);
	}
	void EtudiantEvent::groupeeventid(const string_t &s) {
		this->set_string(STRING_GROUPEEVENTID, s);
	}
	///////////////////////////////////////////
}// geninfo
