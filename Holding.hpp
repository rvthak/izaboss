#ifndef HOLDING
#define HOLDING

#include "Card.hpp"

class Holding : public BlackCard
{
	public:
		Holding();
		~Holding();
		unsigned int getHarvestValue(){
			return harvestValue;
		};
	protected:
		unsigned int harvestValue;
		Holding *upperHolding;
		Holding *subHolding;
};

//==============================================

class Stronghold : public Holding
{
	public:
		Stronghold();
		~Stronghold();
		unsigned int getHonour(){
			return honour;
		};
		unsigned int getMoney(){
			return money;
		};
	private:
		const unsigned int honour;
		const unsigned int money;
		const unsigned int initialDefense;
	
};

//==============================================

class Plain : public Holding
{
public:
	Plain();
	~Plain();
	
};

class Mine : public Holding
{
public:
	Mine();
	~Mine();
	
};

class GoldMine : public Holding
{
public:
	GoldMine();
	~GoldMine();
	
};

class CrystalMine : public Holding
{
public:
	CrystalMine();
	~CrystalMine();
	
};

class Farmland : public Holding
{
public:
	Farmland();
	~Farmland();
	
};

class GiftAndFavour : public Holding
{
public:
	GiftAndFavour();
	~GiftAndFavour();
	
};

#endif