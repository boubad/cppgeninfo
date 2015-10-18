#include "stdafx.h"
#include "person.h"
#include "domainconstants.h"
#include "idatamanager.h"
#include "md5.h"
///////////////////////////////
namespace geninfo {
	///////////////////////////////
	const std::string STRING_DEP("depid");
	const std::string STRING_ROLE("role");
	//////////////////////////////
	PersonRole::PersonRole() {

	}
	PersonRole::PersonRole(const std::string &depid, const std::string &role) :m_depid(depid), m_role(role) {

	}
	PersonRole::PersonRole(const PersonRole &other) : m_depid(other.m_depid), m_role(other.m_role) {

	}
	PersonRole & PersonRole::operator=(const PersonRole &other) {
		if (this != &other) {
			this->m_depid = other.m_depid;
			this->m_role = other.m_role;
		}
		return (*this);
	}
	bool PersonRole::operator<(const PersonRole &other) const {
		if (this->m_depid < other.m_depid) {
			return true;
		}
		else if (this->m_depid > other.m_depid) {
			return false;
		}
		return (this->m_role < other.m_role);
	}
	bool PersonRole::operator==(const PersonRole &other) const {
		if (this->m_depid != other.m_depid) {
			return false;
		}
		return (this->m_role == other.m_role);
	}
	PersonRole::~PersonRole() {

	}
	const std::string & PersonRole::departementid(void) const {
		return (this->m_depid);
	}
	void PersonRole::departementid(const std::string &s) {
		this->m_depid = s;
	}
	const std::string & PersonRole::role(void) const {
		return (this->m_role);
	}
	void PersonRole::role(const std::string &s) {
		this->m_role = s;
	}
	///////////////////////////////
	std::shared_ptr<Person> Person::find_by_username(const std::string &suser, IDataManager &oMan) {
		std::shared_ptr<Person> oRet;
		Person oPers;
		oPers.username(suser);
		oPers.check_id();
		std::string id = oPers.id();
		if (id.empty()) {
			Value v = oMan.read_doc(id,true);
			if (v.is_object()) {
				Object *pObj = v.as_object();
				if (pObj != nullptr) {
					std::string sx = pObj->get_string(DomainConstants::ID);
					if (sx == id) {
						oRet = std::make_shared<Person>(v);
					}
				}// pObj
			}
		}
		return oRet;
	}
	Person::Person() {
		this->type(DomainConstants::PERSON_TYPE);
		this->modified(false);
	}
	Person::Person(const Value &oMap) :BaseItem(oMap) {
		this->type(DomainConstants::PERSON_TYPE);
		this->modified(false);
	}
	Person::Person(const Person &other) : BaseItem(other) {

	}
	Person & Person::operator=(const Person &other) {
		if (this != &other) {
			BaseItem::operator=(other);
		}
		return (*this);
	}
	Person::~Person() {

	}
	std::string Person::username(void) const {
		return this->get_string(DomainConstants::USERNAME);
	}
	void Person::username(const std::string &s) {
		this->set_string(DomainConstants::USERNAME, to_upper(trim(s)));
	}
	std::string Person::password(void) const {
		return this->get_string(DomainConstants::PASSWORD);
	}
	void Person::password(const std::string &s) {
		this->set_string(DomainConstants::PASSWORD, s);
	}
	std::string Person::firstname(void) const {
		return this->get_string(DomainConstants::FIRSTNAME);
	}
	void Person::firstname(const std::string &s) {
		std::string ss = format_name(s);
		this->set_string(DomainConstants::FIRSTNAME, ss);
	}
	std::string Person::lastname(void) const {
		return this->get_string(DomainConstants::LASTNAME);
	}
	void Person::lastname(const std::string &s) {
		this->set_string(DomainConstants::LASTNAME, to_upper(trim(s)));
	}
	std::string Person::email(void) const {
		return this->get_string(DomainConstants::EMAIL);
	}
	void Person::email(const std::string &s) {
		this->set_string(DomainConstants::EMAIL, s);
	}
	std::string Person::phone(void) const {
		return this->get_string(DomainConstants::PHONE);
	}
	void Person::phone(const std::string &s) {
		this->set_string(DomainConstants::PHONE, s);
	}
	std::vector<PersonRole> Person::roles(void) const {
		std::vector<PersonRole> oRet;
		Array *pAr = this->get_array(DomainConstants::ROLES);
		if (pAr != nullptr) {
			size_t n = pAr->size();
			for (size_t i = 0; i < n; ++i) {
				PValue vv = (*pAr)[i];
				Value *v = vv.get();
				if ((v != nullptr) && v->is_object()) {
					Object *pObj = v->as_object();
					if (pObj != nullptr) {
						std::string depid = pObj->get_string(STRING_DEP);
						std::string role = pObj->get_string(STRING_DEP);
						if ((!depid.empty()) && (!role.empty())) {
							PersonRole r(depid, role);
							oRet.push_back(r);
						}
					}// pObj
				}// v
			}// i
		}// pAr
		return oRet;
	}
	bool Person::add_role(const std::string &depid, std::string &srole) {
		std::string role = to_lower(trim(srole));
		if (depid.empty() || role.empty()) {
			return false;
		}
		std::vector<PersonRole> oRet = this->roles();
		bool bFound = false;
		PersonRole temp(depid, role);
		for (auto it = oRet.begin(); it != oRet.end(); ++it) {
			if ((*it) == temp) {
				bFound = true;
				break;
			}
		}
		if (bFound) {
			return false;
		}
		Array *pAr = this->set_array(DomainConstants::ROLES);
		if (pAr == nullptr) {
			return false;
		}
		PObject obj = Value::create_object();
		Object *p = obj.get();
		p->set_string(STRING_DEP, depid);
		p->set_string(STRING_ROLE, role);
		pAr->append_object(obj);
		this->modified(true);
		return true;
	}// add_role
	//
	std::set<std::string> Person::departementids(void) const {
		std::set<std::string> oRet;
		std::vector<PersonRole> xRet = this->roles();
		for (auto it = xRet.begin(); it != xRet.end(); ++it) {
			std::string id = (*it).departementid();
			if (oRet.find(id) == oRet.end()) {
				oRet.insert(id);
			}
		}
		return oRet;
	}
	std::set<std::string> Person::anneeids(void) const {
		std::set<std::string> oRet;
		Array *pAr = this->get_array(DomainConstants::ANNEESIDS);
		if (pAr != nullptr) {
			size_t n = pAr->size();
			for (size_t i = 0; i < n; ++i) {
				PValue vv = (*pAr)[i];
				Value *v = vv.get();
				if ((v != nullptr) && v->is_string()) {
					std::string sv = v->as_string();
					if (!sv.empty()) {
						oRet.insert(sv);
					}
				}
			}// i
		}// pAR
		return oRet;
	}
	void Person::add_anneeid(const std::string &s) {
		std::string ss = trim(s);
		if (ss.empty()) {
			return;
		}
		std::set<std::string> oSet = this->anneeids();
		if (oSet.find(s) != oSet.end()) {
			return;
		}
		Array *pAr = this->set_array(DomainConstants::ANNEESIDS);
		if (pAr != nullptr) {
			pAr->append_string(ss);
		}
	}
	
