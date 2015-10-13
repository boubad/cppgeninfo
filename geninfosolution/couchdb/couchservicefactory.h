#pragma once
#ifndef __COUCHSERVICEFACTORY_H__
#define __COUCHSERVICEFACTORY_H__
///////////////////////////////////
#include <iservicefactory.h>
/////////////////////////////////////
namespace geninfo {
	///////////////////////////////////////////
	class CouchServiceFactory : public IServiceFactory
	{
	public:
		CouchServiceFactory();
		CouchServiceFactory(const CouchServiceFactory &other);
		CouchServiceFactory & operator=(const CouchServiceFactory &other);
		~CouchServiceFactory();
	public:
		virtual std::shared_ptr<IDataManager> get_datamanager(const std::string &url, const std::string &database);
	};
	////////////////////////////////////
}// namespace geninfo
//////////////////////////////////////
#endif // __COUCHSERVICEFACTORY_H__
