#include "Personality.hpp"

using namespace std;

void Personality::usedItems(){
	list<Item *>::iterator itm;
	for(itm = items.begin(); itm != items.end(); itm++){
		if( (*itm)->loseDurability() ){
			list.remove(*itm);
			delete itm;
			itm=items.begin();
		}
	}
}

unsigned int Personality::followerAmount(){
	unsigned int count=0;
	list<Follower *>::iterator flr;
	for(flr = followers.begin(); flr != followers.end(); flr++){
		count++;
	}
	return count;
}

unsigned int Personality::itemAmount(){
	unsigned int count=0;
	list<Item *>::iterator itm;
	for(itm = items.begin(); itm != items.end(); itm++){
		count++;
	}
	return count;
}

void Personality::equip(Follower *f){
	followers.push_back(f);
}
void Personality::equip(Item *i){
	items.push_back(i);
}


Attacker::Attacker(const string n){
	name=n;
	cost=5;
	isTapped=0;

	isRevealed=0;
	isDead=0;

	attack=3;
	defence=2;
	honour=2;
}

Defender::Defender(const string n){
	name=n;
	cost=5;
	isTapped=0;

	isRevealed=0;
	isDead=0;

	attack=2;
	defence=3;
	honour=2;
}

Champion::Champion(const string n){
	name=n;
	cost=30;
	isTapped=0;

	isRevealed=0;
	isDead=0;

	attack=20;
	defence=20;
	honour=12;
}

Chancellor::Chancellor(const string n){
	name=n;
	cost=15;
	isTapped=0;

	isRevealed=0;
	isDead=0;

	attack=5;
	defence=10;
	honour=8;
}

Shogun::Shogun(const string n){
	name=n;
	cost=15;
	isTapped=0;

	isRevealed=0;
	isDead=0;

	attack=10;
	defence=5;
	honour=8;
}
