#include "stdafx.h"
#include "groupeevent.h"
#include "affectation.h"
#include "person.h"
#include "etudiantevent.h"
#include "semestre.h"
#include "matiere.h"
#include "IDatabaseManager.h"
////////////////////////////////
namespace geninfo {
	//////////////////////////////////////
	const string_t GroupeEvent::GROUPEEVENT_TYPE(U("groupeevent"));
	const string_t GROUPEEVENT_PREFIX = U("GVT");
	const string_t STRING_ENSEIGNANTAFFECTATIONID = U("enseignantaffectationid");
	const string_t STRING_SEMESTREID = U("semestreid");
	const string_t STRING_MATIEREID = U("matiereid");
	const string_t STRING_GENRE = U("genre");
	const string_t STRING_EVENTDATE = U("eventdate");
	const string_t STRING_NAME = U("name");
	const string_t STRING_LOCATION = U("location");
	const string_t STRING_STARTTIME = U("starttime");
	const string_t STRING_ENDTIME = U("endtime");
	const string_t STRING_COEFFICIENT = U("coefficient");
	const string_t STRING_MINNOTE = U("minnote");
	const string_t STRING_MAXNOTE = U("maxnote");
	////////////////////////////////////////
	GroupeEvent::GroupeEvent() {
		this->set_string(BaseItem::TYPE_KEY, GROUPEEVENT_TYPE);
	}
	GroupeEvent::GroupeEvent(const value &oMap) : PersonItem(oMap) {
		this->set_string(BaseItem::TYPE_KEY, GROUPEEVENT_TYPE);
	}
	GroupeEvent::GroupeEvent(const EnseignantAffectation &oAff) {
		this->set_string(BaseItem::TYPE_KEY, GROUPEEVENT_TYPE);
		this->enseignantaffectationid(oAff.id());
		this->personid(oAff.personid());
		this->semestreid(oAff.semestreid());
		this->matiereid(oAff.matiereid());
	}
	GroupeEvent::GroupeEvent(const GroupeEvent &other) : PersonItem(other) {

	}
	GroupeEvent & GroupeEvent::operator=(const GroupeEvent &other) {
		if (this != &other) {
			PersonItem::operator=(other);
		}
		return *this;
	}
	GroupeEvent::~GroupeEvent() {

	}
	string_t GroupeEvent::semestreid(void) const {
		string_t sRet;
		if (this->has_field(STRING_SEMESTREID)) {
			sRet = (this->get_value_at(STRING_SEMESTREID)).as_string();
		}
		return sRet;
	}
	void GroupeEvent::semestreid(const string_t &s) {
		this->set_string(STRING_SEMESTREID, s);
	}
	string_t GroupeEvent::matiereid(void) const {
		string_t sRet;
		if (this->has_field(STRING_MATIEREID)) {
			sRet = (this->get_value_at(STRING_MATIEREID)).as_string();
		}
		return sRet;
	}
	void GroupeEvent::matiereid(const string_t &s) {
		this->set_string(STRING_MATIEREID, s);
	}
	string_t GroupeEvent::enseignantaffectationid(void) const {
		string_t sRet;
		if (this->has_field(STRING_ENSEIGNANTAFFECTATIONID)) {
			sRet = (this->get_value_at(STRING_ENSEIGNANTAFFECTATIONID)).as_string();
		}
		return sRet;
	}
	void GroupeEvent::enseignantaffectationid(const string_t &s) {
		this->set_string(STRING_ENSEIGNANTAFFECTATIONID, s);
	}
	Date GroupeEvent::event_date(void) const {
		Date dRet;
		if (this->has_field(STRING_EVENTDATE)) {
			value v = this->get_value_at(STRING_EVENTDATE);
			dRet = value_to_date(v);
		}
		return dRet;
	}
	void GroupeEvent::event_date(Date d) {
		this->set_value_at(STRING_EVENTDATE, date_to_value(d));
	}
	string_t GroupeEvent::name(void) const {
		string_t sRet;
		if (this->has_field(STRING_NAME)) {
			sRet = (this->get_value_at(STRING_NAME)).as_string();
		}
		return sRet;
	}
	void GroupeEvent::name(const string_t &s) {
		string_t ss = trim(s);
		if (ss.length() > 1) {
			ss = to_upper(ss.substr(0, 1)) + ss.substr(1);
		}
		else {
			ss = to_upper(s);
		}
		this->set_string(STRING_NAME, ss);
	}
	string_t GroupeEvent::genre(void) const {
		string_t sRet;
		if (this->has_field(STRING_GENRE)) {
			sRet = (this->get_value_at(STRING_GENRE)).as_string();
		}
		return sRet;
	}
	void GroupeEvent::genre(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_GENRE, ss);
	}
	string_t GroupeEvent::location(void) const {
		string_t sRet;
		if (this->has_field(STRING_LOCATION)) {
			sRet = (this->get_value_at(STRING_LOCATION)).as_string();
		}
		return sRet;
	}
	void GroupeEvent::location(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_LOCATION, ss);
	}
	double GroupeEvent::coefficient(void) const {
		double dRet = 1.0;
		if (this->has_field(STRING_COEFFICIENT)) {
			value v = this->get_value_at(STRING_COEFFICIENT);
			if ((!v.is_null()) && v.is_double()) {
				dRet = v.as_double();
			}
		}
		return (dRet > 0.0) ? dRet : 1.0;
	}
	void GroupeEvent::coefficient(double d) {
		double x = (d > 0.0) ? d : 1.0;
		this->set_double(STRING_COEFFICIENT, x);
	}
	DateTime GroupeEvent::start_time(void) const {
		DateTime oRet;
		if (this->has_field(STRING_STARTTIME)) {
			value  v = this->get_value_at(STRING_STARTTIME);
			if ((!v.is_null()) && v.is_string()) {
				oRet = value_to_datetime(v);
			}
		}// field
		return oRet;
	}
	void GroupeEvent::start_time(DateTime d) {
		this->set_value_at(STRING_STARTTIME, datetime_to_value(d));
	}
	DateTime GroupeEvent::end_time(void) const {
		DateTime oRet;
		if (this->has_field(STRING_ENDTIME)) {
			value  v = this->get_value_at(STRING_ENDTIME);
			if ((!v.is_null()) && v.is_string()) {
				oRet = value_to_datetime(v);
			}
		}// field
		return oRet;
	}
	void GroupeEvent::end_time(DateTime d) {
		this->set_value_at(STRING_ENDTIME, datetime_to_value(d));
	}
	double GroupeEvent::min_note(void) const {
		double dRet = 0.0;
		if (this->has_field(STRING_MINNOTE)) {
			value v = this->get_value_at(STRING_MINNOTE);
			if ((!v.is_null()) && v.is_double()) {
				dRet = v.as_double();
			}
		}
		return dRet;
	}
	void GroupeEvent::min_note(double d) {
		this->set_double(STRING_MINNOTE, d);
	}
	double GroupeEvent::max_note(void) const {
		double dRet = 20.0;
		if (this->has_field(STRING_MAXNOTE)) {
			value v = this->get_value_at(STRING_MAXNOTE);
			if ((!v.is_null()) && v.is_double()) {
				dRet = v.as_double();
			}
		}
		return dRet;
	}
	void GroupeEvent::max_note(double d) {
		this->set_double(STRING_MAXNOTE, d);
	}
	string_t GroupeEvent::type(void) const {
		return GROUPEEVENT_TYPE;
	}
	string_t GroupeEvent::store_prefix(void) const {
		return GROUPEEVENT_PREFIX;
	}
	bool GroupeEvent::is_storeable(void) const {
		string_t s1 = this->enseignantaffectationid();
		string_t s2 = this->genre();
		string_t s3 = this->name();
		Date d = this->event_date();
		return (!d.is_not_a_date()) && (!s1.empty()) && (!s2.empty()) && (!s3.empty()) && PersonItem::is_storeable();
	}
	string_t GroupeEvent::start_key(void) const {
		string_t s1 = this->store_prefix();
		string_t s2 = this->semestreid();
		string_t s3 = this->matiereid();
		return (s1 + s2 + s3);
	}
	string_t GroupeEvent::create_id(void) const {
		string_t s1 = this->start_key();
		string_t s2 = this->enseignantaffectationid();
		string_t  s3;
		Date d = this->event_date();
		if (!d.is_not_a_date()) {
			s3 = url_encode((date_to_value(d)).as_string());
		}
		string_t s4 = url_encode(this->name());
		return (s1 + s2 + s3 + s4);
	}
	pplx::task<std::shared_ptr<EnseignantAffectation> > GroupeEvent::get_enseignantaffectation(IDatabaseManager &oMan) const {
		string_t id = this->enseignantaffectationid();
		EnseignantAffectation model;
		return oMan.load_item(model, id);
	}
	pplx::task<std::vector<std::shared_ptr<EtudiantEvent>>> GroupeEvent::get_etudiantevents(IDatabaseManager &oMan) const {
		EtudiantAffectation aff;
		EtudiantEvent model(*this, aff);
		return oMan.load_items_range(model, model.start_key(), model.end_key());
	}
	void GroupeEvent::update_save(Person &oPers) {
		PersonItem::update_save(oPers);
		oPers.add_eventid(this->id());
	}
	pplx::task<std::vector<std::shared_ptr<GroupeEvent>>> GroupeEvent::get_semestre_matiere_groupeevents(IDatabaseManager &oMan, const Semestre &oSem, const Matiere &oMat) {
		GroupeEvent g;
		g.semestreid(oSem.id());
		g.matiereid(oMat.id());
		return oMan.load_items_range(g, g.start_key(), g.end_key());
	}
	pplx::task<std::vector<std::shared_ptr<GroupeEvent>>> GroupeEvent::get_semestre_groupeevents(IDatabaseManager &oMan, const Semestre &oSem) {
		GroupeEvent g;
		string_t start = g.store_prefix() + oSem.id();
		string_t end = start + U("z");
		return oMan.load_items_range(g, start, end);
	}
	//////////////////////////////////////
}// namespace geninfo
