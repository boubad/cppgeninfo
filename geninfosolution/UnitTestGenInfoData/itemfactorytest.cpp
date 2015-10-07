#include "stdafx.h"
#include "CppUnitTest.h"
//////////////////////////////
#include <itemfactory.h>
#include <departement.h>
#include <couchdatamanager.h>
//////////////////////////////////
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace geninfo;
////////////////////////////////////////////////////////////
namespace UnitTestGenUtils
{
	TEST_CLASS(ItemFactoryTest)
	{
	protected:
		CouchDataManager m_man;
	public:

		TEST_METHOD(TestDepartement)
		{
			Departement p;
			p.sigle(U("testdepsigle"));
			p.name(U("testdepname"));
			p.description(U("testdepdesc"));
			p.status(U("teststatus"));
			{
				stringstream_t os;
				os << p;
				string_t s = os.str() + U("\r\n");
				Logger::WriteMessage(s.c_str());
			}
			bool bRet = p.save(this->m_man).get();
			Assert::IsTrue(bRet);
			{
				stringstream_t os;
				os << p;
				string_t s = os.str() + U("\r\n");
				Logger::WriteMessage(s.c_str());
			}
			BaseItem *px = this->m_man.read_item(p.id(), true, true).get();
			Assert::IsNotNull(px);
			Departement *pp = dynamic_cast<Departement *>(px);
			Assert::IsNotNull(pp);
			std::unique_ptr<Departement> o(pp);
			{
				stringstream_t os;
				os << *pp;
				string_t s = os.str() + U("\r\n");
				Logger::WriteMessage(s.c_str());
			}
			bRet = pp->remove(this->m_man).get();
			Assert::IsTrue(bRet);
			BaseItem *py = this->m_man.read_item(p.id(), true, true).get();
			Assert::IsNull(py);
		}//TestGetServerInfo

	};
}
