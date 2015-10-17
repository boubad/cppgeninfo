#include "stdafx.h"
#include "CppUnitTest.h"
#include "TestFixture.h"
/////////////////////////
#include <couchservicefactory.h>
#include <couchdbdatamanager.h>
//////////////////////////////////
namespace UnitTestGenUtils {
	///////////////////////////////
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;
	using namespace geninfo;
	using namespace std;
	////////////////////////////////
	std::string STRING_OK("ok");
	//////////////////////////////////
	TestFixture::TestFixture():m_baseUrl("http://localhost:5984"),m_databaseName("test")
	{
	}

	TestFixture::TestFixture(const std::string &baseUrl, const std::string &databaseName):m_baseUrl(baseUrl),m_databaseName(databaseName) {
	}
	TestFixture::~TestFixture()
	{
	}
	std::string TestFixture::baseUrl(void) {
		return this->m_baseUrl;
	}
	std::string TestFixture::databaseName(void) {
		return this->m_databaseName;
	}
	geninfo::IDataManager *TestFixture::dataManager(void) {
		IDataManager *pRet = this->m_dataManager.get();
		if (pRet == nullptr) {
			CouchServiceFactory oFact;
			this->m_dataManager = oFact.get_datamanager(this->m_baseUrl, this->m_databaseName);
			pRet = this->m_dataManager.get();
			Assert::IsNotNull(pRet);
			bool bRet = pRet->exists_database(this->m_databaseName);
			if (!bRet) {
				Value vr = pRet->create_database(this->m_databaseName);
				Assert::IsTrue(vr.is_object());
				Object *pObj = vr.as_object();
				Assert::IsNotNull(pObj);
				Assert::IsTrue(pObj->has_field(STRING_OK));
				bRet = pObj->get_bool(STRING_OK);
				Assert::IsTrue(bRet);
			}
		}
		return pRet;
	}
	geninfo::Departement *TestFixture::departement(void) {
		Departement *pRet = this->m_departement.get();
		if (pRet == nullptr) {
			Departement p;
			p.sigle("test");
			p.name("testDepartement");
			p.check_id();
			IDataManager *pMan = this->dataManager();
			Assert::IsNotNull(pMan);
			if (p.load(*pMan)) {
				this->m_departement = std::make_shared<Departement>(p);
			}
			else {
				bool bRet = p.save(*pMan);
				Assert::IsTrue(bRet);
				this->m_departement = std::make_shared<Departement>(p);
			}
			pRet = this->m_departement.get();
			Assert::IsNotNull(pRet);
		}// pRet
		return pRet;
	}
	std::vector<std::shared_ptr<geninfo::Unite>> &TestFixture::unites(void) {
		if (!this->m_unites.empty()) {
			return this->m_unites;
		}
		IDataManager *pMan = this->dataManager();
		Assert::IsNotNull(pMan);
		Departement *pDep = this->departement();
		Assert::IsNotNull(pDep);
		this->m_unites = pDep->unites(*pMan);
		if (this->m_unites.size() >= 4) {
			return this->m_unites;
		}
		{
			Unite un(*pDep);
			un.sigle("UE1");
			un.name("Physique");
			un.order(1);
			bool bRet = un.save(*pMan);
			Assert::IsTrue(bRet);
			Matiere mat(un);
			mat.genre("theorie");
			mat.sigle("optique");
			mat.name("optique");
			mat.order(1);
			mat.coefficient(2.0);
			bRet = mat.save(*pMan);
			Assert::IsTrue(bRet);
		}
		{
			Unite un(*pDep);
			un.sigle("UE2");
			un.name("Spécialites");
			un.order(2);
			bool bRet = un.save(*pMan);
			Assert::IsTrue(bRet);
			Matiere mat(un);
			mat.genre("theorie");
			mat.sigle("thloc");
			mat.name("Thermique des locaux");
			mat.order(2);
			mat.coefficient(3.0);
			bRet = mat.save(*pMan);
			Assert::IsTrue(bRet);
		}
		{
			Unite un(*pDep);
			un.sigle("UE3");
			un.name("Formation generale");
			un.order(3);
			bool bRet = un.save(*pMan);
			Assert::IsTrue(bRet);
			Matiere mat(un);
			mat.genre("parique");
			mat.sigle("tpinfo");
			mat.name("TP Informatique");
			mat.order(3);
			mat.coefficient(4.0);
			bRet = mat.save(*pMan);
			Assert::IsTrue(bRet);
		}
		{
			Unite un(*pDep);
			un.sigle("UE4");
			un.name("Pratique");
			un.order(4);
			bool bRet = un.save(*pMan);
			Assert::IsTrue(bRet);
		}
		this->m_unites = pDep->unites(*pMan);
		return (this->m_unites);
	}// unites
	std::vector<std::shared_ptr<geninfo::Groupe>>& TestFixture::groupes(void) {
		if (!this->m_groupes.empty()) {
			return this->m_groupes;
		}
		IDataManager *pMan = this->dataManager();
		Assert::IsNotNull(pMan);
		Departement *pDep = this->departement();
		Assert::IsNotNull(pDep);
		this->m_groupes = pDep->groupes(*pMan);
		if (this->m_groupes.size() >= 9) {
			return this->m_groupes;
		}
		Groupe grpa(*pDep);
		grpa.sigle("a");
		grpa.name("Groupe A");
		grpa.genre(Groupe::GENRE_TP);
		grpa.check_id();
		bool bRet = grpa.save(*pMan);
		Assert::IsTrue(bRet);
		Groupe grpb(*pDep);
		grpb.sigle("b");
		grpb.name("Groupe B");
		grpb.genre(Groupe::GENRE_TP);
		grpb.check_id();
		bRet = grpb.save(*pMan);
		Assert::IsTrue(bRet);
		Groupe grpab(*pDep);
		grpab.sigle("ab");
		grpab.name("Groupe AB");
		grpab.genre(Groupe::GENRE_TD);
		grpab.check_id();
		grpab.add_child(grpa);
		grpab.add_child(grpb);
		bRet = grpab.save(*pMan);
		Assert::IsTrue(bRet);
		//
		Groupe grpc(*pDep);
		grpc.sigle("c");
		grpc.name("Groupe C");
		grpc.genre(Groupe::GENRE_TP);
		grpc.check_id();
		bRet = grpc.save(*pMan);
		Assert::IsTrue(bRet);
		Groupe grpd(*pDep);
		grpd.sigle("d");
		grpd.name("Groupe D");
		grpd.genre(Groupe::GENRE_TP);
		grpd.check_id();
		bRet = grpd.save(*pMan);
		Assert::IsTrue(bRet);
		Groupe grpcd(*pDep);
		grpcd.sigle("cd");
		grpcd.name("Groupe CD");
		grpcd.genre(Groupe::GENRE_TD);
		grpcd.check_id();
		grpcd.add_child(grpc);
		grpcd.add_child(grpd);
		bRet = grpcd.save(*pMan);
		Assert::IsTrue(bRet);
		//
		Groupe grpe(*pDep);
		grpe.sigle("e");
		grpe.name("Groupe E");
		grpe.genre(Groupe::GENRE_TP);
		grpe.check_id();
		bRet = grpe.save(*pMan);
		Assert::IsTrue(bRet);
		Groupe grpee(*pDep);
		grpee.sigle("ee");
		grpee.name("Groupe EE");
		grpee.genre(Groupe::GENRE_TD);
		grpee.check_id();
		bRet = grpee.save(*pMan);
		Assert::IsTrue(bRet);
		//
		Groupe grpp(*pDep);
		grpp.sigle("P1");
		grpp.name("Promo S1");
		grpp.genre(Groupe::GENRE_PROMO);
		grpp.check_id();
		grpp.add_child(grpab);
		grpp.add_child(grpcd);
		grpp.add_child(grpee);
		bRet = grpp.save(*pMan);
		Assert::IsTrue(bRet);
		//
		this->m_groupes = pDep->groupes(*pMan);
		return (this->m_groupes);
	}// groupes
	std::vector<std::shared_ptr<geninfo::Annee>> &TestFixture::annees(void) {
		if (!this->m_annees.empty()) {
			return this->m_annees;
		}
		IDataManager *pMan = this->dataManager();
		Assert::IsNotNull(pMan);
		Departement *pDep = this->departement();
		Assert::IsNotNull(pDep);
		this->m_annees = pDep->annees(*pMan);
		if (this->m_annees.size() >= 2) {
			return this->m_annees;
		}
		{
			Annee un(*pDep);
			un.start_date("2014-09-01");
			un.end_date("2015-06-30");
			un.sigle("2014_2015");
			un.name("Annee 2014-2015");
			bool bRet = un.save(*pMan);
			Assert::IsTrue(bRet);
			Semestre sem1(un);
			sem1.start_date("2014-09-01");
			sem1.end_date("2015-01-15");
			sem1.sigle("S1_S3_2014");
			sem1.name("S1/S3 2014-2015");
			bRet = sem1.save(*pMan);
			Assert::IsTrue(bRet);
			Semestre sem2(un);
			sem2.start_date("2015-01-16");
			sem2.end_date("2015-06-30");
			sem2.sigle("S2_S4_2015");
			sem2.name("S2/S4 2014-2015");
			bRet = sem2.save(*pMan);
			Assert::IsTrue(bRet);
		}
		{
			Annee un(*pDep);
			un.start_date("2015-09-01");
			un.end_date("2016-06-30");
			un.sigle("2015_2016");
			un.name("Annee 2015-2016");
			bool bRet = un.save(*pMan);
			Assert::IsTrue(bRet);
		}
		this->m_annees = pDep->annees(*pMan);
		return (this->m_annees);
	}// annees
	////////////////////////////////
} // namespace UnitTestGenUtils 