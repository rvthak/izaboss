#include "Holding.hpp"

using namespace std;

bool Holding::getMineType(){
	if(isMine==0){ return 0; }
	else if(harvestValue==3){ return 1; }
	else if(harvestValue==5){ return 2; }
	else if(harvestValue==10){ return 3; }
	else{ return -1; }
}

void Holding::chain(Holding *target){
	int type=getMineType(); // Get the mine type
	
	if(type==1){ // Mine => NO sub
		upperHolding=target;
		target->subHolding=this;

		// Handle chain income benefits
		harvestValue=harvestValue+2;

		if(target->upperHolding!=NULL){ // full chain complete
			upperHolding->harvestValue=(upperHolding->harvestValue-5)*2;
			upperHolding->upperHolding->harvestValue=upperHolding->upperHolding->harvestValue/2*3;
		}
		else{ // chain with gold mine only
			upperHolding->harvestValue=upperHolding->harvestValue+4;
		}
	}
	else if(type==2){ // Gold Mine
		if(target->getMineType()==1){ // chain to a mine
			subHolding=target;
			target->upperHolding=this;

			// Handle chain income benefits
			harvestValue=harvestValue+4;
			subHolding->harvestValue=subHolding->harvestValue+2;
		}
		else{ // chain to a crystal mine
			upperHolding=target;
			target->subHolding=this;

			// Handle chain income benefits
			harvestValue=harvestValue+5;
			upperHolding->harvestValue=upperHolding->harvestValue*2;
		}
	}
	else if(type==3){ // Crystal Mine
		subHolding=target;
		target->upperHolding=this;

		// Handle chain income benefits
		if(target->subHolding!=NULL){ // full chain complete
			harvestValue=harvestValue*3;
			subHolding->harvestValue=(subHolding->harvestValue-4)*2;
		}
		else{ // chain with gold only
			harvestValue=harvestValue*2; 
			subHolding->harvestValue=subHolding->harvestValue+5;
		}
	}
	else{ // error do nothing
		return;	// That is never supposed to happen
	}
}

unsigned int Stronghold::honcnt=1;

Stronghold::Stronghold(){
	name="Stronghold";
	cost=0;
	isTapped=0;
	isRevealed=0;
	upperHolding=NULL;
	subHolding=NULL;
	harvestValue=0;

	// Get a unique honour to determine the game turns
	honour=honcnt++;
	
	// Get a money value in [5, 15]
	money=5+rand()%(15-5+1);

	// Get an amount of initial defence according to your money value for game balance
	initialDefense=20-money;
}


Plain::Plain(const string n){
	name=n;
	cost=2;
	isTapped=0;

	isRevealed=0;

	harvestValue=2;
	upperHolding=NULL;
	subHolding=NULL;
}


Mine::Mine(const string n){
	name=n;
	cost=5;
	isTapped=0;

	isMine=1;
	isRevealed=0;

	harvestValue=3;
	upperHolding=NULL;
	subHolding=NULL;
}

GoldMine::GoldMine(const string n){
	name=n;
	cost=7;
	isTapped=0;

	isMine=1;
	isRevealed=0;

	harvestValue=5;
	upperHolding=NULL;
	subHolding=NULL;
}


CrystalMine::CrystalMine(const string n){
	name=n;
	cost=12;
	isTapped=0;

	isMine=1;
	isRevealed=0;

	harvestValue=10;
	upperHolding=NULL;
	subHolding=NULL;
}


Farmland::Farmland(const string n){
	name=n;
	cost=3;
	isTapped=0;

	isRevealed=0;

	harvestValue=4;
	upperHolding=NULL;
	subHolding=NULL;
}

GiftAndFavour::GiftAndFavour(const string n){
	name=n;
	cost=2;
	isTapped=0;

	isRevealed=0;

	harvestValue=2;
	upperHolding=NULL;
	subHolding=NULL;
}
