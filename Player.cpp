#include <ctime>
#include <cstdlib>
#include "ui.hpp"
#include "Player.hpp"
#include "inputMgr.hpp"
#include "TypeConverter.hpp"

using namespace std;

Player::Player():numberOfProvinces(4){
	fateDeck = my_deck.createFateDeck();
	dynastyDeck = my_deck.createDynastyDeck();
	my_deck.deckShuffler(fateDeck);
	my_deck.deckShuffler(dynastyDeck);

	list<BlackCard *>::iterator itb;
	itb = dynastyDeck->begin();
	for(int i=0; i<numberOfProvinces ; i++){
		provinces.push_back(*itb);
		dynastyDeck->pop_front();
		itb = dynastyDeck->begin();
	}
	for(int i=0;i<7;i++)
		hand[i]=NULL;
	cout<<"\tA new player joined the game!"<<endl;
}

Player::~Player(){
	for(int i=0; i<7;i++)
		if(hand[i]!=NULL)
			delete hand[i];
	list<Holding *>::iterator ith;
	for(ith = holdings.begin(); ith != holdings.end(); ith++)
		delete *ith;
	list<Personality *>::iterator ita;
	for(ita = army.begin(); ita != army.end(); ita++)
		delete *ita;
}

// Starting phase =============================================

