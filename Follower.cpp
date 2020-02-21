#include <iostream>
#include "Follower.hpp"


using namespace std;

// TODO add description text here
void Follower::print()const{
	cout << "Follower: ";
	GreenCard::print();
}

void Follower::detach(){
	delete this;
}

Footsoldier::Footsoldier(const string n){
	name=n;
	cost=0;
	isTapped=0;
	attackBonus=2;
	defenceBonus=0;
	min_honour=1;
	effectBonus=1;
	effectCost=2;
	cardText="Each scar teaches him more than a library"; 
}

Archer::Archer(const string n){
	name=n;
	cost=0;
	isTapped=0;
	attackBonus=0;
	defenceBonus=2;
	min_honour=1;
	effectBonus=1;
	effectCost=2;
	cardText="Precise and effective on defending the province from long distances";
}

Cavalry::Cavalry(const string n){
	name=n;
	cost=3;
	isTapped=0;
	attackBonus=4;
	defenceBonus=2;
	min_honour=3;
	effectBonus=3;
	effectCost=4;
	cardText="Dont worry tha Cavalry is here";
}

Bushido::Bushido(const string n){
	name=n;
	cost=8;
	isTapped=0;
	attackBonus=8;
	defenceBonus=8;
	min_honour=6;
	effectBonus=3;
	effectCost=8;
	cardText="The way of the samurai";
}

Sieger::Sieger(const string n){
	name=n;
	cost=5;
	isTapped=0;
	attackBonus=3;
	defenceBonus=3;
	min_honour=2;
	effectBonus=2;
	effectCost=3;
	cardText="CHAAAAARGE";
}

Atakebune::Atakebune(const string n){
	name=n;
	cost=3;
	isTapped=0;
	attackBonus=4;
	defenceBonus=2;
	min_honour=3;
	effectBonus=3;
	effectCost=4;
	cardText="Their structure above the surface is fully covered by iron,and they are worth admiring";
}
