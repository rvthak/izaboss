#include <iostream>
#include "Item.hpp"

using namespace std;

unsigned int Item::getDurability(){ return durability; }

void Item::print()const{
	cout << "Item: ";
	GreenCard::print();
	cout << "\t" << "Card Durability: "<< durability <<endl;
}

void Item::detach(){
	delete this;
}

Katana::Katana(const string n){
	name=n;
	cost=0;
	isTapped=0;
	attackBonus=2;
	defenceBonus=0;
	min_honour=1;
	effectBonus=1;
	effectCost=2;
	durability=3;
	cardText="Venerated japanese divine blade";
}

Spear::Spear(const string n){
	name=n;
	cost=0;
	isTapped=0;
	attackBonus=0;
	defenceBonus=2;
	min_honour=1;
	effectBonus=1;
	effectCost=2;
	durability=3;
	cardText="A moderate-range melee lethal weapon"; 
}

Bow::Bow(const string n){
	name=n;
	cost=2;
	isTapped=0;
	attackBonus=2;
	defenceBonus=2;
	min_honour=2;
	effectBonus=3;
	effectCost=4;
	durability=5;
	cardText="It's the power of the bow that determines the flight of the arrow";
}

Ninjato::Ninjato(const string n){
	name=n;
	cost=4;
	isTapped=0;
	attackBonus=3;
	defenceBonus=3;
	min_honour=3;
	effectBonus=2;
	effectCost=2;
	durability=4;
	cardText="The sword of a Shinobi";
}

Wakizashi::Wakizashi(const string n){
	name=n;
	cost=8;
	isTapped=0;
	attackBonus=5;
	defenceBonus=5;
	min_honour=3;
	effectBonus=3;
	effectCost=3;
	durability=8;
	cardText="Japanese sword and the honor of a Samurai";
}
