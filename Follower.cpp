#include "Follower.hpp"

using namespace std;

// TODO add description text here

Footsoldier::Footsoldier(const string n){
	name=n;
	cost=0;
	isTapped=0;
	attackBonus=2;
	defenceBonus=0;
	min_honour=1;
	effectBonus=1;
	effectCost=2;
	cardText=""; 
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
	cardText="";
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
	cardText="";
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
	cardText="";
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
	cardText="";
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
	cardText="";
}