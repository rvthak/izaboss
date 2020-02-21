#ifndef _PERSONALITY
#define _PERSONALITY

#include <list>
#include "Card.hpp"
#include "Item.hpp"
#include "Follower.hpp"

class Personality : public BlackCard
{
	public:
		Personality(){}
		~Personality();

		void untap(){ isTapped=0; }
		void usedItems();
		void performSeppuku();

		unsigned int getAttack()const{ return attack; }
		unsigned int getDefence()const{ return defence; }
		unsigned int getHonour()const{ return honour; }
		bool getIsDead()const{ return isDead; }

		bool CheckFollowerCapacity(){ return (followerAmount()<honour); }
		bool CheckItemCapacity(){ return (itemAmount()<honour); }

		unsigned int followerAmount();
		unsigned int itemAmount();

		void equip(Follower *f);
		void equip(Item *i);

		void print()const;
		void printFull();

		void follower_cas(unsigned int);
		
		virtual int getType()const{ return 1; }
    
	protected:
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