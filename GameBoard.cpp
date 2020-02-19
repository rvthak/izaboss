#include <cstdlib>
#include "inputMgr.hpp"
#include "GameBoard.hpp"
#include "TypeConverter.hpp"
#include <limits>

using namespace std;

void swap(unsigned int *x, unsigned int *y){  
    unsigned int temp = *x;
    *x = *y;
  	*y = temp;
}
void sortPlayers(unsigned int *buf, unsigned int *val, int n){   
    for (int i=0; i<n-1; i++){
    	for (int j=0; j<n-i-1; j++){
    		if (val[j] > val[j+1]){
    			swap(&val[j], &val[j+1]);
    			swap(&buf[j], &buf[j+1]);
    		} 
    	}
    }
}

GameBoard::GameBoard(){
	running=0;
	player=NULL;
}
GameBoard::~GameBoard(){
	if(player!=NULL){ delete[] player; }
	if(buf!=NULL){ delete[] buf; }
}


void GameBoard::initializeGameBoard(unsigned int playerNo){
	// Prepare the board for a game by creating the players
	if(playerNo>1&&playerNo<9){	// Check the player number is in the set range
		player_amount=playerNo;
		player=new Player[player_amount];

		// Players Created => Their honour can't change during the game so we sort
		// so we "sort the player array" to make playing in each turn easier
		buf=new unsigned int[player_amount];	// in this array we store the players positions sorted
		unsigned int *bufval=new unsigned int[player_amount];	// this array has their honour values stored (used for sorting)
		
		// We pass the initial values to both arrays
		for (unsigned int i=0; i<player_amount; i++){
			buf[i]=i;
	    		bufval[i]=player[i].getHonour();
	    	}
		// sort the buf according to the bufval values
		sortPlayers(buf, bufval, player_amount);
		delete []bufval;
		cout << " > Game board initialized succesfully!" << endl;
	}
	else{
		cout << " > Parameter Error: Player Number outside bounds." << endl;
		cout << " > Game board initialization failed! Please try again with different values" << endl;
	}
	return;
}
void GameBoard::printGameStatistics(){
	if(player==NULL){
		cout << " > Game Error: Game board not initialized. Terminating print..." << endl;
		return;
	}
	print(); // Print the game board state/stats

	// Print each player's stats 
    cout << "   Player\tProvinces\tAttack\t\tDefence\t\tCurrent Income\t\tHoldings" << endl;
    for(unsigned int j=0; j<player_amount; j++){
            cout << " " << j+1 << ". Player " << j+1 << ": "
             << "\t    " << player[buf[j]].GetProvinceAmount()
             << "\t\t   "<< player[buf[j]].getPlayerAttack()
             << "\t\t   "<< player[buf[j]].getPlayerDefence()
             << "\t\t      "<< player[buf[j]].getMoney()
             << "\t\t  "<< player[buf[j]].HoldingCardsNo()
             << endl;
    }
}
void GameBoard::print(){
	if(player==NULL){
		cout << " > Game Error: Game board not initialized. Terminating print..." << endl;
		return;
	}
	cout << "	- Number of players: " << player_amount << endl;
	return;
}
void GameBoard::gameplay(){
	if(player==NULL){
		cout << " > Game Error: Game board not initialized. Terminating gameplay..." << endl;
		return;
	}
	running=1;

	// Main game loop
	while(running){
		startingPhase();
		//equipPhase();
		//battlePhase();
		if(!running){break;}
		economyPhase();
		finalPhase();
	}
	return;
}

//=====================================================