void Player::untapEverything(){
	cout<<"\t<> Untapping everything!"<<endl;
	list<Personality *>::iterator ita;
	stronghold.untap();
	Holding *another;
	for(ita = army.begin(); ita != army.end(); ita++){
		(*ita)->untap();
	}
	list<Holding *>::iterator ith;
	for(ith = holdings.begin(); ith != holdings.end(); ith++){
		(*ith)->untap();
		if((*ith)->hasUpper()){
			another = (*ith)->getUpperHolding();
			another->untap();
		}
		if((*ith)->hasSub()){
			another = (*ith)->getSubHolding();
			another->untap();
		}
	}
}
void Player::drawFateCard(){
	cout<<"\t<> Drawing a fate card!"<<endl;
	list<GreenCard *>::iterator itg;
	if((itg = fateDeck->begin())!= fateDeck->end()){
		int counter =0;
		for(int i=0; i<7 ;i++){
			if(hand[i]!=NULL){
				counter++;
				break;
			}
		}
		if(counter!=7){
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

void Player::revealProvinces(){
	cout<<"\t<> Revealing Provinces!"<<endl;
	list<BlackCard *>::iterator itp;
	for(itp = provinces.begin();itp != provinces.end();itp++){
		(*itp)->revealCard();
	}
}


// Print ===========================

void Player::print(){
	this->printHand();
	this->printArmy();
	this->printProvinces();
	this->printHoldings();
	cout<< "\t\t($) Money: " << this->getMoney()<<endl;
}

void Player::printHand(){
	cout<<"\t\t<> Cards on Hand: ";
	int j=0;
	for(int i=0; i<7 ;i++){
		if(hand[i]!=NULL){
			j++;
			cout << endl << " " << j << ".";
			hand[i]->print();
		}
	}
	if(j==0){ cout << "NONE" << endl; }	
}
void Player::printArmy(){
	list<Personality *>::iterator ita;
	int i=1;
	cout<<"\t\t<> Cards on Army: ";
	if( army.begin()==army.end() ){ cout << "NONE" << endl; return;}
	for(ita = army.begin(); ita != army.end(); ita++){
		cout << endl << " " << i << ".";
		(*ita)->print();
		i++;
	}
}
void Player::printArena(){
	list<Personality *>::iterator ita;
	int i=1;
	cout<<"\t\t<> Cards on Army: ";
	if( army.begin()==army.end() ){ cout << "NONE" << endl; return;}
	for(ita = army.begin(); ita != army.end(); ita++){
		cout << endl << " " << i << ".";
		(*ita)->printFull();
		i++;
	}
}
void Player::printProvinces(){
	cout<<"\t\t<> Provinces available:"<<endl;
	int i=1;
	list<BlackCard *>::iterator itp;
	for(itp = provinces.begin();itp != provinces.end();itp++){
		if((*itp)->getRevealed()){
			cout << " " << i << ".";
			(*itp)->print();
		}
		else{
			cout << "\t\t" << i << ": HIDDEN " << endl;
		}
		i++;
	}
}
void Player::printHoldings(){
	cout<<"\t\t<> Holdings owned: ";
	if( holdings.begin()==holdings.end() ){
		cout << "NONE" << endl; return; 
	}else
		cout<<endl;
	list<Holding *>::iterator ith;
	Holding *h;
	ith = holdings.begin();
	for(int i=1; ith != holdings.end(); i++){
		h = *ith;
		if((*ith)->hasUpper()){
			cout<< " " << i << ".";
			h = (*ith)->getUpperHolding();
			h->print();
			h = *ith;
			i++;
		}
		cout<< " " << i <<".";
		h->print();
		if((*ith)->hasSub()){
			i++;
			cout<< " " << i <<".";
			h = (*ith)->getSubHolding();
			h->print();
		}
		ith++;
	}
}

void Player::printTapHoldings(){
	cout<<"\t\t<> Holdings available: "<< endl;
	if( holdings.begin()==holdings.end() ){
		if( stronghold.tapped()){
			cout << "NONE" << endl;
		}
		else{
			cout << " 1. Stronghold:" <<endl;
			cout << "\tHavest value: " << stronghold.getMoney() << endl;
			cout << "\t(!) Not Tapped" << endl;
		}
		return;
	}else{
		cout<<endl;
	}

	list<Holding *>::iterator ith;
	Holding *h;
	ith = holdings.begin();
	int i;
	for(i=1; ith != holdings.end(); i++){
		h = *ith;

		if((*ith)->hasUpper()){
			cout<< " " << i << ".";
			h = (*ith)->getUpperHolding();
			h->print();
			if((*ith)->getUpperHolding()->tapped())
				cout<<"\t(!) Tapped"<<endl;
			else
				cout<<"\t(!) Not Tapped"<<endl;
			h = *ith;
			i++;
		}

		cout << " " << i <<".";
		h->print();
		if((*ith)->tapped())
			cout<<"\t(!) Tapped"<<endl;
		else
			cout<<"\t(!) Not Tapped"<<endl;
		
		if((*ith)->hasSub()){
			i++;
			cout<< " " << i <<".";
			h = (*ith)->getSubHolding();
			h->print();
			if( (*ith)->getSubHolding()->tapped())
				cout<<"\t(!) Tapped"<<endl;
			else
				cout<<"\t(!) Not Tapped"<<endl;
		}
		ith++;
	}
	if( stronghold.tapped()){
		cout << " " << i << ". Stronghold:" <<endl;
		cout << "\tHavest value: " << stronghold.getMoney() << endl;
		cout << "\t(!) Tapped" << endl;
	}
	else{
		cout << " " << i << ". Stronghold:" <<endl;
		cout << "\tHavest value: " << stronghold.getMoney() << endl;
		cout << "\t(!) Not Tapped" << endl;
	}
}

void Player::printTapArmy(){
	list<Personality *>::iterator ita;
	int i=0;
	for(ita = army.begin(); ita != army.end(); ita++){
		i++;
		cout << " " << i << ". ";
		(*ita)->print();
		cout<<'\t';
		if((*ita)->tapped())
			cout<<"(!) Tapped"<<endl;
		else
			cout<<"(!) Not Tapped"<<endl;
	}
}
int Player::printUntappedArmy(){
	int i=0; // counts untapped army members
	list<Personality *>::iterator ita;
	for(ita = army.begin();ita != army.end();ita++){

		if(!((*ita)->tapped())){ // if its not tapped print it
			i++;
			cout << " " << i << ". ";
			(*ita)->print();
		}
	}

	if(i==0){ // All the remaining army members are tapped
		return 1;
	}

	return 0;
}

// =================================


bool Player::hasArmy(){

	return (army.begin()!= army.end());
}

bool Player::hasProvinces(){

	return (numberOfProvinces!=0);
}

unsigned int Player::HandCardsNo(){
	int k=0;
	for(int i=0;i<7;i++)
		if(hand[i]!=NULL)
			k++;
	return k;
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
	for(ith = holdings.begin();ith != holdings.end();ith++){
		k++;
		if((*ith)->hasUpper())
			k++;
		if((*ith)->hasSub())
			k++;
	}
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
	ita = army.begin();
	for(int i=1;i<no && ita != army.end();i++)
		ita++;
	return (*ita)->getHonour();
}

unsigned int Player::GetHandMemberHonour(unsigned int no){
	int j=0;
	for(int i=0;i<no && j<7;j++){
		if(hand[j]!=NULL)
			i++;
	}
	return hand[j-1]->getMinHonour();
}
unsigned int Player::getMoney(){
	list<Holding *>::iterator ith;
	Holding *another;
	unsigned int money;
	
	if(stronghold.tapped())
		money=0;
	else{
	 	money=stronghold.getMoney();
	}
	
	for(ith = holdings.begin();ith != holdings.end();ith++){
		if(!((*ith)->tapped()))
			money += (*ith)->getHarvestValue();
		if((*ith)->hasUpper()){
			another = (*ith)->getUpperHolding();
			if(!another->tapped())
				money += another->getHarvestValue();
		}
		if((*ith)->hasSub()){
			another = (*ith)->getSubHolding();
			if(!another->tapped())
				money += another->getHarvestValue();
		}
	}
	return money;
}

unsigned int Player::getPotentialIncome(){
	list<Holding *>::iterator ith;
	Holding *another;
	unsigned int money;
	money=stronghold.getMoney();

	for(ith = holdings.begin();ith != holdings.end();ith++){
		money += (*ith)->getHarvestValue();
		if((*ith)->hasUpper()){
			another = (*ith)->getUpperHolding();
			money += another->getHarvestValue();
		}
		if((*ith)->hasSub()){
			another = (*ith)->getSubHolding();
			money += another->getHarvestValue();
		}
	}
	return money;
}

void Player::buyAndAssign(unsigned int hno, unsigned int ano){
	int j=0;
	int cost = GetHandCardCost(hno);
	pay_cost(cost);
	cout << " ($) Transaction succesful!" << endl;
	list<Personality *>::iterator ita;
	ita = army.begin();
	for(int i=1;i<ano && ita != army.end();i++)
		ita++;
	for(int i=0;i<hno && j<7;j++){
		if(hand[j] != NULL)
			i++;
	}

	// Give the player the info needed to take further decisions
	cout << endl << " (i) Upgrade boosts unit's Attack and Defense by: " << hand[j-1]->getEffectBonus() << endl;
	cout << " ($) Player money: " << getMoney() << endl;
	cost = hand[j-1]->getEffectCost();
	cout << " ($) Upgrade Cost: " << cost << endl;

	if(getDesision(" > Do you want to upgrade your new card? (y/n)"))
		if(getMoney()>=cost){
			hand[j-1]->upgrade();
			pay_cost(cost);
			cout << " ($) Upgrade successful!" << endl;
		}else{
			cout<<" > You don't have the money to upgrade teme"<<endl;
		}
	Follower **follow=new Follower*;
	Item **item=new Item*;
	TypeConverter::getCorrectType(hand[j-1],follow,item);
	if(*follow != NULL)
		(*ita)->equip(*follow);
	else
		(*ita)->equip(*item);
	hand[j-1]=NULL;
	delete follow;
	delete item;
}

bool Player::ProvinceHidden(int trg){
	list<BlackCard *>::iterator itp;
	int i=1;
	for(itp=provinces.begin(); itp!=provinces.end(); itp++){
		if(i==trg){
			if((*itp)->getRevealed()){ // card is revealed
				return 0;
			}
			else{
				return 1;
			}
		}
		i++;
	}
	return 0; // default termination (will never reach that return point)
}

void Player::pay_cost(int cost){
	list<Holding *>::iterator ith;
	Holding *h;
	int index;
	int flag=0;

	while(cost >0){
		#ifdef UI
		uiClear();
		#endif
		cout << endl << "\t ~ ~ ~ ($) Transaction screen ($) ~ ~ ~" << endl << endl << endl;
		printTapHoldings();
		cout << endl;
		cout << " (i) Pending cost: " << cost << endl;
		cout << endl << " > Choose a Card to use for payment: " << endl;
		cout << " (!) The machine gives no change (!) => choose wisely" << endl;
		if(!stronghold.tapped()){
			cout << " > Type the number of the holding you want to use:" << endl;
			index = choosefrom(HoldingCardsNo()+1);
		}
		else{
			cout<<" > Type  the number of the holding you want to use"<<endl;
			index = choosefrom(HoldingCardsNo());
		}
		
		if(index != HoldingCardsNo()+1){
			ith = holdings.begin();
			for(int i=0;ith != holdings.end();ith++){
				if((*ith)->hasUpper()){
					i++;
					if(i>=index){
						h= (*ith)->getUpperHolding();
						break;
					}
				}
			
				i++;
				if(i>=index){
					h =*ith;
					break;
				}

				if((*ith)->hasSub()){
					i++;
					if(i>=index){
						h =(*ith)->getSubHolding();
						break;
					}
				}
			}

			if(h->tapped()){
				cout<<" > You can't use the same card to pay your debt!"<<endl;
			}
			else{
				cout << " ($) Payed using Holding!" << endl;
				cost -= h->getHarvestValue();
				if(cost>0){
					cout << " (!) Money still owed:" << cost << endl;
				}
				h->tap();
			}
		}
		else{
			if(stronghold.tapped()){
				cout<<" (!) Stronghold income arleady used can't use it again"<<endl;
			}
			else{
				cout << " ($) Payed using stronghold!" << endl;
				cost -= stronghold.getMoney();
				if(cost>0){
					cout << " (!) Money still owed:" << cost << endl;
				}
				stronghold.tap();
			}
		}
		cout << " > Press Enter key to continue" << endl;
		pause();
	}
}

int Player::TapArmyCard(unsigned int ano){
	list<Personality *>::iterator ita;
	ita = army.begin();
	for(int i=1;i<ano && ita != army.end();i++)
		ita++;
	if((*ita)->tapped()){
		//cout<<"This card is already tapped"<<endl;
		return 1;
	}
	else{
		(*ita)->tap();
		return 0;
	}
}

unsigned int Player::ActiveArmyCardsNo(){
	list<Personality *>::iterator ita;
	unsigned int k=0;
	for(ita = army.begin();ita != army.end();ita++)
		if(!((*ita)->tapped()))
			k++;
	return k;
}

void Player::AddToAttackForce(unsigned int ano){
	list<Personality *>::iterator ita;
	ita = army.begin();
	for(int i=0; i<ano && ita!=army.end(); ita++)
		if(!((*ita)->tapped()))
			i++;
	ita--;
	attackForce.push_back(*ita);
	army.remove(*ita);
}

unsigned int Player::getPlayerAttack(){
	list<Personality *>::iterator ita;
	unsigned int sum=0;
	for(ita = attackForce.begin(); ita != attackForce.end();ita++)
		sum += (*ita)->getAttack(0);
	return sum;
}

unsigned int Player::getPlayerManPower(){
	list<Personality *>::iterator ita;
	unsigned int sum=0;
	for(ita = army.begin(); ita != army.end();ita++)
		sum+=(*ita)->getAttack(0);
	return sum;
}

unsigned int Player::getPlayerDefence(){
	list<Personality *>::iterator ita;
	unsigned int sum=getInitialDefense();
	for(ita = army.begin(); ita != army.end();ita++)
		if(!((*ita)->tapped()))
			sum += (*ita)->getDefence(0);
	return sum;
}

unsigned int Player::GetProvinceAmount(){

	return numberOfProvinces;
}

bool Player::CheckPersonalityCapacity(unsigned int ano,unsigned int hno){
	list<Personality *>::iterator ita;
	ita = army.begin();
	int j=0;
	for(int i=1; i<ano && ita!=army.end(); i++)
		ita++;
	for(int i=0;i<hno && j<7;j++){
		if(hand[j] != NULL)
			i++;
	}
	Follower **follow=new Follower*;
	Item **item=new Item*;
	TypeConverter::getCorrectType(hand[j-1],follow,item);
	if(*follow!=NULL)
		return (*ita)->CheckFollowerCapacity();
	else
		return (*ita)->CheckItemCapacity();
	delete follow;
	delete item;
}

void Player::attack(Player &target, unsigned int pno){
	//cout << " attack: " << this->getPlayerAttack() << " defence:" << target.getPlayerDefence() << " initial: " << target.getInitialDefense() << endl;
	if( this->getPlayerAttack() > target.getPlayerDefence() + target.getInitialDefense()){
	//if(this->getPlayerAttack()-target.getPlayerDefence() > target.getInitialDefense()){
		cout << endl <<"\t<^> Attacker's absolute Victory <^>" << endl << endl;

		target.dcasualties(0);
		target.destroyProvince(pno);
		
		this->returnHome();
	}
	else if(this->getPlayerAttack() > target.getPlayerDefence()){
		cout << endl <<"\t<^> Attacker's Victory with casualties <^>" << endl << endl;

		target.dcasualties(0);
		target.destroyProvince(pno);
		this->acasualties(this->getPlayerAttack()-target.getPlayerDefence());
		
		this->damage();

		this->returnHome();
	}
	else if(this->getPlayerAttack() == target.getPlayerDefence()){
		cout << endl <<"\t<^> Battle ended in a draw <^>" << endl << endl;
		target.dcasualties(0);
		this->acasualties(0);
	}
	else{
		cout << endl <<"\t<^> Defender's victory <^>" << endl << endl;
		target.dcasualties(target.getPlayerDefence() - this->getPlayerAttack());
		this->acasualties(0);
	}
}

void Player::dcasualties(unsigned int limit){
	cout<<"\t > Defence Casualties: "<<endl;
	if( army.begin()==army.end() ){
		cout << "\t\tNONE" << endl << endl;
		return;
	}
	bool none=1;
	list<Personality *>::iterator ita;
	Personality *tod = NULL;
	for(ita = army.begin(); ita != army.end();){
		if(!((*ita)->tapped()) && (*ita)->getAttack(1)>=limit){
			none=0;
			(*ita)->print();
			tod = *ita;
			army.remove((*ita));
			delete (tod);
			ita = army.begin();
		}else if(!((*ita)->tapped())){
			if( !(*ita)->follower_cas(limit) ){
				none=0;
			}
			ita++;
		}
		else{
			ita++;
		}
	}
	if(none){
		cout << "\t\tNONE" << endl << endl;
	}
}

void Player::acasualties(unsigned int limit){
	cout<<"\t > Attack Casualties: "<<endl;
	bool none=1;
	list<Personality *>::iterator ita;
	Personality *tod = NULL;
	for(ita = attackForce.begin(); ita != attackForce.end();){
		if((*ita)->getAttack(1)>=limit){
			none=0;
			(*ita)->print();
			tod = *ita;
			attackForce.remove((*ita));
			delete (tod);
			ita = attackForce.begin();
		}else{
			if( !(*ita)->follower_cas(limit) ){
				none=0;
			}
			ita++;
		}
	}
	if(none){
		cout << "\t\tNONE" << endl << endl;
	}
}

void Player::returnHome(){
	list<Personality *>::iterator ita;
	for(ita = attackForce.begin(); ita != attackForce.end();){
		(*ita)->tap();
		army.push_back(*ita);
		attackForce.remove(*ita);
		ita = attackForce.begin();
	}
	
	if(attackForce.begin()==attackForce.end() ){
		cout << " > Attack force successfully returned home" << endl;
	}
}

void Player::damage(){
	list<Personality *>::iterator ita;
	// For all remaining personalities in attack force
	for(ita = attackForce.begin(); ita != attackForce.end();){
		// Decrease their honnor and damage their items
		(*ita)->damage();

		// if honnor reaches 0 SEPPUKU TIME
		if( (*ita)->getHonour()==0 ){
			cout << " (!) Personality dishonored. Performing Seppuku..." << endl;
			attackForce.remove(*ita);
			(*ita)->performSeppuku();
			ita = attackForce.begin();
		}else
			ita++;
	}

}

void Player::destroyProvince(unsigned int pno){
	list<BlackCard *>::iterator itp;
	BlackCard *tod = NULL;
	itp = provinces.begin();
	for(int i=1;i<pno && i<numberOfProvinces;i++)
		itp++;
	tod = *itp;
	provinces.remove((*itp));
	delete (tod);
	numberOfProvinces--;
	cout<<"Provinces left: "<<numberOfProvinces<<endl;
	this->printProvinces();
}

unsigned int Player::GetProvinceCardCost(unsigned int pno){
	list<BlackCard *>::iterator itp;
	itp = provinces.begin();
	for(int i=1;i<pno && i<numberOfProvinces;i++)
		itp++;
	return (*itp)->getCost();
}

void Player::buyAndUse(unsigned int pno){
	list<BlackCard *>::iterator itp;
	itp = provinces.begin();
	for(int i=1;i<pno && itp != provinces.end();i++)
		itp++;
	int cost = GetProvinceCardCost(pno);
	pay_cost(cost);
	Personality **person=new Personality*;
	Holding **hold=new Holding*;
	TypeConverter::getCorrectType((*itp),person,hold);
	if(*person !=NULL)
		army.push_back(*person);
	else{
		if((*hold)->getMineType())
			this->ChainCreation(*hold);
		else
			holdings.push_back(*hold);
	}
	provinces.remove(*itp);
	list<BlackCard *>::iterator itd;
	delete person;
	delete hold;
	if(dynastyDeck->begin()==dynastyDeck->end()){
		cout << " > Dynasty Deck empty. Cant draw any more" << endl;
		return;
	}
	itd = dynastyDeck->begin();
	provinces.push_back(*itd);
	dynastyDeck->pop_front();
}

void Player::ChainCreation(Holding *nhold){
	srand(time(NULL));
	list<Holding *>::iterator ith;
	Holding *toChain = NULL;
	Holding *toChain2 = NULL;
	switch(nhold->getMineType()){
		case 1:{
			for(ith = holdings.begin(); ith != holdings.end(); ith++)
				if((*ith)->getMineType()==2){
					if(!((*ith)->hasSub()) && (*ith)->hasUpper()){
						toChain = *ith;
						break;
					}
					else if(!((*ith)->hasSub())){
						if(toChain!=NULL && rand()%2==1)
							toChain = *ith;
						else if(toChain==NULL)
							toChain = *ith;
					}
				}
			if(toChain==NULL)
				holdings.push_back(nhold);
			else
				nhold->chain(toChain);
			break;
		}
		case 2:{
			bool flag =0;
			for(ith = holdings.begin(); ith != holdings.end(); ith++)
					if((*ith)->getMineType() == 1 && !(*ith)->hasUpper()){
						if(!flag){
							list<Holding *>::iterator ith2;
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
					else if((*ith)->getMineType() == 3 && !(*ith)->hasSub()){
						if(!flag){
							list<Holding *>::iterator ith2;
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
			else if(toChain2==NULL && toChain!=NULL){
				nhold->chain(toChain);
				holdings.push_back(nhold);
				holdings.remove(toChain);
			}
			break;
		}
		case 3:{
			for(ith = holdings.begin(); ith != holdings.end(); ith++)
				if((*ith)->getMineType()==2){
					if(!((*ith)->hasUpper()) && (*ith)->hasSub()){
						toChain = *ith;
						break;
					}
					else if(!(*ith)->hasUpper()){
						if(toChain!=NULL && rand()%2==1)
							toChain = *ith;
						else if(toChain==NULL)
							toChain = *ith;
					}
				}
			if(toChain==NULL)
				holdings.push_back(nhold);
			else
				nhold->chain(toChain);
			break;
		}
	}
}

void Player::discardSurplusFateCards(){
	int k=0;
	for(int i=0;i<7;i++)
		if(hand[i]!=NULL)
			k++;
	if(k==7){
		printHand();
		k=choosefrom(7)-1;
		delete hand[k];
		hand[k]=NULL;
	}
}
