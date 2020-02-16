#include "Card.hpp"

bool Card::tap(){
		if(isTapped){
			isTapped=0;
			return 0;
		}
		else{
			isTapped=1;
			return 1; 
		}
	};