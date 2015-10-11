#include "stdafx.h"
#include "domainconstants.h"
////////////////////////////////
namespace geninfo {
	////////////////////////////
	const std::string DomainConstants::TYPE("type");
	const std::string DomainConstants::ID("_id");
	const std::string DomainConstants::REV("_rev");
	const std::string DomainConstants::DELETED("_deleted");
	const std::string DomainConstants::STATUS("status");
	const std::string DomainConstants::DESCRIPTION("description");
	///////////////////////////////////////////////////
	const std::string DomainConstants::SIGLE("sigle");
	const std::string DomainConstants::NAME("name");
	const std::string DomainConstants::ORDER("ordre");
	const std::string DomainConstants::GENRE("genre");
	const std::string DomainConstants::CHILDRENIDS("childrenids");
	const std::string DomainConstants::STARTDATE("startdate");
	const std::string DomainConstants::ENDDATE("enddate");
	const std::string DomainConstants::MODULE("module");
	const std::string DomainConstants::COEFFICIENT("coefficient");
	const std::string DomainConstants::ECS("ecs");
	const std::string DomainConstants::DEPARTEMENTID("departementid");
	const std::string DomainConstants::UNITEID("uniteid");
	const std::string DomainConstants::ANNEEID("anneeid");
	const std::string DomainConstants::MATIEREID("matiereid");
	const std::string DomainConstants::SEMESTREID("semestreid");
	const std::string DomainConstants::GROUPEID("groupeid");
	const std::string DomainConstants::ENSEIGNANTID("enseignantid");
	const std::string DomainConstants::ETUDIANTID("etudiantid");
	const std::string DomainConstants::ENSEIGNANTAFFECTATIONID("enseignantaffectationid");
	const std::string DomainConstants::ETUDIANTAFFECTATIONID("etudiantaffectationid");
	const std::string DomainConstants::GROUPEEVENTID("groupeeventid");
	const std::string DomainConstants::LOCATION("location");
	const std::string DomainConstants::STARTTIME("starttime");
	const std::string DomainConstants::ENDTIME("endtime");
	const std::string DomainConstants::MINNOTE("minnote");
	const std::string DomainConstants::MAXNOTE("maxnote");
	const std::string DomainConstants::NOTE("note");
	const std::string DomainConstants::USERNAME("username");
	const std::string DomainConstants::PASSWORD("password");
	const std::string DomainConstants::FIRSTNAME("firstname");
	const std::string DomainConstants::LASTNAME("lastname");
	const std::string DomainConstants::EMAIL("email");
	const std::string DomainConstants::PHONE("phone");
	const std::string DomainConstants::DOSSIER("dossier");
	const std::string DomainConstants::SEXE("sexe");
	const std::string DomainConstants::BIRTHDATE("birthdate");
	const std::string DomainConstants::VILLE("ville");
	const std::string DomainConstants::ETABLISSEMENT("etablissement");
	const std::string DomainConstants::SERIEBAC("seriebac");
	const std::string DomainConstants::OPTIONBAC("optionbac");
	const std::string DomainConstants::MENTIONBAC("mentionbac");
	const std::string DomainConstants::ETUDESSUPERIEURES("etudessuperieures");
	const std::string DomainConstants::APB("apb");
	const std::string DomainConstants::REDOUBLANT("redoublant");
	//
	const std::string DomainConstants::DEPARTEMENTSIDS("departementids");
	const std::string DomainConstants::UNITESIDS("unitesids");
	const std::string DomainConstants::ANNEESIDS("anneesids");
	const std::string DomainConstants::SEMESTRESIDS("semestresids");
	const std::string DomainConstants::MATIERESIDS("matieresids");
	const std::string DomainConstants::AFFECTATIONSIDS("affectationsids");
	const std::string DomainConstants::EVENTSIDS("eventsids");
	const std::string DomainConstants::ADMINISTRATORSIDS("administratorsids");
	const std::string DomainConstants::ENSEIGNANTSIDS("enseignantsids");
	const std::string DomainConstants::ETUDIANTSIDS("etudiantsids");
	const std::string DomainConstants::GROUPESIDS("groupesids");
	//
	const std::string DomainConstants::GENRE_PROMO("PROMO");
	const std::string DomainConstants::GENRE_TD("TD");
	const std::string DomainConstants::GENRE_TP("TP");
	const std::string DomainConstants::GENRE_PRATIQUE("PRATIQUE");
	const std::string DomainConstants::GENRE_THEORIE("THEORIE");
	const std::string DomainConstants::GENRE_ABSENCE("ABS");
	const std::string DomainConstants::GENRE_RETARD("RET");
	const std::string DomainConstants::GENRE_MISC("MISC");
	const std::string DomainConstants::GENRE_NOTE("NOTE");
	//
	const std::string DomainConstants::DEPARTEMENT_TYPE("departement");
	const std::string DomainConstants::GROUPE_TYPE("groupe");
	const std::string DomainConstants::UNITE_TYPE("unite");
	const std::string DomainConstants::MATIERE_TYPE("matiere");
	const std::string DomainConstants::ANNEE_TYPE("annee");
	const std::string DomainConstants::SEMESTRE_TYPE("semestre");
	const std::string DomainConstants::PERSON_TYPE("person");
	const std::string DomainConstants::ADMINISTRATORPERSON_TYPE("administratorperson");
	const std::string DomainConstants::ENSEIGNANTPERSON_TYPE("enseignantperson");
	const std::string DomainConstants::ETUDIANTPERSON_TYPE("etudiantperson");
	const std::string DomainConstants::ENSEIGNANTAFFECTATION_TYPE("enseignantaffectation");
	const std::string DomainConstants::ETUDIANTAFFECTATION_TYPE("etudiantaffectation");
	const std::string DomainConstants::GROUPEEVENT_TYPE("groupeevent");
	const std::string DomainConstants::ETUDIANTEVENT_TYPE("etudiantevent");
	const std::string DomainConstants::ETUDIANT_TYPE("etudiant");
	const std::string DomainConstants::ENSEIGNANT_TYPE("enseignant");
	const std::string DomainConstants::ADMINISTRATOR_TYPE("administrator");
	const std::string DomainConstants::SUPERPERSON_TYPE("superperson");
	//
	const std::string DomainConstants::ETUDIANTEVENT_PREFIX("TV");
	const std::string DomainConstants::GROUPEEVENT_PREFIX("GV");
	const std::string DomainConstants::ETUDIANTAFFECTATION_PREFIX("TA");
	const std::string DomainConstants::ENSEIGNANTAFFECTATION_PREFIX("EA");
	const std::string DomainConstants::PERSON_PREFIX("PS");
	const std::string DomainConstants::SEMESTRE_PREFIX("SM");
	const std::string DomainConstants::MATIERE_PREFIX("MT");
	const std::string DomainConstants::UNITE_PREFIX("UN");
	const std::string DomainConstants::GROUPE_PREFIX("GP");
	const std::string DomainConstants::ANNEE_PREFIX("AN");
	const std::string DomainConstants::DEPARTEMENT_PREFIX("DP");
	const std::string DomainConstants::ETUDIANT_PREFIX("ET");
	const std::string DomainConstants::ENSEIGNANT_PREFIX("EN");
	const std::string DomainConstants::ADMINISTRATOR_PREFIX("AD");
	///////////////////////////////////////////////////////
	//////////////////////////////
}// namespace geninfo
