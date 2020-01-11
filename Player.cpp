#include "Player.hpp"

Player::Player()
:numberOfProvinces(4),stronghold(5,5,5){
	fateDeck = my_deck.createFateDeck();
	dynastyDeck = my_deck.createDynastyDeck();

	list<BlackCard *>::iterator itb;
	itb = dynastyDeck->begin();
	for(int i=0; i<numberOfProvinces ; i++){
		provinces.push_back(*itb);
		dynastyDeck->pop_front();
		itb = dynastyDeck->begin();
	}
	for(int i=0;i<6;i++)
		hand[i];
}

Player::~Player(){

}

Player::untapEverything(){
	list<BlackCard *>::iterator itb;
	for(itb = army->begin(); itb != provinces->end(); itb++){

	}
}