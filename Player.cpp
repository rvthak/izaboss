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
	for(int i=0;i<7;i++)
		hand[i]=NULL;
	money = stronghold.getMoney();
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
		for(int i=0; i<7 ;i++){
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
			cout<<"Your hand is full! You can't have more than 7 cards on your hand"<<endl;
	}else
		cout<<"Fate deck is empty! You can't draw a card"<<endl;
}

void Player::revealProvince(){
	list<Province *>::iterator itp;
	for(itp = provinces.begin();itp != provinces.end();itp++){
		(*itp)->revealCard();
	}
}

void Player::printHand(){
	for(int i=0; i<7 ;i++)
		if(hand[i]!=NULL)
			hand[i]->print();
}

void Player::printProvinces(){
	list<Province *>::iterator itp;
	for(itp = provinces.begin();itp != provinces.end();itp++)
		(*itp)->print();
}

bool Player::hasArmy(){
	return (army.begin()!= army.end());
}

void Player::printArmy(){
	list<Personality *>::iterator ita;
	for(ita = army.begin(); ita != army.end(); ita++){
		(*ita)->print();
	}
}

unsigned int Player::HandCardsNo(){
	int k=0;
	for(int i=0;i<7;i++)
		if(hand[i]!=NULL)
			k++;
}

unsigned int Player::ArmyCardsNo(){
	int k=0;
	list<Personality *>::iterator ita;
	for(ita = army.begin();ita != army.end();ita++)
		k++;
	return k;
}

unsigned int Player::HoldingCardsNo(){
	int k=0;
	list<Holding *>::iterator ith;
	for(ith = holdings.begin();ith != holdings.end();ith++)
		k++;
	return k;
}

unsigned int Player::GetHandCardCost(unsigned int no){
	int j=0;
	for(int i=0;i<no && j<7;j++){
		if(hand[j]!=NULL)
			i++;
	}
	return hand[j-1]->getCost();
}

unsigned int Player::GetArmyMemberHonour(unsigned int no){
	list<Personality *>::iterator ita;
	ita = army.begin()
	for(int i=0;i<no && ita != army.end();i++)
		ita++;
	ita--;
	return (*ita)->getHonour();
}

unsigned int Player::GetHandMemberHonour(unsigned int no){
	int j=0;
	for(int i=0;i<no && j<7;j++){
		if(hand[j]!=NULL)
			i++;
	}
	return hand[j-1]->getHonour();
}

void Player::buyAndAssign(unsigned int hno, unsigned int ano){
	int j=0;
	int cost = GetHandCardCost(hno);
	pay_cost(cost);
	list<Army *>::iterator ita;
	ita = army.begin();
	for(int i=1;i<ano && ita != army.end();i++)
		ita++;
	for(int i=0;i<hno && j<7;j++){
		if(hand[j] != NULL)
			i++;
	}
	if(getDesision("Do you want to upgrade your new card? (y/n)"))
		if(getMoney()>=(cost = hand[j-1]->getEffectCost())){
			hand[j-1]->effectBonus();
			pay_cost(cost);
		}else
			cout<<"You don't have the money to upgrade teme"<<endl;
	Follower **follow;
	Item **item;
	getCorrectType(hand[j-1],follow,item);
	if(*follow != NULL)
		(*ita)->equip(*follow);
	else
		(*ita)->equip(*item);
	hand[j-1]=NULL;
}

void Player::pay_cost(int cost){
	list<Holding *>::iterator ith;
	int index,i;
	while(cost >0){
		index = choosefrom(HoldingCardsNo());
		i=1;
		for(ith = holdings.begin();i<index && ith != holdings.end();ith++)
			i++;
		if((*ith)->tap())
			cost -=(*ith)->getHarvestValue();
		else
			cost +=(*ith)->getHarvestValue();
	}
//allaje ta lefta
}

void Player::printTapArmy(){
	list<Personality *>::iterator ita;
	for(ita = army.begin(); ita != army.end(); ita++){
		(*ita)->print();
		cout<<'\t';
		if((*ita)->tapped())
			cout<<"Tapped"<<endl;
		else
			cout<<"Not Tapped"<<endl;
	}
}

void Player::TapArmyCard(unsigned int ano){
	list<Personality *>::iterator ita;
	ita = army.begin();
	for(int i=1;i<ano && ita != army.end();i++)
		ita++;
	if(!((*ita)->tap())){
		cout<<"This card is already tapped"<<endl;
		(*ita)->tap();
	}
}

void Player::printUntappedArmy(){
	list<Personality *>::iterator ita;
	for(ita = army.begin();ita != army.end();ita++)
		if(!((*ita)->tapped()))
			(*ita)->print();
}

unsigned int Player::ActiveArmyCardsNo(){
	list<Personality *>::iterator ita;
	unsigned int k=0;
	for(ita = army.begin();ita != army.end();ita++)
		if(!((*ita)->tapped()))
			k++;
}

void Player::AddToAttackForce(unsigned int ano){
	list<Personality *>::iterator ita;
	ita = army.begin();
	for(int i=0; i<ano && ita!=army.end(); ita++)
		if(!((*ita)->tapped()))
			i++;
	ita--;
	attackForce.push_back() = (*ita);
	army.remove(*ita);
}

unsigned int Player::getPlayerAttack(){
	list<Personality *>::iterator ita;
	unsigned int sum=0;
	for(ita = attackForce.begin(); ita != attackForce.end();ita++)
		sum += (*ita)->getAttack();
	return sum;
}

unsigned int Player::GetProvinceAmount(){
	return numberOfProvinces;
}

//eqononmy_phase
unsigned int Player::GetProvinceCardCost(unsigned int pno){
	list<Province *>::iterator itp;
	itp = provinces.begin();
	for(int i=1;i<pno && itp != provinces.end();i++)
		itp++;
	return (*itp)->getCardCost();
}

void Player::buyAndUse(unsigned int pno){
	list<Province *>::iterator itp;
	itp = provinces.begin();
	for(int i=1;i<pno && itp != provinces.end();i++)
		itp++;
	int cost = GetProvinceCardCost(pno);
	pay_cost(cost);
	Personality **person;
	Holding **hold;
	getCorrectType((*itp)->getAttachedCard(),person,hold);
	if(*person !=NULL)
		army.push_back(*person);
	else
		holdings.push_back(*hold);
	(*itp)->detach();
	list<BlackCard *>::iterator itd;
	itd = dynastyDeck->begin();
	(*itp)->attach(*itd);
	dynastyDeck->pop_front();
}

void Player::discardSurplusFateCards(){
	int k;
	for(int i=0;i<7;i++)
		if(hand[i]!=NULL)
			k++;
	printHand();
	if(k==7){
		k=choosefrom(7);
		delete hand[i];
	}
}