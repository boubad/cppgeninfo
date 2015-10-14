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
		TEST_METHOD(TestDatabaseInfo)
		{
			IDataManager *pMan = m_man.get();
			Assert::IsNotNull(pMan);
			string database("test");
			Value val = pMan->database_info(database);
			Assert::IsTrue(val.is_object());
			Object *pObj = val.as_object();
			Assert::IsNotNull(pObj);
			Assert::IsTrue(pObj->has_field("db_name"));
			string ss = pObj->get_string("db_name");
			Assert::AreEqual("test", ss.c_str());
			string s = val.to_string();
			Logger::WriteMessage(s.c_str());
		}//TestDatabaseInfo
		TEST_METHOD(TestExistsDatabase)
		{
			IDataManager *pMan = m_man.get();
			Assert::IsNotNull(pMan);
			string database("test");
			bool bRet = pMan->exists_database(database);
			Assert::IsTrue(bRet);
		}//TestExistsDatabase
		TEST_METHOD(TestGetAllDbs)
		{
			IDataManager *pMan = m_man.get();
			Assert::IsNotNull(pMan);
			vector<string> oVec = pMan->get_all_dbs();
			for (auto it = oVec.begin(); it != oVec.end(); ++it) {
				string s = *it;
				string ss = s + std::string("\r\n");
				Logger::WriteMessage(ss.c_str());
			}
		}//TestGetAllDbs
		TEST_METHOD(TestGetUuids)
		{
			IDataManager *pMan = m_man.get();
			Assert::IsNotNull(pMan);
			vector<string> oVec = pMan->get_uuids(5);
			for (auto it = oVec.begin(); it != oVec.end(); ++it) {
				string s = *it;
				string ss = s + std::string("\r\n");
				Logger::WriteMessage(ss.c_str());
			}
		}//TestGetUuids
		TEST_METHOD(TestGetAllDocs)
		{
			IDataManager *pMan = m_man.get();
			Assert::IsNotNull(pMan);
			string start;
			string end;
			end += "zzz";
			Value val = pMan->read_docs_range(start, end);
			string s = val.to_string();
			Logger::WriteMessage(s.c_str());
		}//TestGetAllDocs
		TEST_METHOD(TestGetAllDocsIds)
		{
			IDataManager *pMan = m_man.get();
			Assert::IsNotNull(pMan);
			string start;
			string end;
			end += "zzz";
			vector<string> oVec = pMan->read_docs_ids_range(start, end);
			for (auto it = oVec.begin(); it != oVec.end(); ++it) {
				string s = *it;
				string ss = s + std::string("\r\n");
				Logger::WriteMessage(ss.c_str());
			}
		}//TestGetAllDocsIds
		TEST_METHOD(TestInsertUpdateDoc)
		{
			IDataManager *pMan = m_man.get();
			Assert::IsNotNull(pMan);
			PObject o = Value::create_object();
			Object *p = o.get();
			Assert::IsNotNull(p);
			p->set_string("_id", "testid");
			p->set_string("sval", "blablabla");
			Value doc(o);
			//
			Value val = pMan->insert_doc(doc);
			string s = val.to_string();
			Logger::WriteMessage(s.c_str());
		}//TestInsertUpdateDoc
		TEST_METHOD(TestDeleteDoc)
		{
			IDataManager *pMan = m_man.get();
			Assert::IsNotNull(pMan);
			PObject o = Value::create_object();
			Object *p = o.get();
			Assert::IsNotNull(p);
			p->set_string("_id", "testid");
			p->set_string("sval", "blablabla");
			Value doc(o);
			//
			Value val = pMan->insert_doc(doc);
			string s = val.to_string();
			Logger::WriteMessage(s.c_str());
			//
			val = pMan->remove_doc(doc);
			s = val.to_string();
			Logger::WriteMessage(s.c_str());
		}//TestDeleteDoc
		TEST_METHOD(TestReadDoc)
		{
			IDataManager *pMan = m_man.get();
			std::string id("testid");
			Assert::IsNotNull(pMan);
			PObject o = Value::create_object();
			Object *p = o.get();
			Assert::IsNotNull(p);
			p->set_string("_id", id);
			p->set_string("sval", "blablabla");
			Value doc(o);
			//
			Value val = pMan->insert_doc(doc);
			string s = val.to_string();
			Logger::WriteMessage(s.c_str());
			//
			val = pMan->read_doc(id, true, true);
			s = val.to_string();
			Logger::WriteMessage(s.c_str());
		}//TestReadDoc
		TEST_METHOD(TestBulkMaintains)
		{
			size_t n = 10;
			IDataManager *pMan = m_man.get();
			vector<Value> docs;
			for (size_t i = 0; i < n; ++i) {
				stringstream os;
				os << (i + 1);
				string si = os.str();
				while (si.length() < 2) {
					si = "0" + si;
				}
				string id = "test" + si;
				PObject o = Value::create_object();
				Object *p = o.get();
				Assert::IsNotNull(p);
				p->set_string("_id", id);
				p->set_string("sval", "blablabla" + id);
				Value doc(o);
				docs.push_back(doc);
			}//i
			//
			Value val = pMan->maintains_docs(docs);
			string s = val.to_string();
			Logger::WriteMessage(s.c_str());
			val = pMan->maintains_docs(docs, true);
			s = val.to_string();
		   Logger::WriteMessage(s.c_str());
		}//TestBulkMaintains
		TEST_METHOD(TestReadArray)
		{
			size_t n = 10;
			IDataManager *pMan = m_man.get();
			vector<string> ids;
			for (size_t i = 0; i < n; ++i) {
				stringstream os;
				os << (i + 1);
				string si = os.str();
				while (si.length() < 2) {
					si = "0" + si;
				}
				string id = "test" + si;
				ids.push_back(id);
			}//i
			 //
			Value val = pMan->read_docs_array(ids);
			string s = val.to_string();
			Logger::WriteMessage(s.c_str());
		}//TestReadArray
	};
	string DataManagerTest::m_baseUrl("http://localhost:5984");
	string DataManagerTest::m_database("test");
	std::shared_ptr<IDataManager> DataManagerTest::m_man;
}
