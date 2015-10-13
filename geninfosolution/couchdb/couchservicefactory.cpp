#include "stdafx.h"
#include "couchservicefactory.h"
#include "couchdbdatamanager.h"
//////////////////////////////////////////
namespace geninfo {
	CouchServiceFactory::CouchServiceFactory()
	{
	}
	CouchServiceFactory::CouchServiceFactory(const CouchServiceFactory & /*other*/) {

	}
	CouchServiceFactory & CouchServiceFactory::operator=(const CouchServiceFactory & /*other*/) {
		return (*this);
	}

	CouchServiceFactory::~CouchServiceFactory()
	{
	}
	std::shared_ptr<IDataManager> CouchServiceFactory::get_datamanager(const std::string &url, const std::string &database) {
		IDataManager *p = new CouchDBDataManager(url, database);
		std::shared_ptr<IDataManager> oRet(p);
		return oRet;
	}
}// namespace geninfo
