#include "stdafx.h"
#include "unite.h"
#include "matiere.h"
#include "IDatabaseManager.h"
//////////////////////////////
namespace geninfo {
	//////////////////////////
	const string_t Unite::UNITE_TYPE(U("unite"));
	const string_t UNITE_PREFIX = U("unt");
	////////////
	const string_t STRING_ORDER = U("order");
	//////////////////////////////////////////
	Unite::Unite() {
		this->set_string(BaseItem::TYPE_KEY, Unite::UNITE_TYPE);
	}
	Unite::Unite(const Departement &oDep) :DepSigleNamedItem(oDep) {
		this->set_string(BaseItem::TYPE_KEY, Unite::UNITE_TYPE);
	}
	Unite::Unite(const value &oMap) :DepSigleNamedItem(oMap) {
		this->set_string(BaseItem::TYPE_KEY, Unite::UNITE_TYPE);
	}
	Unite::Unite(const Unite &other) : DepSigleNamedItem(other) {

	}
	Unite & Unite::operator=(const Unite &other) {
		if (this != &other) {
			DepSigleNamedItem::operator=(other);
		}
		return *this;
	}
	Unite::~Unite() {

	}
	size_t Unite::order(void) const {
		size_t nRet = 0;
		if (this->has_field(STRING_ORDER)) {
			value v = this->get_value_at(STRING_ORDER);
			if ((!v.is_null()) && v.is_integer()) {
				nRet = v.as_integer();
			}
		}
		return nRet;
	}
	void Unite::order(size_t n) {
		this->set_value_at(STRING_ORDER, value(n));
	}
	string_t Unite::type(void) const {
		return UNITE_TYPE;
	}
	string_t Unite::store_prefix(void) const {
		return UNITE_PREFIX;
	}
	pplx::task<std::vector<std::shared_ptr<Matiere> > > Unite::get_matieres(IDatabaseManager &oMan) {
		this->check_id();
		Matiere model(*this);
		return oMan.load_items_range(model, model.start_key(), model.end_key());
	} // get_matieres
	//////////////////////////////////////////
}// namespace geninfo
