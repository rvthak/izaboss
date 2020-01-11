#ifndef PLAYER
#define PLAYER

class Player
{
public:
	Player();
	~Player();

	untapEverything();
	drawFateCard();
	revealProvince();
	printHand();
	printProvinces();


protected:
	unsigned int numberOfProvinces;
	list<GreenCard *>* fateDeck;
	list<BlackCard *>* dynastyDeck;

	list<Card *> provinces;
	list<GreenCard *> hand;
	list<BlackCard *> holdings;
	list<BlackCard *> holdings;
	Stronghold stonghold;
	
};

#endif