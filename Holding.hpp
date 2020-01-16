#ifndef HOLDING
#define HOLDING

#include "Card.hpp"

class Holding : public BlackCard
{
	public:
		Holding():isMine(0), harvestValue(0), upperHolding(NULL), subHolding(NULL){}
		~Holding(){}

		bool checkMine(){ return isMine; }
		unsigned int getHarvestValue()const{ return harvestValue; }
		Holding *getUpperHolding()const{ return upperHolding; }
		Holding *getSubHolding()const{ return subHolding; }
		virtual int getType()const{ return 2; }

		bool hasSub(){ return subHolding!=NULL }
		bool hasUpper(){ return upperHolding!=NULL }
 	
 		void chain(Holding *target);

		void chainSub(Holding *target){ subHolding=target; }
		void chainUpper(Holding *target){ upperHolding=target; }
		void unchanSub(){ subHolding=NULL; }
		void unchanUpper(){ upperHolding=NULL; }

		bool getMineType();

	protected:
		bool isMine;
		unsigned int harvestValue;
		Holding *upperHolding;
		Holding *subHolding;
};

//==============================================

class Stronghold : public Holding
{
	public:
		Stronghold(){}
		~Stronghold(){}

		unsigned int getHonour()const{ return honour; }
		unsigned int getMoney()const{ return money; }
		unsigned int getInitialDefense()const{ return initialDefense; }

	private:
		const unsigned int honour;
		const unsigned int money;
		const unsigned int initialDefense;
		static unsigned int honcnt;
};

//==============================================

class Mine : public Holding
{
public:
	Mine(const std::string n);
	~Mine(){}
};

class GoldMine : public Holding
{
public:
	GoldMine(const std::string n);
	~GoldMine(){}
};

class CrystalMine : public Holding
{
public:
	CrystalMine(const std::string n);
	~CrystalMine(){}
};



class Plain : public Holding
{
public:
	Plain(const std::string n);
	~Plain(){}
};

class Farmland : public Holding
{
public:
	Farmland(const std::string n);
	~Farmland(){}
};

class GiftAndFavour : public Holding // SOLO
{
public:
	GiftAndFavour(const std::string n);
	~GiftAndFavour()
};

#endif