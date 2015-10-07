#include "stdafx.h"
#include "annee.h"
#include "semestre.h"
#include "IDatabaseManager.h"
///////////////////////////
namespace geninfo {
	//////////////////////////
	const string_t Annee::ANNEE_TYPE(U("annee"));
	const string_t ANNEE_PREFIX = U("ANN");
	////////////
	const string_t STRING_STARTDATE = U("startdate");
	const string_t STRING_ENDDATE = U("enddate");
	//////////////////////////////////////////
	Annee::Annee() {
		this->set_string(BaseItem::TYPE_KEY, Annee::ANNEE_TYPE);
	}
	Annee::Annee(const Departement &oDep): DepSigleNamedItem(oDep) {
		this->set_string(BaseItem::TYPE_KEY, Annee::ANNEE_TYPE);
	}
	Annee::Annee(const value &oMap) :DepSigleNamedItem(oMap) {
		this->set_string(BaseItem::TYPE_KEY, Annee::ANNEE_TYPE);
	}
	Annee::Annee(const Annee &other) : DepSigleNamedItem(other) {

	}
	Annee &Annee::operator=(const Annee &other) {
		if (this != &other) {
			DepSigleNamedItem::operator=(other);
		}
		return *this;
	}
	Annee::~Annee() {

	}
	Date Annee::start_date(void) const {
		Date dRet;
		if (this->has_field(STRING_STARTDATE)) {
			value v = this->get_value_at(STRING_STARTDATE);
			dRet = value_to_date(v);
		}
		return dRet;
	}
	void Annee::start_date(Date d) {
		this->set_value_at(STRING_STARTDATE, date_to_value(d));
	}
	Date Annee::end_date(void) const {
		Date dRet;
		if (this->has_field(STRING_ENDDATE)) {
			value v = this->get_value_at(STRING_ENDDATE);
			dRet = value_to_date(v);
		}
		return dRet;
	}
	void Annee::end_date(Date d) {
		this->set_value_at(STRING_ENDDATE, date_to_value(d));
	}
	string_t Annee::type(void) const {
		return ANNEE_TYPE;
	}
	string_t Annee::store_prefix(void) const {
		return ANNEE_PREFIX;
	}
	bool Annee::is_storeable(void) const {
		Date d1 = this->start_date();
		Date d2 = this->end_date();
		return (!d1.is_not_a_date()) && (!d2.is_not_a_date()) && (d1 <= d2) && DepSigleNamedItem::is_storeable();
	}
	string_t Annee::create_id(void) const {
		string_t s1 = this->start_key();
		value v = date_to_value(this->start_date());
		string_t s2 = ((!v.is_null()) && v.is_string()) ? v.as_string() : string_t();
		string_t ss = s1 + url_encode(s2);
		return ss;
	}// create_id
	pplx::task<std::vector<std::shared_ptr<Semestre> > > Annee::get_semestres(IDatabaseManager &oMan) {
		this->check_id();
		Semestre model(*this);
		return oMan.load_items_range(model, model.start_key(), model.end_key());
	} // get_semestres
	//////////////////////////////////////////
}
