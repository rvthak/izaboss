#ifndef PLAYER
#define PLAYER

#include <list>
#include "DeckBuilder.hpp"

class Player
{
public:
	Player();
	~Player();

	void untapEverything();
	void drawFateCard();
	void revealProvinces();
	void printHand();
	void printProvinces();
	void printArmy();
	void printTapArmy();
	void printUntappedArmy();
	void printHoldings();
	void printArena();
	void print();
	unsigned int getHonour(){
		return stronghold.getHonour();
	};
	unsigned int getMoney();
	unsigned int getPlayerAttack();
	unsigned int GetProvinceAmount();
	bool hasArmy();

	unsigned int HandCardsNo();
	unsigned int ArmyCardsNo();
	unsigned int HoldingCardsNo();
	unsigned int ActiveArmyCardsNo();
	
	unsigned int GetHandCardCost(unsigned int);
	unsigned int GetProvinceCardCost(unsigned int);
	void pay_cost(unsigned int );
	unsigned int GetArmyMemberHonour(unsigned int);
	unsigned int GetHandMemberHonour(unsigned int);
	
	void buyAndAssign(unsigned int, unsigned int);
	void buyAndUse(unsigned int);

	void AddToAttackForce(unsigned int);
	void attack(Player &, unsigned int);

	void TapArmyCard(unsigned int);
	void discardSurplusFateCards();

protected:
	unsigned int numberOfProvinces;
	list<GreenCard *>* fateDeck;
	list<BlackCard *>* dynastyDeck;

	list<Province *> provinces;
	GreenCard *hand[7];
	list<Holding *> holdings;
	list<Personality *> army;
	Strong stronghold;

	list<Personality *> attackForce;
	list<Personality *> defenceForce;
private:
	DeckBuilder my_deck;
};

#endif
