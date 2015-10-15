#include "stdafx.h"
#include "unite.h"
#include "domainconstants.h"
///////////////////////////////////////
namespace geninfo {
	//////////////////////////
	Unite::Unite()
	{
		this->type(DomainConstants::UNITE_TYPE);
		this->modified(false);
	}
	Unite::Unite(const Value &oMap) :DepSigleNamedItem(oMap) {
		this->type(DomainConstants::UNITE_TYPE);
		this->modified(false);
	}
	Unite::Unite(const Departement &oDep) : DepSigleNamedItem(oDep) {
		this->type(DomainConstants::UNITE_TYPE);
		this->modified(false);
	}
	Unite::Unite(const Unite &other) : DepSigleNamedItem(other) {

	}
	Unite & Unite::operator=(const Unite &other) {
		if (this != &other) {
			DepSigleNamedItem::operator=(other);
		}
		return (*this);
	}

	Unite::~Unite()
	{
	}
	int Unite::order(void) const {
		return this->get_int(DomainConstants::ORDER);
	}
	void Unite::order(int n) {
		this->set_int(DomainConstants::ORDER, n);
	}
	std::string Unite::store_prefix(void) const {
		return (DomainConstants::UNITE_PREFIX);
	}
	/////////////////////////////////
}// namespace geninfo
