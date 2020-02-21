#ifndef _ITEM
#define _ITEM

#include "Card.hpp"

class Item : public GreenCard {

	public:
		Item(){}
		~Item(){}

		unsigned int getDurability();	// Get the current durability of the item
		int loseDurability(){ durability--; return (durability==0); }	// Damage the item
		
		void detach();	// Detach the item from its Personality (deletes it)

		virtual void print()const;
		virtual int getType()const{ return 4; }
		
	protected:
		unsigned int durability; // The items durability
};

//==============================================

class Katana : public Item {
	public:
		Katana(const std::string n);
		~Katana(){}
};

class Spear : public Item {
	public:
		Spear(const std::string n);
		~Spear(){}
};

class Bow : public Item {
	public:
		Bow(const std::string n);
		~Bow(){}
};

class Ninjato : public Item {
	public:
		Ninjato(const std::string n);
		~Ninjato(){}
};

class Wakizashi : public Item {
	public:
		Wakizashi(const std::string n);
		~Wakizashi(){}
};

#endif