#include "stdafx.h"
#include "depperson.h"
#include "departement.h"
#include "person.h"
#include "IDatabaseManager.h"
////////////////////////////////
namespace geninfo {
	/////////////////////////////
	const string_t STRING_DEPARTEMENTID = U("departementid");
	const string_t Etudiant::ETUDIANT_TYPE(U("etudiant"));
	const string_t ETUDIANT_PREFIX = U("ETD");
	const string_t Enseignant::ENSEIGNANT_TYPE(U("enseignant"));
	const string_t ENSEIGNANT_PREFIX = U("PROF");
	const string_t Administrator::ADMINISTRATOR_TYPE(U("administrator"));
	const string_t ADMINISTRATOR_PREFIX = U("ADM");
	/////////////////////////////////
	DepartementPerson::DepartementPerson() {

	}
	DepartementPerson::DepartementPerson(const Departement &oDep, const Person &oPers) :PersonItem(oPers) {
		this->departementid(oDep.id());
	}
	DepartementPerson::DepartementPerson(const value &oMap) :PersonItem(oMap) {

	}
	DepartementPerson::DepartementPerson(const DepartementPerson &other) : PersonItem(other) {

	}
	DepartementPerson & DepartementPerson::operator=(const DepartementPerson &other) {
		if (this != &other) {
			PersonItem::operator=(other);
		}
		return *this;
	}
	DepartementPerson::~DepartementPerson() {

	}
	string_t DepartementPerson::departementid(void) const {
		string_t sRet;
		if (this->has_field(STRING_DEPARTEMENTID)) {
			sRet = (this->get_value_at(STRING_DEPARTEMENTID)).as_string();
		}
		return sRet;
	}
	void DepartementPerson::departementid(const string_t &s) {
		this->set_string(STRING_DEPARTEMENTID, s);
	}
	pplx::task<std::shared_ptr<Departement> > DepartementPerson::get_departement(IDatabaseManager &oMan) const {
		string_t id = this->departementid();
		Departement model;
		return oMan.load_item(model, id);
	}
	bool DepartementPerson::is_storeable(void) const {
		string_t s = this->departementid();
		return (!s.empty()) && PersonItem::is_storeable();
	}
	void DepartementPerson::update_save(Person &oPers) {
		PersonItem::update_save(oPers);
		oPers.add_departementid(this->id());
	}
	string_t DepartementPerson::start_key(void) const {
		string_t s1 = this->store_prefix();
		string_t s2 = this->departementid();
		return (s1 + s2);
	}// start_key
	string_t DepartementPerson::create_id(void) const {
		string_t s1 = this->start_key();
		string_t s2 = this->personid();
		return (s1 + s2);
	}
	////////////////////////////////////
	Etudiant::Etudiant() {
		this->set_string(BaseItem::TYPE_KEY, ETUDIANT_TYPE);
	}
	Etudiant::Etudiant(const Departement &oDep, const Person &oPers) :DepartementPerson(oDep, oPers) {
		this->set_string(BaseItem::TYPE_KEY, ETUDIANT_TYPE);
	}
	Etudiant::Etudiant(const value &oMap) : DepartementPerson(oMap) {
		this->set_string(BaseItem::TYPE_KEY, ETUDIANT_TYPE);
	}
	Etudiant::Etudiant(const Etudiant &other) : DepartementPerson(other) {

	}
	Etudiant & Etudiant::operator=(const Etudiant &other) {
		if (this != &other) {
			DepartementPerson::operator=(other);
		}
		return *this;
	}
	Etudiant::~Etudiant() {

	}
	string_t Etudiant::type(void) const {
		return ETUDIANT_TYPE;
	}
	string_t Etudiant::store_prefix(void) const {
		return ETUDIANT_PREFIX;
	}
	void Etudiant::update_save(Person &oPers) {
		DepartementPerson::update_save(oPers);
		oPers.add_etudiantid(this->id());
	}
	///////////////////////////////////
	Enseignant::Enseignant() {
		this->set_string(BaseItem::TYPE_KEY, ENSEIGNANT_TYPE);
	}
	Enseignant::Enseignant(const Departement &oDep, const Person &oPers) :DepartementPerson(oDep, oPers) {
		this->set_string(BaseItem::TYPE_KEY, ENSEIGNANT_TYPE);
	}
	Enseignant::Enseignant(const value &oMap) : DepartementPerson(oMap) {
		this->set_string(BaseItem::TYPE_KEY, ENSEIGNANT_TYPE);
	}
	Enseignant::Enseignant(const Enseignant &other) : DepartementPerson(other) {

	}
	Enseignant & Enseignant::operator=(const Enseignant &other) {
		if (this != &other) {
			DepartementPerson::operator=(other);
		}
		return *this;
	}
	Enseignant::~Enseignant() {

	}
	string_t Enseignant::type(void) const {
		return ENSEIGNANT_TYPE;
	}
	string_t Enseignant::store_prefix(void) const {
		return ENSEIGNANT_PREFIX;
	}
	void Enseignant::update_save(Person &oPers) {
		DepartementPerson::update_save(oPers);
		oPers.add_enseignantid(this->id());
	}
	//////////////////////////////////////
	Administrator::Administrator() {
		this->set_string(BaseItem::TYPE_KEY, ADMINISTRATOR_TYPE);
	}
	Administrator::Administrator(const Departement &oDep, const Person &oPers) :DepartementPerson(oDep, oPers) {
		this->set_string(BaseItem::TYPE_KEY, ADMINISTRATOR_TYPE);
	}
	Administrator::Administrator(const value &oMap) : DepartementPerson(oMap) {
		this->set_string(BaseItem::TYPE_KEY, ADMINISTRATOR_TYPE);
	}
	Administrator::Administrator(const Administrator &other) : DepartementPerson(other) {

	}
	Administrator & Administrator::operator=(const Administrator &other) {
		if (this != &other) {
			DepartementPerson::operator=(other);
		}
		return *this;
	}
	Administrator::~Administrator() {

	}
	string_t Administrator::type(void) const {
		return ADMINISTRATOR_TYPE;
	}
	string_t Administrator::store_prefix(void) const {
		return ADMINISTRATOR_PREFIX;
	}
	void Administrator::update_save(Person &oPers) {
		DepartementPerson::update_save(oPers);
		oPers.add_operatorid(this->id());
	}
	///////////////////////////////////
}// namespace geninfo
