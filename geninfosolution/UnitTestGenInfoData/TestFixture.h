#pragma once
#pragma once
#ifndef __TESTFIXTURE_H__
#define __TESTFIXTURE_H__
//////////////////////////////
#include <domainconstants.h>
#include <idatamanager.h>
#include <departement.h>
#include <groupe.h>
#include <unite.h>
#include <annee.h>
#include <semestre.h>
///////////////////////////
namespace UnitTestGenUtils {
	///////////////////////////////
	class TestFixture
	{
	public:
		TestFixture();
		TestFixture(const std::string &baseUrl, const std::string &databaseName);
		~TestFixture();
	public:
		std::string baseUrl(void);
		std::string databaseName(void);
		geninfo::IDataManager *dataManager(void);
		geninfo::Departement *departement(void);
		std::vector<std::shared_ptr<geninfo::Unite>> &unites(void);
		std::vector<std::shared_ptr<geninfo::Groupe>>& groupes(void);
		std::vector<std::shared_ptr<geninfo::Annee>>& annees(void);
	private:
		std::string m_baseUrl;
		std::string m_databaseName;
		std::shared_ptr<geninfo::IDataManager> m_dataManager;
		std::shared_ptr<geninfo::Departement> m_departement;
		std::vector<std::shared_ptr<geninfo::Unite>> m_unites;
		std::vector<std::shared_ptr<geninfo::Groupe>> m_groupes;
		std::vector<std::shared_ptr<geninfo::Annee>> m_annees;
	}; // class TestFixture
} // namespaceUnitTestGenUtils
/////////////////////
#endif // __TESTFIXTURE_H__
