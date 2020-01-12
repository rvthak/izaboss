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
	print();
	unsigned int getHonour(){
		return stronghold.getHonour();
	};

protected:
	unsigned int numberOfProvinces;
	list<GreenCard *>* fateDeck;
	list<BlackCard *>* dynastyDeck;

	list<Province *> provinces;
	GreenCard *hand[6];
	list<Holding *> holdings;
	list<Personality *> army;
	Strong stronghold;
private:
	DeckBuilder my_deck;
};

#endif