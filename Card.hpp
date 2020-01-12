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
	unsigned int minimumHonor;
	unsigned int effectBonus;
	unsigned int effectCost;
	std::string cardText;

};

class BlackCard : public Card
{
public:
	BlackCard();
	~BlackCard();

protected:
	bool isRevealed;

};

class Province : public Card
{
public:
	Province();
	~Province();
	
protected:
	Card *attached;

};

#endif
