#include "stdafx.h"
#include "semestre.h"
#include "annee.h"
#include "IDatabaseManager.h"
///////////////////////////
namespace geninfo {
	//////////////////////////
	const string_t Semestre::SEMESTRE_TYPE(U("semestre"));
	const string_t SEMESTRE_PREFIX = U("SEM");
	////////////
	const string_t STRING_ANNEEID = U("anneeid");
	const string_t STRING_STARTDATE = U("startdate");
	const string_t STRING_ENDDATE = U("enddate");
	//////////////////////////////////////////
	Semestre::Semestre() {
		this->set_string(BaseItem::TYPE_KEY, Semestre::SEMESTRE_TYPE);
	}
	Semestre::Semestre(const Annee &oAnnee) {
		this->anneeid(oAnnee.id());
		this->set_string(BaseItem::TYPE_KEY, Semestre::SEMESTRE_TYPE);
	}
	Semestre::Semestre(const value &oMap) :SigleNamedItem(oMap) {
		this->set_string(BaseItem::TYPE_KEY, Semestre::SEMESTRE_TYPE);
	}
	Semestre::Semestre(const Semestre &other) : SigleNamedItem(other) {

	}
	Semestre &Semestre::operator=(const Semestre &other) {
		if (this != &other) {
			SigleNamedItem::operator=(other);
		}
		return *this;
	}
	Semestre::~Semestre() {

	}
	string_t Semestre::anneeid(void) const {
		string_t sRet;
		if (this->has_field(STRING_ANNEEID)) {
			sRet = (this->get_value_at(STRING_ANNEEID)).as_string();
		}
		return sRet;
	}
	void Semestre::anneeid(const string_t &s) {
		this->set_string(STRING_ANNEEID, s);
	}
	Date Semestre::start_date(void) const {
		Date dRet;
		if (this->has_field(STRING_STARTDATE)) {
			value v = this->get_value_at(STRING_STARTDATE);
			dRet = value_to_date(v);
		}
		return dRet;
	}
	void Semestre::start_date(Date d) {
		this->set_value_at(STRING_STARTDATE, date_to_value(d));
	}
	Date Semestre::end_date(void) const {
		Date dRet;
		if (this->has_field(STRING_ENDDATE)) {
			value v = this->get_value_at(STRING_ENDDATE);
			dRet = value_to_date(v);
		}
		return dRet;
	}
	void Semestre::end_date(Date d) {
		this->set_value_at(STRING_ENDDATE, date_to_value(d));
	}
	string_t Semestre::type(void) const {
		return SEMESTRE_TYPE;
	}
	string_t Semestre::store_prefix(void) const {
		return SEMESTRE_PREFIX;
	}
	bool Semestre::is_storeable(void) const {
		string_t sx = this->anneeid();
		Date d1 = this->start_date();
		Date d2 = this->end_date();
		return (!d1.is_not_a_date()) && (!d2.is_not_a_date()) && (d1 <= d2) && SigleNamedItem::is_storeable() &&
			(!sx.empty());
	}
	string_t Semestre::start_key(void) const {
		string_t s1 = this->store_prefix();
		string_t s2 = this->anneeid();
		return (s1 + s2);
	}
	string_t Semestre::create_id(void) const {
		string_t s1 = this->start_key();
		value v = date_to_value(this->start_date());
		string_t s2 = ((!v.is_null()) && v.is_string()) ? v.as_string() : string_t();
		string_t ss = s1 + url_encode(s2);
		return ss;
	}// create_id
	pplx::task<std::shared_ptr<Annee> > Semestre::get_annee(IDatabaseManager &oMan) {
		string_t id = this->anneeid();
		Annee model;
		return oMan.load_item(model, id);
	}// get_annee
	 //////////////////////////////////////////
}
