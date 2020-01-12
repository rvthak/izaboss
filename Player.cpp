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
		hand[i]=NULL;
}

Player::~Player(){

}

void Player::untapEverything(){
	list<Personality *>::iterator ita;
	for(ita = army.begin(); ita != army.end(); ita++){
		(*ita)->untap();
	}
	list<Holding *>::iterator ith;
	for(ith = holdings.begin(); ith != holdings.end(); ith++){
		(*ith)->untap();
	}
}

void Player::drawFateCard(){
	list<GreenCard *>::iterator itg;
	if((itg = fateDeck->begin())!= fateDeck->end()){
		bool flag =0;
		for(int i=0; i<6 ;i++){
			if(hand[i]!=NULL){
				flag = 1;
				break;
			}
		}
		if(flag){
			int i;
			for(i=0;hand[i]!=NULL;i++);
			hand[i] = (*itg);
			fateDeck->pop_front();			
		}
		else
			cout<<"Your hand is full! You can't have more than 6 cards on your hand"<<endl;
	}else
		cout<<"Fate deck is empty! You can't draw a card"<<endl;
}

void Player::revealProvince(){
	list<Province *>::iterator itp;
	for(itp = provinces.begin();itp != provinces.end();itp++)
		(*itp)->revealCard();
}

void Player::printHand(){
	for(int i=0; i<6 ;i++)
		if(hand[i]!=NULL)
			hand[i]->print();
}

void Player::printProvinces(){
	list<Province *>::iterator itp;
	for(itp = provinces.begin();itp != provinces.end();itp++)
		(*itp)->print();
}