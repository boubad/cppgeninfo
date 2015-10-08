#pragma once
#ifndef __BASEITEM_H__
#define __BASEITEM_H__
//////////////////////////////
#include "rootobject.h"
/////////////////////////////////
namespace geninfo {
	////////////////////////////////
	class IDatabaseManager;
	class Departement;
	//////////////////////////////
	class BaseItem : public BaseDocument
	{
	public:
		BaseItem();
		BaseItem(const value &oMap);
		BaseItem(const BaseItem &other);
		BaseItem & operator=(const BaseItem &other);
		virtual ~BaseItem();
	public:
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
		virtual bool is_storeable(void) const;
		virtual string_t start_key(void) const;
		virtual string_t end_key(void) const;
		virtual string_t create_id(void) const;
	public:
		void check_id(void);
	public:
		string_t status(void) const;
		void status(const string_t &s);
		string_t description(void) const;
		void description(const string_t &s);
	public:
		virtual pplx::task<bool> save(IDatabaseManager &oMan);
		virtual pplx::task<bool> remove(IDatabaseManager &oMan);
	}; // class baseitem
	///////////////////////
	class NamedItem : public BaseItem {
	public:
		NamedItem();
		NamedItem(const value &oMap);
		NamedItem(const NamedItem &other);
		NamedItem & operator=(const NamedItem &other);
		virtual ~NamedItem();
	public:
		string_t name(void) const;
		void name(const string_t &s);
	public:
		virtual bool is_storeable(void) const;
	};// class NamedItem
	class SigleNamedItem : public NamedItem {
	public:
		SigleNamedItem();
		SigleNamedItem(const value &oMap);
		SigleNamedItem(const SigleNamedItem &other);
		SigleNamedItem & operator=(const SigleNamedItem &other);
		virtual ~SigleNamedItem();
	public:
		string_t sigle(void) const;
		void sigle(const string_t &s);
	public:
		virtual bool is_storeable(void) const;
		virtual string_t create_id(void) const;
	};// class SigleNamedItem
	/////////////////////////////
	class DepSigleNamedItem : public SigleNamedItem {
	public:
		DepSigleNamedItem();
		DepSigleNamedItem(const Departement &oDep);
		DepSigleNamedItem(const value &oMap);
		DepSigleNamedItem(const DepSigleNamedItem &other);
		DepSigleNamedItem & operator=(const DepSigleNamedItem &other);
		virtual ~DepSigleNamedItem();
	public:
		string_t departementid(void) const;
		pplx::task<std::shared_ptr<Departement> > get_departement(IDatabaseManager &oMan);
	public:
		virtual bool is_storeable(void) const;
		virtual string_t start_key(void) const;
		virtual string_t create_id(void) const;
	protected:
		void departementid(const string_t &s);
	};// Depclass NamedItem
	  /////////////////////////////
}// namespace geninfo
///////////////////////////
#endif // __BASEITEM_H__
