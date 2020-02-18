#ifndef PLAYER
#define PLAYER

#include <list>
#include "Holding.hpp"
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
	void print();
	unsigned int getHonour(){
		return stronghold.getHonour();
	};
	unsigned int getMoney();
	unsigned int getPlayerAttack();
	unsigned int getPlayerDefence();
	unsigned int getInitialDefense(){
		return stronghold.getInitialDefense();
	};
	unsigned int GetProvinceAmount();
	bool hasArmy();
	bool hasProvinces();

	unsigned int HandCardsNo();
	unsigned int ArmyCardsNo();
	unsigned int HoldingCardsNo();
	unsigned int ActiveArmyCardsNo();
	
	unsigned int GetHandCardCost(unsigned int);
	unsigned int GetProvinceCardCost(unsigned int);
	void pay_cost(int );

	unsigned int GetArmyMemberHonour(unsigned int);
	unsigned int GetHandMemberHonour(unsigned int);
	
	void buyAndAssign(unsigned int, unsigned int);
	void buyAndUse(unsigned int);

	bool CheckPersonalityCapacity(unsigned int,unsigned int);

	void AddToAttackForce(unsigned int);
	void attack(Player &, unsigned int);
	void dcasualties(unsigned int);
	void destroyProvince(unsigned int);
	void celebrate();
	void acasualties(unsigned int);

	void TapArmyCard(unsigned int);
	void ChainCreation(Holding *);
	void discardSurplusFateCards();

protected:
	unsigned int numberOfProvinces;
	std::list<GreenCard *>* fateDeck;
	std::list<BlackCard *>* dynastyDeck;

	std::list<BlackCard *> provinces;
	GreenCard *hand[7];
	std::list<Holding *> holdings;
	std::list<Personality *> army;
	Stronghold stronghold;

	std::list<Personality *> attackForce;

private:
	DeckBuilder my_deck;
};

#endif
