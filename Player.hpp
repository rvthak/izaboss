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
	print();

protected:
	unsigned int numberOfProvinces;
	list<GreenCard *>* fateDeck;
	list<BlackCard *>* dynastyDeck;

	list<BlackCard *> provinces;
	GreenCard *hand[6];
	list<Holding *> holdings;
	list<Personality *> army;
	Strong stronghold;
private:
	DeckBuilder my_deck;
};

#endif