#include "stdafx.h"
#include "person.h"
#include "md5.h"
#include "IDatabaseManager.h"
////////////////////////////////
namespace geninfo {
	const string_t Person::PERSON_TYPE(U("person"));
	const string_t  PERSON_PREFIX = U("PER");
	/////////////////////
	const string_t STRING_USERNAME = U("username");
	const string_t STRING_PASSWORD = U("password");
	const string_t STRING_FIRSTNAME = U("firstname");
	const string_t STRING_LASTNAME = U("lastname");
	const string_t STRING_EMAIL = U("email");
	const string_t STRING_PHONE = U("phone");
	const string_t STRING_ETUDIANTIDS = U("etudiantids");
	const string_t STRING_ENSEIGNANTIDS = U("enseignantids");
	const string_t STRING_OPERATORIDS = U("operatorids");
	const string_t STRING_DEPARTEMENTIDS = U("departementids");
	const string_t STRING_ANNEEIDS = U("anneeids");
	const string_t STRING_SEMESTREIDS = U("semestreids");
	const string_t STRING_UNITEIDS = U("uniteids");
	const string_t STRING_MATIEREIDS = U("matiereids");
	const string_t STRING_GROUPEIDS = U("groupeids");
	const string_t STRING_AFFECTATIONIDS = U("affectationids");
	const string_t STRING_EVENTIDS = U("evantids");
	//
	const string_t EtudiantPerson::ETUDIANTPERSON_TYPE(U("etudiantperson"));
	const string_t STRING_DOSSIER = U("dossier");
	const string_t STRING_SEXE = U("sexe");
	const string_t STRING_BIRTHDATE = U("birthdate");
	const string_t STRING_VILLE = U("ville");
	const string_t STRING_ETABLISSEMENT = U("etablissement");
	const string_t STRING_SERIEBAC = U("seriebac");
	const string_t STRING_OPTIONBAC = U("optionbac");
	const string_t STRING_MENTIONBAC = U("mentionbac");
	const string_t STRING_ETUDESSUPERIEURES = U("etudessuperieures");
	const string_t STRING_REDOUBLANT = U("redoublant");
	const string_t STRING_APB = U("apb");
	//
	const string_t EnseignantPerson::ENSEIGNANTPERSON_TYPE(U("enseignantperson"));
	//
	const string_t OperatorPerson::OPERATORPERSON_TYPE(U("operatorperson"));
	//
	const string_t SuperAdminPerson::SUPERADMINPERSON_TYPE(U("superadminperson"));
	//////////////////////////////////////////
	pplx::task<Person *> Person::find_person_by_username(IDatabaseManager &oMan, const string_t &susername, bool bAttachments /*= false*/) {
		Person oPers;
		oPers.username(susername);
		oPers.check_id();
		string_t id = oPers.id();
		return oMan.read_item(id, bAttachments).then([=](pplx::task<BaseItem *> t) {
			Person *pPers = nullptr;
			try {
				BaseItem *p = t.get();
				pPers = dynamic_cast<Person *>(p);
			}
			catch (...) {}
			return pplx::task_from_result(pPers);
		});
	}//find_person_by_username 
	Person::Person() {
		this->set_string(BaseItem::TYPE_KEY, Person::PERSON_TYPE);
	}
	Person::Person(const value &oMap) :BaseItem(oMap) {
		this->set_string(BaseItem::TYPE_KEY, Person::PERSON_TYPE);
	}
	Person::Person(const Person &other) : BaseItem(other) {

	}
	Person & Person::operator=(const Person &other) {
		if (this != &other) {
			BaseItem::operator=(other);
		}
		return *this;
	}
	Person::~Person() {

	}
	string_t Person::username(void) const {
		string_t sRet;
		if (this->has_field(STRING_USERNAME)) {
			sRet = (this->get_value_at(STRING_USERNAME)).as_string();
		}
		return sRet;
	}
	void Person::username(const string_t &s) {
		string_t ss = to_lower(trim(s));
		this->set_string(STRING_USERNAME, ss);
	}
	string_t Person::password(void) const {
		string_t sRet;
		if (this->has_field(STRING_PASSWORD)) {
			sRet = (this->get_value_at(STRING_PASSWORD)).as_string();
		}
		return sRet;
	}
	void Person::password(const string_t &s) {
		this->set_string(STRING_PASSWORD, s);
	}
	string_t Person::firstname(void) const {
		string_t sRet;
		if (this->has_field(STRING_FIRSTNAME)) {
			sRet = (this->get_value_at(STRING_FIRSTNAME)).as_string();
		}
		return sRet;
	}
	void Person::firstname(const string_t &s) {
		string_t ss = trim(s);
		if (ss.length() > 1) {
			ss = to_upper(ss.substr(0, 1)) + ss.substr(1);
		}
		else {
			ss = to_upper(s);
		}
		this->set_string(STRING_FIRSTNAME, ss);
	}
	string_t Person::lastname(void) const {
		string_t sRet;
		if (this->has_field(STRING_LASTNAME)) {
			sRet = (this->get_value_at(STRING_LASTNAME)).as_string();
		}
		return sRet;
	}
	void Person::lastname(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_LASTNAME, ss);
	}
	string_t Person::email(void) const {
		string_t sRet;
		if (this->has_field(STRING_EMAIL)) {
			sRet = (this->get_value_at(STRING_EMAIL)).as_string();
		}
		return sRet;
	}
	void Person::email(const string_t &s) {
		this->set_string(STRING_EMAIL, trim(s));
	}
	string_t Person::phone(void) const {
		string_t sRet;
		if (this->has_field(STRING_PHONE)) {
			sRet = (this->get_value_at(STRING_PHONE)).as_string();
		}
		return sRet;
	}
	void Person::phone(const string_t &s) {
		this->set_string(STRING_PHONE, trim(s));
	}
	void Person::reset_password(void) {
		this->change_password(this->username());
	}
	bool Person::check_password(const string_t &sc) const {
		string_t sx = to_md5(sc);
		string_t s = this->password();
		return (sx == s);
	}
	void Person::change_password(const string_t &sc) {
		string_t sx = to_md5(sc);
		this->password(sx);
	}
	string_t Person::type(void) const {
		return PERSON_TYPE;
	}
	string_t Person::store_prefix(void) const {
		return PERSON_PREFIX;
	}
	bool Person::is_storeable(void) const {
		string_t s1 = this->firstname();
		string_t s2 = this->lastname();
		return (!s1.empty()) && (!s2.empty());
	}
	string_t Person::create_id(void) const {
		string_t s1 = this->store_prefix();
		string_t s2 = url_encode(this->username());
		string_t ss = s1 + s2;
		return ss;
	}
	std::set<string_t> Person::departementids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_DEPARTEMENTIDS)) {
			const value &v = this->at(STRING_DEPARTEMENTIDS);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}
	bool Person::add_departementid(const string_t &id) {
		if (id.empty()) {
			return false;
		}
		std::set<string_t> vec = this->departementids();
		if (vec.find(id) != vec.end()) {
			return false;
		}
		vec.insert(id);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_DEPARTEMENTIDS] = v;
		return true;
	}
	std::set<string_t> Person::anneeids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_ANNEEIDS)) {
			const value &v = this->at(STRING_ANNEEIDS);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}
	bool Person::add_anneeid(const string_t &id) {
		if (id.empty()) {
			return false;
		}
		std::set<string_t> vec = this->anneeids();
		if (vec.find(id) != vec.end()) {
			return false;
		}
		vec.insert(id);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_ANNEEIDS] = v;
		return true;
	}
	std::set<string_t> Person::semestreids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_SEMESTREIDS)) {
			const value &v = this->at(STRING_SEMESTREIDS);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}
	bool Person::add_semestreid(const string_t &id) {
		if (id.empty()) {
			return false;
		}
		std::set<string_t> vec = this->semestreids();
		if (vec.find(id) != vec.end()) {
			return false;
		}
		vec.insert(id);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_SEMESTREIDS] = v;
		return true;
	}
	std::set<string_t> Person::uniteids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_UNITEIDS)) {
			const value &v = this->at(STRING_UNITEIDS);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}
	bool Person::add_uniteid(const string_t &id) {
		if (id.empty()) {
			return false;
		}
		std::set<string_t> vec = this->uniteids();
		if (vec.find(id) != vec.end()) {
			return false;
		}
		vec.insert(id);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_UNITEIDS] = v;
		return true;
	}
	std::set<string_t> Person::matiereids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_MATIEREIDS)) {
			const value &v = this->at(STRING_MATIEREIDS);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}
	bool Person::add_matiereid(const string_t &id) {
		if (id.empty()) {
			return false;
		}
		std::set<string_t> vec = this->matiereids();
		if (vec.find(id) != vec.end()) {
			return false;
		}
		vec.insert(id);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_MATIEREIDS] = v;
		return true;
	}
	std::set<string_t> Person::groupeids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_GROUPEIDS)) {
			const value &v = this->at(STRING_GROUPEIDS);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}
	bool Person::add_groupeid(const string_t &id) {
		if (id.empty()) {
			return false;
		}
		std::set<string_t> vec = this->groupeids();
		if (vec.find(id) != vec.end()) {
			return false;
		}
		vec.insert(id);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_GROUPEIDS] = v;
		return true;
	}
	std::set<string_t> Person::affectationids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_AFFECTATIONIDS)) {
			const value &v = this->at(STRING_AFFECTATIONIDS);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}
	bool Person::add_affectationid(const string_t &id) {
		if (id.empty()) {
			return false;
		}
		std::set<string_t> vec = this->affectationids();
		if (vec.find(id) != vec.end()) {
			return false;
		}
		vec.insert(id);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_AFFECTATIONIDS] = v;
		return true;
	}
	std::set<string_t>  Person::eventids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_EVENTIDS)) {
			const value &v = this->at(STRING_EVENTIDS);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}
	bool Person::add_eventid(const string_t &id) {
		if (id.empty()) {
			return false;
		}
		std::set<string_t> vec = this->eventids();
		if (vec.find(id) != vec.end()) {
			return false;
		}
		vec.insert(id);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_EVENTIDS] = v;
		return true;
	}
	std::set<string_t>  Person::operatorids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_OPERATORIDS)) {
			const value &v = this->at(STRING_OPERATORIDS);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}
	bool Person::add_operatorid(const string_t &id) {
		if (id.empty()) {
			return false;
		}
		std::set<string_t> vec = this->operatorids();
		if (vec.find(id) != vec.end()) {
			return false;
		}
		vec.insert(id);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_OPERATORIDS] = v;
		return true;
	}
	std::set<string_t>  Person::enseignantids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_ENSEIGNANTIDS)) {
			const value &v = this->at(STRING_ENSEIGNANTIDS);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}
	bool Person::add_enseignantid(const string_t &id) {
		if (id.empty()) {
			return false;
		}
		std::set<string_t> vec = this->enseignantids();
		if (vec.find(id) != vec.end()) {
			return false;
		}
		vec.insert(id);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_ENSEIGNANTIDS] = v;
		return true;
	}
	std::set<string_t>  Person::etudiantids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_ETUDIANTIDS)) {
			const value &v = this->at(STRING_ETUDIANTIDS);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}
	bool Person::add_etudiantid(const string_t &id) {
		if (id.empty()) {
			return false;
		}
		std::set<string_t> vec = this->etudiantids();
		if (vec.find(id) != vec.end()) {
			return false;
		}
		vec.insert(id);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_ETUDIANTIDS] = v;
		return true;
	}
	std::vector<string_t> Person::get_all_items_ids(void) {
		std::vector<string_t> oRes;
		this->check_id();
		string_t sid = this->id();
		if (sid.empty()) {
			return oRes;
		}
		oRes.push_back(sid);
		{
			std::set<string_t> oSet = this->operatorids();
			for (auto it = oSet.begin(); it != oSet.end(); ++it) {
				string_t s = *it;
				if (!s.empty()) {
					oRes.push_back(s);
				}
			}// it
		}
		{
			std::set<string_t> oSet = this->enseignantids();
			for (auto it = oSet.begin(); it != oSet.end(); ++it) {
				string_t s = *it;
				if (!s.empty()) {
					oRes.push_back(s);
				}
			}// it
		}
		{
			std::set<string_t> oSet = this->etudiantids();
			for (auto it = oSet.begin(); it != oSet.end(); ++it) {
				string_t s = *it;
				if (!s.empty()) {
					oRes.push_back(s);
				}
			}// it
		}
		{
			std::set<string_t> oSet = this->departementids();
			for (auto it = oSet.begin(); it != oSet.end(); ++it) {
				string_t s = *it;
				if (!s.empty()) {
					oRes.push_back(s);
				}
			}// it
		}
		{
			std::set<string_t> oSet = this->groupeids();
			for (auto it = oSet.begin(); it != oSet.end(); ++it) {
				string_t s = *it;
				if (!s.empty()) {
					oRes.push_back(s);
				}
			}// it
		}
		{
			std::set<string_t> oSet = this->anneeids();
			for (auto it = oSet.begin(); it != oSet.end(); ++it) {
				string_t s = *it;
				if (!s.empty()) {
					oRes.push_back(s);
				}
			}// it
		}
		{
			std::set<string_t> oSet = this->semestreids();
			for (auto it = oSet.begin(); it != oSet.end(); ++it) {
				string_t s = *it;
				if (!s.empty()) {
					oRes.push_back(s);
				}
			}// it
		}
		{
			std::set<string_t> oSet = this->uniteids();
			for (auto it = oSet.begin(); it != oSet.end(); ++it) {
				string_t s = *it;
				if (!s.empty()) {
					oRes.push_back(s);
				}
			}// it
		}
		{
			std::set<string_t> oSet = this->matiereids();
			for (auto it = oSet.begin(); it != oSet.end(); ++it) {
				string_t s = *it;
				if (!s.empty()) {
					oRes.push_back(s);
				}
			}// it
		}
		{
			std::set<string_t> oSet = this->affectationids();
			for (auto it = oSet.begin(); it != oSet.end(); ++it) {
				string_t s = *it;
				if (!s.empty()) {
					oRes.push_back(s);
				}
			}// it
		}
		{
			std::set<string_t> oSet = this->eventids();
			for (auto it = oSet.begin(); it != oSet.end(); ++it) {
				string_t s = *it;
				if (!s.empty()) {
					oRes.push_back(s);
				}
			}// it
		}
		return oRes;
	}//get_all_items_ids
	/////////////////////////////////////////////
	EtudiantPerson::EtudiantPerson() {
		this->set_string(BaseItem::TYPE_KEY, EtudiantPerson::ETUDIANTPERSON_TYPE);
	}
	EtudiantPerson::EtudiantPerson(const value &oMap) :Person(oMap) {
		this->set_string(BaseItem::TYPE_KEY, EtudiantPerson::ETUDIANTPERSON_TYPE);
	}
	EtudiantPerson::EtudiantPerson(const EtudiantPerson &other) : Person(other) {

	}
	EtudiantPerson & EtudiantPerson::operator=(const EtudiantPerson &other) {
		if (this != &other) {
			Person::operator=(other);
		}
		return *this;
	}
	EtudiantPerson::~EtudiantPerson() {

	}
	string_t EtudiantPerson::dossier(void) const {
		string_t sRet;
		if (this->has_field(STRING_DOSSIER)) {
			sRet = (this->get_value_at(STRING_DOSSIER)).as_string();
		}
		return sRet;
	}
	void EtudiantPerson::dossier(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_DOSSIER, ss);

	}
	string_t EtudiantPerson::sexe(void) const {
		string_t sRet;
		if (this->has_field(STRING_SEXE)) {
			sRet = (this->get_value_at(STRING_SEXE)).as_string();
		}
		return sRet;
	}
	void EtudiantPerson::sexe(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_SEXE, ss);
	}
	Date EtudiantPerson::birth_date(void) const {
		Date dRet;
		if (this->has_field(STRING_BIRTHDATE)) {
			value v = this->get_value_at(STRING_BIRTHDATE);
			dRet = value_to_date(v);
		}
		return dRet;
	}
	void EtudiantPerson::birth_date(const Date d) {
		this->set_value_at(STRING_BIRTHDATE, date_to_value(d));
	}
	string_t EtudiantPerson::ville(void) const {
		string_t sRet;
		if (this->has_field(STRING_VILLE)) {
			sRet = (this->get_value_at(STRING_VILLE)).as_string();
		}
		return sRet;
	}
	void EtudiantPerson::ville(const string_t &s) {
		this->set_string(STRING_VILLE, s);
	}
	string_t EtudiantPerson::etablissement(void) const {
		string_t sRet;
		if (this->has_field(STRING_ETABLISSEMENT)) {
			sRet = (this->get_value_at(STRING_ETABLISSEMENT)).as_string();
		}
		return sRet;
	}
	void EtudiantPerson::etablissement(const string_t &s) {
		this->set_string(STRING_VILLE, s);
	}
	string_t EtudiantPerson::serie_bac(void) const {
		string_t sRet;
		if (this->has_field(STRING_SERIEBAC)) {
			sRet = (this->get_value_at(STRING_SERIEBAC)).as_string();
		}
		return sRet;
	}
	void EtudiantPerson::serie_bac(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_SERIEBAC, ss);
	}
	string_t EtudiantPerson::option_bac(void) const {
		string_t sRet;
		if (this->has_field(STRING_OPTIONBAC)) {
			sRet = (this->get_value_at(STRING_OPTIONBAC)).as_string();
		}
		return sRet;
	}
	void EtudiantPerson::option_bac(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_OPTIONBAC, ss);
	}
	string_t EtudiantPerson::mention_bac(void) const {
		string_t sRet;
		if (this->has_field(STRING_MENTIONBAC)) {
			sRet = (this->get_value_at(STRING_MENTIONBAC)).as_string();
		}
		return sRet;
	}
	void EtudiantPerson::mention_bac(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_MENTIONBAC, ss);
	}
	string_t EtudiantPerson::etudes_superieures(void) const {
		string_t sRet;
		if (this->has_field(STRING_ETUDESSUPERIEURES)) {
			sRet = (this->get_value_at(STRING_ETUDESSUPERIEURES)).as_string();
		}
		return sRet;
	}
	void EtudiantPerson::etudes_superieures(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_ETUDESSUPERIEURES, ss);
	}
	string_t EtudiantPerson::apb(void) const {
		string_t sRet;
		if (this->has_field(STRING_APB)) {
			sRet = (this->get_value_at(STRING_APB)).as_string();
		}
		return sRet;
	}
	void EtudiantPerson::apb(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_APB, ss);
	}
	string_t EtudiantPerson::redoublant(void) const {
		string_t sRet;
		if (this->has_field(STRING_REDOUBLANT)) {
			sRet = (this->get_value_at(STRING_REDOUBLANT)).as_string();
		}
		return sRet;
	}
	void EtudiantPerson::redoublant(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(STRING_REDOUBLANT, ss);
	}
	string_t EtudiantPerson::type(void) const {
		return ETUDIANTPERSON_TYPE;
	}
	//////////////////////////////////////////
	EnseignantPerson::EnseignantPerson() {
		this->set_string(BaseItem::TYPE_KEY, EnseignantPerson::ENSEIGNANTPERSON_TYPE);
	}
	EnseignantPerson::EnseignantPerson(const value &oMap) :Person(oMap) {
		this->set_string(BaseItem::TYPE_KEY, EnseignantPerson::ENSEIGNANTPERSON_TYPE);
	}
	EnseignantPerson::EnseignantPerson(const EnseignantPerson &other) : Person(other) {

	}
	EnseignantPerson & EnseignantPerson::operator=(const EnseignantPerson &other) {
		if (this != &other) {
			Person::operator=(other);
		}
		return *this;
	}
	EnseignantPerson::~EnseignantPerson() {

	}
	string_t EnseignantPerson::type(void) const {
		return ENSEIGNANTPERSON_TYPE;
	}
	///////////////////////////////////////////
	OperatorPerson::OperatorPerson() {
		this->set_string(BaseItem::TYPE_KEY, OperatorPerson::OPERATORPERSON_TYPE);
	}
	OperatorPerson::OperatorPerson(const value &oMap) :Person(oMap) {
		this->set_string(BaseItem::TYPE_KEY, OperatorPerson::OPERATORPERSON_TYPE);
	}
	OperatorPerson::OperatorPerson(const OperatorPerson &other) : Person(other) {
	}
	OperatorPerson & OperatorPerson::operator=(const OperatorPerson &other) {
		if (this != &other) {
			Person::operator=(other);
		}
		return *this;
	}
	OperatorPerson::~OperatorPerson() {

	}
	string_t OperatorPerson::type(void) const {
		return OPERATORPERSON_TYPE;
	}
	/////////////////////////////////////////////
	SuperAdminPerson::SuperAdminPerson() {
		this->set_string(BaseItem::TYPE_KEY, SuperAdminPerson::SUPERADMINPERSON_TYPE);
		this->username(U("admin"));
		this->firstname(U("Administrateur"));
		this->lastname(U("Système"));
	}
	SuperAdminPerson::SuperAdminPerson(const value &oMap) :Person(oMap) {
		this->set_string(BaseItem::TYPE_KEY, SuperAdminPerson::SUPERADMINPERSON_TYPE);
	}
	SuperAdminPerson::SuperAdminPerson(const SuperAdminPerson &other) : Person(other) {

	}
	SuperAdminPerson & SuperAdminPerson::operator=(const SuperAdminPerson &other) {
		if (this != &other) {
			Person::operator=(other);
		}
		return *this;
	}
	SuperAdminPerson::~SuperAdminPerson() {

	}
	string_t SuperAdminPerson::type(void) const {
		return SUPERADMINPERSON_TYPE;
	}
	///////////////////////////////////////////
}// namespace geninfo
