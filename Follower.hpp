#ifndef FOLLOWER
#define FOLLOWER

#include "Card.hpp"

class Follower : public GreenCard
{
	public:
		Follower();
		~Follower();
		virtual int getType(){ return 3; }

	private:
		
		
};

//==============================================

class Footsoldier : public Follower
{
public:
	Footsoldier();
	~Footsoldier();
	
};

class Archer : public Follower
{
public:
	Archer();
	~Archer();
	
};

class Cavalry : public Follower
{
public:
	Cavalry();
	~Cavalry();
	
};

class Bushido : public Follower
{
public:
	Bushido();
	~Bushido();
	
};

class Sieger : public Follower
{
public:
	Sieger();
	~Sieger();
	
};

class Atakebune : public Follower // Naval
{
public:
	Atakebune();
	~Atakebune();
	
};

#endif