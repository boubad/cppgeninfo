#include "stdafx.h"
#include "departement.h"
#include "domainconstants.h"
#include "idatamanager.h"
#include "unite.h"
#include "groupe.h"
//////////////////////////////
namespace geninfo {
	//////////////////////////////////////
	std::vector<PDepartement> Departement::get_all_departements(IDataManager &oMan) {
		std::vector<PDepartement> oRet;
		Departement model;
		Value vr = oMan.read_docs_range(model.start_key(), model.end_key());
		if (vr.is_array()) {
			Array *pAr = vr.as_array();
			if (pAr != nullptr) {
				size_t n = pAr->size();
				for (size_t i = 0; i < n; ++i) {
					PValue ov = (*pAr)[i];
					Value *pv = ov.get();
					if (pv != nullptr) {
						PDepartement d = std::make_shared<Departement>(*pv);
						oRet.push_back(d);
					}
				}// i
			}// pAr
		}// array
		return oRet;
	}
	Departement::Departement()
	{
		this->type(DomainConstants::DEPARTEMENT_TYPE);
		this->modified(false);
	}
	Departement::Departement(const Value &oMap):SigleNamedItem(oMap) {
		this->type(DomainConstants::DEPARTEMENT_TYPE);
		this->modified(false);
	}
	Departement::Departement(const Departement &other):SigleNamedItem(other) {

	}
	Departement & Departement::operator=(const Departement & other) {
		if (this != &other) {
			SigleNamedItem::operator=(other);
		}
		return *this;
	}

	Departement::~Departement()
	{
	}
	std::string Departement::store_prefix(void) const {
		return DomainConstants::DEPARTEMENT_PREFIX;
	}
	std::vector<std::shared_ptr<Groupe>> Departement::groupes(IDataManager &oMan) {
		std::vector<std::shared_ptr<Groupe>> oRet;
		if (this->has_id()) {
			Groupe model(*this);
			std::string start = model.start_key();
			std::string end = model.end_key();
			Value vr = oMan.read_docs_range(start, end);
			if (vr.is_array()) {
				Array *pAr = vr.as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue ov = (*pAr)[i];
						Value *pv = ov.get();
						if (pv != nullptr) {
							std::shared_ptr<Groupe> d = std::make_shared<Groupe>(*pv);
							oRet.push_back(d);
						}
					}// i
				}// pAr
			}// array
		}// has_id
		return oRet;
	}
	std::vector<std::shared_ptr<Unite>> Departement::unites(IDataManager &oMan) {
		std::vector<std::shared_ptr<Unite>> oRet;
		if (this->has_id()) {
			Unite model(*this);
			std::string start = model.start_key();
			std::string end = model.end_key();
			Value vr = oMan.read_docs_range(start, end);
			if (vr.is_array()) {
				Array *pAr = vr.as_array();
				if (pAr != nullptr) {
					size_t n = pAr->size();
					for (size_t i = 0; i < n; ++i) {
						PValue ov = (*pAr)[i];
						Value *pv = ov.get();
						if (pv != nullptr) {
							std::shared_ptr<Unite> d = std::make_shared<Unite>(*pv);
							oRet.push_back(d);
						}
					}// i
				}// pAr
			}// array
		}// has_id
		return oRet;
	}
	///////////////////////////////////
}// namespace geninfo
