#include "stdafx.h"
#include "matiere.h"
#include "unite.h"
#include "IDatabaseManager.h"
/////////////////////////////////////
namespace geninfo {
	//////////////////////////
	const string_t Matiere::MATIERE_TYPE(U("matiere"));
	const string_t Matiere::MATIERE_PRATIQUE(U("P"));
	const string_t Matiere::MATIERE_THEORIE(U("T"));
	const string_t MATIERE_PREFIX = U("MAT");
	////////////
	const string_t STRING_UNITEID = U("uniteid");
	const string_t STRING_GENRE = U("genre");
	const string_t STRING_ORDER = U("ordre");
	const string_t STRING_COEFF = U("coefficient");
	const string_t STRING_ECS = U("ecs");
	const string_t STRING_MODULE = U("module");
	//////////////////////////////////////////
	Matiere::Matiere() {
		this->set_string(BaseItem::TYPE_KEY, Matiere::MATIERE_TYPE);
	}
	Matiere::Matiere(const Unite &oUnite) {
		this->uniteid(oUnite.id());
		this->set_string(BaseItem::TYPE_KEY, Matiere::MATIERE_TYPE);
	}
	Matiere::Matiere(const value &oMap) :SigleNamedItem(oMap) {
		this->set_string(BaseItem::TYPE_KEY, Matiere::MATIERE_TYPE);
	}
	Matiere::Matiere(const Matiere &other) : SigleNamedItem(other) {

	}
	Matiere &Matiere::operator=(const Matiere &other) {
		if (this != &other) {
			SigleNamedItem::operator=(other);
		}
		return *this;
	}
	Matiere::~Matiere() {

	}
	string_t Matiere::uniteid(void) const {
		string_t sRet;
		if (this->has_field(STRING_UNITEID)) {
			sRet = (this->get_value_at(STRING_UNITEID)).as_string();
		}
		return sRet;
	}
	void Matiere::uniteid(const string_t &s) {
		this->set_string(STRING_UNITEID, s);
	}
	string_t Matiere::genre(void) const {
		string_t sRet;
		if (this->has_field(STRING_GENRE)) {
			sRet = (this->get_value_at(STRING_GENRE)).as_string();
		}
		return sRet;
	}
	void Matiere::genre(const string_t &s) {
		this->set_string(STRING_GENRE, s);
	}
	string_t Matiere::module(void) const {
		string_t sRet;
		if (this->has_field(STRING_MODULE)) {
			sRet = (this->get_value_at(STRING_MODULE)).as_string();
		}
		return sRet;
	}
	void Matiere::module(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_MODULE, ss);
	}
	size_t Matiere::order(void) const {
		size_t nRet = 0;
		if (this->has_field(STRING_ORDER)) {
			value v = this->get_value_at(STRING_ORDER);
			if ((!v.is_null()) && v.is_integer()) {
				nRet = v.as_integer();
			}
		}
		return nRet;
	}
	void Matiere::order(size_t n) {
		this->set_value_at(STRING_ORDER, value(n));
	}
	double Matiere::coefficient(void) const {
		double dRet = 1.0;
		if (this->has_field(STRING_COEFF)) {
			value v = this->get_value_at(STRING_COEFF);
			if ((!v.is_null()) && v.is_double()) {
				dRet = v.as_double();
			}
		}
		return (dRet > 0.0) ? dRet : 1.0;
	}
	void Matiere::coefficient(double d) {
		double x = (d > 0.0) ? d : 1.0;
		this->set_double(STRING_COEFF, x);
	}
	double Matiere::ecs(void) const {
		double dRet = 0;
		if (this->has_field(STRING_ECS)) {
			value v = this->get_value_at(STRING_ECS);
			if ((!v.is_null()) && v.is_double()) {
				dRet = v.as_double();
			}
		}
		return (dRet > 0.0) ? dRet : 0.0;
	}
	void Matiere::ecs(double d) {
		double x = (d >= 0.0) ? d : 0.0;
		this->set_double(STRING_ECS, x);
	}
	string_t Matiere::type(void) const {
		return MATIERE_TYPE;
	}
	string_t Matiere::store_prefix(void) const {
		return MATIERE_PREFIX;
	}
	bool Matiere::is_storeable(void) const {
		string_t sx = this->uniteid();
		return (!sx.empty()) && SigleNamedItem::is_storeable();
	}
	string_t Matiere::start_key(void) const {
		string_t s1 = this->store_prefix();
		string_t s2 = this->uniteid();
		return (s1 + s2);
	}
	string_t Matiere::create_id(void) const {
		string_t s1 = this->start_key();
		string_t s2 = url_encode(this->sigle());
		string_t ss = s1 + s2;
		return ss;
	}// create_id
	pplx::task<std::shared_ptr<Unite> > Matiere::get_unite(IDatabaseManager &oMan) {
		string_t id = this->uniteid();
		Unite model;
		return oMan.load_item(model, id);
	}// get_unite
	 //////////////////////////////////////////
}