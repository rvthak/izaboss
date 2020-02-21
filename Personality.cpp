#include <iostream>
#include "Personality.hpp"


using namespace std;

Personality::~Personality(){
	list<Follower *>::iterator itf;
	for(itf = followers.begin(); itf !=followers.end();itf++)
		delete(*itf);
	list<Item *>::iterator iti;
	for(iti = items.begin(); iti != items.end();iti++)
		delete (*iti);
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

void Personality::damage(){
	list<Item *>::iterator iti;

	// Personality loses honnor
	honour--;

	// Items lose durability
	for(iti = items.begin(); iti != items.end(); iti++){
		if( (*iti)->loseDurability() ){ // durability reaches 0 => detach
			cout << " (!) Item destroyed..." << endl;
			items.remove(*iti);
			(*iti)->detach();
			iti=items.begin();
		}
	}
}

void Personality::performSeppuku(){
	list<Follower *>::iterator itf;
	list<Item *>::iterator iti;

	// Personality dies
	isDead=1;

	// detach followers
	for(itf = followers.begin(); itf != followers.end(); itf++){
		followers.remove(*itf);
		(*itf)->detach();
		itf=followers.begin();
		
	}

	// detach items
	for(iti = items.begin(); iti != items.end(); iti++){
		items.remove(*iti);
		(*iti)->detach();
		iti=items.begin();
		
	}

	delete this;
}

void Personality::equip(Follower *f){
	attack+=f->getAttackBonus();
	defence+=f->getDefenceBonus();
	followers.push_back(f);
}
void Personality::equip(Item *i){
	attack+=i->getAttackBonus();
	defence+=i->getDefenceBonus();
	items.push_back(i);
}

void Personality::print()const{
	cout<< "Personality Card: ";
	BlackCard::print();
	cout<< "\t" << "Attack: "<< attack
		<< "\n\t" << "Defence: " << defence
		<< "\n\t" << "Honour: " << honour<<endl;
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
