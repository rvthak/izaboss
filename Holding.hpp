#ifndef _HOLDING
#define _HOLDING

#include "Card.hpp"

class Holding : public BlackCard {

	public:
		// We chose use an initializer list for some basic initial values
		Holding():isMine(0), harvestValue(0), upperHolding(NULL), subHolding(NULL){}
		~Holding(){}

		// Basic getters
		bool checkMine(){ return isMine; }
		unsigned int getHarvestValue()const{ return harvestValue; }
		Holding *getUpperHolding()const{ return upperHolding; }
		Holding *getSubHolding()const{ return subHolding; }
		
		// Check if a mine has an upper or sub connection
		bool hasSub(){ return subHolding!=NULL; }
		bool hasUpper(){ return upperHolding!=NULL; }
 		
 		// Chain functions
 		void chain(Holding *target); // Chains the mine correctly

 		// Chain creation funcions
		void chainSub(Holding *target){ subHolding=target; }
		void chainUpper(Holding *target){ upperHolding=target; }

		// Chain destruction functions
		void unchanSub(){ subHolding=NULL; }
		void unchanUpper(){ upperHolding=NULL; }

		// Checks the mine type (if its a mine)
		int getMineType();

		virtual void print()const;
		virtual int getType()const{ return 2; }

	protected:
		int isMine;			// Depending on its value it indicates if a card is a mine + its exact type
		unsigned int harvestValue;	// The harvest value of the holding
		Holding *upperHolding;		// For mines only: its upper chain
		Holding *subHolding;		// For mines only: its lower chain
};

//==============================================

class Stronghold : public Holding {

	public:
		Stronghold();
		~Stronghold(){}

		unsigned int getHonour()const{ return honour; }
		unsigned int getMoney()const{ return money; }
		unsigned int getInitialDefense()const{ return initialDefense; }

		void print()const;
		
	private:
		unsigned int honour;			// The honour the stronghold provides
		unsigned int money;				// The money the stronghold provides
		unsigned int initialDefense;	// The initial defense the stronghold provides 
		static unsigned int honcnt;		// An honour counter to ensure that each stronghold has different honour and the turn of each player is clear
};

//==============================================

class Mine : public Holding {
	public:
		Mine(const std::string n);
		~Mine(){}
};

class GoldMine : public Holding {
	public:
		GoldMine(const std::string n);
		~GoldMine(){}
};

class CrystalMine : public Holding {
	public:
		CrystalMine(const std::string n);
		~CrystalMine(){}
};


class Plain : public Holding {
	public:
		Plain(const std::string n);
		~Plain(){}
};

class Farmland : public Holding {
	public:
		Farmland(const std::string n);
		~Farmland(){}
};

class GiftAndFavour : public Holding { // SOLO
	public:
		GiftAndFavour(const std::string n);
		~GiftAndFavour(){};
};

#endif
