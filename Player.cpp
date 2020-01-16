#include "Player.hpp"
#include <cstlib>
#include <ctime>

Player::Player()
:numberOfProvinces(4){
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
unsigned int Player::getMoney(){
	list<Holding *>::iterator ith;
	unsigned int money= stronghold.getMoney();
	for(ith = holdings.begin();ith != holdings.end();ith++)
		if(!((*ith)->tapped()))
			money += (*ith)->getHarvestValue();
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

unsigned int Player::getPlayerDefence(){
	list<Personality *>::iterator ita;
	unsigned int sum=getInitialDefense();
	for(ita = army.begin(); ita != army.end();ita++)
		if(!((*ita)->tapped()))
			sum += (*ita)->getDefence();
	return sum;
}

unsigned int Player::GetProvinceAmount(){
	return numberOfProvinces;
}

void Player::attack(Player &target, unsigned int pno){
	if(this->getPlayerAttack()-target.getPlayerDefence() >= target.getInitialDefense()){
		target.dcasualties(0);
		target.destroyProvince(pno);
		this->celebrate();
		cout<<"Attacker's absolute victory"<<endl;
	}else if(this->getPlayerAttack() > target.getPlayerDefence()){
		target.dcasualties(0);
		target.destroyProvince(pno);
		this->acasualties(this->getPlayerAttack()-target.getPlayerDefence());
		this->celebrate();
		cout<<"Attacker's victory"<<endl;
	}else if(this->getPlayerAttack() == target.getPlayerDefence()){
		target.dcasualties(0);
		this->acasualties(0);
		cout<<"Battle ended with a draw"<<endl;
	}else{
		target.dcasualties(target.getPlayerDefence() - this->getPlayerAttack());
		this->acasualties(0);
		cout<<"Defender's victory"<<endl;
	}
}

void Player::destroyProvince(unsigned int pno){
	list<Province *>::iterator itp;
	itp = provinces.begin();
	for(int i=1;i<pno && itp != provinces.end();i++)
		itp++;
	provinces.remove(*itp);
	delete *itp;
	numberOfProvinces--;
}

void Player::dcasualties(unsigned int limit){
	list<Personality *>::iterator ita;
	for(ita = army.begin(); ita != army.end();ita++)
		if(!((*ita)->tapped()) && (*ita)->getAttack()>=limit){
			army.remove(*ita);
			delete *ita;
			ita = army.begin();
		}
}

void Player::celebrate(){
	list<Personality *>::iterator ita;
	for(ita = attackForce.begin(); ita != attackForce.end();ita++){
		(*ita)->tap();
		army.push_back(*ita);
		attackForce.remove(*ita);
		ita = attackForce.begin();
	}
}

void Player::acasualties(unsigned int limit){
	list<Personality *>::iterator ita;
	for(ita = attackForce.begin(); ita != attackForce.end();ita++)
		if((*ita)->getAttack()>=limit){
			attackForce.remove(*ita);
			delete *ita;
			ita = attackForce.begin();
		}
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
	else{
		if((*hold)->getMineType())
			this->ChainCreation(*hold);
		else
			holdings.push_back(*hold);
	}
	(*itp)->detach();
	list<BlackCard *>::iterator itd;
	itd = dynastyDeck->begin();
	(*itp)->attach(*itd);
	dynastyDeck->pop_front();
}

void Player::ChainCreation(Holding *nhold){
	srand(time(NULL));
	list<Holding *>::iterator ith;
	Holding *toChain = NULL;
	Holding *toChain2 = NULL;
	switch(nhold->getMineType()){
		case 1:
			for(ith = holdings.begin(); ith != holdings.end(); ith++)
				if((*ith)->getMineType()==2){
					if(!(*ith)->hasSub() && (*ith)->hasUpper()){
						toChain = *ith;
						break;
					}
					else(!(*ith)->hasSub()){
						if(toChain!=NULL && rand()%2==1)
							toChain = *ith;
						else if(toChain==NULL)
							toChain = *ith;
					}
				}
			if(toChain==NULL)
				holdings.push_back(nhold);
			else
				toChain->chain(nhold);
			break;
		case 2:
			bool flag =0;
			for(ith = holdings.begin(); ith != holdings.end(); ith++)
					if((*ith)->getMineType() == 1 && !(*ith)->hasUpper()){
						if(!flag){
							list<Holding *>iterator::ith2;
							for(ith2 = holdings.begin(); ith2 != holdings.end();ith2++)
								if(((*ith2)->getMineType() == 3) && !(*ith2)->hasSub()){
									toChain2 = *ith2;
									break;								
								}
							if(toChain2!=NULL){
								toChain = *ith;
								nhold->chain(toChain);
								nhold->chain(toChain2);
								holdings.remove(toChain);
								holdings.remove(toChain2);
								break;
							}else{
								flag = 1;
								if(toChain != NULL && rand()%2==1)
									toChain = *ith;
								else if(toChain==NULL)
									toChain = *ith;
							}
						}
						else
							if(toChain != NULL && rand()%2==1)
								toChain = *ith;
							else if(toChain==NULL)
								toChain = *ith;
					}
					else if((*ith)->getMineType() == 3 && !(*ith)->hasSub()){
						if(!flag){
							list<Holding *>iterator::ith2;
							for(ith2 = holdings.begin(); ith2 != holdings.end();ith2++)
								if(((*ith2)->getMineType() == 1) && !(*ith2)->hasUpper()){
									toChain2 = *ith2;
									break;								
								}
							if(toChain2!=NULL){
								toChain = *ith;
								nhold->chain(toChain);
								nhold->chain(toChain2);
								holdings.remove(toChain);
								holdings.remove(toChain2);
								holdings.push_back(nhold);
								break;
							}else{
								flag = 1;
								if(toChain != NULL && rand()%2==1)
									toChain = *ith;
								else if(toChain==NULL)
									toChain = *ith;
							}
						}
						else
							if(toChain != NULL && rand()%2==1)
								toChain = *ith;
							else if(toChain==NULL)
								toChain = *ith;
					}
			if(toChain2==NULL && toChain==NULL)
				holdings.push_back(nhold);
			else if(toChain2==NULL && toChain!=NULL)
				nhold->chain(toChain);
			break;
		case 3:
			for(ith = holdings.begin(); ith != holdings.end(); ith++)
				if((*ith)->getMineType()==2){
					if(!(*ith)->hasUpper() && (*ith)->hasSub()){
						toChain = *ith;
						break;
					}
					else(!(*ith)->hasUpper()){
						if(toChain!=NULL && rand()%2==1)
							toChain = *ith;
						else if(toChain==NULL)
							toChain = *ith;
					}
				}
			if(toChain==NULL)
				holdings.push_back(nhold);
			else
				toChain->chain(nhold);
			break;
	}
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