#pragma once
#ifndef __MATIERE_H__
#define __MATIERE_H__
/////////////////////////////
#include "baseitem.h"
/////////////////////////////
namespace geninfo {
	/////////////////////////////////////
	class Unite;
	//////////////////////////////////////
	class Matiere : public SigleNamedItem
	{
	public:
		static const string_t MATIERE_TYPE;
		static const string_t MATIERE_THEORIE;
		static const string_t MATIERE_PRATIQUE;
	public:
	public:
		Matiere();
		Matiere(const Unite &oUnite);
		Matiere(const value &oMap);
		Matiere(const Matiere &other);
		Matiere & operator=(const Matiere &other);
		virtual ~Matiere();
	public:
		string_t uniteid(void) const;
		string_t genre(void) const;
		void genre(const string_t &s);
		size_t order(void) const;
		void order(size_t n);
		double coefficient(void) const;
		void coefficient(double s);
		double ecs(void) const;
		void ecs(double s);
		string_t module(void) const;
		void module(const string_t &s);
		pplx::task<std::shared_ptr<Unite> > get_unite(IDatabaseManager &oMan);
	public:
		virtual string_t start_key(void) const;
		virtual string_t create_id(void) const;
		virtual bool is_storeable(void) const;
		virtual string_t type(void) const;
		virtual string_t store_prefix(void) const;
	protected:
		void uniteid(const string_t &s);
	};
}// namespace geninfo
 /////////////////////////
////////////////////////////
#endif // __MATIERE_H__
