#ifndef CARD
#define CARD

#include <string>

class Card
{
public:
	Card(){}
	~Card(){}

	void tap();
	void untap()=0;
	bool tapped()const{ return isTapped; }
	std::string getName()const{ return name; }
	unsigned int getCost()const{ return cost; }

	virtual void print()const=0;
	virtual int getType()const=0;

protected:
	std::string name;
	unsigned int cost;
	bool isTapped;
};


class GreenCard : public Card
{	// Follower + Item sub-classes go at their own files
public:
	GreenCard(){}
	~GreenCard(){}

	virtual void untap()=0;

	int getAttackBonus()const{ return attackBonus; }
	int getDefenceBonus()const{ return defenceBonus; }
	unsigned int getMinHonour()const{ return min_honour; }
	unsigned int getEffectBonus()const{ return effectBonus; }
	unsigned int getEffectCost()const{ return effectCost; }
	std::string getCardText()const{ return cardText; }

	virtual void print()const;
	virtual int getType()const=0;

protected:
	int attackBonus;
	int defenceBonus;
  	unsigned int min_honour;
	unsigned int effectBonus;
	unsigned int effectCost;
	std::string cardText;
};

class BlackCard : public Card
{
public:
	BlackCard(){}
	~BlackCard(){}

	void untap()=0;

	void revealCard(){ isRevealed = 1; }
	void hideCard(){ isRevealed = 0; }
	bool getRevealed()const( return isRevealed; )

	virtual void print()const;
	virtual int getType()=0;

protected:
	bool isRevealed;
};

class Province : public BlackCard
{
public:
	Province(){}
	~Province(){}
	void untap(){}
	void print()const;
	void attach(BlackCard *n){ attached = n; }
	void detach(){ attached =NULL; }
	unsigned int getCardCost(){	return attached->getCost(); }
	BlackCard *getAttachedCard(){ return attached; }
	virtual int getType(){ return -1; }
protected:
	BlackCard *attached;
};

#endif
