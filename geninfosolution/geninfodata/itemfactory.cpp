#include "stdafx.h"
#include "itemfactory.h"
//////////////////////////
#include "departement.h"
#include "groupe.h"
#include "unite.h"
#include "annee.h"
#include "semestre.h"
#include "matiere.h"
#include "person.h"
#include "depperson.h"
#include "affectation.h"
#include "groupeevent.h"
#include "etudiantevent.h"
////////////////////////////
namespace geninfo {
	//////////////////////////////
	ItemFactory::ItemFactory()
	{
	}

	ItemFactory::ItemFactory(const ItemFactory & other) :IItemFactory(other)
	{
	}
	ItemFactory & ItemFactory::operator=(const ItemFactory & other)
	{
		return *this;
	}
	ItemFactory::~ItemFactory()
	{
	}
	BaseItem *ItemFactory::create_item(const value &oMap, const string_t &type /*= string_t()*/) const {
		BaseItem *pRet = nullptr;
		string_t xtype = boost::to_lower_copy(boost::trim_copy(type));
		if (xtype.empty()) {
			if (oMap.is_object() && oMap.has_field(BaseItem::TYPE_KEY)) {
				const value &v = oMap.at(BaseItem::TYPE_KEY);
				if ((!v.is_null()) && v.is_string()) {
					xtype = to_lower(trim(v.as_string()));
				}
			}
		}
		if (xtype.empty()) {
			return pRet;
		}
		if (xtype == Departement::DEPARTEMENT_TYPE) {
			pRet = new Departement(oMap);
		}
		else if (xtype == Groupe::GROUPE_TYPE) {
			pRet = new Groupe(oMap);
		}
		else if (xtype == Unite::UNITE_TYPE) {
			pRet = new Unite(oMap);
		}
		else if (xtype == Annee::ANNEE_TYPE) {
			pRet = new Annee(oMap);
		}
		else if (xtype == Semestre::SEMESTRE_TYPE) {
			pRet = new Semestre(oMap);
		}
		else if (xtype == Matiere::MATIERE_TYPE) {
			pRet = new Matiere(oMap);
		}
		else if (xtype == Person::PERSON_TYPE) {
			pRet = new Person(oMap);
		}
		else if (xtype == EtudiantPerson::ETUDIANTPERSON_TYPE) {
			pRet = new EtudiantPerson(oMap);
		}
		else if (xtype == EnseignantPerson::ENSEIGNANTPERSON_TYPE) {
			pRet = new EnseignantPerson(oMap);
		}
		else if (xtype == OperatorPerson::OPERATORPERSON_TYPE) {
			pRet = new OperatorPerson(oMap);
		}
		else if (xtype == SuperAdminPerson::SUPERADMINPERSON_TYPE) {
			pRet = new SuperAdminPerson(oMap);
		}
		else if (xtype == Etudiant::ETUDIANT_TYPE) {
			pRet = new Etudiant(oMap);
		}
		else if (xtype == Enseignant::ENSEIGNANT_TYPE) {
			pRet = new Enseignant(oMap);
		}
		else if (xtype == Administrator::ADMINISTRATOR_TYPE) {
			pRet = new Administrator(oMap);
		}
		else if (xtype == EnseignantAffectation::ENSEIGNANTAFFECTATION_TYPE) {
			pRet = new EnseignantAffectation(oMap);
		}
		else if (xtype == EtudiantAffectation::ETUDIANTAFFECTATION_TYPE) {
			pRet = new EtudiantAffectation(oMap);
		}
		else if (xtype == GroupeEvent::GROUPEEVENT_TYPE) {
			pRet = new GroupeEvent(oMap);
		}
		else if (xtype == EtudiantEvent::ETUDIANTEVENT_TYPE) {
			pRet = new EtudiantEvent(oMap);
		}
		return pRet;
	}// create_item
	//////////////////////////////
}// namespace geninfo