void GameBoard::startingPhase(){
    #ifndef UI
	cout << " ================================================ " << endl;
	cout << "                   Starting Phase                 " << endl;
	cout << " ================================================ " << endl;
	#endif
	for(unsigned int i=0; i<player_amount; i++){
		#ifdef UI
		system("clear");
		cout << " ================================================ " << endl;
		cout << "                   Starting Phase                 " << endl;
		cout << " ================================================ " << endl;
		#endif
		cout << endl << " > Player " << i+1 << "'s turn: " << endl;
    	player[buf[i]].untapEverything();
    	player[buf[i]].drawFateCard();
  	 	player[buf[i]].revealProvinces();
  	 	cout << endl;
    	player[buf[i]].printHand();
    	cout << endl;
    	player[buf[i]].printProvinces();
    	cout << endl;
    	#ifdef UI
    	cout << " > Phase ended for Player " << i+1 << " : Press Enter key to continue" << endl;
		cin.get();
		#endif
    }
}
void GameBoard::equipPhase(){
	#ifndef UI
	cout << " ================================================ " << endl;
	cout << "                    Equip Phase                   " << endl;
	cout << " ================================================ " << endl;
	#endif
	for(unsigned int i=0; i<player_amount; i++){
		#ifdef UI
		system("clear");
		cout << " ================================================ " << endl;
		cout << "                    Equip Phase                   " << endl;
		cout << " ================================================ " << endl;
		#endif
		cout << endl << " > Player " << i+1 << "'s turn: " << endl;
		if(player[buf[i]].hasArmy()){ // if the player has army
			
			// Print his hand and army to allow him to choose his next move
			player[buf[i]].printHand();
			cout << " ================================================ " << endl;
			player[buf[i]].printArmy();

			// Print player's money
			cout << endl << " ($) Player money: " << player[buf[i]].getMoney() << endl << endl;

			while(getDesision(" > Do you want continue on transactions(y) or pass(n)? (y/n)")){
				// Get user input for the requested move
				cout << " > Please choose a card from your hand:" << endl;
				unsigned int handCard = choosefrom(player[buf[i]].HandCardsNo());

				cout << " > Please choose a card from your Army:" << endl;
				unsigned int armyCard = choosefrom(player[buf[i]].ArmyCardsNo());

				if( player[buf[i]].getMoney() >= player[buf[i]].GetHandCardCost(handCard) ){
					if( player[buf[i]].GetArmyMemberHonour(armyCard) >= player[buf[i]].GetHandMemberHonour(handCard) ){
						if( player[buf[i]].CheckPersonalityCapacity(armyCard, handCard) ){
							player[buf[i]].buyAndAssign(handCard, armyCard); // remember to tap the according cards
						}
						else{
							cout << " This personality already has reached its max capacity for that card type." << endl;
						}	
					}
					else{
						cout << " > Can't move on with the process. Not enough personality honour." << endl;
						cout << " He is a disgrace to our family" << endl;
					}	
				}
				else{
					cout << " > Can't move on with the process. Not enough money." << endl;
					cout << " Get rich and come back you little pleb" << endl;
				}

				#ifdef UI
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << " > Press Enter key to continue" << endl;
				cin.get();
				system("clear");
				cout << " ================================================ " << endl;
				cout << "                    Equip Phase                   " << endl;
				cout << " ================================================ " << endl;
				cout << endl << " > Player " << i+1 << "'s turn: " << endl;
				#endif

				// Print his hand and army to allow him to choose his next move
				player[buf[i]].printHand();
				player[buf[i]].printArmy();

				// Print player's money
				cout << " ($) Player money: " << player[buf[i]].getMoney() << endl << endl;
			}
    	}
    	else{
    		cout << " > Player has no army can't do any transaction." << endl;
    	}
    	#ifdef UI
    	cout << " > Phase ended for Player " << i+1 << " : Press Enter key to continue" << endl;
		cin.get();
		#endif
    }
}
void GameBoard::battlePhase(){
	#ifndef UI
	cout << " ================================================ " << endl;
	cout << "                   Battle Phase                   " << endl;
	cout << " ================================================ " << endl;
	#endif
	for(unsigned int i=0; i<player_amount; i++){	// for each player in the correct order
		#ifdef UI
		system("clear");
		cout << " ================================================ " << endl;
		cout << "                   Battle Phase                   " << endl;
		cout << " ================================================ " << endl;
		#endif
		cout << endl << " > Player " << i+1 << "'s turn: " << endl;
		if(player[buf[i]].hasArmy()){ 		// check if he has an army
			player[buf[i]].printTapArmy();	// Show the player his army + tap status

			cout << " --- War Preparations ---" << endl;

			// Let the player decide which of his army cards does he want tapped
			while( getDesision(" > Do you want to tap any/more of your army members to leave them aside? (y/n)") ){
				cout << " > Which one of your army members do you want to tap?" << endl;
				unsigned int armyCard = choosefrom(player[buf[i]].ArmyCardsNo());
				player[buf[i]].TapArmyCard(armyCard);
				player[buf[i]].printTapArmy();
			}

			// Let the player decide which of his army cards does he want for attack
			player[buf[i]].printUntappedArmy();
			while( getDesision(" > Do you want to use any/more soldier to perform an attack? (y/n)") ){
				if(!player[buf[i]].hasArmy()){
					cout << " > No Army left to lead to battle. Moving on..." << endl;
					break;
				}
				cout << " > Which one of your army members do you want to tap?" << endl;
				unsigned int sol = choosefrom(player[buf[i]].ActiveArmyCardsNo());
				player[buf[i]].AddToAttackForce(sol);
				player[buf[i]].printUntappedArmy();
			}

			cout << endl << " > Army Ready! " << endl;
			cout << " <> ------ WAR ------ <> " << endl;

			// Calculate player attack

			while(1){
				if( getDesision(" > Do you want to perform an attack? (y/n)") ){
					// Print the available players to attack
					cout << " > Choose a player to attack " << endl;
					for(unsigned int j=0; j<player_amount; j++){
						if(j!=i){ // we dont print the current player
							cout << " Player " << j+1 << endl;
							player[buf[j]].print();			
						}
					}

					// let him choose his attack
					cout << " > Which one of the available players do you want to attack?" << endl;
					unsigned int target = choosefrom(player_amount-1);
					while(target==i){
						cout << " > You cant attack yourself... " << endl;
						cout << " > Which one of the available players do you want to attack?" << endl;
						target = choosefrom(player_amount-1);
					}

					// let him choose his enemy's province-target
					player[buf[target]].printProvinces();
					player[buf[target]].printArmy();
					unsigned int tmp=player[buf[target]].GetProvinceAmount();
					cout << " > Which one of the available provinces do you want to attack?" << endl;
					cout << " - Type " << tmp+1 << " to go back if you change your mind" << endl;
					unsigned int targetprov = choosefrom(tmp+1);
					if(target==tmp+1){
						cout << " Going back..." << endl;
						break;
					}
					else{
						cout << " > ATTACK " << endl;
						player[buf[i]].attack(player[buf[target]], targetprov); // remember to print the attack results
						if( checkWinningCondition(i) ){ // exit if someone wins
							cout << "    > Player " << i+1 << " WON! < " << endl;
							return; 
						}
						break;
					}
				}
				else{
					cout << " > No attack perform" << endl;
					break;
				}
			}
		}
		else{
    		cout << " > Player has no army. He is unable to battle." << endl;
    	}
    	#ifdef UI
    	cout << " > Phase ended for Player " << i+1 << " : Press Enter key to continue" << endl;
		cin.get();
		#endif
	}
}
void GameBoard::economyPhase(){
	#ifndef UI
	cout << " ================================================ " << endl;
	cout << "                   Economy Phase                  " << endl;
	cout << " ================================================ " << endl;
	#endif
	for(unsigned int i=0; i<player_amount; i++){ // !!! each player can buy only one card in this phase
		#ifdef UI
		system("clear");
		cout << " ================================================ " << endl;
		cout << "                   Economy Phase                  " << endl;
		cout << " ================================================ " << endl;
		#endif
		cout << endl << " > Player " << i+1 << "'s turn: " << endl;	
		while(1){
			// Print his army and holdings
			player[buf[i]].printArmy();
			cout << endl;
			player[buf[i]].printHoldings();
			cout << endl;
			// Then print the provinces he can choose from
			player[buf[i]].printProvinces();
			cout << endl;

			// Print player's money
			cout << " ($) Player money: " << player[buf[i]].getMoney() << endl << endl;

			unsigned int tmp=player[buf[i]].GetProvinceAmount();
			cout << " > Choose one of the available options:" << endl;
			cout << " - Province number to choose it [1, " << tmp << "]" << endl;
			cout << " - Type " << tmp+1 << " to pass this phase " << endl;
			unsigned int choice=choosefrom(tmp+1);
			if(choice!=tmp+1){
				if( player[buf[i]].getMoney() >= player[buf[i]].GetProvinceCardCost(choice) ){
					player[buf[i]].buyAndUse(choice);
					cout << " ($) Transaction succesful!" << endl;
					break;
				}
				else{
					#ifdef UI
			    	system("clear");
					#endif
					cout << " > Not enough money please try something else or pass" << endl;
				}
			}
			else{
				cout << " > Phase passed!" << endl;
				break;
			}
		}
		#ifdef UI
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
    	cout << " > Phase Ended for Player " << i+1 << " : Press Enter key to continue" << endl;
		cin.get();
		#endif
	}
}
void GameBoard::finalPhase(){
	#ifndef UI
	cout << " ================================================ " << endl;
	cout << "                    Final Phase                   " << endl;
	cout << " ================================================ " << endl;
	#endif
	for(unsigned int i=0; i<player_amount; i++){
		#ifdef UI
		system("clear");
		cout << " ================================================ " << endl;
		cout << "                    Final Phase                   " << endl;
		cout << " ================================================ " << endl;
		#endif
		cout << endl << " > Player " << i+1 << "'s turn: " << endl;
		// Discard excess hand cards
		cout << " > Discarding extra hand cards if any.." << endl;
		player[buf[i]].discardSurplusFateCards();
		cout << endl;
		player[buf[i]].printHand();
		cout << endl;
		player[buf[i]].printProvinces();
		cout << endl;
		player[buf[i]].printArmy(); // TO CHANGE ptrint attack force ?
		cout << endl;
		player[buf[i]].printHoldings();
		cout << endl;
		#ifdef UI
    	cout << " > Phase ended for Player " << i+1 << " : Press Enter key to continue" << endl;
    	cin.clear(); 
    	cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cin.get();
		#endif
	}
	#ifdef UI
	system("clear");
	#endif
	cout << " > Round ended: Printing Game Statistics..." << endl << endl;
	printGameStatistics();
	cout << "             Game statistics printed " << endl;
	cout << " ================================================ " << endl;
	cout << "                   End of Round                   " << endl;
	cout << " ================================================ " << endl;
	#ifdef UI
	cout << " > Press Enter key to start next game Round:" << endl;
	cin.get();
	#endif
}

bool GameBoard::checkWinningCondition(unsigned int i){
	if( player[buf[i]].hasProvinces()){
		bool flag=1;
		for(unsigned int j=0; j<player_amount; j++){
			if(j!=i){ // dont check the current player
				if( player[buf[j]].hasProvinces() ){
					flag=0;
					break;
				}
			}
		}

		if(flag){
			running=0;
			return 1;
		}
	}
	return 0;
}
