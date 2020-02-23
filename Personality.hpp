#ifndef _PERSONALITY
#define _PERSONALITY

#include <list>
#include "Card.hpp"
#include "Item.hpp"
#include "Follower.hpp"

class Personality : public BlackCard {

	public:
		Personality(){}
		~Personality();

		void damage();			 		// Damage the personality (reduce honour + damage items)
		void performSeppuku();		 	// Personality kills itself (deletes personality)
		int follower_cas(unsigned int); // Upon Victory with casualties some followers get casted away returns 1 if none where deleted
	
		// Basic getters
		unsigned int getAttack(bool);
		unsigned int getDefence(bool);
		unsigned int getHonour()const{ return honour; }
		bool getIsDead()const{ return isDead; }

		// Check if a Personality can equip more items/followers
		bool CheckItemCapacity(){ return (itemAmount()<honour); }
		bool CheckFollowerCapacity(){ return (followerAmount()<honour); }

		// Get the amount of items/followers
		unsigned int itemAmount();
		unsigned int followerAmount();

		// Equip the parameter item/follower 
		void equip(Item *i);
		void equip(Follower *f);
	
		// Print Personality ( ! including equipped Items and followers )
		void printFull();

		virtual void print()const;
		virtual int getType()const{ return 1; }
    
	protected:
		unsigned int attack;	// Personality's attack
		unsigned int defence;	// Personality's defence
		unsigned int honour;	// Personality's honour
		bool isDead;			// Personality Dead flag

		std::list<Item *> items;			// A list of the Personality's Items
		std::list<Follower *> followers;	// A list of the Personality's followers
};

//==============================================

class Attacker : public Personality {
	public:
		Attacker(const std::string n);
		~Attacker(){}
};

class Defender : public Personality {
	public:
		Defender(const std::string n);
		~Defender(){}
};

class Champion : public Personality {
	public:
		Champion(const std::string n);
		~Champion(){}
};


class Chancellor : public Personality {
	public:
		Chancellor(const std::string n);
		~Chancellor(){}
};

class Shogun : public Personality {
	public:
		Shogun(const std::string n);
		~Shogun(){}
};

#endif
