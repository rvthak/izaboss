#ifndef FOLLOWER
#define FOLLOWER

#include "Card.hpp"

class Follower : public GreenCard
{
	public:
		Follower(){}
		~Follower(){}
		virtual int getType(){ return 3; }	
		void print()const;
};

//==============================================

class Footsoldier : public Follower
{
public:
	Footsoldier(const std::string n);
	~Footsoldier(){}
};

class Archer : public Follower
{
public:
	Archer(const std::string n);
	~Archer(){}
};

class Cavalry : public Follower
{
public:
	Cavalry(const std::string n);
	~Cavalry(){}
};

class Bushido : public Follower
{
public:
	Bushido(const std::string n);
	~Bushido(){}
};

class Sieger : public Follower
{
public:
	Sieger(const std::string n);
	~Sieger(){}
};

class Atakebune : public Follower // Naval
{
public:
	Atakebune(const std::string n);
	~Atakebune(){}
};

#endif