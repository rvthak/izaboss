#ifndef CARD
#define CARD

#include <string>

class Card {
	
	public:
		// Constructor + Destructor (no need for bodies)
		Card(){}
		~Card(){}

		void tap(){ isTapped = 1; }						// Taps a Card
		void untap(){ isTapped=0; }						// Untapps a Card
		bool tapped()const{ return isTapped; }			// Return if the Card is tapped or not
		std::string getName()const{ return name; }		// Returns the name of the card
		unsigned int getCost()const{ return cost; }		// Returns the cost of the Card

		virtual void print()const=0;	// Prints the Card
		virtual int getType()const=0;	// Returns the Card type (used in Type Converter)

	protected:
		std::string name;	// The name of the Card
		unsigned int cost;	// The cost of the Card
		bool isTapped;		// The tap state of the Card
};


class GreenCard : public Card {	
// Follower + Item sub-classes go at their own files

	public:
		GreenCard(){}
		~GreenCard(){}

		// Data Member Getters
		int getAttackBonus()const{ return attackBonus; }
		int getDefenceBonus()const{ return defenceBonus; }
		unsigned int getMinHonour()const{ return min_honour; }
		unsigned int getEffectBonus()const{ return effectBonus; }
		unsigned int getEffectCost()const{ return effectCost; }
		std::string getCardText()const{ return cardText; }

		void upgrade(){ // Add the Upgrade bonuses
			attackBonus+=effectBonus; defenceBonus+=effectBonus;
		}
		
		virtual void print()const;
		virtual int getType()const=0;

	protected:
		int attackBonus;			// The bonus provided to the attack of the targeted unit
		int defenceBonus;			// The bonus provided to the defence of the targeted unit
	  	unsigned int min_honour;	// The minimum honour a unit must have to be able to take advantage of this card
		unsigned int effectBonus;	// The Card upgrade bonus provided extra upon upgrading
		unsigned int effectCost;	// The Card upgrade cost
		std::string cardText;		// A small text description of the Card
};

class BlackCard : public Card {

	public:
		BlackCard(){}
		~BlackCard(){}

		// A couple of setters and a getter
		void revealCard(){ isRevealed = 1; }
		void hideCard(){ isRevealed = 0; }
		bool getRevealed()const{ return isRevealed; } 

		virtual void print()const;
		virtual int getType()const=0;

	protected:
		bool isRevealed;	// The revealed state of the card
};

#endif
