#include "stdafx.h"
#include "departement.h"
#include "domainconstants.h"
//////////////////////////////
namespace geninfo {

	Departement::Departement()
	{
		this->type(DomainConstants::DEPARTEMENT_TYPE);
	}
	Departement::Departement(const Value &oMap):SigleNamedItem(oMap) {
		this->type(DomainConstants::DEPARTEMENT_TYPE);
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
}// namespace geninfo
