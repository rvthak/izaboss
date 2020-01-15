#ifndef PERSONALITY
#define PERSONALITY

#include <list>
#include "Card.hpp"
#include "Follower.hpp"
#include "Item.hpp"

class Personality : public BlackCard
{
	public:
		Personality(){}
		~Personality(){}

		unsigned int getAttack()const{ return attack; }
		unsigned int getDefence()const{ return defence; }
		unsigned int getHonour()const{ return honour; }
		bool getIsDead()const{ return isDead; }

		void equip(Follower *f){ followers.push_back(f); }
		void equip(Item *i){ items.push_back(i); }
		void print()const;
		
		virtual int getType()const{ return 1; }
    
	private:
		unsigned int attack;
		unsigned int defence;
		unsigned int honour;
		bool isDead;

		std::list<Follower *> followers;
		std::list<Item *> items;
};

//==============================================

class Attacker : public Personality
{
public:
	Attacker(const std::string n);
	~Attacker(){}
};

class Defender : public Personality
{
public:
	Defender(const std::string n);
	~Defender(){}
};

class Champion : public Personality
{
public:
	Champion(const std::string n);
	~Champion(){}
};


class Chancellor : public Personality
{
public:
	Chancellor(const std::string n);
	~Chancellor(){}
};

class Shogun : public Personality
{
public:
	Shogun(const std::string n);
	~Shogun(){}
};

#endif