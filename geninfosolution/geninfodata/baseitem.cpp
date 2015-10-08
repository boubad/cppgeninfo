#include "stdafx.h"
#include "baseitem.h"
#include "IDatabaseManager.h"
#include "departement.h"
#include "couchdoc.h"
#include "couchconstants.h"
#include "genninfoconstants.h"
/////////////////////////////
namespace geninfo {
	////////////////////////////////////////
	BaseItem::BaseItem()
	{
	}
	BaseItem::BaseItem(const value &oMap) :BaseDocument(oMap)
	{
	}
	BaseItem::BaseItem(const BaseItem &other) : BaseDocument(other)
	{
	}
	BaseItem & BaseItem::operator=(const BaseItem &other) {
		if (this != &other) {
			BaseDocument::operator=(other);
		}
		return *this;
	}
	BaseItem::~BaseItem()
	{
	}
	string_t BaseItem::type(void) const {
		return string_t();
	}
	string_t BaseItem::store_prefix(void) const {
		return string_t();
	}
	bool BaseItem::is_storeable(void) const {
		return true;
	}
	string_t BaseItem::start_key(void) const {
		return this->store_prefix();
	}
	string_t BaseItem::end_key(void) const {
		string_t s = this->start_key();
		s = s + U("z");
		return s;
	}
	void BaseItem::check_id(void) {
		string_t s = this->id();
		if (s.empty()) {
			this->id(this->create_id());
		}
	}
	string_t BaseItem::status(void) const {
		string_t sRet;
		if (this->has_field(GenInfoConstants::STATUS)) {
			sRet = (this->get_value_at(GenInfoConstants::STATUS)).as_string();
		}
		return sRet;
	}
	void BaseItem::status(const string_t &s) {
		this->set_string(GenInfoConstants::STATUS, trim(s));
	}
	string_t BaseItem::description(void) const {
		string_t sRet;
		if (this->has_field(GenInfoConstants::DESCRIPTION)) {
			sRet = (this->get_value_at(GenInfoConstants::DESCRIPTION)).as_string();
		}
		return sRet;
	}
	void BaseItem::description(const string_t &s) {
		this->set_string(GenInfoConstants::DESCRIPTION, trim(s));
	}
	string_t BaseItem::create_id(void) const {
		return string_t();
	}
	pplx::task<bool> BaseItem::save(IDatabaseManager &oMan) {
		return oMan.maintains_item(*this).then([=](pplx::task<UpdateResponse> t) {
			bool bRet = false;
			try {
				UpdateResponse rsp = t.get();
				bRet = rsp.ok();
				if (bRet) {
					this->id(rsp.id());
					this->rev(rsp.rev());
				}
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return pplx::task_from_result(bRet);
		});
	}// save
	pplx::task<bool> BaseItem::remove(IDatabaseManager &oMan) {
		return oMan.remove_item(*this).then([=](pplx::task<UpdateResponse> t) {
			bool bRet = false;
			try {
				UpdateResponse rsp = t.get();
				bRet = rsp.ok();
				if (bRet) {
					value &v = this->get_value();
					v[GenInfoConstants::DELETED] = value::boolean(true);
				}
			}
			catch (std::exception &ex) {
				throw ex;
			}
			return pplx::task_from_result(bRet);
		});
	}// remove
	//////////////////////////////////////////
	NamedItem::NamedItem() {

	}
	NamedItem::NamedItem(const value &oMap) :BaseItem(oMap) {

	}
	NamedItem::NamedItem(const NamedItem &other) : BaseItem(other) {

	}
	NamedItem & NamedItem::operator=(const NamedItem &other) {
		if (this != &other) {
			BaseItem::operator=(other);
		}
		return *this;
	}
	NamedItem::~NamedItem() {

	}
	string_t NamedItem::name(void) const {
		string_t sRet;
		if (this->has_field(GenInfoConstants::NAME)) {
			sRet = (this->get_value_at(GenInfoConstants::NAME)).as_string();
		}
		return sRet;
	}
	void NamedItem::name(const string_t &s) {
		string_t ss = trim(s);
		if (ss.length() > 1) {
			ss = to_upper(ss.substr(0, 1)) + ss.substr(1);
		}
		else {
			ss = to_upper(s);
		}
		this->set_string(GenInfoConstants::NAME, ss);
	}
	bool NamedItem::is_storeable(void) const {
		string_t s = this->name();
		return (!s.empty());
	}
	////////////////////////////////////////////
	SigleNamedItem::SigleNamedItem() {

	}
	SigleNamedItem::SigleNamedItem(const value &oMap) :NamedItem(oMap) {

	}
	SigleNamedItem::SigleNamedItem(const SigleNamedItem &other) : NamedItem(other) {

	}
	SigleNamedItem & SigleNamedItem::operator=(const SigleNamedItem &other) {
		if (this != &other) {
			NamedItem::operator=(other);
		}
		return *this;
	}
	SigleNamedItem::~SigleNamedItem() {

	}
	string_t SigleNamedItem::sigle(void) const {
		string_t sRet;
		if (this->has_field(GenInfoConstants::SIGLE)) {
			sRet = (this->get_value_at(GenInfoConstants::SIGLE)).as_string();
		}
		return sRet;
	}
	void SigleNamedItem::sigle(const string_t &s) {
		string_t ss = to_upper(trim(s));
		this->set_string(GenInfoConstants::SIGLE, ss);
	}
	bool SigleNamedItem::is_storeable(void) const {
		string_t s = this->sigle();
		return (!s.empty()) && NamedItem::is_storeable();
	}
	string_t SigleNamedItem::create_id(void) const {
		string_t s = this->store_prefix();
		string_t sRet = url_encode(s + this->sigle());
		return sRet;
	}
	//////////////////////////////////////////
	DepSigleNamedItem::DepSigleNamedItem() {
	}
	DepSigleNamedItem::DepSigleNamedItem(const Departement &oDep) {
		this->departementid(oDep.id());
	}
	DepSigleNamedItem::DepSigleNamedItem(const value &oMap) :SigleNamedItem(oMap) {
	}
	DepSigleNamedItem::DepSigleNamedItem(const DepSigleNamedItem &other) : SigleNamedItem(other) {
	}
	DepSigleNamedItem & DepSigleNamedItem::operator=(const DepSigleNamedItem &other) {
		if (this != &other) {
			SigleNamedItem::operator=(other);
		}
		return *this;
	}
	DepSigleNamedItem::~DepSigleNamedItem() {
	}
	string_t DepSigleNamedItem::departementid(void) const {
		string_t sRet;
		if (this->has_field(GenInfoConstants::DEPARTEMENTID)) {
			sRet = (this->get_value_at(GenInfoConstants::DEPARTEMENTID)).as_string();
		}
		return sRet;
	}
	void DepSigleNamedItem::departementid(const string_t &s) {
		this->set_string(GenInfoConstants::DEPARTEMENTID, s);
	}
	bool DepSigleNamedItem::is_storeable(void) const {
		string_t s = this->departementid();
		return (!s.empty()) && SigleNamedItem::is_storeable();
	}
	string_t DepSigleNamedItem::start_key(void) const {
		string_t s1 = this->store_prefix();
		string_t s2 = this->departementid();
		return (s1 + s2);
	}
	string_t DepSigleNamedItem::create_id(void) const {
		string_t s1 = this->store_prefix();
		string_t s2 = this->departementid();
		string_t s3 = this->sigle();
		return url_encode(s1 + s2 + s3);
	}
	pplx::task<std::shared_ptr<Departement> > DepSigleNamedItem::get_departement(IDatabaseManager &oMan) {
		string_t id = this->departementid();
		Departement oDep;
		return oMan.load_item(oDep, id);
	}//get_departement
	/////////////////////////////////////////
}// namespace geninfo
