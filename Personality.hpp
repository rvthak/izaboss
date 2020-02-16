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

		void untap(){ isTapped=0; }
		void usedItems();
		void performSeppuku();

		unsigned int getAttack()const{ return attack; }
		unsigned int getDefence()const{ return defence; }
		unsigned int getHonour()const{ return honour; }
		bool getIsDead()const{ return isDead; }

		bool CheckFollowerCapacity()const{ return (followerAmount()<honour); }
		bool CheckItemCapacity()const{ return (itemAmount()<honour); }

		unsigned int followerAmount()const;
		unsigned int itemAmount()const;

		int equip(Follower *f);
		int equip(Item *i);
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