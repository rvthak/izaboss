#ifndef CARD
#define CARD

#include <string>

class Card
{
public:
	Card();
	~Card();
	void untap(){ isTapped = 0; };
	bool tap();
	virtual void print()=0;
	unsigned int getCost(){ return cost; };
	bool tapped(){ return isTapped; };
	virtual int getType()=0;
protected:
	std::string name;
	unsigned int cost;
	bool isTapped;
};


class GreenCard : public Card
{	// Follower + Item sub-classes go at their own files
public:
	GreenCard();
	~GreenCard();

	virtual void print();
	unsigned int getHonour(){
		return min_honour;
	};
	unsigned int getEffectCost(){
		return effectCost;
	};
	virtual int getType()=0;
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
	BlackCard();
	~BlackCard();
	void revealCard(){
		isRevealed = 1;
	};
	virtual void print();
	virtual int getType()=0;

protected:
	bool isRevealed;

};

class Province : public BlackCard
{
public:
	Province();
	~Province();
	void print();
	void attach(BlackCard *n){
		attached = n;
	};
	void detach(){
		attached =NULL;
	};
	unsigned int getCardCost(){
		return attached->getCost();
	};
	BlackCard *getAttachedCard(){
		return attached;
	};
	virtual int getType(){ return -1; }
protected:
	BlackCard *attached;

};

#endif
