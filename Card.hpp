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
	int tap(){
		if(isTapped){
			cout<<"Already tapped"<<endl;
			return 0;
		}
		else{
			isTapped=1;
			return 1;
		}
	};
	virtual void print()=0;
	unsigned int getCost(){
		return cost;
	};
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
	unsigned int getHonour(){
		return min_honour;
	};
	unsigned int getEffectCost(){
		return effectCost;
	};
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
