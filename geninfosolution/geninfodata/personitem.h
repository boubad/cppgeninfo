#pragma once
#ifndef __PERSONITEM_H__
#define __PERSONITEM_H__
/////////////////////////////
#include "baseitem.h"
//////////////////////////////
namespace geninfo {
	class Person;
	//////////////////////////////
	class PersonItem : public BaseItem
	{
	public:
		PersonItem();
		PersonItem(const Person &oPers);
		PersonItem(const value &oMap);
		PersonItem(const PersonItem &other);
		PersonItem & operator=(const PersonItem &other);
		virtual ~PersonItem();
	public:
		string_t personid(void) const;
		string_t firstname(void) const;
		string_t lastname(void) const;
	public:
		pplx::task<std::shared_ptr<Person> > get_person(IDatabaseManager &oMan) const;
	public:
		virtual bool is_storeable(void) const;
		virtual pplx::task<bool> save(IDatabaseManager &oMan);
		virtual pplx::task<bool> remove(IDatabaseManager &oMan);
	protected:
		virtual void update_save(Person &oPers);
		virtual void update_remove(Person &oPers);
		void personid(const string_t &s);
	private:
		void firstname(const string_t &s);
		void lastname(const string_t &s);
	};
}// namespace geninfo
//////////////////////////////
#endif // __PERSONITEM_H__