	std::set<std::string> Person::semestreids(void) const {
		std::set<std::string> oRet;
		Array *pAr = this->get_array(DomainConstants::SEMESTRESIDS);
		if (pAr != nullptr) {
			size_t n = pAr->size();
			for (size_t i = 0; i < n; ++i) {
				PValue vv = (*pAr)[i];
				Value *v = vv.get();
				if ((v != nullptr) && v->is_string()) {
					std::string sv = v->as_string();
					if (!sv.empty()) {
						oRet.insert(sv);
					}
				}
			}// i
		}// pAR
		return oRet;
	}
	void Person::add_semestreid(const std::string &s) {
		std::string ss = trim(s);
		if (ss.empty()) {
			return;
		}
		std::set<std::string> oSet = this->semestreids();
		if (oSet.find(s) != oSet.end()) {
			return;
		}
		Array *pAr = this->set_array(DomainConstants::SEMESTRESIDS);
		if (pAr != nullptr) {
			pAr->append_string(ss);
		}
	}
	std::set<std::string> Person::groupeids(void) const {
		std::set<std::string> oRet;
		Array *pAr = this->get_array(DomainConstants::GROUPESIDS);
		if (pAr != nullptr) {
			size_t n = pAr->size();
			for (size_t i = 0; i < n; ++i) {
				PValue vv = (*pAr)[i];
				Value *v = vv.get();
				if ((v != nullptr) && v->is_string()) {
					std::string sv = v->as_string();
					if (!sv.empty()) {
						oRet.insert(sv);
					}
				}
			}// i
		}// pAR
		return oRet;
	}
	void Person::add_groupeid(const std::string &s) {
		std::string ss = trim(s);
		if (ss.empty()) {
			return;
		}
		std::set<std::string> oSet = this->groupeids();
		if (oSet.find(s) != oSet.end()) {
			return;
		}
		Array *pAr = this->set_array(DomainConstants::GROUPESIDS);
		if (pAr != nullptr) {
			pAr->append_string(ss);
		}
	}
	std::set<std::string> Person::uniteids(void) const {
		std::set<std::string> oRet;
		Array *pAr = this->get_array(DomainConstants::UNITESIDS);
		if (pAr != nullptr) {
			size_t n = pAr->size();
			for (size_t i = 0; i < n; ++i) {
				PValue vv = (*pAr)[i];
				Value *v = vv.get();
				if ((v != nullptr) && v->is_string()) {
					std::string sv = v->as_string();
					if (!sv.empty()) {
						oRet.insert(sv);
					}
				}
			}// i
		}// pAR
		return oRet;
	}
	void Person::add_uniteid(const std::string &s) {
		std::string ss = trim(s);
		if (ss.empty()) {
			return;
		}
		std::set<std::string> oSet = this->uniteids();
		if (oSet.find(s) != oSet.end()) {
			return;
		}
		Array *pAr = this->set_array(DomainConstants::UNITESIDS);
		if (pAr != nullptr) {
			pAr->append_string(ss);
		}
	}
	std::set<std::string> Person::matiereids(void) const {
		std::set<std::string> oRet;
		Array *pAr = this->get_array(DomainConstants::MATIERESIDS);
		if (pAr != nullptr) {
			size_t n = pAr->size();
			for (size_t i = 0; i < n; ++i) {
				PValue vv = (*pAr)[i];
				Value *v = vv.get();
				if ((v != nullptr) && v->is_string()) {
					std::string sv = v->as_string();
					if (!sv.empty()) {
						oRet.insert(sv);
					}
				}
			}// i
		}// pAR
		return oRet;
	}
	void Person::add_matiereid(const std::string &s) {
		std::string ss = trim(s);
		if (ss.empty()) {
			return;
		}
		std::set<std::string> oSet = this->matiereids();
		if (oSet.find(s) != oSet.end()) {
			return;
		}
		Array *pAr = this->set_array(DomainConstants::MATIERESIDS);
		if (pAr != nullptr) {
			pAr->append_string(ss);
		}
	}
	std::set<std::string> Person::affectationids(void) const {
		std::set<std::string> oRet;
		Array *pAr = this->get_array(DomainConstants::AFFECTATIONSIDS);
		if (pAr != nullptr) {
			size_t n = pAr->size();
			for (size_t i = 0; i < n; ++i) {
				PValue vv = (*pAr)[i];
				Value *v = vv.get();
				if ((v != nullptr) && v->is_string()) {
					std::string sv = v->as_string();
					if (!sv.empty()) {
						oRet.insert(sv);
					}
				}
			}// i
		}// pAR
		return oRet;
	}
	void Person::add_affectationid(const std::string &s) {
		std::string ss = trim(s);
		if (ss.empty()) {
			return;
		}
		std::set<std::string> oSet = this->affectationids();
		if (oSet.find(s) != oSet.end()) {
			return;
		}
		Array *pAr = this->set_array(DomainConstants::AFFECTATIONSIDS);
		if (pAr != nullptr) {
			pAr->append_string(ss);
		}
	}
	std::set<std::string> Person::eventids(void) const {
		std::set<std::string> oRet;
		Array *pAr = this->get_array(DomainConstants::EVENTSIDS);
		if (pAr != nullptr) {
			size_t n = pAr->size();
			for (size_t i = 0; i < n; ++i) {
				PValue vv = (*pAr)[i];
				Value *v = vv.get();
				if ((v != nullptr) && v->is_string()) {
					std::string sv = v->as_string();
					if (!sv.empty()) {
						oRet.insert(sv);
					}
				}
			}// i
		}// pAR
		return oRet;
	}
	void Person::add_eventid(const std::string &s) {
		std::string ss = trim(s);
		if (ss.empty()) {
			return;
		}
		std::set<std::string> oSet = this->eventids();
		if (oSet.find(s) != oSet.end()) {
			return;
		}
		Array *pAr = this->set_array(DomainConstants::EVENTSIDS);
		if (pAr != nullptr) {
			pAr->append_string(ss);
		}
	}
	std::string Person::fullname(void) const {
		std::string s = this->lastname() + std::string(" ") + this->firstname();
		return trim(s);
	}
	bool Person::check_password(const std::string &cpass) const {
		std::string s = to_md5(cpass);
		std::string s1 = this->password();
		return (s == s1);
	}
	void Person::change_password(const std::string &s) {
		std::string ss = to_md5(s);
		this->password(ss);
	}
	void Person::reset_password(void) {
		this->change_password(this->username());
	}
	std::string Person::store_prefix(void) const {
		return DomainConstants::PERSON_PREFIX;
	}
	std::string Person::create_id(void) const {
		return (this->start_key() + this->username());
	}
	bool Person::is_storeable(void) const {
		std::string s1 = this->username();
		std::string s2 = this->lastname();
		std::string s3 = this->firstname();
		return ((!s1.empty()) && (!s2.empty()) && (!s3.empty()) && BaseItem::is_storeable());
	}
	std::string Person::text(void) const {
		return this->fullname();
	}
	//////////////////////
}// namespace geninfo
