#ifndef _TYPECONVERTER_HPP_
#define _TYPECONVERTER_HPP_

#include "Card.hpp"
#include "Item.hpp"
#include "Holding.hpp"
#include "Follower.hpp"
#include "Personality.hpp"

#define PERSONALITY 1
#define HOLDING 2
#define FOLLOWER 3
#define ITEM 4

class TypeConverter {
	
	public:
		TypeConverter();
		static void getCorrectType(BlackCard *card, Personality **person, Holding **hold);
		static void getCorrectType(GreenCard *card, Follower **follow, Item **item);
		static Personality *getPersonality(BlackCard *d);
		static Holding *getHolding(BlackCard *d);
		static Follower *getFollower(GreenCard *d);
		static Item *getItem(GreenCard *d);
};

#endif