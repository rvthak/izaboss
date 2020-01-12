#ifndef CARD
#define CARD

class Card
{
public:
	Card();
	~Card();
	void untap(){
		isTapped = 0;
	};
	virtual void print()=0;
protected:
	std::sting name;
	unsigned int cost;
	bool isTapped;
};


class GreenCard : public Card
{	// Follower + Item sub-classes go at their own files
public:
	GreenCard();
	~GreenCard();

	effectBonus(); // call on card upgrade?
	virtual void print();
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
	void revealCard(){
		isRevealed = 1;
	};
	virtual void print();

protected:
	bool isRevealed;

};

class Province : public BlackCard
{
public:
	Province();
	~Province();
	void print();
protected:
	Card *attached;

};

#endif
