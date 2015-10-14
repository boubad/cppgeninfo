#include "stdafx.h"
#include "CppUnitTest.h"
//////////////////////////////
#include <couchservicefactory.h>
#include <departement.h>
#include <domainconstants.h>
//////////////////////////////////
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace geninfo;
using namespace std;
////////////////////////////////////////////////////////////
namespace UnitTestGenUtils
{
	TEST_CLASS(DepartementTest)
	{
	protected:
		static string m_baseUrl;
		static string m_database;
		static std::shared_ptr<IDataManager> m_man;
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			CouchServiceFactory oFact;
			m_man = oFact.get_datamanager(m_baseUrl, m_database);
			Assert::IsNotNull(m_man.get());
		}
		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			m_man.reset();
		}
		TEST_METHOD(TestDepartementDefaultConstructor)
		{
			Departement p;
			Assert::AreEqual(DomainConstants::DEPARTEMENT_TYPE.c_str(), p.type().c_str());
			Assert::AreEqual(DomainConstants::DEPARTEMENT_PREFIX.c_str(), p.store_prefix().c_str());
			Assert::IsTrue(p.description().empty());
			Assert::IsTrue(p.status().empty());
			Assert::IsTrue(p.text().empty());
			Assert::IsTrue(p.id().empty());
			Assert::IsTrue(p.rev().empty());
			Assert::IsFalse(p.is_storeable());
			Assert::IsFalse(p.is_empty());
			//
			Assert::IsTrue(p.sigle().empty());
			Assert::IsTrue(p.name().empty());
		}//TestDepartementDefaultConstructor
		TEST_METHOD(TestDepartementConstructor)
		{
			Departement p;
			p.id("testid");
			p.rev("testrev");
			p.sigle("testsigle");
			p.name("testname");
			p.status("teststatus");
			p.description("testdesc");
			//
			Assert::AreEqual(DomainConstants::DEPARTEMENT_TYPE.c_str(), p.type().c_str());
			Assert::AreEqual(DomainConstants::DEPARTEMENT_PREFIX.c_str(), p.store_prefix().c_str());
			Assert::AreEqual("testdesc",p.description().c_str());
			Assert::AreEqual("TESTSTATUS",p.status().c_str());
			Assert::AreEqual("Testname",p.text().c_str());
			Assert::IsTrue(p.has_id());
			Assert::IsTrue(p.has_rev());
			Assert::IsTrue(p.is_storeable());
			Assert::IsFalse(p.is_empty());
			//
			Assert::AreEqual("TESTSIGLE",p.sigle().c_str());
			Assert::AreEqual("Testname", p.name().c_str());
		}//TestDepartementDefaultConstructor
		TEST_METHOD(TestDepartementSaveLoadRemove)
		{
			Departement p;
			p.id("testid");
			p.sigle("testsigle");
			p.name("testname");
			p.status("teststatus");
			p.description("testdesc");
			//
			IDataManager *pMan = m_man.get();
			Assert::IsNotNull(pMan);
			bool bRet = p.save(*pMan);
			Assert::IsTrue(bRet);
			Departement px;
			px.id("testid");
			bRet = px.load(*pMan);
			Assert::IsTrue(bRet);
			bRet = p.remove(*pMan);
			Assert::IsTrue(bRet);
		}//TestDepartementSaveLoadRemove
	};
	string DepartementTest::m_baseUrl("http://localhost:5984");
	string DepartementTest::m_database("test");
	std::shared_ptr<IDataManager> DepartementTest::m_man;
}
