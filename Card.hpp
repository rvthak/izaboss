#ifndef CARD
#define CARD

class Card
{
public:
	Card();
	~Card();

protected:
	std::sting name;
	unsigned int cost;
	bool isTagged;
};


class GreenCard : public Card
{	// Follower + Item sub-classes go at their own files
public:
	GreenCard();
	~GreenCard();

	effectBonus(); // call on card upgrade?

protected:
	int attackBonus;
	int defenceBonus;
	unsigned int cardText;
	unsigned int effectCost;
	unsigned int durability;

};

class BlackCard : public Card
{
public:
	BlackCard();
	~BlackCard();

protected:
	bool isReleaved;

};

class Province : public Card
{
public:
	Province();
	~Province();
	
protected:
	Card *attached;

}

#endif
