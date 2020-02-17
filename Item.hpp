#ifndef ITEM
#define ITEM

#include "Card.hpp"

class Item : public GreenCard
{
	public:
		Item(){}
		~Item(){}
		int loseDurability(){ durability--; return (durability==0); }
		unsigned int getDurability();
		virtual int getType()const{ return 4; }
	protected:
		unsigned int durability;
};

//==============================================

class Katana : public Item
{
public:
	Katana(const std::string n);
	~Katana(){}
};

class Spear : public Item
{
public:
	Spear(const std::string n);
	~Spear(){}
};

class Bow : public Item
{
public:
	Bow(const std::string n);
	~Bow(){}
};

class Ninjato : public Item
{
public:
	Ninjato(const std::string n);
	~Ninjato(){}
};

class Wakizashi : public Item
{
public:
	Wakizashi(const std::string n);
	~Wakizashi(){}
};

#endif