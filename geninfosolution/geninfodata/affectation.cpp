#include "stdafx.h"
#include "affectation.h"
#include "groupe.h"
#include "semestre.h"
#include "annee.h"
#include "person.h"
#include "matiere.h"
#include "depperson.h"
#include "IDatabaseManager.h"
#include "genninfoconstants.h"
////////////////////////////////
namespace geninfo {
	//////////////////////////////
	EtudiantAffectation::EtudiantAffectation() {
		this->set_string(GenInfoConstants::TYPE, GenInfoConstants::ETUDIANTAFFECTATION_TYPE);
	}
	EtudiantAffectation::EtudiantAffectation(const Etudiant &oEtud, const Semestre &oSem, const Groupe &oGroupe) :Affectation(oSem, oGroupe) {
		this->set_string(GenInfoConstants::TYPE, GenInfoConstants::ETUDIANTAFFECTATION_TYPE);
		this->personid(oEtud.personid());
		this->etudiantid(oEtud.id());
	}
	EtudiantAffectation::EtudiantAffectation(const value &oMap) :Affectation(oMap) {

	}
	EtudiantAffectation::EtudiantAffectation(const EtudiantAffectation &other) : Affectation(other) {

	}
	EtudiantAffectation & EtudiantAffectation::operator=(const EtudiantAffectation &other) {
		if (this != &other) {
			Affectation::operator=(other);
		}
		return *this;
	}
	EtudiantAffectation::~EtudiantAffectation() {

	}
	string_t EtudiantAffectation::etudiantid(void) const {
		string_t sRet;
		if (this->has_field(GenInfoConstants::ETUDIANTID)) {
			sRet = (this->get_value_at(GenInfoConstants::ETUDIANTID)).as_string();
		}
		return sRet;
	}
	void EtudiantAffectation::etudiantid(const string_t &s) {
		this->set_string(GenInfoConstants::ETUDIANTID, s);
	}
	pplx::task<std::shared_ptr<Etudiant> > EtudiantAffectation::get_etudiant(IDatabaseManager &oMan) const {
		string_t id = this->etudiantid();
		Etudiant model;
		return oMan.load_item(model, id);
	}
	bool EtudiantAffectation::is_storeable(void) const {
		string_t id = this->etudiantid();
		return (!id.empty()) && Affectation::is_storeable();
	}
	string_t EtudiantAffectation::type(void) const {
		return GenInfoConstants::ETUDIANTAFFECTATION_TYPE;
	}
	string_t EtudiantAffectation::store_prefix(void) const {
		return GenInfoConstants::ETUDIANTAFFECTATION_PREFIX;
	}
	string_t EtudiantAffectation::start_key(void) const {
		string_t s1 = Affectation::start_key();
		string_t s3 = this->groupeid();
		return (s1 + s3);
	}
	string_t EtudiantAffectation::create_id(void) const {
		string_t s1 = this->start_key();
		string_t s2 = this->etudiantid();
		string_t s3;
		Date d = this->start_date();
		if (!d.is_not_a_date()) {
			value v = date_to_value(d);
			s3 = url_encode(v.as_string());
		}
		return (s1 + s2 + s3);
	}
	void EtudiantAffectation::update_save(Person &oPers) {
		Affectation::update_save(oPers);
		oPers.add_etudiantid(this->etudiantid());
	}
	///////////////////////////////////////////
	EnseignantAffectation::EnseignantAffectation() {
		this->set_string(GenInfoConstants::TYPE, GenInfoConstants::ENSEIGNANTAFFECTATION_TYPE);
	}
	EnseignantAffectation::EnseignantAffectation(const Enseignant &oProf, const Matiere &oMat, const Semestre &oSem, const Groupe &oGroupe) :Affectation(oSem, oGroupe) {
		this->personid(oProf.personid());
		this->enseignantid(oProf.id());
		this->matiereid(oMat.id());
		this->set_string(GenInfoConstants::TYPE, GenInfoConstants::ENSEIGNANTAFFECTATION_TYPE);
	}
	EnseignantAffectation::EnseignantAffectation(const value &oMap) :Affectation(oMap) {
		this->set_string(GenInfoConstants::TYPE, GenInfoConstants::ENSEIGNANTAFFECTATION_TYPE);
	}
	EnseignantAffectation::EnseignantAffectation(const EnseignantAffectation &other) : Affectation(other) {

	}
	EnseignantAffectation & EnseignantAffectation::operator=(const EnseignantAffectation &other) {
		if (this != &other) {
			Affectation::operator=(other);
		}
		return *this;
	}
	EnseignantAffectation::~EnseignantAffectation() {

	}
	string_t EnseignantAffectation::enseignantid(void) const {
		string_t sRet;
		if (this->has_field(GenInfoConstants::ENSEIGNANTID)) {
			sRet = (this->get_value_at(GenInfoConstants::ENSEIGNANTID)).as_string();
		}
		return sRet;
	}
	void EnseignantAffectation::enseignantid(const string_t &s) {
		this->set_string(GenInfoConstants::ENSEIGNANTID, s);
	}
	string_t EnseignantAffectation::matiereid(void) const {
		string_t sRet;
		if (this->has_field(GenInfoConstants::MATIEREID)) {
			sRet = (this->get_value_at(GenInfoConstants::MATIEREID)).as_string();
		}
		return sRet;
	}
	void EnseignantAffectation::matiereid(const string_t &s) {
		this->set_string(GenInfoConstants::MATIEREID, s);
	}
	pplx::task<std::shared_ptr<Enseignant> > EnseignantAffectation::get_enseignant(IDatabaseManager &oMan) const {
		string_t id = this->enseignantid();
		Enseignant model;
		return oMan.load_item(model, id);
	}
	pplx::task<std::shared_ptr<Matiere> > EnseignantAffectation::get_matiere(IDatabaseManager &oMan) const {
		string_t id = this->matiereid();
		Matiere model;
		return oMan.load_item(model, id);
	}
	bool EnseignantAffectation::is_storeable(void) const {
		string_t s1 = this->enseignantid();
		string_t s2 = this->matiereid();
		return (!s1.empty()) && (!s2.empty()) && Affectation::is_storeable();
	}
	string_t EnseignantAffectation::type(void) const {
		return GenInfoConstants::ENSEIGNANTAFFECTATION_TYPE;
	}
	string_t EnseignantAffectation::store_prefix(void) const {
		return GenInfoConstants::ENSEIGNANTAFFECTATION_PREFIX;
	}
	string_t EnseignantAffectation::start_key(void) const {
		string_t s1 = Affectation::start_key();
		string_t s2 = this->matiereid();
		string_t s3 = this->groupeid();
		return (s1 + s2 + s3);
	}
	string_t EnseignantAffectation::create_id(void) const {
		string_t s1 = this->start_key();
		string_t s2 = this->enseignantid();
		string_t s3;
		Date d = this->start_date();
		if (!d.is_not_a_date()) {
			value v = date_to_value(d);
			s3 = url_encode(v.as_string());
		}
		return (s1 + s2 + s3);
	}
	void EnseignantAffectation::update_save(Person &oPers) {
		Affectation::update_save(oPers);
		oPers.add_affectationid(this->id());
		oPers.add_matiereid(this->matiereid());
		oPers.add_enseignantid(this->enseignantid());
	}
	pplx::task<bool> EnseignantAffectation::save(IDatabaseManager &oMan) {
		this->check_id();
		std::shared_ptr<Person> ox = this->get_person(oMan).get();
		Person *pPers = ox.get();
		if (pPers != nullptr) {
			std::shared_ptr<Semestre> osem = this->get_semestre(oMan).get();
			Semestre *pSem = osem.get();
			if (pSem != nullptr) {
				pPers->add_anneeid(pSem->anneeid());
			}
			std::shared_ptr<Matiere> omat = this->get_matiere(oMan).get();
			Matiere *pMat = omat.get();
			if (pMat != nullptr) {
				pPers->add_uniteid(pMat->uniteid());
			}
			this->update_save(*pPers);
			bool bx = pPers->save(oMan).get();
		}
		return BaseItem::save(oMan);
	}// save
	///////////////////////////////////////
	Affectation::Affectation() {

	}
	Affectation::Affectation(const Semestre &oSem, const Groupe &oGroupe) {
		this->semestreid(oSem.id());
		this->groupeid(oGroupe.id());
	}
	Affectation::Affectation(const value &oMap) : PersonItem(oMap) {

	}
	Affectation::Affectation(const Affectation &other) : PersonItem(other) {

	}
	Affectation & Affectation::operator=(const Affectation &other) {
		if (this != &other) {
			PersonItem::operator=(other);
		}
		return *this;
	}
	Affectation::~Affectation() {

	}
	string_t Affectation::semestreid(void) const {
		string_t sRet;
		if (this->has_field(GenInfoConstants::SEMESTREID)) {
			sRet = (this->get_value_at(GenInfoConstants::SEMESTREID)).as_string();
		}
		return sRet;
	}
	void Affectation::semestreid(const string_t &s) {
		this->set_string(GenInfoConstants::SEMESTREID, s);
	}
	string_t Affectation::groupeid(void) const {
		string_t sRet;
		if (this->has_field(GenInfoConstants::GROUPEID)) {
			sRet = (this->get_value_at(GenInfoConstants::GROUPEID)).as_string();
		}
		return sRet;
	}
	void Affectation::groupeid(const string_t &s) {
		this->set_string(GenInfoConstants::GROUPEID, s);
	}
	Date Affectation::start_date(void) const {
		Date dRet;
		if (this->has_field(GenInfoConstants::STARTDATE)) {
			value v = this->get_value_at(GenInfoConstants::STARTDATE);
			dRet = value_to_date(v);
		}
		return dRet;
	}
	void Affectation::start_date(Date d) {
		this->set_value_at(GenInfoConstants::STARTDATE, date_to_value(d));
	}
	Date Affectation::end_date(void) const {
		Date dRet;
		if (this->has_field(GenInfoConstants::ENDDATE)) {
			value v = this->get_value_at(GenInfoConstants::ENDDATE);
			dRet = value_to_date(v);
		}
		return dRet;
	}
	void Affectation::end_date(Date d) {
		this->set_value_at(GenInfoConstants::ENDDATE, date_to_value(d));
	}
	pplx::task<std::shared_ptr<Semestre> > Affectation::get_semestre(IDatabaseManager &oMan) const {
		string_t id = this->semestreid();
		Semestre model;
		return oMan.load_item(model, id);
	}
	pplx::task<std::shared_ptr<Groupe> > Affectation::get_groupe(IDatabaseManager &oMan) const {
		string_t id = this->groupeid();
		Groupe model;
		return oMan.load_item(model, id);
	}
	pplx::task<std::shared_ptr<Annee> > Affectation::get_annee(IDatabaseManager &oMan) const {
		std::shared_ptr<Semestre> osem = this->get_semestre(oMan).get();
		Semestre *pSem = osem.get();
		if (pSem != nullptr) {
			return pSem->get_annee(oMan);
		}
		else {
			std::shared_ptr<Annee> ox;
			return pplx::task_from_result(ox);
		}
	}
	bool Affectation::is_storeable(void) const {
		string_t s1 = this->semestreid();
		string_t s2 = this->groupeid();
		return (!s1.empty()) && (!s2.empty()) && PersonItem::is_storeable();
	}
	string_t Affectation::start_key(void) const {
		string_t s1 = this->store_prefix();
		string_t s2 = this->semestreid();
		return (s1 + s2);
	}
	void Affectation::update_save(Person &oPers) {
		PersonItem::update_save(oPers);
		oPers.add_semestreid(this->semestreid());
		oPers.add_groupeid(this->groupeid());
	}
	pplx::task<bool> Affectation::save(IDatabaseManager &oMan) {
		this->check_id();
		std::shared_ptr<Person> ox = this->get_person(oMan).get();
		Person *pPers = ox.get();
		if (pPers != nullptr) {
			std::shared_ptr<Annee> oan = this->get_annee(oMan).get();
			Annee *pAn = oan.get();
			if (pAn != nullptr) {
				pPers->add_anneeid(pAn->id());
			}
			this->update_save(*pPers);
			bool bx = pPers->save(oMan).get();
		}
		return BaseItem::save(oMan);
	}// save
	///////////////////////////////
}// namespace geninfo
