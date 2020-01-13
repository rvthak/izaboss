#ifndef PERSONALITY
#define PERSONALITY

#include "Card.hpp"

class Personality : public BlackCard
{
	public:
		Personality();
		~Personality();
		unsigned int getHonour(){
			return honour;
		};
		void equip(Follower *f){
			followers.push_back(f);
		};
		void equip(Item *i){
			items.push_back(i);
		};
		void print();
		
	private:
		unsigned int attack;
		unsigned int defence;
		unsigned int honour;
		bool isDead;

		list<Follower *> followers;
		list<Item *> items;
	
};

//==============================================

class Attacker : public Personality
{
public:
	Attacker();
	~Attacker();
	
};

class Defender : public Personality
{
public:
	Defender();
	~Defender();
	
};

class Champion : public Personality
{
public:
	Champion();
	~Champion();
	
};


class Chancellor : public Personality
{
public:
	Chancellor();
	~Chancellor();
	
};

class Shogun : public Personality
{
public:
	Shogun();
	~Shogun();
	
};

#endif