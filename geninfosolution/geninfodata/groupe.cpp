#include "stdafx.h"
#include "groupe.h"
#include "IDatabaseManager.h"
///////////////////////////////
namespace geninfo {
	///////////////////////////////
	const string_t Groupe::GROUPE_TYPE(U("groupe"));
	const string_t Groupe::GENRE_COURS(U("COURS"));
	const string_t Groupe::GENRE_TD(U("TD"));
	const string_t Groupe::GENRE_TP(U("TP"));
	/////////////////////////////////
	const string_t STRING_GENRE = U("genre");
	const string_t STRING_CHILDREN = U("childrenids");
	const string_t GROUPE_PREFIX = U("GRP");
	//////////////////////////////////
	std::vector<string_t> Groupe::genres(void) {
		std::vector<string_t> vec;
		vec.push_back(GENRE_COURS);
		vec.push_back(GENRE_TD);
		vec.push_back(GENRE_TP);
		return vec;
	}
	/////////////////////////////
	Groupe::Groupe()
	{
		this->set_string(BaseItem::TYPE_KEY, Groupe::GROUPE_TYPE);
	}
	Groupe::Groupe(const Departement &oDep):DepSigleNamedItem(oDep)
	{
		this->set_string(BaseItem::TYPE_KEY, Groupe::GROUPE_TYPE);
	}
	Groupe::Groupe(const value &oMap) :DepSigleNamedItem(oMap)
	{
		this->set_string(BaseItem::TYPE_KEY, Groupe::GROUPE_TYPE);
	}
	Groupe::Groupe(const Groupe &other) : DepSigleNamedItem(other)
	{
	}
	Groupe & Groupe::operator=(const Groupe &other)
	{
		if (this != &other) {
			DepSigleNamedItem::operator=(other);
		}
		return *this;
	}
	Groupe::~Groupe()
	{
	}
	string_t Groupe::genre(void) const {
		string_t sRet;
		if (this->has_field(STRING_GENRE)) {
			sRet = (this->get_value_at(STRING_GENRE)).as_string();
		}
		return sRet;
	}
	void Groupe::genre(const string_t &s) {
		string_t ss = to_upper(trim(s));
		if ((ss == GENRE_COURS) || (ss == GENRE_TD) || (ss == GENRE_TP)) {
			this->set_string(STRING_GENRE, ss);
		}
	}
	std::set<string_t> Groupe::children_ids(void) const {
		std::set<string_t> vec;
		if (this->has_field(STRING_CHILDREN)) {
			const value &v = this->at(STRING_CHILDREN);
			vec = value_to_string_set(v);
		}// field
		return vec;
	}// children_ids
	bool Groupe::add_child(const Groupe &g) {
		string_t gid = g.id();
		if (gid.empty()) {
			return false;
		}
		string_t gr = this->genre();
		string_t gx = g.genre();
		if (gx.empty() || gr.empty()) {
			return false;
		}
		if (gr == GENRE_TP) {
			return false;
		}
		if ((gr == GENRE_COURS) && (gx != GENRE_TD)) {
			return false;
		}
		if ((gr == GENRE_TD) && (gx != GENRE_TP)) {
			return false;
		}
		std::set<string_t> vec = this->children_ids();
		if (vec.find(gid) != vec.end()) {
			return false;
		}
		vec.insert(gid);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_CHILDREN] = v;
		return true;
	}// add
	bool Groupe::remove_child(const Groupe &g) {
		string_t gid = g.id();
		if (gid.empty()) {
			return false;
		}
		std::set<string_t> vec = this->children_ids();
		auto it = vec.find(gid);
		if (it == vec.end()) {
			return false;
		}
		vec.erase(it);
		value v = string_set_to_value(vec);
		this->_m_val[STRING_CHILDREN] = v;
		return true;
	}//remove_child
	pplx::task<std::vector<std::shared_ptr<Groupe>>> Groupe::get_children(IDatabaseManager &oMan) const {
		std::set<string_t> oSet = this->children_ids();
		if (oSet.empty()) {
			std::vector<std::shared_ptr<Groupe>> ox;
			return pplx::task_from_result(ox);
		}
		std::vector<string_t> vec(oSet.begin(), oSet.end());
		Groupe model;
		return oMan.load_items_array(model, vec);
	}// get_children
	bool Groupe::is_storeable(void) const {
		string_t s = this->genre();
		return (!s.empty()) && DepSigleNamedItem::is_storeable();
	}
	string_t Groupe::type(void) const {
		return GROUPE_TYPE;
	}
	string_t Groupe::store_prefix(void) const {
		return GROUPE_PREFIX;
	}
	/////////////////////////////
}// namespace geninfo