#ifndef ITEM
#define ITEM

#include "Card.hpp"

class Item : public GreenCard
{
	public:
		Item();
		~Item();

	private:
	
	
};

//==============================================

class Katana : public Item
{
public:
	Katana();
	~Katana();
	
};

class Spear : public Item
{
public:
	Spear();
	~Spear();
	
};

class Bow : public Item
{
public:
	Bow();
	~Bow();
	
};

class Ninjato : public Item
{
public:
	Ninjato();
	~Ninjato();
	
};

class Wakizashi : public Item
{
public:
	Wakizashi();
	~Wakizashi();
	
};

#endif