#pragma once
#ifndef __GENINFOCONSTANTS_H
#define __GENINFOCONSTANTS_H
////////////////////////////////
#include "gendefs.h"
///////////////////////////////
namespace geninfo {
	////////////////////////////////
	class GenInfoConstants
	{
	public:
		
		//
		static const string_t TYPE;
		static const string_t ID;
		static const string_t REV;
		static const string_t STATUS;
		static const string_t DESCRIPTION;
		static const string_t DELETED;
		//
		static const string_t SIGLE;
		static const string_t NAME;
		static const string_t ORDER;
		static const string_t GENRE;
		static const string_t CHILDRENIDS;
		static const string_t STARTDATE;
		static const string_t ENDDATE;
		static const string_t MODULE;
		static const string_t COEFFICIENT;
		static const string_t ECS;
		static const string_t DEPARTEMENTID;
		static const string_t UNITEID;
		static const string_t ANNEEID;
		static const string_t MATIEREID;
		static const string_t SEMESTREID;
		static const string_t GROUPEID;
		static const string_t ENSEIGNANTID;
		static const string_t ETUDIANTID;
		static const string_t ENSEIGNANTAFFECTATIONID;
		static const string_t ETUDIANTAFFECTATIONID;
		static const string_t GROUPEEVENTID;
		static const string_t LOCATION;
		static const string_t STARTTIME;
		static const string_t ENDTIME;
		static const string_t MINNOTE;
		static const string_t MAXNOTE;
		static const string_t NOTE;
		static const string_t USERNAME;
		static const string_t PASSWORD;
		static const string_t FIRSTNAME;
		static const string_t LASTNAME;
		static const string_t EMAIL;
		static const string_t PHONE;
		static const string_t DOSSIER;
		static const string_t SEXE;
		static const string_t BIRTHDATE;
		static const string_t VILLE;
		static const string_t ETABLISSEMENT;
		static const string_t SERIEBAC;
		static const string_t OPTIONBAC;
		static const string_t MENTIONBAC;
		static const string_t ETUDESSUPERIEURES;
		static const string_t APB;
		static const string_t REDOUBLANT;
		//
		static const string_t DEPARTEMENTSIDS;
		static const string_t UNITESIDS;
		static const string_t ANNEESIDS;
		static const string_t SEMESTRESIDS;
		static const string_t MATIERESIDS;
		static const string_t AFFECTATIONSIDS;
		static const string_t EVENTSIDS;
		static const string_t ADMINISTRATORSIDS;
		static const string_t ENSEIGNANTSIDS;
		static const string_t ETUDIANTSIDS;
		static const string_t GROUPESIDS;
		//
		static const string_t GENRE_PROMO;
		static const string_t GENRE_TD;
		static const string_t GENRE_TP;
		static const string_t GENRE_PRATIQUE;
		static const string_t GENRE_THEORIE;
		static const string_t GENRE_ABSENCE;
		static const string_t GENRE_RETARD;
		static const string_t GENRE_MISC;
		static const string_t GENRE_NOTE;
		//
		static const string_t DEPARTEMENT_TYPE;
		static const string_t GROUPE_TYPE;
		static const string_t UNITE_TYPE;
		static const string_t MATIERE_TYPE;
		static const string_t ANNEE_TYPE;
		static const string_t SEMESTRE_TYPE;
		static const string_t PERSON_TYPE;
		static const string_t ADMINISTRATORPERSON_TYPE;
		static const string_t ENSEIGNANTPERSON_TYPE;
		static const string_t ETUDIANTPERSON_TYPE;
		static const string_t ENSEIGNANTAFFECTATION_TYPE;
		static const string_t ETUDIANTAFFECTATION_TYPE;
		static const string_t GROUPEEVENT_TYPE;
		static const string_t ETUDIANTEVENT_TYPE;
		static const string_t ETUDIANT_TYPE;
		static const string_t ENSEIGNANT_TYPE;
		static const string_t ADMINISTRATOR_TYPE;
		static const string_t SUPERPERSON_TYPE;
		//
		static const string_t ETUDIANTEVENT_PREFIX;
		static const string_t GROUPEEVENT_PREFIX;
		static const string_t ETUDIANTAFFECTATION_PREFIX;
		static const string_t ENSEIGNANTAFFECTATION_PREFIX;
		static const string_t PERSON_PREFIX;
		static const string_t SEMESTRE_PREFIX;
		static const string_t MATIERE_PREFIX;
		static const string_t UNITE_PREFIX;
		static const string_t GROUPE_PREFIX;
		static const string_t ANNEE_PREFIX;
		static const string_t DEPARTEMENT_PREFIX;
		static const string_t ETUDIANT_PREFIX;
		static const string_t ENSEIGNANT_PREFIX;
		static const string_t ADMINISTRATOR_PREFIX;
	};
}// namespace geninfo
//////////////////////////
#endif // __GENINFOCONSTANTS_H
