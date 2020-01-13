#ifndef PLAYER
#define PLAYER

class Player
{
public:
	Player();
	~Player();

	void untapEverything();
	void drawFateCard();
	void revealProvince();
	void printHand();
	void printProvinces();
	void printArmy();
	print();
	unsigned int getHonour(){
		return stronghold.getHonour();
	};
	bool hasArmy();
	unsigned int HandCardsNo();
	unsigned int ArmyCardsNo();
	unsigned int HoldingCardsNo();
	unsigned int getMoney(){
		return money;
	};
	unsigned int GetHandCardCost(unsigned int);
	unsigned int GetArmyMemberHonour(unsigned int);
	unsigned int GetHandMemberHonour(unsigned int);
	void buyAndAssign(unsigned int, unsigned int);
protected:
	unsigned int numberOfProvinces;
	list<GreenCard *>* fateDeck;
	list<BlackCard *>* dynastyDeck;

	list<Province *> provinces;
	GreenCard *hand[7];
	list<Holding *> holdings;
	list<Personality *> army;
	Strong stronghold;
	unsigned int money;
	list<Personality *> attackForce;
	list<Personality *> defenceForce;
private:
	DeckBuilder my_deck;
};

#endif
