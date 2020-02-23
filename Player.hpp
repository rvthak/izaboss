#ifndef PLAYER
#define PLAYER

#include <list>
#include "Holding.hpp"
#include "DeckBuilder.hpp"


class Player {

	public:
		Player();
		~Player();

		// Print
		void print();					// Print all the Player data
		void printHand();				// Print Player Hand
		void printHoldings();			// Print Player Holdings
		void printTapHoldings(); 		// Print Player Holdings including tap state
		void printProvinces();			// Print Player Provinces
		void printArmy();				// Print Player Army
		void printArena();				// Print Player Army including Items and followers
		void printTapArmy();			// Print Player Army including tap state
		int printUntappedArmy();		// Print only the untapped Army soldiers

		// Support functions
		bool ProvinceHidden(int);													// Returns 1 if the targeted (int) province of the player is hidden 
		unsigned int getHonour(){ return stronghold.getHonour(); }					// Get the player's Honour
		unsigned int getInitialDefense(){ return stronghold.getInitialDefense(); }	// Get the player's initial defense
		unsigned int HoldingCardsNo();												// Returns how many holdings the player has								

		// Starting Phase
		unsigned int getPlayerManPower(); 	// Returns the total attack power of all the Player's personalities
		unsigned int getPotentialIncome();	// Returns the total revenue all the holdings can provide per round
		void untapEverything();				// Untap every card in army + holdings
		void drawFateCard();				// Draw a new fate card
		void revealProvinces();				// Reveal all the hidden provinces
		
		// Equip Phase
		bool hasArmy();											// Check if player has army
		void pay_cost(int );									// Use Holdings to pay dept
		unsigned int getMoney();								// Returns the currently available money of the player
		unsigned int HandCardsNo(); 							// Returns how many cards the player has in hand
		unsigned int ArmyCardsNo(); 							// Returns how many cards the player has in his army
		unsigned int GetHandCardCost(unsigned int);				// Get the cost of the int card in player's hand
		unsigned int GetArmyMemberHonour(unsigned int); 		// Get the honour of the int card in player's army
		unsigned int GetHandMemberHonour(unsigned int); 		// Get the honour of the int card in the player's hand
		void buyAndAssign(unsigned int hno, unsigned int ano);	// buy and equip the targeted hand card(hno) to the targeted army personality(ano)
		
		// Battle phase
		unsigned int ActiveArmyCardsNo();				// Return the amount of the still active cards in the army
		unsigned int GetProvinceAmount();				// Return the amount of provinces of the player
		unsigned int getPlayerAttack();					// Return the attack power of the player
		unsigned int getPlayerDefence();				// Return the defense power of the player
		void AddToAttackForce(unsigned int);			// Add the targeted personality from the army to the attack force
		void attack(Player &target, unsigned int pno);	// Attack the targeted player's province(pno)
		void acasualties(unsigned int);					// Calculaties of amount (int) on attacker's force 
		void dcasualties(unsigned int);					// Calculaties of amount (int) on defender's force 
		void damage();									// Damage the player's whole army
		void destroyProvince(unsigned int);				// Destroy the targeted Province
		void returnHome();								// Remaining soldiers from attack force return to army
		int TapArmyCard(unsigned int);					// Tap the (int) targeted army card

		//Economy Phase
		void buyAndUse(unsigned int);										// Buy the province targeted by the parameter int
		void ChainCreation(Holding *);										// Create a chain of mines
		unsigned int GetProvinceCardCost(unsigned int);						// Get the cost of the targeted Province
		bool CheckPersonalityCapacity(unsigned int ano,unsigned int hno);	// Check the item/follower capacity of the targeted army personality(ano) for the targeted hand card(hno)

		// Final phase
		void discardSurplusFateCards();	// Discard extra cards from hand (You can have up to 6 in the end)

		// Check win condition
		bool hasProvinces();	// Check if the targeted player has provinces

	protected:
		Stronghold stronghold;	// The Player's Stronghold

		// Player's Provinces
		unsigned int numberOfProvinces;		// The number of the Provinces the Player has
		std::list<BlackCard *> provinces; 	// A list of those Provinces
		
		// Player's Holdings
		std::list<Holding *> holdings; // A list of the player's holdings

		// Player's Army
		std::list<Personality *> army;			// All the available army of Personalities
		std::list<Personality *> attackForce;	// A list of the attack army troops

		// Player's Hand Cards
		GreenCard *hand[7];

		// Player's Card Decks
		std::list<GreenCard *>* fateDeck;
		std::list<BlackCard *>* dynastyDeck;

	private:
		DeckBuilder my_deck;	// The player's Deckbuilder to provide deck building and shuffle functionality
};

#endif
