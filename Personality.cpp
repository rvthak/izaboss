#include <iostream>
#include "Personality.hpp"


using namespace std;

Personality::~Personality(){
	// Personality dies
	isDead=1;

	// detach followers
	list<Follower *>::iterator itf;
	for(itf = followers.begin(); itf !=followers.end();itf++)
		(*itf)->detach();

	// detach items
	list<Item *>::iterator iti;
	for(iti = items.begin(); iti != items.end();iti++)
		(*iti)->detach();
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
	for(iti = items.begin(); iti != items.end();){
		if( (*iti)->loseDurability() ){ // durability reaches 0 => detach
			cout << " (!) Item destroyed..." << endl;
			items.remove(*iti);
			this->removeBuffs(*iti);
			(*iti)->detach();
			iti=items.begin();
		}else
			iti++;
	}
}

void Personality::performSeppuku(){
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

void Personality::printFull(){
	cout<<"Personality Card: ";
	BlackCard::print();
	cout<< "\t"<<"Attack: "<< attack
		<< "\n\t" << "Defence: " <<defence
		<< "\n\t" << "Honour: " << honour
		<< "\n\t" << "Followers: ";

	int i=0;
	if(followers.begin()==followers.end()){
		cout<<"NONE\n\t";
	}else{
		cout<<endl;
		list<Follower *>::iterator itf;
		for(itf = followers.begin();itf != followers.end();itf++){
			i++;
			cout<< "\t\t" << i << ".";
			(*itf)->print();
		}
	}
	cout<<"\n\tItems: ";
	if(items.begin()==items.end()){
		cout<<"NONE"<<endl;
	}else{
		cout<<endl;
		list<Item *>::iterator iti;
		i=0;
		for(iti = items.begin();iti != items.end();iti++){
			i++;
			cout<< "\t\t" << i << ".";
			(*iti)->print();
		}
	}

}

int Personality::follower_cas(unsigned int limit){
	if( followers.begin()==followers.end() ){
		return 1;
	}
	cout<<"\tFollower casualties:"<<endl;
	list<Follower *>::iterator itf;
	Follower *tod = NULL;
	for(itf = followers.begin();itf != followers.end();){
		if((*itf)->getAttackBonus()>=limit){
			(*itf)->print();
			tod = *itf;
			followers.remove(*itf);
			this->removeBuffs(*itf);
			(*itf)->detach();
			itf = followers.begin();
		}else
			itf++;
	}
	return 0;
}

void Personality::removeBuffs(Follower *f){
	if(f->checkUpgraded()){
		attack-= (f->getAttackBonus() + f->getEffectBonus());
		defence-= (f->getDefenceBonus()+ f->getEffectBonus());
	}
	else{
		attack-= f->getAttackBonus();
		defence-= f->getDefenceBonus();
	}
}

void Personality::removeBuffs(Item *it){
	if(it->checkUpgraded()){
		attack-= (it->getAttackBonus() + it->getEffectBonus());
		defence-= (it->getDefenceBonus()+ it->getEffectBonus());
	}
	else{
		attack-= it->getAttackBonus();
		defence-= it->getDefenceBonus();
	}
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
