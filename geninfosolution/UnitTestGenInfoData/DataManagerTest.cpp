#include "stdafx.h"
#include "CppUnitTest.h"
//////////////////////////////
#include <couchservicefactory.h>
#include <idatamanager.h>
//////////////////////////////////
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace geninfo;
using namespace std;
////////////////////////////////////////////////////////////
namespace UnitTestGenUtils
{
	TEST_CLASS(DataManagerTest)
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
		TEST_METHOD(TestServerInfo)
		{
			IDataManager *pMan = m_man.get();
			Assert::IsNotNull(pMan);
			Value val = pMan->server_info();
			Assert::IsTrue(val.is_object());
			Object *pObj = val.as_object();
			Assert::IsNotNull(pObj);
			Assert::IsTrue(pObj->has_field("couchdb"));
			string ss = pObj->get_string("couchdb");
			Assert::AreEqual("Welcome", ss.c_str());
			string s = val.to_string();
			Logger::WriteMessage(s.c_str());
		}//TestServerInfo

	};
	string DataManagerTest::m_baseUrl("http://localhost:5984");
	string DataManagerTest::m_database("test");
	std::shared_ptr<IDataManager> DataManagerTest::m_man;
}
