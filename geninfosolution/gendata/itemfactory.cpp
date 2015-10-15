#include "stdafx.h"
#include "itemfactory.h"
#include "domainconstants.h"
#include "departement.h"
#include "groupe.h"
#include "unite.h"
//////////////////////////////
namespace geninfo {
	ItemFactory::ItemFactory()
	{
	}
	ItemFactory::ItemFactory(const ItemFactory & /*other*/) {

	}
	ItemFactory & ItemFactory::operator=(const ItemFactory & /*other*/) {
		return (*this);
	}

	ItemFactory::~ItemFactory()
	{
	}
	std::shared_ptr<BaseItem> ItemFactory::create(const Value &oMap, bool *pOk /*= nullptr*/) const {
		std::shared_ptr<BaseItem> oRet;
		if (pOk != nullptr) {
			*pOk = false;
		}
		if (oMap.is_object()) {
			Object *pObj = oMap.as_object();
			if ((pObj != nullptr) && pObj->has_field(DomainConstants::TYPE)) {
				std::string stype = pObj->get_string(DomainConstants::TYPE);
				if (stype == DomainConstants::DEPARTEMENT_TYPE) {
					if (pOk != nullptr) {
						*pOk = true;
					}
					oRet.reset(new Departement(oMap));
				} else if (stype == DomainConstants::GROUPE_TYPE) {
					if (pOk != nullptr) {
						*pOk = true;
					}
					oRet.reset(new Groupe(oMap));
				}
				else if (stype == DomainConstants::UNITE_TYPE) {
					if (pOk != nullptr) {
						*pOk = true;
					}
					oRet.reset(new Unite(oMap));
				}
			}// object
		}// object
		return oRet;
	}
}// namespace geninfo