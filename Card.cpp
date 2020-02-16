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
}

void GreenCard::print()const{
	cout << "Green Card: " << name << "\n\t" << "Cost: " << cost 
		 << "\n\t" << "Attack Bonus: " << attackBonus
		 << "\n\t" << "Defence Bonus: " << defenceBonus
		 << "\n\t" << "Minimum Honour required: " << min_honour
		 << "\n\t" << "Bonus Effect if you upgrade: " << effectBonus
		 << "\n\t" << "Cost for upgrade: "<< effectCost
		 << "\n\t" << "Card Description: "<< cardText <<endl;
}

void BlackCard::print()const{
	cout << "Black Card: " << name << "\n\t" << "Cost: " << cost <<endl;
}
