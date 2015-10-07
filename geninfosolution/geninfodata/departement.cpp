#include "stdafx.h"
#include "departement.h"
#include "annee.h"
#include "groupe.h"
#include "unite.h"
#include "IDatabaseManager.h"
//////////////////////////////////
namespace geninfo {
	//////////////////////////////////////
	const string_t Departement::DEPARTEMENT_TYPE(U("departement"));
	//
	const string_t DEPARTEMENT_PREFIX = U("DEP");
	////////////////////////////////////////
	Departement::Departement()
	{
		this->set_string(BaseItem::TYPE_KEY, Departement::DEPARTEMENT_TYPE);
	}
	Departement::Departement(const value &oMap) :SigleNamedItem(oMap)
	{
		this->set_string(BaseItem::TYPE_KEY, Departement::DEPARTEMENT_TYPE);
	}
	Departement::Departement(const Departement &other) : SigleNamedItem(other)
	{
	}
	Departement & Departement::operator=(const Departement &other)
	{
		if (this != &other) {
			SigleNamedItem::operator=(other);
		}
		return *this;
	}
	Departement::~Departement()
	{
	}
	string_t Departement::type(void) const {
		return DEPARTEMENT_TYPE;
	}
	string_t Departement::store_prefix(void) const {
		return DEPARTEMENT_PREFIX;
	}
	pplx::task<std::vector<std::shared_ptr<Departement>>> Departement::get_all_departements(IDatabaseManager &oMan) {
		Departement oDep;
		string_t startkey = oDep.start_key();
		string_t endkey = oDep.end_key();
		return oMan.load_items_range(oDep, startkey, endkey);
	}//get_all_departements
	pplx::task<std::vector<std::shared_ptr<Groupe> > > Departement::get_groupes(IDatabaseManager &oMan) {
		this->check_id();
		Groupe model(*this);
		return oMan.load_items_range(model, model.start_key(), model.end_key());
	}
	pplx::task<std::vector<std::shared_ptr<Unite> > > Departement::get_unites(IDatabaseManager &oMan) {
		this->check_id();
		Unite model(*this);
		return oMan.load_items_range(model, model.start_key(), model.end_key());
	}
	pplx::task<std::vector<std::shared_ptr<Annee> > > Departement::get_annees(IDatabaseManager &oMan) {
		this->check_id();
		Annee model(*this);
		return oMan.load_items_range(model, model.start_key(), model.end_key());
	}
}