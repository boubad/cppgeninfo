#include "stdafx.h"
#include "CppUnitTest.h"
//////////////////////////////
#include "TestFixture.h"
//////////////////////////////////
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace geninfo;
using namespace std;
////////////////////////////////////////////////////////////
namespace UnitTestGenUtils
{
	TEST_CLASS(TestFixtureTest)
	{
	protected:
		static string m_baseUrl;
		static string m_database;
		static std::unique_ptr<TestFixture> m_fixture;
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			m_fixture.reset(new TestFixture());
			Assert::IsNotNull(m_fixture.get());
		}
		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			m_fixture.reset();
		}
		TEST_METHOD(TestFixtureGetDataManager)
		{
			TestFixture *p = m_fixture.get();
			Assert::IsNotNull(p);
			Assert::IsNotNull(p->dataManager());
		}//TestFixtureGetDataManager
		TEST_METHOD(TestFixtureGetDepartement)
		{
			TestFixture *p = m_fixture.get();
			Assert::IsNotNull(p);
			Assert::IsNotNull(p->departement());
		}//TestFixtureGetDepartement
		TEST_METHOD(TestFixtureGetUnites)
		{
			TestFixture *p = m_fixture.get();
			Assert::IsNotNull(p);
			vector<shared_ptr<Unite>> oVec = p->unites();
			size_t n = oVec.size();
			Assert::IsTrue(n >= 4);
		}//TestFixtureGetUnites
		TEST_METHOD(TestFixtureGetGroupes)
		{
			TestFixture *p = m_fixture.get();
			Assert::IsNotNull(p);
			vector<shared_ptr<Groupe>> oVec = p->groupes();
			size_t n = oVec.size();
			Assert::IsTrue(n >= 9);
		}//TestFixtureGetGroupes
	};
	string TestFixtureTest::m_baseUrl("http://localhost:5984");
	string TestFixtureTest::m_database("test");
	std::unique_ptr<TestFixture> TestFixtureTest::m_fixture;
}
